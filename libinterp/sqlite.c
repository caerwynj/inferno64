#include "lib9.h"
#include "kernel.h"
#include <isa.h>
#include "interp.h"
#include "runt.h"
#include "pool.h"
#include "raise.h"
#include "sqlitemod.h"
#include "sqlite3.h"

typedef struct XConn XConn;
typedef struct XStmt XStmt;

static Type*	TSqlite_Conn;
static Type*	TSqlite_Stmt;

static uchar Connmap[] = Sqlite_Conn_map;
static uchar Stmtmap[] = Sqlite_Stmt_map;

struct XConn
{
	Sqlite_Conn	x;
	sqlite3		*db;
};

struct XStmt
{
	Sqlite_Stmt	x;
	sqlite3_stmt	*stmt;
};

static char exBadConn[] = "bad connection";
static char exBadStmt[] = "bad statement";

void
sqlitemodinit(void)
{
	TSqlite_Conn = dtype(freeheap, sizeof(XConn), Connmap, sizeof(Connmap));
	TSqlite_Stmt = dtype(freeheap, sizeof(XStmt), Stmtmap, sizeof(Stmtmap));

	builtinmod("$Sqlite", Sqlitemodtab, Sqlitemodlen);
}

void
Sqlite_open(void *fp)
{
	F_Sqlite_open *f;
	Heap *h;
	XConn *conn;
	void *r;
	int rc;
	char *path;
	sqlite3 *db;

	f = fp;
	r = f->ret->t0;
	f->ret->t0 = H;
	destroy(r);

	path = strdup(string2c(f->file));
	//release();
	rc = sqlite3_open(path, &db);
	//acquire();
	free(path);
	if(rc != 0) {
		f->ret->t0 = H;
		f->ret->t1 = rc;
		return;
	}
	h = heap(TSqlite_Conn);
	conn = H2D(XConn*, h);
	conn->db = db;

	f->ret->t0 = (Sqlite_Conn*) conn;
	f->ret->t1 = rc;
}

void
Sqlite_close(void *fp)
{
	F_Sqlite_close *f;
	XConn *conn;
	sqlite3 *db;

	f = fp;
	conn = checktype(f->conn, TSqlite_Conn, exBadConn, 0);
	db = conn->db;
	conn->db = H;
	*f->ret = sqlite3_close_v2(db);
}

void
Sqlite_bind_big(void *fp)
{
	F_Sqlite_bind_big *f;
	XStmt *stmt;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	*f->ret = sqlite3_bind_int64(stmt->stmt, f->n, f->v);
}


void
Sqlite_bind_int(void *fp)
{
	F_Sqlite_bind_int *f;
	XStmt *stmt;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	*f->ret = sqlite3_bind_int(stmt->stmt, f->n, f->v);
}

void
Sqlite_bind_real(void *fp)
{
	F_Sqlite_bind_real *f;
	XStmt *stmt;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	*f->ret = sqlite3_bind_double(stmt->stmt, f->n, f->v);
}

void
Sqlite_bind_text(void *fp)
{
	F_Sqlite_bind_text *f;
	XStmt *stmt;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	*f->ret = sqlite3_bind_text(stmt->stmt, f->n, string2c(f->v), -1, NULL);
}

void
Sqlite_column_big(void *fp)
{
	F_Sqlite_column_big *f;
	XStmt *stmt;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	*f->ret = sqlite3_column_int64(stmt->stmt, f->col);
}

void
Sqlite_column_int(void *fp)
{
	F_Sqlite_column_int *f;
	XStmt *stmt;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	*f->ret = sqlite3_column_int(stmt->stmt, f->col);
}

void
Sqlite_column_real(void *fp)
{
	F_Sqlite_column_real *f;
	XStmt *stmt;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	*f->ret = sqlite3_column_double(stmt->stmt, f->col);
}

void
Sqlite_column_text(void *fp)
{
	F_Sqlite_column_text *f;
	XStmt *stmt;
	char *text;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	text = sqlite3_column_text(stmt->stmt, f->col);
	*f->ret = c2string(text, strlen(text));
}

void
Sqlite_column_blob(void *fp)
{
	F_Sqlite_column_blob *f;
	XStmt *stmt;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	*f->ret = sqlite3_column_blob(stmt->stmt, f->col);
	// TODO; copy to Array
}

void
Sqlite_column_bytes(void *fp)
{
	F_Sqlite_column_bytes *f;
	XStmt *stmt;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	*f->ret = sqlite3_column_bytes(stmt->stmt, f->col);
}

void
Sqlite_finalize(void *fp)
{
	F_Sqlite_finalize *f;
	XStmt *stmt;
	sqlite3_stmt *st;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	st = stmt->stmt;
	stmt->stmt = H;
	*f->ret = sqlite3_finalize(st);
}

void
Sqlite_step(void *fp)
{
	F_Sqlite_step *f;
	XStmt *stmt;
	int rc;

	f = fp;
	stmt = checktype(f->stmt, TSqlite_Stmt, exBadStmt, 0);
	//release();
	rc = sqlite3_step(stmt->stmt);
	//acquire();
	*f->ret = rc;
}

void
Sqlite_prepare(void *fp)
{
	F_Sqlite_prepare *f;
	Heap *h;
	void *r;
	XStmt *stmt;
	XConn *conn;
	int rc;
	char *sql;
	sqlite3_stmt *sql3stmt;

	f = fp;
	r = f->ret->t0;
	f->ret->t0 = H;
	destroy(r);

	conn = checktype(f->db, TSqlite_Conn, exBadConn, 0);
	sql = strdup(string2c(f->sql));

	//release();
	rc = sqlite3_prepare_v2(conn->db, sql, -1, &sql3stmt, NULL);
	//acquire();
	free(sql);
	if(rc != 0) {
		f->ret->t0 = H;
		f->ret->t1 = rc;
		return;
	}
	h = heap(TSqlite_Stmt);
	stmt = H2D(XStmt*, h);
	stmt->stmt = sql3stmt;

	f->ret->t0 = (Sqlite_Stmt*) stmt;
	f->ret->t1 = rc;
}

