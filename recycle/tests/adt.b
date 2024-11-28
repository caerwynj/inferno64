implement Sample;
include "sys.m";
	sys: Sys;

Person: adt
{
	name: string;
	age: int;
};

Sample: module
{
	init: fn();
};

init()
{
	sys = load Sys Sys->PATH;
	d : Person;

	d.name = "Jane";
	d.age = 20;
	sys->print("should print Jane result %s\n", d.name);
	sys->print("should print 20 result %d\n", d.age);

	a := ("Doe", 21);
	a = d;
	sys->print("should print Jane result %s\n", d.name);

	p, np : ref Person;
	p = np = ref Person("Jane", 20);
	d.name = "Doe";
	sys->print("should print Jane result %s\n", p.name);
}
