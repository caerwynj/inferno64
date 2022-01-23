#include <u.h>
#include <libc.h>
#include <libsec.h>

/*
	ori disk throughput script
17:54 < ori> single proc random reads with the test program => 130 megs/sec
17:54 < h9ro> ah, that wasn't clear
17:54 < ori> gefs => 50 megs/sec
17:54 < h9ro> ok, then you're right of course :)
17:55 < ori> no, gefs doesn't do parallel reads, but it clearly does something dumb.
17:55 < h9ro> if your random offsets are ok and same blocksize...
17:55 < ori> oh. that's actually a good thing to check.
17:55 < ori> I should make sure that the offsets ARE aligned.
17:55 < ori> pretty sure they are.
17:55 < ori> but it'd be dumb if I'm wrong.
17:55 < h9ro> try some really big alignments
17:55 < h9ro> just in case
17:55 < h9ro> you never know how dumb the SSD is!!!
17:56 < h9ro> maybe make a test to find the internal ssd blocksizes
17:56 < ori> yeah, but the test program is doing the same alignments I *think* I'm doing in gefs.
17:56 < h9ro> and the ssd might have implemented readahead
17:56 < ori> no worries. I'll figure it out.

20:10 < ori> when you have multiple procs
20:11 < ori> eg, for gefs testing one of the tests I use is '{for(i in *){cat $i&}} | tput'

 */
enum {
        KiB = 1024,
        MiB = 1024*KiB,
        GiB = 1024*MiB,
};

int     nproc   = 1;
int     iosize  = 8*1024;
char    *order  = "seq";
vlong   fsize   = 0;

int     fd;
char    *buf;
vlong   nbytes  = 0;
long    (*iofn)(int, void*, long, vlong);

void
usage(void)
{
        fprint(2, "usage: %s [-p procs] [-s iosize] [-o order] path\n", argv0);
        exits("usage");
}

void
inc64(vlong *v, vlong dv)
{
        vlong ov, nv;

        while(1){
                ov = *v;
                nv = ov + dv;
                extern int cas64(u64int*, u64int, u64int);
                if(cas64((u64int*)v, ov, nv))
                        break;
        }
}

vlong
seq(vlong off)
{
        return off + iosize;
}

vlong
skip(vlong off)
{
        return off + 2*iosize;
}

vlong
randoff(vlong off)
{
        return (fastrand()<<32)|fastrand();
}

void
io(vlong (*next)(vlong))
{
        vlong off = 0;

        while(1){
                pwrite(fd, buf, iosize, off);
                inc64(&nbytes, iosize);
                off = next(off);
                if(off > fsize + iosize)
                        off -= fsize;
                off -= off % iosize;
        }
}

void
showstats(void)
{
        double speed;
        int sec;

        sec = 0;
        while(1){
                sleep(1000);
                sec++;
                speed = (double)nbytes/(double)sec;
                print("%lld/%d\n", nbytes, sec);
                if(speed > GiB)
                        print("%f GiB/s\n", speed/GiB);
                else if(speed > MiB)
                        print("%f MiB/s\n", speed/MiB);
                else if(speed > KiB)
                        print("%f KiB/s\n", speed/KiB);
        }
}

void
main(int argc, char **argv)
{
        Dir *d;
        int i, pid;

        iofn = pwrite;
        ARGBEGIN{
        case 'p':
                nproc = atoi(EARGF(usage()));
                break;
        case 's':
                iosize = atoi(EARGF(usage()));
                break;
        case 'o':
                order = EARGF(usage());
                break;
        case 'r':
                iofn = pread;
                break;
        default:
                usage();
                break;
        }ARGEND;

        if(argc != 1)
                usage();
        if((fd = open(argv[0], OWRITE)) == -1)
                sysfatal("open %s: %r", argv[0]);
        if((d = dirfstat(fd)) == nil)
                sysfatal("stat %s: %r", argv[0]);
        if((buf = malloc(iosize)) == nil)
                sysfatal("alloc buf: %r");
        fsize = d->length;

        for(i = 0; i < nproc; i++){
                if((pid = rfork(RFPROC|RFMEM)) == -1)
                        sysfatal("rfork: %r");
                if(pid == 0){
                        if(strcmp(order, "seq") == 0)
                                io(seq);
                        else if(strcmp(order, "skip") == 0)
                                io(skip);
                        else if(strcmp(order, "rand") == 0)
                                io(randoff);
                        else
                                sysfatal("unknown order %s\n", order);
                        exits(nil);
                }
        }
        showstats();
        exits(nil);
}

