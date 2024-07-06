#!/bin/bash

echo "Input test number: "

read -r num

read -r -d "_" -p "Input variables: " variables
echo ""

echo "$variables" > "./func_tests/data/neg_""$num""_in.txt"
