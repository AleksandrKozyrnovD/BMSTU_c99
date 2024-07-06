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
	exit 1
fi

#Берем ключ командной строки
word=$(cat "$3" | cut -d' ' -f1)

# command="$command $(cat "$3")"
#проверка на совпадение ключа командной строки
if [ "$word" == "s" ]; then
	# echo $in_test
	$converter t2b "$in_test" ./input.txt
	../../app.exe s ./input.txt
	$converter b2t ./input.txt $out_prog
	# $command
	error="$?"
	# cat $out_prog
elif [ "$word" == "p" ]; then
	$converter t2b "$in_test" ./input.txt
	command="$command p ./input.txt"
	$command > "$out_prog"
	error="$?"
elif [ "$word" == "c" ]; then
	cat "$in_test" > ./input.txt
	number=$(cat "$3" | cut -d' ' -f2)
	command="$command c $number ./input.txt"
	# echo $command
	$command
	error="$?"
	$converter b2t ./input.txt $out_prog
fi


# $command < "$in_test" > "$out_prog"
# $command
# error="$?"

# проверка завершения программы
if ! [ "$error" -eq 0 ]; then							# не нулевой код ошибки	(ошибка значит, лол)
	exit "$test_f"
fi

# сравниваем выходные данные программы и данные в тесте


if ! ./comparator.sh "$out_prog" "$out_test"; then		# неверный тест, ибо ненулевой код выхода
	exit "$test_f"
else													# верный тест	
	exit "$test_p"
fi
