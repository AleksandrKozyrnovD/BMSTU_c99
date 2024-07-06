#!/bin/bash

echo "Input test number: "

read -r num


read -r -d "-" -p "Input variables: " variables
echo ""

read -r -d "-" -p "Input result: " result
echo ""

result="Result: "$result

echo "$variables" > "./func_tests/data/pos_""$num""_in.txt"
echo "$result" > "./func_tests/data/pos_""$num""_out.txt"
