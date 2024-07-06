#!/bin/bash

echo "Input test number: "

read -r num

echo "Input variables: "

read -r variables

echo "$variables" > "./func_tests/data/neg_""$num""_in.txt"
