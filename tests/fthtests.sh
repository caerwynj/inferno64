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

	# get stack depth
	send 'depth . '
	d="{readline}

	send $sendargs

	for i in $expected {
		send ' . '
		r="{readline}
		if{! ~ $"i^' ' $"r}{ # forth . puts a space at the end
			echo $sendargs '->' $expected
			echo does not match: exected '"'$"i' "' actual '"'$"r'"'
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
	
	t ' 0s 0s and '  0s
	t ' 0s 1s and '  0s
	t ' 1s 0s and '  0s
	t ' 1s 1s and '  1s


