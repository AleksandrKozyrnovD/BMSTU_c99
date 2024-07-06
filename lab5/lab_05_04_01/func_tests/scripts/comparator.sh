#!/bin/bash

# проверка количества аргументов
if [ $# -ne 3 ]; then
    exit 1
fi

prog_result=$1
test_expectations=$2

# маска для данной задачи
#mask="[+-]?[0-9][0-9]*.?[0-9]*"

# записываем результат grep в соответсвующие переменные
#clean_prog_result=$(grep -Eo "$mask" "$prog_result")
#clean_test_expectations=$(grep -Eo "$mask" "$test_expectations")

# num1=$(grep -oE '*' "$prog_result")
# num2=$(grep -oE '*' "$test_expectations")

res=$(diff "$prog_result" "$test_expectations")
# сравниваем их
if [ "$res" == "" ]; then
    exit 0
fi

exit 1
