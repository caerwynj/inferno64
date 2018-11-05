#!/dis/sh -n
load std

for d in /opt/*/dis/* /opt/*/*/dis/* {
	or {ftest -d $d} {raise continue}
	n := `{basename $d}
	and {~ $n lib} {raise continue}
	and {~ $n cmd} {n=''}
	bind -b $d /dis/$n
}
