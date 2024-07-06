#!/bin/bash

files="./func_tests/scripts/*.txt *.exe *.o *.out *.gcno *.gcda *.gcov vgcore* out_prog.txt"

for file in $files; do
	rm -f "${file}" 
done
