#!/dis/sh

load std
echo my pid is ${pid}

bind '#|' /n/ffshm
bind '#|' /n/ffshm1
<[7]/n/ffshm/data >[8]/n/ffshm/data1 >[9]/n/ffshm/data <[10]/n/ffshm/data1 <[17]/n/ffshm1/data >[18]/n/ffshm1/data1 >[19]/n/ffshm1/data <[20]/n/ffshm1/data1 {

	# data1 -> data, write to 8, read on 7
	# data -> data1, write to 9, read on 10

	cat '/prog/'^${pid}^'/fd'
	space=' '

	echo parent block pid ${pid}
	cat '/prog/'^${pid}^'/fd'

	# forth process 1 startup
	<'#f/forth/new'{ n=`{read} }
	echo forth pid is $n
	cat '#o/'^$n^'/fd'
	echo 'forkenv forkfd forkns shmem redirfds 7 9 2 ' >'#f/forth/'^$n^'/ctl'

	# forth process 2 startup
	<'#f/forth/new'{ o=`{read} }
	echo forth pid is $o
	cat '#o/'^$o^'/fd'
	echo 'forkenv forkfd forkns shmem redirfds 17 19 2 ' >'#f/forth/'^$o^'/ctl'

#	echo ' 10 . ' >[1=8] $space
#	<[0=10] { read }

	fn sendn {
		echo $"* >[1=8]
	}

	fn readlinen {
		<[0=10] { read }
	}

	fn tn {
		args=$*
		(sendargs expected)=$*
		#echo $args
		echo $sendargs ' => ' $expected

		# get stack depth
		sendn 'depth . ' $space
		d="{readlinen}
		readlinen # to ignore the space following the .

		sendn $sendargs

		for i in $expected {
			r="{readlinen}
			if{! ~ $"i $"r}{ # forth . puts a space at the end
				echo $sendargs '->' $expected
				echo does not match: expected '"'$"i'"' actual '"'$"r'"'
			}
		}

		# compare stack depth now
		sendn 'depth . ' $space
		dnew="{readlinen}
		readlinen # to ignore the space following the .
		if{! ~ $"dnew $"d}{
			echo $sendargs '->' $expected
			echo stack depth changed: start $d end $dnew
		}
	}

	tn ' variable Shmfd 10 Shmfd ! Shmfd @ . ' 10 $space
	tn ' 9 : shmfd@ Shmfd @ ; . ' 9 $space
	tn ' 9 : shmfd! Shmfd ! ; . ' 9 $space
	tn ' 11 shmfd! shmfd@ . ' 11 $space
	tn ' variable Outputchars 1 vallot 65 Outputchars ! 66 Outputchars 1+ ! Outputchars 2 type ' AB
	tn ' 9 Outputchars 2 type . ' AB 9 $space
	tn ' 9 " #h/init" r/w 420 create-file drop shmfd! Outputchars 2 shmfd@ write-file drop shmfd@ close-file drop . ' 9 $space
	tn ' variable Oc1 1 vallot 67 Oc1 ! 68 Oc1 1+ ! Oc1 2 type ' CD
	tn ' 9 " #h/init" r/o open-file ( fd ioresult ) drop shmfd! Oc1 2 shmfd@ read-file ( n ioresult ) drop dup . ( n ) Oc1 swap type . ' 2 $space AB 9 $space

	fn sendo {
		echo $"* >[1=18]
	}

	fn readlineo {
		<[0=20] { read }
	}

	fn to {
		args=$*
		(sendargs expected)=$*
		#echo $args
		echo $sendargs ' => ' $expected

		# get stack depth
		sendo 'depth . ' $space
		d="{readlineo}
		readlineo # to ignore the space following the .

		sendo $sendargs

		for i in $expected {
			r="{readlineo}
			if{! ~ $"i $"r}{ # forth . puts a space at the end
				echo $sendargs '->' $expected
				echo does not match: expected '"'$"i'"' actual '"'$"r'"'
			}
		}

		# compare stack depth now
		sendo 'depth . ' $space
		dnew="{readlineo}
		readlineo # to ignore the space following the .
		if{! ~ $"dnew $"d}{
			echo $sendargs '->' $expected
			echo stack depth changed: start $d end $dnew
		}
	}

	to ' variable Shmfd 10 Shmfd ! Shmfd @ . ' 10 $space
	to ' 9 : shmfd@ Shmfd @ ; . ' 9 $space
	to ' 9 : shmfd! Shmfd ! ; . ' 9 $space
	to ' 11 shmfd! shmfd@ . ' 11 $space
	to ' variable Outputchars 1 vallot 65 Outputchars ! 66 Outputchars 1+ ! Outputchars 2 type ' AB
	to ' 9 Outputchars 2 type . ' AB 9 $space
	to ' 9 " #h/init" r/w 420 create-file drop shmfd! Outputchars 2 shmfd@ write-file drop shmfd@ close-file drop . ' 9 $space
	to ' variable Oc1 1 vallot 67 Oc1 ! 68 Oc1 1+ ! Oc1 2 type ' CD
	to ' 9 " #h/init" r/o open-file ( fd ioresult ) drop shmfd! Oc1 2 shmfd@ read-file ( n ioresult ) drop dup . ( n ) Oc1 swap type . ' 2 $space AB 9 $space

}
echo exiting fthshm.sh
