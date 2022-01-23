#!/dis/sh

load std
echo starting fthclose.sh pid ${pid}

#{echo testing; sleep 1; echo exiting} | { cat - ; echo exiting the receiver }
bind '#|' /n/ff
{sleep 1; echo 10; sleep 1; echo . } | >[8]/n/ff/data1{
	cat '#p/'^${pid}^'/fd'
	# forth process startup
	<'#f/forth/new'{ n=`{read} }
	echo parent block pid ${pid}
	echo forth pid is $n
	echo 'forkenv forkfd forkns noshmem redirfds 0 8 2 ' >'#f/forth/'^$n^'/ctl'
	sleep 10

}
echo exiting fthclose.sh

