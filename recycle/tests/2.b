implement Sample;

Sample: module
{
	init: fn();
};

init()
{
	a := 1;
	b := 3;
	c : int;

	c = a*b + b*b*b*b + a;
}
