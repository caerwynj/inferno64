#!/bin/awk -f

# rc script to build amd64 9front forth words from words-nasm.s
#	./mkdict.awk primitives-nasm.s words-nassm.s
# watch -e 'mkdict.awk' 'cat primitives-nasm.s words-nasm.s | ./mkdict.awk'
# watch -e 'mkdict.awk' 'echo start `{date}; ./mkdict.awk primitives-nasm.s words-nasm.s > forth.h && bell ; echo end `{date} '

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
	dtop = -1
	t = "	"	# tab
	t2 = t t	# 2 tabs
	nl = ",\n"
}

function align(here){
	if((here%8) == 0)
		return here
	here += 8- (here%8)
	return here
}
function sourceline(){
	gsub(/\\/,"backslash");
	gsub(/\"/,"\\\"");
	gsub(/\\\\\"/,"\\\"");
	fentries = fentries t "{.what Sourceline, .desc \"" $0 "\"}" nl;
}
function header(len, name, prefix, label, cfa, immediate){
	h = align(h);	# to align here if the string or byte un-aligned it

	sourceline()
	if(dtop == -1)
		fentries = fentries t2 "{.what Here, .desc \"link\",.here " h ", .there " vh ",.type Absolute, .p 0 }" nl;
	else
		fentries = fentries t2 "{.what Here, .desc \"link\",.here " h ", .there " vh ",.type Relativedictionary, .p " dtop " }" nl;
	dtop = h
	h+=8; # for link

	fentries = fentries t2 "{.what Here, .desc \"len\", .here " h ", .there " vh ",.type Byte, .b " (immediate*128) " + " len " }" nl;
	h+=1;
	fentries = fentries t2 "{.what Here, .desc \"name\",.here " h ", .there " vh ",.type Chars, .str " name " }" nl;
	h = align(h+len);
	fentries = fentries t2 "{.what Here, .desc \"cfa\", .here " h ", .there " vh ",.type Absoluteptr, .ptr " cfa " }" nl;
	labels[nlabels++] = prefix label " = "  h;
	h+=8; # for cfa
	cfas[cfa] = 1
}
$1 == "MENTRY" {
	name = $2
	header($4, name, "M_", $3, $3);
}
$1 == "MCENTRY" {
	name = $2
	header($4, name, "MC_", $3, "constant")
	fentries = fentries t2 "{.what Here, .desc \"constant\", .here " h ", .there " vh ",.type Absolute, .p " $5 " }" nl;
	h+=8;
}
$1 == "MVDENTRY" { # defined memory locations in user memory
	name = $2
	header($4, name, "MV_", $3, "variable")
	fentries = fentries t2 "{.what Here, .desc \"pfa\", .here " h ", .there " vh ",.type Relative, .p " $5 " }" nl;
	h+=8; # for pfa
}
$1 == "MVENTRY" {
	name = $2
	header($4, name, "MV_", $3, "variable")
	fentries = fentries t2 "{.what Here, .desc \"pfa\", .here " h ", .there " vh ",.type Relativevar, .p FORTHVARS + " vh " }" nl;
	h+=8; # for pfa
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
	sourceline()
	h = align(h);	# to align here if the string or byte un-aligned it
	fentries = fentries t2 "{.what Here, .desc \"value\", .here " h ", .there " vh ",.type Absolute, .p " $2 " }" nl;
	h+=8
}
$1 == "dd" && $2 ~ "^[M_|C_|CI_|(MC_)|(MV_)|L]" {
	sourceline()
	h = align(h);	# to align here if the string or byte un-aligned it
	fentries = fentries t2 "{.what Here, .desc \"address\", .here " h ", .there " vh ",.type Relativedictionary, .p " $2 " }" nl;
	h+=8
}
$1 ~ branchlabel {
	sourceline()
	gsub(/:/,"", $1)
	labels[nlabels++] = $1 " = "  h;
}
$1 == "db" {	# will leave h unaligned.
	sourceline()
	if($2 ~ literal) { # obsolete, now all are counted strings
		fentries = fentries t2 "{.what Here, .desc \"byte\", .here " h ", .there " vh ",.type Byte, .b " $2 " }" nl;
		h+=1;
	}else{
		gsub(/^db /,"", $0)
		gsub(/[ 	]*;.*/,"", $0)
		gsub(/\\\"/,"\"");
		fentries = fentries t2 "{.what Here, .desc \"len\", .here " h ", .there " vh ",.type Byte, .b " length($0)-2 " }" nl;
		h+=1;
		fentries = fentries t2 "{.what Here, .desc \"name\",.here " h ", .there " vh ",.type Chars, .str " $0 " }" nl;
		h += length($0)-2; # -2 for the quotes
	}
}
$0 ~ /^;/ || $1 == ";" {
#	sourceline()
}
$0 ~ /^$/ {
}
END{
	h = align(h);	# to align here if the string or byte un-aligned it
	vh = align(vh);	# does not need to be aligned as we are not assigning variable bytes
	fentries = fentries t "{.what Here,  .desc \"end here\", .here " h ", .there " vh ",.type End }" nl;
	fentries = fentries t "{.what There, .desc \"end there\", .here " h ", .there " vh ",.type End }" nl;
	fentries = fentries t "{.what Dtop, .desc \"end dtop\", .p " dtop " }" nl;
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
