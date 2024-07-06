#!/bin/bash

echo "Input test number: "

read -r num


read -r -d "_" -p "Input variables: " variables
echo ""

read -r -d "_" -p "Input result: " result
echo ""

echo "$variables" > "./func_tests/data/pos_""$num""_in.txt"
echo "$result" > "./func_tests/data/pos_""$num""_out.txt"
