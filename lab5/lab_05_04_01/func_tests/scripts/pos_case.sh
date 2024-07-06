#!/bin/bash

# проверка количества аргументов
if [ $# -lt 2 ]; then
	exit 1
fi

in_test=$1
out_test=$2
out_prog="out_prog.txt"
command="../../app.exe"
converter="./converter/converter.exe"

# Коды ошибок
test_p="0"
test_f="1"

if [ $# -ne 3 ]; then
	# command="$command $(cat "$3")"
	exit 1
fi

#И что он ругается на это? Это переменная, а не командаs
word=$(cat "$3" | cut -d' ' -f1)

if [ "$word" == "ft" ]; then
	file_source=$(cat "$3" | cut -d' ' -f2)
	prefix=$(cat "$3" | cut -d' ' -f4)
	command="$command ft $file_source $out_prog $prefix"
	$command
	error="$?"
elif [ "$word" == "sb" ]; then
	# file=$(cat "$3" | cut -d' ' -f2)
	# cat "$in_test" > ./tmp_prog.txt
	$converter t2b "$in_test" ./tmp_prog.txt
	command="$command sb ./tmp_prog.txt"
	$command
	error="$?"
	$converter b2t ./tmp_prog.txt $out_prog
fi

# $command < "$in_test" > "$out_prog"
# error="$?"


# проверка завершения программы 
if ! [ "$error" -eq 0 ]; then							# не нулевой код ошибки	(ошибка значит)
	exit "$test_f"
fi

# сравниваем выходные данные программы и данные в тесте
if ! ./comparator.sh "$out_prog" "$out_test" "$word"; then		# неверный тест, ибо ненулевой код выхода
	exit "$test_f"
else													# верный тест	
	exit "$test_p"
fi
