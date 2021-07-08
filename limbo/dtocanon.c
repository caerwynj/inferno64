#include "limbo.h"

void
dtocanon(double f, u32 v[])
{
	union { double d; u32 ul[2]; } a;

	a.d = 1.;
	if(a.ul[0]){
		a.d = f;
		v[0] = a.ul[0];
		v[1] = a.ul[1];
	}else{
		a.d = f;
		v[0] = a.ul[1];
		v[1] = a.ul[0];
	}
}

double
canontod(u32 v[2])
{
	union { double d; u32 ul[2]; } a;

	a.d = 1.;
	if(a.ul[0]) {
		a.ul[0] = v[0];
		a.ul[1] = v[1];
	}
	else {
		a.ul[1] = v[0];
		a.ul[0] = v[1];
	}
	return a.d;
}
