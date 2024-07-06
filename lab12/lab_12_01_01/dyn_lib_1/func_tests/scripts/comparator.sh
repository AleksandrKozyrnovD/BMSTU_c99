#!/bin/bash

# проверка количества аргументов
if [ $# -ne 2 ]; then
    exit 1
fi

prog_result=$1
test_expectations=$2

# echo ====
# echo $1
# cat $1
# echo ====
# echo $2
# cat $2
# echo ====
# маска для данной задачи
#mask="[+-]?[0-9][0-9]*.?[0-9]*"

# записываем результат grep в соответсвующие переменные
#clean_prog_result=$(grep -Eo "$mask" "$prog_result")
#clean_test_expectations=$(grep -Eo "$mask" "$test_expectations")

# num1=$(grep -oE '[-]?[0-9]*\.?[0-9]*' "$prog_result")
# num2=$(grep -oE '[-]?[0-9]*\.?[0-9]*' "$test_expectations")
# # сравниваем их
# if [ "$num1" != "$num2" ]; then
#     exit 1
# fi
#
# exit 0

res=$(diff "$prog_result" "$test_expectations")
# echo $res
# сравниваем их
if [ "$res" == "" ]; then
    exit 0
fi

exit 1
