#!/bin/bash

echo "Input test number: "

read -r num

echo "Input variables: "

read -r variables

echo "Input result: "

read -r result

echo "$variables" > "./func_tests/data/pos_""$num""_in.txt"
echo "$result" > "./func_tests/data/pos_""$num""_out.txt"
