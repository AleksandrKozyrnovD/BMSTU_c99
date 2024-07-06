#!/bin/bash

# проверка количества аргументов
if [ $# -ne 2 ]; then
    exit 1
fi

prog_result=$1
test_expectations=$2

# маска для данной задачи
mask="[+-]?[0-9][0-9]*.?[0-9]*"

# записываем результат grep в соответсвующие переменные
clean_prog_result=$(grep -Eo "$mask" "$prog_result")
clean_test_expectations=$(grep -Eo "$mask" "$test_expectations")

# сравниваем их
if [ "$clean_prog_result" != "$clean_test_expectations" ]; then
    exit 1
fi

exit 0