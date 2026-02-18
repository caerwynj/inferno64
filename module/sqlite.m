Sqlite: module {
	PATH: con "$Sqlite";

	Conn: adt {
		x: int;  # dummy. State is hidden
	};
	Stmt: adt {
		x: int;  # dummy
	};

	OK, ERROR, INTERNAL, PERM, ABORT, BUSY, LOCKED,
	NOMEM, READONLY, INTERRUPT, IOERR, CORRUPT, NOTFOUND,
	FULL, CANTOPEN, PROTOCOL, EMPTY, SCHEMA, TOOBIG,
	CONSTRAINT, MISMATCH, MISUSE, NOLFS, AUTH, FORMAT, RANGE,
	NOTADB, NOTICE, WARNING: con iota;
	ROW: con 100;
	DONE: con 101;

	open:fn(file: string): (ref Conn, int);
	prepare:fn(db: ref Conn, sql: string): (ref Stmt, int);
	bind_int:fn(stmt: ref Stmt, n: int, v: int): int;
	bind_text:fn(stmt: ref Stmt, n: int, v: string): int;
	bind_big:fn(stmt: ref Stmt, n:int, v: big): int;
	bind_real:fn(stmt: ref Stmt, n:int, v: real): int;
	step:fn(stmt: ref Stmt): int;
	column_int:fn(stmt: ref Stmt, col: int): int;
	column_bytes:fn(stmt: ref Stmt, col: int): int;
	column_real:fn(stmt: ref Stmt, col: int): real;
	column_big:fn(stmt: ref Stmt, col: int): big;
	column_text:fn(stmt: ref Stmt, col: int): string;
	column_blob:fn(stmt: ref Stmt, col: int): array of byte;
	finalize:fn(stmt: ref Stmt): int;
	close:fn(conn: ref Conn): int;
};
