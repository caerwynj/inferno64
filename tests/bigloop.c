#include <u.h>
#include <libc.h>

void
main(int, void**)
{
	uvlong n, t, s;

	s = nsec();
	print("start nanoseconds %zd\n", s);
	for(n = 0; n<1000*1000*1000; n++){
		;
	}
	print("n %zd\n", n);
	t = nsec();
	print("end   nanoseconds %zd taken %zd\n", t, t -s);
	exits(0);
}
