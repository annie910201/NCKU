#!/bin/bash
make clean && make
case $1 in
	0)
		./myscanner < input/a00_helloWorld_comment.rs >| tmp.out
		diff -y tmp.out answer/a00_helloWorld_comment.out
	;;
	1)
		./myscanner < input/a01_arithmetic.rs >| tmp.out
		diff -y tmp.out answer/a01_arithmetic.out
	;;
	2)
		./myscanner < input/a02_precedence.rs >| tmp.out
		diff -y tmp.out answer/a02_precedence.out
	;;
	3)
		./myscanner < input/a03_scope.rs >| tmp.out
                diff -y tmp.out answer/a03_scope.out
	;;
	4)
		./myscanner < input/a04_assigment.rs >| tmp.out
                diff -y tmp.out answer/a04_assigment.out
	;;
	5)
		./myscanner < input/a05_casting.rs >| tmp.out
                diff -y tmp.out answer/a05_casting.out
	;;
	6)
		./myscanner < input/a06_if.rs >| tmp.out
		diff -y tmp.out answer/a06_if.out
	;;
	7)
		./myscanner < input/a07_while.rs >| tmp.out
                diff -y tmp.out answer/a07_while.out
	;;
	8)
		./myscanner < input/a08_function.rs >| tmp.out
                diff -y tmp.out answer/a08_function.out
	;;
        9)
		./myscanner < input/a09_array.rs >| tmp.out
                diff -y tmp.out answer/a09_array.out
	;;
        10)
		./myscanner < input/a10_error.rs >| tmp.out
                diff -y tmp.out answer/a10_error.out
	;;
        11)
		./myscanner < input/b01_auto_type_detection.rs >| tmp.out
		diff -y tmp.out answer/b01_auto_type_detection.out
	;;

        12)
		./myscanner < input/b02_loop.rs >| tmp.out
                diff -y tmp.out answer/b02_loop.out
	;;
        13)
		./myscanner < input/b03_foreach.rs >| tmp.out
                diff -y tmp.out answer/b03_foreach.out
	;;
        14)
		./myscanner < input/b04_2d_array.rs >| tmp.out
                diff -y tmp.out answer/b04_2d_array.out
	;;
        15)
		./myscanner < input/b05_slice.rs >| tmp.out
                diff -y tmp.out answer/b05_slice.out
	;;
esac





