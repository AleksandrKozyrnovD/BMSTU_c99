#!/bin/bash

echo "Input test number: "

read -r num

echo "Input variables: "

read -r variables

echo "Input args to file: "

read -r args

echo "$variables" > "./func_tests/data/neg_""$num""_in.txt"
echo "$args" > "./func_tests/data/neg_""$num""_args.txt"