implement Emuinit;
include "sys.m";
	sys: Sys;
include "draw.m";
include "sh.m";
include "arg.m";
	arg: Arg;

Emuinit: module
{
	init: fn();
};

init()
{
	sys = load Sys Sys->PATH;
	unquoted("emu -v");
}

unquoted(s: string): list of string
{
	args: list of string;
	word: string;
	inquote := 0;
	sys->print("unquoted %s\n", s);
	for(j := len s; j > 0;){
		c := s[j-1];
		if(c == ' ' || c == '\t' || c == '\n'){
			j--;
			continue;
		}
		for(i := j-1; i >= 0 && ((c = s[i]) != ' ' && c != '\t' && c != '\n' || inquote); i--){	# collect word
			if(c == '\''){
				word = s[i+1:j] + word;
				j = i;
				if(!inquote || i == 0 || s[i-1] != '\'')
					inquote = !inquote;
				else
					i--;
			}
		}
		args = (s[i+1:j]+word) :: args;
		word = nil;
		j = i;
	}
	# if quotes were unbalanced, balance them and try again.
	if(inquote)
		return unquoted(s + "'");
	sys->print("before exiting\n");
	sys->print("unquoted ending args %s\n", s);
	return args;
}
