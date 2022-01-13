#!/dis/sh

# https://forth-standard.org/standard/testsuite

# F.2 Test Harness
# The tester defines functions that compare the results of a test with a
# set of expected results. The syntax for each test starts with 
# "T{" (T-open brace) followed by a code sequence to test. This is followed
# by "->", the expected results, and "}T" (close brace-T). For example, the
# following: 
# 
# T{ 1 1 + -> 2 }T 
# tests that one plus one indeed equals two. 
# The "T{" records the stack depth prior to the test code so that they can
# be eliminated from the test. The "->" records the stack depth and moves
# the entire stack contents to an array. In the example test, the recorded
# stack depth is one and the saved array contains one value, two. The "}T"
# compares the current stack depth to the saved stack depth. If they are
# equal each value on the stack is removed from the stack and compared to
# its corresponding value in the array. If the depths are not equal or if
# the stack comparison fails, an error is reported. For example: 
# T{ 1 2 3 SWAP -> 1 3 2 }T 
# T{ 1 2 3 SWAP -> 1 2 3 }T INCORRECT RESULT: T{ 1 2 3 SWAP -> 1 2 3 }T 
# T{ 1 2 SWAP -> 1 }T WRONG NUMBER OF RESULTS: T{ 1 2 SWAP -> 1 }T 

