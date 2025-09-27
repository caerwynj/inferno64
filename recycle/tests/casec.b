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
	a : string = "Jane";

	case a {
	"jane" or "JANE" => sys->print("is jane or JANE\n");
	"Jane" => sys->print("is Jane\n");
	* => sys->print("is default\n");
	}
}
