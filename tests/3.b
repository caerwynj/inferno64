implement Sample;

Person : adt
{
	age : int;
	name : string;
};

Sample: module
{
	init: fn();
};

init()
{
	a := 1;
	b := 3;
	c : int;
	d : Person;

	d.age = 10;
	d.name = "person name";
	c = a*b + b*b*b*b + a;
}
