#!/bin/bash

# проверка количества аргументов
if [ $# -lt 2 ]; then
	exit 1
fi

# in_test=$1
out_test=$2
out_prog="out_prog.txt"
command="./app.exe"

# Коды ошибок
test_p="0"
test_f="1"


args=$(cat "$3")
# прикрепляем аргументы командной строки к команде вызова бинарного файла
command="${command} ${args}"

$command > "$out_prog"
error="$?"
# echo $error
# проверка завершения программы
if ! [ "$error" -eq 0 ]; then							# не нулевой код ошибки	(ошибка значит, лол)
	exit "$test_f"
fi

# сравниваем выходные данные программы и данные в тесте


if ! ./func_tests/scripts/comparator.sh "$out_prog" "$out_test"; then		# неверный тест, ибо ненулевой код выхода
	exit "$test_f"
else													# верный тест	
	exit "$test_p"
fi
