implement Sample;
include "sys.m";
	sys: Sys;

Sample: module
{
	init: fn();
};

init()
{
	sys = load Sys Sys->PATH;
	sys->print("init 1\n");
#	sys->bind("#e", "/env", sys->MREPL|sys->MCREATE);	# if #e not configured, that's fine
#	fd := sys->open("#e/", Sys->OREAD);
#	if(fd != nil)
#		sys->print("init 2 %q\n", sys->fd2path(fd));
	i : int = 4;
	i = i+100;
	i = i-101;
	case i {
	0 => sys->print("begins with a vowel\n");
	1 => sys->print("begins with a consonant\n");
	2 => sys->print("begins with a consonant\n");
	3 => sys->print("begins with a consonant\n");
	4 => sys->print("begins with a consonant\n");
	* => sys->print("sorry don't understand\n");
	}
	sys->print("ending the program\n");
}
