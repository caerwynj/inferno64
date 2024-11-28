#!/bin/awk -f

# rc script to build amd64 9front forth words from words-nasm.s
#	./words words-nassm.s
# watch -e 'words.awk' 'head words-nasm.s | ./words.awk'

BEGIN{
	FS=", [ \t]*|[ \t]+"
	last=""
	nlines=0
	addr=""
	strlabel["L137:"] = 1
	strlabel["L170:"] = 1
	strlabel["L173:"] = 1
	strlabel["L180:"] = 1
	strlabel["L193:"] = 1
	strlabel["L247:"] = 1
	strlabel["L251:"] = 1
	strlabel["L255:"] = 1
}
{
	lines[++nlines]=sprintf("/* %s */\n", $0);
}
function writelast(typ, label, last){
	if(last == "")
		lines[++nlines]=sprintf("DATA	%s_%s(SB)/8, LAST\n", typ, label);
	else
		lines[++nlines]=sprintf("DATA	%s_%s(SB)/8, $%s\n", typ, label, last);
}
$2 == "CENTRY" {
	if(label != ""){
		lines[++nlines]=sprintf("GLOBL	%s, $%d\n", last, tot);
	}
	gsub(/`/,"", $3)
	name = $3
	label = $4
	tot = 0
	writelast("centry", label, last)
	last=sprintf("centry_%s(SB)", label);
	lines[++nlines]=sprintf("DATA	centry_%s+8(SB)/1, $%d\n", label, length(name));
	for(i=1; i<=length(name); i++){
		lines[++nlines]=sprintf("DATA	centry_%s+%d(SB)/1, $'%c'\n", label, 8+i, substr(name,i,1));
	}
	tot = 8+i;
	# for alignment
	if(tot%8 > 0)
		tot += 8-(tot%8);
	lines[++nlines]=sprintf("DATA	centry_%s+%d(SB)/8, $colon(SB)\n", label, tot);
	lines[++nlines]=sprintf("#define	%s(SB) centry_%s+%d(SB)\n", label, label, tot);
	tot += 8
	addrlabel = sprintf("centry_%s", label)
}
$2 == "CIENTRY" {
	if(label != ""){
		lines[++nlines]=sprintf("GLOBL	%s, $%d\n", last, tot);
	}
	gsub(/`/,"", $3)
	name = $3
	label = $4
	tot = 0
	writelast("cientry", label, last)
	last=sprintf("cientry_%s(SB)", label);
	lines[++nlines]=sprintf("DATA	cientry_%s+8(SB)/1, $%d\n", label, length(name)+128);
	if(name == "\\"){
		lines[++nlines]=sprintf("DATA	cientry_%s+%d(SB)/1, $92\n", label, 8+1);
	} else
		for(i=1; i<=length(name); i++){
			lines[++nlines]=sprintf("DATA	cientry_%s+%d(SB)/1, $'%c'\n", label, 8+i, substr(name,i,1));
		}
	tot = 8+i;
	# for alignment
	if(tot%8 > 0)
		tot += 8-(tot%8);
	lines[++nlines]=sprintf("DATA	cientry_%s+%d(SB)/8, $colon(SB)\n", label, tot);
	lines[++nlines]=sprintf("#define	%s(SB) cientry_%s+%d(SB)\n", label, label, tot);
	tot += 8
	addrlabel = sprintf("cientry_%s", label)
}
$2 == "VENTRY" {
	if(label != ""){
		lines[++nlines]=sprintf("GLOBL	%s, $%d\n", last, tot);
	}
	gsub(/`/,"", $3)
	name = $3
	label = $4
	tot = 0
	writelast("ventry", label, last)
	last=sprintf("ventry_%s(SB)", label);
	lines[++nlines]=sprintf("DATA	ventry_%s+8(SB)/1, $%d\n", label, length(name));
	for(i=1; i<=length(name); i++){
		lines[++nlines]=sprintf("DATA	ventry_%s+%d(SB)/1, $'%c'\n", label, 8+i, substr(name,i,1));
	}
	tot = 8+i;
	# for alignment
	if(tot%8 > 0)
		tot += 8-(tot%8);
	lines[++nlines]=sprintf("DATA	ventry_%s+%d(SB)/8, $variable(SB)\n", label, tot);
	lines[++nlines]=sprintf("#define	%s(SB) ventry_%s+%d(SB)\n", label, label, tot);
	tot += 8;
	lines[++nlines]=sprintf("DATA	ventry_%s+%d(SB)/8, $0\n", label, tot);
	tot += 8;
	addrlabel = sprintf("ventry_%s", label)
}
$1 ~ /:$/ && $1 in strlabel {
	if(label != ""){
		if(last != ""){
			lines[++nlines]=sprintf("GLOBL	%s, $%d\n", last, tot);
			lines[++nlines]=sprintf("#undef	LAST\n");
			lines[++nlines]=sprintf("#define	LAST $%s\n", last);
		}
		else
			lines[++nlines]=sprintf("GLOBL	%s(SB), $%d\n", addrlabel, tot);

	}
	gsub(/:/,"", $1)
	name = $3
	label = $1
	tot = 0
	last="" #sprintf("$%s(SB)", label);
	addrlabel = sprintf("%s", label)
}
$2 == "db" {
	start = index($0,"'")+1
	str = substr($0,start,length($0)-start)
	#printf("str length %d %d: %s\n", length(str), index($0,"'"), str);
	for(i=1; i<=length(str); i++){
		lines[++nlines]=sprintf("DATA	%s+%d(SB)/1, $'%c'\n", addrlabel, i-1, substr(str,i,1));
	}
	tot = i-1
}
$2 == "dd" {
	if($3 ~ /^[-0-9]+$/)
		lines[++nlines]=sprintf("DATA	%s+%d(SB)/8, $%s\n", addrlabel, tot, $3);
	else if($3 ~ /^L[0-9]+$/)
		lines[++nlines]=sprintf("DATA	%s+%d(SB)/8, $%s(SB)\n", addrlabel, tot, $3);
	else
		lines[++nlines]=sprintf("DATA	%s+%d(SB)/8, $%s(SB)\n", addrlabel, tot, $3);
	tot += 8
	#addr = sprintf("$centry_%s+%d(SB)", label, tot)
}
$1 ~ /:$/ && !($1 in strlabel) {
	l=$1
	gsub(/:$/,"",l)
	# for not printing out the labels while still developing the program
	#	to only print the unprocessed lines
	#lines[++nlines] = ""
	printf("#define	%s(SB) %s+%d(SB)\n", l, addrlabel, tot);
}
{
#	if(done == nlines){
#		print $0
#	}
#	for(i = done+1; i <= nlines; i++){
#		printf("%s", lines[i])
#	}
#	done=nlines	
}
END{
	if(label != ""){
		lines[++nlines]=sprintf("GLOBL	%s(SB), $%d\n", addrlabel, tot);
	}
	for(i = 1; i <= nlines; i++){
		printf("%s", lines[i])
	}	
}
