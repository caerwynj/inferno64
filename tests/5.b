implement Sample;

Person : adt
{
	age : int;
	next : cyclic ref Person;
	age1 : int;
	age2 : int;
};

Sample: module
{
	init: fn();
	fn1: fn();
	fn2: fn();
	fn3: fn();
};

init()
{
	a := 1;
	b := 3;
	c : int;
	d : Person;

	d.age = 10;
	d.next = nil;
	d.age1 = 20;
	d.age2 = 30;
	c = a*b + b*b*b*b + a;
	fn3();
	fn1();
	fn2();
}

fn1()
{
	d: Person;

	d.age=40;
	d.next = nil;
	d.age1 = 50;
	d.age2 = 60;
}

fn2()
{
	s: string;

	s = "testing the string";
}

fn3()
{
	s: string;
	s1: string;

	s = "testing the string";
	s1 = "testing again";
}
