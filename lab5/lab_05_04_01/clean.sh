#!/bin/bash

files="./func_tests/scripts/*.txt ./func_tests/scripts/converter/*.exe *.exe *.o *.out *.gcno *.gcda *.gcov"

for file in $files; do
	rm -f "$file" 
done