bind '#|' /n/ff
<[7]/n/ff/data >[8]/n/ff/data1 >[9]/n/ff/data <[10]/n/ff/data1 {

	cat '/prog/'^${pid}^'/fd'

	# testing pipe
	# data1 -> data, write to 8, read on 7
	echo 10 >>[1=8]
	# data -> data1, write to 9, read on 10
	echo 20 >>[1=9]

	echo read /n/ff/data
	<[0=7] { read }
	echo after read /n/ff/data

	echo read /n/ff/data1
	<[0=10] { read }
	echo read /n/ff/data1

	# forth process startup
	<'#f/forth/new'{ n=`{read} }
	echo parent block pid ${pid}
	echo forth pid is $n
	cat '#o/'^$n^'/fd'
	echo 'forkenv forkfd forkns noshmem redirfds 7 9 2 ' >'#f/forth/'^$n^'/ctl'

	cat '/prog/'^${pid}^'/fd'
	cat '#o/'^$n^'/fd'

#	echo ' 10 . ' >[1=8] $space
#	<[0=10] { read }

	fn send {
		echo $"* >[1=8]
	}

	fn readline {
		<[0=10] { read }
	}

	fn t {
		args=$*
		(sendargs expected)=$*
		#echo $args
		echo $sendargs ' => ' $expected

		# get stack depth
		send 'depth . ' $space
		d="{readline}
		readline # to ignore the space following the .

		send $sendargs

		for i in $expected {
			r="{readline}
			if{! ~ $"i $"r}{ # forth . puts a space at the end
				echo $sendargs '->' $expected
				echo does not match: expected '"'$"i'"' actual '"'$"r'"'
			}
		}

		# compare stack depth now
		send 'depth . ' $space
		dnew="{readline}
		readline # to ignore the space following the .
		if{! ~ $"dnew $"d}{
			echo $sendargs '->' $expected
			echo stack depth changed: start $d end $dnew
		}
	}
	space=' '

	t '       9 . ' 9 $space
	t '       0 . ' 0 $space
	t '      -1 . ' -1 $space
	t '       1 . ' 1 $space

	# and tests
	# F.6.1.0720 AND
	t ' 0 0 and . '  0 $space
	t ' 0 1 and . '  0 $space
	t ' 1 0 and . '  0 $space
	t ' 1 1 and . '  1 $space

	t ' 0 invert 1 and . '  1 $space
	t ' 1 invert 1 and . '  0 $space

	t ' 0 0 and . '  0 $space
	t ' 0 1 and . '  0 $space
	t ' 1 0 and . '  0 $space
	t ' 1 1 and . '  1 $space

	t ' 0 invert . ' -1 $space
	t ' -1 invert . ' 0 $space

	t '  0  0 * . '  0 $space # test identities
	t '  0  1 * . '  0 $space
	t '  1  0 * . '  0 $space
	t '  1  2 * . '  2 $space
	t '  2  1 * . '  2 $space
	t '  3  3 * . '  9 $space
	t ' -3  3 * . ' -9 $space
	t '  3 -3 * . ' -9 $space
	t ' -3 -3 * . '  9 $space

	#t '       0 2       1 * / '       0 $space
	#t '       1 2       1 * / '       1 $space
	#t '       2 2       1 * / '		  1 $space
	#t '      -1 2       1 * / '      -1 $space
	#t '      -2 2       1 * / '      -1 $space
	#t '       0 2      -1 * / '       0 $space
	#t '       1 2      -1 * / '      -2 $space
	#t '       2 2      -1 * / '      -1 $space
	#t '      -1 2      -1 * / '       2 $space
	#t '      -2 2      -1 * / '       1 $space
	#t '       2 2       2 * / '       2 $space
	#t '      -1 2      -1 * / '       2 $space
	#t '      -2 2      -2 * / '       2 $space
	#t '       7 2       3 * / '       1 $space
	#t '       7 2      -3 * / '      -1 $space
	#t '      -7 2       3 * / '      -1 $space
	#t '      -7 2      -3 * / '       1 $space

	#t '       0 2       1 * /mod '       0 2       1 t* /mod $space
	#t '       1 2       1 * /mod '       1 2       1 t* /mod $space
	#t '       2 2       1 * /mod '       2 2       1 t* /mod $space
	#t '      -1 2       1 * /mod '      -1 2       1 t* /mod $space
	#t '      -2 2       1 * /mod '      -2 2       1 t* /mod $space
	#t '       0 2      -1 * /mod '       0 2      -1 t* /mod $space
	#t '       1 2      -1 * /mod '       1 2      -1 t* /mod $space
	#t '       2 2      -1 * /mod '       2 2      -1 t* /mod $space
	#t '      -1 2      -1 * /mod '      -1 2      -1 t* /mod $space
	#t '      -2 2      -1 * /mod '      -2 2      -1 t* /mod $space
	#t '       2 2       2 * /mod '       2 2       2 t* /mod $space
	#t '      -1 2      -1 * /mod '      -1 2      -1 t* /mod $space
	#t '      -2 2      -2 * /mod '      -2 2      -2 t* /mod $space
	#t '       7 2       3 * /mod '       7 2       3 t* /mod $space
	#t '       7 2      -3 * /mod '       7 2      -3 t* /mod $space
	#t '      -7 2       3 * /mod '      -7 2       3 t* /mod $space
	#t '      -7 2      -3 * /mod '      -7 2      -3 t* /mod $space

	t '        0  5 + . '          5 $space
	t '        5  0 + . '          5 $space
	t '        0 -5 + . '         -5 $space
	t '       -5  0 + . '         -5 $space
	t '        1  2 + . '          3 $space
	t '        1 -2 + . '         -1 $space
	t '       -1  2 + . '          1 $space
	t '       -1 -2 + . '         -3 $space
	t '       -1  1 + . '          0 $space

	t ' 0 Args !  Args @ .       ' 0 $space
	t ' 0 Args ! 1 Args +!  Args @ .       ' 1 $space
	t ' 0 Args ! 1 Args +! -1 Args +! Args @ . ' 0 $space

	t '          0  5 - . '       -5 $space
	t '          5  0 - . '        5 $space
	t '          0 -5 - . '        5 $space
	t '         -5  0 - . '       -5 $space
	t '          1  2 - . '       -1 $space
	t '          1 -2 - . '        3 $space
	t '         -1  2 - . '       -3 $space
	t '         -1 -2 - . '        1 $space
	t '          0  1 - . '       -1 $space

	#t '       0       1 / '       0       1  $space
	#t '       1       1 / '       1       1  $space
	#t '       2       1 / '       2       1  $space
	#t '      -1       1 / '      -1       1  $space
	#t '      -2       1 / '      -2       1  $space
	#t '       0      -1 / '       0      -1  $space
	#t '       1      -1 / '       1      -1  $space
	#t '       2      -1 / '       2      -1  $space
	#t '      -1      -1 / '      -1      -1  $space
	#t '      -2      -1 / '      -2      -1  $space
	#t '       2       2 / '       2       2  $space
	#t '      -1      -1 / '      -1      -1  $space
	#t '      -2      -2 / '      -2      -2  $space
	#t '       7       3 / '       7       3  $space
	#t '       7      -3 / '       7      -3  $space
	#t '      -7       3 / '      -7       3  $space
	#t '      -7      -3 / '      -7      -3  $space

	#t '       0       1 '       0       1 $space
	#t '       1       1 '       1       1 $space
	#t '       2       1 '       2       1 $space
	#t '      -1       1 '      -1       1 $space
	#t '      -2       1 '      -2       1 $space
	#t '       0      -1 '       0      -1 $space
	#t '       1      -1 '       1      -1 $space
	#t '       2      -1 '       2      -1 $space
	#t '      -1      -1 '      -1      -1 $space
	#t '      -2      -1 '      -2      -1 $space
	#t '       2       2 '       2       2 $space
	#t '      -1      -1 '      -1      -1 $space
	#t '      -2      -2 '      -2      -2 $space
	#t '       7       3 '       7       3 $space
	#t '       7      -3 '       7      -3 $space
	#t '      -7       3 '      -7       3 $space
	#t '      -7      -3 '      -7      -3 $space

	t '        0 0= . ' -1 $space
	t '        1 0= . ' 0 $space
	t '        2 0= . ' 0 $space
	t '       -1 0= . ' 0 $space

	t '        0 1+ . '          1 $space
	t '       -1 1+ . '          0 $space
	t '        1 1+ . '          2 $space

	t '          2 1- . '        1 $space
	t '          1 1- . '        0 $space
	t '          0 1- . '       -1 $space

	t '   0 2*    .   '   0 $space
	t '    1 2*   .    '    2 $space
	t ' 4000 2*   .    ' 8000 $space
	t '   1 2* 1 xor . '   3 $space

	t '          0 2/ . '   0 $space
	t '           1 2/ . '    0 $space
	t '        4000 2/ . ' 2000 $space
	t '          1 2/ . '   0 $space # msb propogated
	t '    1 1 xor 2/ . '   0 $space

	t '  0 negate . '  0 $space
	t '  1 negate . ' -1 $space
	t ' -1 negate . '  1 $space
	t '  2 negate . ' -2 $space
	t ' -2 negate . '  2 $space

	t ' 0 0 or . ' 0 $space
	t ' 0 1 or . ' 1 $space
	t ' 1 0 or . ' 1 $space
	t ' 1 1 or . ' 1 $space

	t ' 1 2 over . . . ' 1 $space 2 $space 1 $space

	t ' 1 2 3 rot . . . ' 1 $space 3 $space 2 $space # 1 2 3 rot = 2 3 1. outputting the stack with . writes out 1 3 2 $space

	t '    1 0 rshift . ' 1 $space
	t '    1 1 rshift . ' 0 $space
	t '    2 1 rshift . ' 1 $space
	t '    4 2 rshift . ' 1 $space
	t ' hex 8000 f rshift decimal . ' 1 $space # biggest

	t ' 1 2 swap . . ' 1 $space 2 $space # 1 2 swap = 2 1. outputting the stack with . writes out 1 2 $space

	t ' 0 0 xor . ' 0 $space
	t ' 0 1 xor . ' 1 $space
	t ' 1 0 xor . ' 1 $space
	t ' 1 1 xor . ' 0 $space

	t ' false . ' 0 $space

	t ' true . ' -1 $space

	t ' 2 1 2 2drop . ' 2 $space

	t ' 1 2 2dup . . . . ' 2 $space 1 $space 2 $space 1 $space # 1 2 2dup = 1 2 1 2. outputting the stack with . writes out 2 1 2 1 $space

	#t ' 1 2 3 4 2over . . . . . . ' 2 $space 1 $space 4 $space 3 $space 2 $space 1 $space # 1 2 3 4 2over = 1 2 3 4 1 2. outputting stack with . writes 2 1 4 3 2 1 $space

	t ' 1 2 3 4 2swap  . . . . ' 2 $space 1 $space 4 $space 3 $space # 3 4 1 2 on the stack. outputting stack with . writes 2 1 4 3 $space

	t '       0       1 < . ' -1 $space
	t '       1       2 < . ' -1 $space
	t '      -1       0 < . ' -1 $space
	t '      -1       1 < . ' -1 $space
	t '       0       0 < . ' 0 $space
	t '       1       1 < . ' 0 $space
	t '       1       0 < . ' 0 $space
	t '       2       1 < . ' 0 $space
	t '       0      -1 < . ' 0 $space
	t '       1      -1 < . ' 0 $space

	t '  0  0 = . ' -1 $space
	t '  1  1 = . ' -1 $space
	t ' -1 -1 = . ' -1 $space
	t '  1  0 = . ' 0 $space
	t ' -1  0 = . ' 0 $space
	t '  0  1 = . ' 0 $space
	t '  0 -1 = . ' 0 $space

	t '       0       1 > . ' 0 $space
	t '       1       2 > . ' 0 $space
	t '      -1       0 > . ' 0 $space
	t '      -1       1 > . ' 0 $space
	t '       0       0 > . ' 0 $space
	t '       1       1 > . ' 0 $space
	t '       1       0 > . ' -1 $space
	t '       2       1 > . ' -1 $space
	t '       0      -1 > . ' -1 $space
	t '       1      -1 > . ' -1 $space

# TODO t ' 123456 depth over 9 < 35 and + 3 + >in ! ' 123456 23456 3456 456 56 6 $space

	t ' -1 ?dup . . ' -1 $space -1 $space
	t '  0 ?dup . '  0    $space
	t '  1 ?dup . . '  1 $space 1 $space

	t '       0 abs . '          0 $space
	t '       1 abs . '          1 $space
	t '      -1 abs . '          1 $space

	t ' 0 0 and . ' 0 $space
	t ' 0 1 and . ' 0 $space
	t ' 1 0 and . ' 0 $space
	t ' 1 1 and . ' 1 $space

	t ' 0 invert 1 and . ' 1 $space
	t ' 1 invert 1 and . ' 0 $space

	t ' 0 0 and . ' 0 $space
	t ' 0 1 and . ' 0 $space
	t ' 1 0 and . ' 0 $space
	t ' 1 1 and . ' 1 $space

	t ' char X     . ' 88 $space
	t ' char HELLO . ' 72 $space

	t ' 0 1 depth . . . ' 2 $space 1 $space 0 $space
	t '   0 depth . . ' 1 $space 0   $space
	t '     depth . ' 0     $space

	t ' 1 2 drop . ' 1 $space
	t ' 9 0   drop . ' 9  $space

	t ' 1 dup . . ' 1 $space 1 $space

#emit
#: output-test
#   ." you should see the standard graphic characters:" cr
#   41 bl do i emit loop cr
#   61 41 do i emit loop cr
#   7f 61 do i emit loop cr
#   ." you should see 0-9 separated by a space:" cr
#   9 1+ 0 do i . loop cr
#   ." you should see 0-9 (with no spaces):" cr
#   [char] 9 1+ [char] 0 do i 0 spaces emit loop cr
#   ." you should see a-g separated by a space:" cr
#   [char] g 1+ [char] a do i emit space loop cr
#   ." you should see 0-5 separated by two spaces:" cr
#   5 1+ 0 do i [char] 0 + emit 2 spaces loop cr
#   ." you should see two separate lines:" cr
#   s" line 1" type cr s" line 2" type cr
#   ." you should see the number ranges of signed and unsigned numbers:" cr
#   ." signed: " min-int . max-int . cr
#   ." unsigned: " 0 u. max-uint u. cr
#;
#
	#t ' output-test '

	t ' 0 invert . ' -1 $space
	t ' -1 invert . ' 0 $space

	t '   1 0 lshift . '    1 $space
	t '   1 1 lshift . '    2 $space
	t '   1 2 lshift . '    4 $space
	t '   1 hex f lshift . ' 8000 $space      # biggest guaranteed shift
	t ' decimal 1 1 lshift 1 xor . ' 3 $space

	t '       0       1 max . '       1 $space
	t '       1       2 max . '       2 $space
	t '      -1       0 max . '       0 $space
	t '      -1       1 max . '       1 $space
	t '       0       0 max . '       0 $space
	t '       1       1 max . '       1 $space
	t '       1       0 max . '       1 $space
	t '       2       1 max . '       2 $space
	t '       0      -1 max . '       0 $space
	t '       1      -1 max . '       1 $space

	t '       0       1 min . '       0 $space
	t '       1       2 min . '       1 $space
	t '      -1       0 min . '      -1 $space
	t '      -1       1 min . '      -1 $space
	t '       0       0 min . '       0 $space
	t '       1       1 min . '       1 $space
	t '       1       0 min . '       0 $space
	t '       2       1 min . '       1 $space
	t '       0      -1 min . '      -1 $space
	t '       1      -1 min . '      -1 $space

	#t '       0       1 mod '       0       1 tmod $space
	#t '       1       1 mod '       1       1 tmod $space
	#t '       2       1 mod '       2       1 tmod $space
	#t '      -1       1 mod '      -1       1 tmod $space
	#t '      -2       1 mod '      -2       1 tmod $space
	#t '       0      -1 mod '       0      -1 tmod $space
	#t '       1      -1 mod '       1      -1 tmod $space
	#t '       2      -1 mod '       2      -1 tmod $space
	#t '      -1      -1 mod '      -1      -1 tmod $space
	#t '      -2      -1 mod '      -2      -1 tmod $space
	#t '       2       2 mod '       2       2 tmod $space
	#t '      -1      -1 mod '      -1      -1 tmod $space
	#t '      -2      -2 mod '      -2      -2 tmod $space
	#t '       7       3 mod '       7       3 tmod $space
	#t '       7      -3 mod '       7      -3 tmod $space
	#t '      -7       3 mod '      -7       3 tmod $space
	#t '      -7      -3 mod '      -7      -3 tmod $space

	t ' decimal 1000 1000 * 1000 * . ' 1000000000 $space

	t ' 0     aligned . '      0 $space
	t ' 3      aligned . '      8 $space
	t ' 8     aligned . '      8 $space
	t ' 10     aligned . '      16 $space
	t ' 16     aligned . '      16 $space


	t ' char testing . ' 116	$space # ascii value of t = 116
	t ' : just1 char ; char esting . ' 101 $space # ascii value of e = 101

	t ': just1 1 ; just1 . ' 1 $space
	t ': dostuff do 1+ loop ; 0 2 0 dostuff . ' 2 $space
	t ': showstuff ." testingstring" ; 10 showstuff . ' testingstring 10 $space
	t ': showstuff ." testingstring " space ; 10 showstuff . ' 'testingstring ' $space 10 $space
	t ': showstuff s" /tmp/test" ; 10 showstuff type . ' /tmp/test 10 $space
	t ' 10 " string  to type " type . ' 'string  to type ' 10 $space

	t ' 10 : testif 0 0 = if ." 0 0 = true" else ." 0 0 = false" then ; testif . ' '0 0 = true' 10 $space
	t ' 10 : testif 0 1 = if ." 0 0 = true" else ." 0 1 = false" then ; testif . ' '0 1 = false' 10 $space
	t '10 constant  MYCONSTANT MYCONSTANT . ' 10 $space
	t '10 variable myfd 9 myfd ! myfd @ . . ' 9 $space 10 $space

	t ' 10 " /dis/init" r/o open-file . . . ' -1 $space 4 $space 10 $space

	t ' 9 Tib 10 " /dis/init" r/o open-file drop read-file Tib 10 type . . . ' '#!/dis/sh ' -1 $space 10 $space 9 $space

	# first -1 is the true flag of close-file
	# second -1 is the true flag of read-file
	# 10 is the number of characters read by read-file
	#	the true flag of open-file is drop'ped
	# 9 is the top of stack at the start
	t ' 9 Tib 10 " /dis/init" r/o open-file drop dup variable myfd myfd ! read-file Tib 10 type myfd @ close-file . . . . ' '#!/dis/sh ' -1 $space -1 $space 10 $space 9 $space

	# first -1 is the true flag of close-file
	# second -1 is the true flag of read-file
	# 10 is the number of characters read by read-file
	# third -1 is the true flag of reposition-file
	#	the true flag of open-file is drop'ped
	# fourth -1 is the true flag of read-file
	# 10 is the number of characters read by read-file
	# 9 is the top of stack at the start
	t ' 9 Tib 10 " /dis/init" r/o open-file drop dup variable myfd myfd ! read-file Tib 10 type 0 0 myfd @ reposition-file Tib 10 erase Tib 10 myfd @ read-file Tib 10 type myfd @ close-file . . . . . . . ' '#!/dis/sh ' '#!/dis/sh ' -1 $space -1 $space 10 $space -1 $space -1 $space 10 $space 9 $space

	load expr
	echo '		looping with forth '
	start=`{cat /dev/time}
	echo start microseconds $start
	send ': donothing do loop ; 0 1000 1000 * 1000 * dup 0 donothing . '
	echo n "{readline}
	end=`{cat /dev/time}
	echo end microseconds $end
	echo microseconds taken: ${expr $end $start - }
	echo

	start=`{cat /dev/time}
	echo start microseconds $start
	send ': dodupdrop do dup drop loop ; 9 1000 1000 * 1000 * dup 0 dodupdrop . '
	echo n "{readline}
	end=`{cat /dev/time}
	echo end microseconds $end
	echo microseconds taken: ${expr $end $start - }
	echo

	echo '		doing the same with limbo '
	start=`{cat /dev/time}
	echo start microseconds $start
	#time /tests/progtest.dis
	/tests/progtest.dis
	end=`{cat /dev/time}
	echo end microseconds $end
	echo microseconds taken: ${expr $end $start - }
	echo

}
