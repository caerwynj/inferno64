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

<'#f/forth/new'{ n=`{read} }
echo forth pid is $n

fn send {
	echo $* >> '#f/forth/'^$n^'/stdin'
}

fn readline {
	<'#f/forth/'^$n^'/stdout'{read}
}

fn t {
	args=$*
	(sendargs expected)=$*
	echo $args

	# get stack depth
	send 'depth . '
	d="{readline}

	send $sendargs

	for i in $expected {
		send ' . '
		r="{readline}
		if{! ~ $"i^' ' $"r}{ # forth . puts a space at the end
			echo $sendargs '->' $expected
			echo does not match: expected '"'$"i' "' actual '"'$"r'"'
		}
	}

	# compare stack depth now
	send 'depth . '
	dnew="{readline}
	if{! ~ $"dnew $"d}{
		echo $sendargs '->' $expected
		echo stack depth changed: start $d end $dnew
	}
}

	# and tests
	# F.6.1.0720 AND
	t ' 0 0 and '  0
	t ' 0 1 and '  0
	t ' 1 0 and '  0
	t ' 1 1 and '  1
	
	t ' 0 invert 1 and '  1
	t ' 1 invert 1 and '  0
	
	t ' 0 0 and '  0
	t ' 0 1 and '  0
	t ' 1 0 and '  0
	t ' 1 1 and '  1

t ' 0 invert ' -1
t ' -1 invert ' 0

t '  0  0 * '  0           # test identities
t '  0  1 * '  0
t '  1  0 * '  0
t '  1  2 * '  2
t '  2  1 * '  2
t '  3  3 * '  9
t ' -3  3 * ' -9
t '  3 -3 * ' -9
t ' -3 -3 * '  9

#t '       0 2       1 * / '       0
#t '       1 2       1 * / '       1
#t '       2 2       1 * / '		  1
#t '      -1 2       1 * / '      -1
#t '      -2 2       1 * / '      -1
#t '       0 2      -1 * / '       0
#t '       1 2      -1 * / '      -2
#t '       2 2      -1 * / '      -1
#t '      -1 2      -1 * / '       2
#t '      -2 2      -1 * / '       1
#t '       2 2       2 * / '       2
#t '      -1 2      -1 * / '       2
#t '      -2 2      -2 * / '       2
#t '       7 2       3 * / '       1
#t '       7 2      -3 * / '      -1
#t '      -7 2       3 * / '      -1
#t '      -7 2      -3 * / '       1
#
#t '       0 2       1 * /mod '       0 2       1 t* /mod
#t '       1 2       1 * /mod '       1 2       1 t* /mod
#t '       2 2       1 * /mod '       2 2       1 t* /mod
#t '      -1 2       1 * /mod '      -1 2       1 t* /mod
#t '      -2 2       1 * /mod '      -2 2       1 t* /mod
#t '       0 2      -1 * /mod '       0 2      -1 t* /mod
#t '       1 2      -1 * /mod '       1 2      -1 t* /mod
#t '       2 2      -1 * /mod '       2 2      -1 t* /mod
#t '      -1 2      -1 * /mod '      -1 2      -1 t* /mod
#t '      -2 2      -1 * /mod '      -2 2      -1 t* /mod
#t '       2 2       2 * /mod '       2 2       2 t* /mod
#t '      -1 2      -1 * /mod '      -1 2      -1 t* /mod
#t '      -2 2      -2 * /mod '      -2 2      -2 t* /mod
#t '       7 2       3 * /mod '       7 2       3 t* /mod
#t '       7 2      -3 * /mod '       7 2      -3 t* /mod
#t '      -7 2       3 * /mod '      -7 2       3 t* /mod
#t '      -7 2      -3 * /mod '      -7 2      -3 t* /mod

t '        0  5 + '          5
t '        5  0 + '          5
t '        0 -5 + '         -5
t '       -5  0 + '         -5
t '        1  2 + '          3
t '        1 -2 + '         -1
t '       -1  2 + '          1
t '       -1 -2 + '         -3
t '       -1  1 + '          0

t ' 0 Args !  Args @        ' 0
t ' 0 Args ! 1 Args +!  Args @        ' 1
t ' 0 Args ! 1 Args +! -1 Args +! Args @ ' 0

t '          0  5 - '       -5
t '          5  0 - '        5
t '          0 -5 - '        5
t '         -5  0 - '       -5
t '          1  2 - '       -1
t '          1 -2 - '        3
t '         -1  2 - '       -3
t '         -1 -2 - '        1
t '          0  1 - '       -1

#t '       0       1 / '       0       1 
#t '       1       1 / '       1       1 
#t '       2       1 / '       2       1 
#t '      -1       1 / '      -1       1 
#t '      -2       1 / '      -2       1 
#t '       0      -1 / '       0      -1 
#t '       1      -1 / '       1      -1 
#t '       2      -1 / '       2      -1 
#t '      -1      -1 / '      -1      -1 
#t '      -2      -1 / '      -2      -1 
#t '       2       2 / '       2       2 
#t '      -1      -1 / '      -1      -1 
#t '      -2      -2 / '      -2      -2 
#t '       7       3 / '       7       3 
#t '       7      -3 / '       7      -3 
#t '      -7       3 / '      -7       3 
#t '      -7      -3 / '      -7      -3 
#
#
#t '       0       1 '       0       1
#t '       1       1 '       1       1
#t '       2       1 '       2       1
#t '      -1       1 '      -1       1
#t '      -2       1 '      -2       1
#t '       0      -1 '       0      -1
#t '       1      -1 '       1      -1
#t '       2      -1 '       2      -1
#t '      -1      -1 '      -1      -1
#t '      -2      -1 '      -2      -1
#t '       2       2 '       2       2
#t '      -1      -1 '      -1      -1
#t '      -2      -2 '      -2      -2
#t '       7       3 '       7       3
#t '       7      -3 '       7      -3
#t '      -7       3 '      -7       3
#t '      -7      -3 '      -7      -3

t '       0 ' 0
t '      -1 ' -1
t '       1 ' 1

t '        0 0= ' -1
t '        1 0= ' 0
t '        2 0= ' 0
t '       -1 0= ' 0

t '        0 1+ '          1
t '       -1 1+ '          0
t '        1 1+ '          2

t '          2 1- '        1
t '          1 1- '        0
t '          0 1- '       -1

t '   0 2*       '   0
t '    1 2*       '    2
t ' 4000 2*       ' 8000
t '   1 2* 1 xor '   3

t '          0 2/ '   0
t '           1 2/ '    0
t '        4000 2/ ' 2000
t '          1 2/ '   0  # msb propogated
t '    1 1 xor 2/ '   0

t '  0 negate '  0
t '  1 negate ' -1
t ' -1 negate '  1
t '  2 negate ' -2
t ' -2 negate '  2

t ' 0 0 or ' 0
t ' 0 1 or ' 1
t ' 1 0 or ' 1
t ' 1 1 or ' 1

t ' 1 2 over ' 1 2 1

t ' 1 2 3 rot ' 1 3 2	# 1 2 3 rot = 2 3 1. outputting the stack with . writes out 1 3 2

t '    1 0 rshift ' 1
t '    1 1 rshift ' 0
t '    2 1 rshift ' 1
t '    4 2 rshift ' 1
t ' hex 8000 f rshift ' 1 	               # biggest

t ' 1 2 swap ' 1 2	# 1 2 swap = 2 1. outputting the stack with . writes out 1 2

t ' 0 0 xor ' 0
t ' 0 1 xor ' 1
t ' 1 0 xor ' 1
t ' 1 1 xor ' 0

t ' false ' 0

t ' true ' -1

t ' 2 1 2 2drop ' 2

t ' 1 2 2dup ' 2 1 2 1 # 1 2 2dup = 1 2 1 2. outputting the stack with . writes out 2 1 2 1

#t ' 1 2 3 4 2over ' 2 1 4 3 2 1 # 1 2 3 4 2over = 1 2 3 4 1 2. outputting stack with . writes 2 1 4 3 2 1

t ' 1 2 3 4 2swap ' 2 1 4 3 # 3 4 1 2 on the stack. outputting stack with . writes 2 1 4 3

t '       0       1 < ' -1
t '       1       2 < ' -1
t '      -1       0 < ' -1
t '      -1       1 < ' -1
t '       0       0 < ' 0
t '       1       1 < ' 0
t '       1       0 < ' 0
t '       2       1 < ' 0
t '       0      -1 < ' 0
t '       1      -1 < ' 0

t '  0  0 = ' -1
t '  1  1 = ' -1
t ' -1 -1 = ' -1
t '  1  0 = ' 0
t ' -1  0 = ' 0
t '  0  1 = ' 0
t '  0 -1 = ' 0

t '       0       1 > ' 0
t '       1       2 > ' 0
t '      -1       0 > ' 0
t '      -1       1 > ' 0
t '       0       0 > ' 0
t '       1       1 > ' 0
t '       1       0 > ' -1
t '       2       1 > ' -1
t '       0      -1 > ' -1
t '       1      -1 > ' -1

# TODO t ' 123456 depth over 9 < 35 and + 3 + >in ! ' 123456 23456 3456 456 56 6

t ' -1 ?dup ' -1 -1
t '  0 ?dup '  0   
t '  1 ?dup '  1  1

t '       0 abs '          0
t '       1 abs '          1
t '      -1 abs '          1

t ' 0 0 and ' 0
t ' 0 1 and ' 0
t ' 1 0 and ' 0
t ' 1 1 and ' 1

t ' 0 invert 1 and ' 1
t ' 1 invert 1 and ' 0

t ' 0 0 and ' 0
t ' 0 1 and ' 0
t ' 1 0 and ' 0
t ' 1 1 and ' 1

t ' char X     ' 88
t ' char HELLO ' 72

t ' 0 1 depth ' 2 1 0
t '   0 depth ' 1 0  
t '     depth ' 0    

t ' 1 2 drop ' 1
t ' 0   drop '  

t ' 1 dup ' 1 1

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

t ' 0 invert ' -1
t ' -1 invert ' 0

t '   1 0 lshift '    1
t '   1 1 lshift '    2
t '   1 2 lshift '    4
t '   1 hex f lshift ' 8000       # biggest guaranteed shift
t '  1 1 lshift 1 xor ' 3

t '       0       1 max '       1
t '       1       2 max '       2
t '      -1       0 max '       0
t '      -1       1 max '       1
t '       0       0 max '       0
t '       1       1 max '       1
t '       1       0 max '       1
t '       2       1 max '       2
t '       0      -1 max '       0
t '       1      -1 max '       1

t '       0       1 min '       0
t '       1       2 min '       1
t '      -1       0 min '      -1
t '      -1       1 min '      -1
t '       0       0 min '       0
t '       1       1 min '       1
t '       1       0 min '       0
t '       2       1 min '       1
t '       0      -1 min '      -1
t '       1      -1 min '      -1

#t '       0       1 mod '       0       1 tmod
#t '       1       1 mod '       1       1 tmod
#t '       2       1 mod '       2       1 tmod
#t '      -1       1 mod '      -1       1 tmod
#t '      -2       1 mod '      -2       1 tmod
#t '       0      -1 mod '       0      -1 tmod
#t '       1      -1 mod '       1      -1 tmod
#t '       2      -1 mod '       2      -1 tmod
#t '      -1      -1 mod '      -1      -1 tmod
#t '      -2      -1 mod '      -2      -1 tmod
#t '       2       2 mod '       2       2 tmod
#t '      -1      -1 mod '      -1      -1 tmod
#t '      -2      -2 mod '      -2      -2 tmod
#t '       7       3 mod '       7       3 tmod
#t '       7      -3 mod '       7      -3 tmod
#t '      -7       3 mod '      -7       3 tmod
#t '      -7      -3 mod '      -7      -3 tmod
