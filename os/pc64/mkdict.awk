#!/bin/awk -f

# rc script to build amd64 9front forth words from words-nasm.s
#	./mkdict.awk primitives-nasm.s words-nassm.s
# watch -e 'mkdict.awk' 'cat primitives-nasm.s words-nasm.s | ./mkdict.awk'

BEGIN{
	last=""
	nlines=0
	addr=""
	h=0 # here = dictionary pointer
	vh=0 # vhere = variable space pointer
	nlabels=0
	literal = "^[+-]?[0-9]+$"
	branchlabel = "^L[0-9]+:$"
	fentries = "Fentry fentries[] = {\n";
}

function header(len, name, prefix, label, cfa, immediate){
	h+=8; # for link
	h+=len+1;
	if((len+1)%8 > 0)
		h += 8-((len+1)%8);
	labels[nlabels++] = prefix label " = "  h;
	h+=8; # for cfa
	cfas[cfa] = 1
	if(immediate == 1)
		type = "IHeader"
	else
		type = "Header"
	fentries = fentries "	{.type " type ", {.hdr { " len ", " name ", /* " labels[nlabels-1] " */ " cfa " }}}, /* " $0 " h " h " */\n";
	# print(prefix label " @ " labels[nlabels-1]);
}
$1 == "MENTRY" {
	name = $2
	header($4, name, "M_", $3, $3);
}
$1 == "MCENTRY" {
	name = $2
	header($5, name, "MC_", $3, "constant")
	h+=8;
	fentries = fentries "	{.type Absolute, {.p " $4"}},		/* " h " */\n"
}
$1 == "MVENTRY" {
	name = $2
	header($5, name, "MV_", $3, "variable")
	h+=8; # for pfa
	fentries = fentries "	{.type FromV0, {.p " vh " }},	/* " h " " vh " */\n"
	vh+=8;
}
$1 == "CENTRY" {
	name = $2
	gsub(/^C_/,"", $3)
	header($4, name, "C_", $3, "colon")
}
$1 == "CIENTRY" {
	name = $2
	gsub(/^CI_/,"", $3)
	header($4, name, "CI_", $3, "colon", 1)
}
$1 == "dd" && $2 ~ literal {
	h+=8
	fentries = fentries "	{.type Absolute, {.p " $2 "}},		/* " $0 " " h " */\n"
}
$1 == "dd" && $2 ~ "^[M_|C_|CI_|(MC_)|(MV_)|L]" {
	h+=8
	fentries = fentries "	{.type FromH0, {.p " $2 "}, .src = \"" $0 "\"},		/* " $0 " " h " */\n"
}
$1 ~ branchlabel {
	gsub(/:/,"", $1)
	labels[nlabels++] = $1 " = "  h;
}
$1 == "db" {
	gsub(/^db /,"", $0)
	h += length($0)-2+1; # -2 for the quotes, +1 for the null character
	fentries = fentries "	{.type Chars, {.str " $0 "}},		/* " h " */\n"
}
$0 ~ /^;/ || $1 == ";" {
	fentries = fentries "/* " $0 " */"
}
$0 ~ /^$/ {
	fentries = fentries $0
}
END{
	fentries= fentries "};\n"
	# print("here " h);
	print("enum {");
	for(i = 0; i < nlabels; i++)
		print "	" labels[i] ","
	print("};");
	for(c in cfas)
		print "extern void *" c "(void);"
	print(fentries);
}
