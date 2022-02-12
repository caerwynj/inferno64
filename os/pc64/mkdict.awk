#!/bin/awk -f

# rc script to build amd64 9front forth words from words-nasm.s
#	./mkdict.awk primitives-nasm.s words-nassm.s
# watch -e 'mkdict.awk' 'cat primitives-nasm.s words-nasm.s | ./mkdict.awk'

BEGIN{
	last=""
	nlines=0
	addr=""
	h=0 # here = dictionary pointer
	vh=0 # there = variable space pointer
	nlabels=0
	literal = "^[+-]?[0-9]+$"
	branchlabel = "^L[0-9a-zA-Z_]+:$"
	fentries = "Fentry fentries[] = {\n";
}

function align(here){
	if((here%8) == 0)
		return here
	here += 8- (here%8)
	return here
}
function header(len, name, prefix, label, cfa, immediate){
	h = align(h);	# to align here if the string or byte un-aligned it
	h+=8; # for link
	h+=len+1;
	h = align(h);
	labels[nlabels++] = prefix label " = "  h;
	h+=8; # for cfa
	cfas[cfa] = 1
	if(immediate == 1)
		type = "IHeader"
	else
		type = "Header"
	fentries = fentries "	{.type " type ", {.hdr { " len ", " name ", /* " labels[nlabels-1] " */ " cfa " }}}, /* " $0 " h " h " */\n";
	# print(prefix label " @ " labels[nlabels-1]);
	fentries = fentries "	{.type Here, {.p " h " }},	/* " h " " vh " */\n"
	fentries = fentries "	{.type There, {.p " vh " }},	/* " h " " vh " */\n"
}
$1 == "MENTRY" {
	name = $2
	header($4, name, "M_", $3, $3);
}
$1 == "MCENTRY" {
	name = $2
	header($4, name, "MC_", $3, "constant")
	h+=8;
	fentries = fentries "	{.type Absolute, {.p " $5"}},		/* " h " */\n"
}
$1 == "MVDENTRY" {
	name = $2
	header($4, name, "MV_", $3, "variable")
	h+=8; # for pfa
	fentries = fentries "	{.type FromH0, {.p " $5 " }},	/* " h " " vh " */\n"
}
$1 == "MVENTRY" {
	name = $2
	header($4, name, "MV_", $3, "variable")
	h+=8; # for pfa
	fentries = fentries "	{.type FromV0, {.p " vh " }},	/* " h " " vh " */\n"
	if(NF >= 5 && $5 != ";")
		vh+=$5*8;
	else
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
	h = align(h);	# to align here if the string or byte un-aligned it
	h+=8
	fentries = fentries "	{.type Absolute, {.p " $2 "}},		/* " $0 " " h " */\n"
}
$1 == "dd" && $2 ~ "^[M_|C_|CI_|(MC_)|(MV_)|L]" {
	h = align(h);	# to align here if the string or byte un-aligned it
	h+=8
	fentries = fentries "	{.type FromDictionary, {.p " $2 "}, .src = \"" $0 "\"},		/* " $0 " " h " */\n"
}
$1 ~ branchlabel {
	h = align(h);	# to align here if the string or byte un-aligned it
	gsub(/:/,"", $1)
	labels[nlabels++] = $1 " = "  h;
}
$1 == "db" {	# will leave h unaligned.
	if($2 ~ literal) { # obsolete, now all are counted strings
		h += 1;
		fentries = fentries "	{.type Byte, {.b " $2 "}},	/* " $0 " " h " */\n"
	}else{
		gsub(/^db /,"", $0)
		gsub(/[ 	]*;.*/,"", $0)
		h += length($0)-2+1; # -2 for the quotes, +1 for the count that will be added by devforth
		fentries = fentries "	{.type Chars, {.str " $0 "}},	/* " $0 " " h " */\n"
	}
}
$0 ~ /^;/ || $1 == ";" {
	fentries = fentries "/* " $0 " */"
}
$0 ~ /^$/ {
	fentries = fentries $0
}
{
	fentries = fentries "	{.type Here, {.p " h " }},	/* " h " " vh " */\n"
	fentries = fentries "	{.type There, {.p " vh " }},	/* " h " " vh " */\n"
}
END{
	h = align(h);	# to align here if the string or byte un-aligned it
	vh = align(vh);	# does not need to be aligned as we are not assigning variable bytes
	fentries = fentries "	{.type Here, {.p " h " }},	/* " h " " vh " */\n"
	fentries = fentries "	{.type There, {.p " vh " }},	/* " h " " vh " */\n"
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
