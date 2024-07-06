#!/bin/bash

echo "Input test number: "

read -r num

echo "Input variables: "

read -r variables

echo "Input args to file: "

read -r args

echo "Input result: "

read -r result

echo "$variables" > "./func_tests/data/pos_""$num""_in.txt"
echo "$args" > "./func_tests/data/pos_""$num""_args.txt"
echo "$result" > "./func_tests/data/pos_""$num""_out.txt"
