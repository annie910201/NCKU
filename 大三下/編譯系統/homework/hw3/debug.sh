#!/bin/bash
make clean && make all
path=""
case $1 in
	0)
		path="a00_helloWorld_comment"
	;;
	1)
		path="a01_arithmetic"
	;;
	2)
		path="a02_precedence"
	;;
	3)
		path="a03_scope"
	;;
	4)
		path="a04_assigment"
	;;
	5)
		path="a05_casting"
	;;
	6)
		path="a06_if"
	;;
	7)
		path="a07_while"
	;;
	8)
		path="a08_function"
	;;
	9)
		path="a09_array"
	;;
	10)
		path="a10_error"
	;;
	11)
		path="b01_auto_type_detection"
	;;
	12)
		path="b02_loop"
	;;
	13)
		path="b03_foreach"
	;;
	14)
		path="b04_2d_array"
	;;
	15)
		path="b05_slice"
	;;
esac

input_path="input/${path}.rs"
output_path="answer/${path}.out"

./mycompiler < ${input_path} > parse.out
java -jar jasmin.jar hw3.j
java Main > tmp.out
diff -f tmp.out ${output_path}
