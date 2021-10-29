#!/bin/awk -f

# rc script to build amd64 9front forth words from words-nasm.s
#	./words words-nassm.s
# watch -e 'words.awk' 'head words-nasm.s | ./words.awk'

BEGIN{
	FS=",[ \t]*|[ \t]+"
	last=""
	nlines=0
	addr=""
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
$2 == "MENTRY" {
	if(label != ""){
		lines[++nlines]=sprintf("GLOBL	%s, $%d\n", last, tot);
	}
	gsub(/"/,"", $3)
	name = $3
	label = $4
	tot = 0
	writelast("mentry", label, last)
	last=sprintf("mentry_%s(SB)", label);
	lines[++nlines]=sprintf("DATA	mentry_%s+8(SB)/1, $%d\n", label, length(name));
	for(i=1; i<=length(name); i++){
		lines[++nlines]=sprintf("DATA	mentry_%s+%d(SB)/1, $'%c'\n", label, 8+i, substr(name,i,1));
	}
	tot = 8+i;
	# for alignment
	if(tot%8 > 0)
		tot += 8-(tot%8);
	lines[++nlines]=sprintf("DATA	mentry_%s+%d(SB)/8, $%s(SB)\n", label, tot, label);
	lines[++nlines]=sprintf("#define	m_%s(SB) mentry_%s+%d(SB)\n", label, label, tot);
	tot += 8
	addrlabel = sprintf("mentry_%s", label)
}
$2 == "MVENTRY" {
	if(label != ""){
		lines[++nlines]=sprintf("GLOBL	%s, $%d\n", last, tot);
	}
	gsub(/"/,"", $3)
	name = $3
	label = $4
	tot = 0
	writelast("mventry", label, last)
	last=sprintf("mventry_%s(SB)", label);
	lines[++nlines]=sprintf("DATA	mventry_%s+8(SB)/1, $%d\n", label, length(name));
	for(i=1; i<=length(name); i++){
		lines[++nlines]=sprintf("DATA	mventry_%s+%d(SB)/1, $'%c'\n", label, 8+i, substr(name,i,1));
	}
	tot = 8+i;
	# for alignment
	if(tot%8 > 0)
		tot += 8-(tot%8);
	lines[++nlines]=sprintf("DATA	mventry_%s+%d(SB)/8, $constant(SB)\n", label, tot);
	lines[++nlines]=sprintf("#define	mc_%s(SB) mventry_%s+%d(SB)\n", label, label, tot);
	tot += 8;
	lines[++nlines]=sprintf("DATA	mventry_%s+%d(SB)/8, $%s(SB)\n", label, tot, $5);
	tot += 8;
	addrlabel = sprintf("mventry_%s", label)
}
$1 ~ /:$/ && $1 !~ /^dict:$/ {
	l=$1
	gsub(/:$/,"",l)
	# for not printing out the labels while still developing the program
	#	to only print the unprocessed lines
	#lines[++nlines] = ""
	printf("#define	%s(SB) %s+%d(SB)\n", l, addrlabel, tot);
}
{
	#if(done == nlines){
	#	print $0
	#}
	#for(i = done+1; i <= nlines; i++){
	#	printf("%s", lines[i])
	#}
	done=nlines	
}
END{
	if(label != ""){
		lines[++nlines]=sprintf("GLOBL	%s(SB), $%d\n", addrlabel, tot);
		lines[++nlines]=sprintf("#undef	LAST\n");
		lines[++nlines]=sprintf("#define	LAST $%s\n", last);
	}
	for(i = 1; i <= nlines; i++){
		printf("%s", lines[i])
	}	
}
