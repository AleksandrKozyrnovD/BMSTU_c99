#!/bin/bash

# проверка количества аргументов
if [ $# -lt 2 ]; then
	exit 1
fi

in_test=$1
in_test_name=$(basename "$in_test" .txt)
out_test=$2
out_prog="out/out_prog.txt"
command="./app.exe"
valgrind="valgrind --quiet --leak-check=yes --error-exitcode=1001"
logfile="./out/log.txt"

# Коды ошибок
test_p="0"
test_f="1"
# test_p_val_n="2"
# test_n_val_n="3"


if [ $# -gt 3 ]; then
	# command="$command $(cat "$3")"
	exit 1
fi

args=$(cat "$3")
# echo $args
command="${command} ${args}"

# $command < "$in_test" > "$out_prog"
# echo $command
$command > "$out_prog"
error="$?"

valtest="${valgrind} --log-file=${logfile} ${command}"
$valtest > "out/temp.txt"
var=$(cat $logfile)

# echo $var
if [[ -z "$var" ]]; then
    val_error=0
else
    val_error=2
    echo "${var}" > "${logfile}_${in_test_name}.txt"
fi
# echo $val_error
# echo $error

# if [ "$error" == "$val_error" ]; then
#     val_error="0"
# else
#     cat "${logfile}" > "${logfile}${in_test_name}.txt"   
#     val_error="2"
# fi
# val_error=$((error + val_error))


# проверка завершения программы 
if ! [ "$error" -eq 0 ]; then							# не нулевой код ошибки	(ошибка значит)
    exit $((test_f + val_error))
fi

# cat $out_prog
# cat $out_test
# сравниваем выходные данные программы и данные в тесте
if ! ./func_tests/scripts/comparator.sh "$out_prog" "$out_test"; then		# неверный тест, ибо ненулевой код выхода
    # echo $((error + val_error + 1))
    exit $((val_error + test_f))
else													# верный тест	
	# exit 0
    exit $((val_error + test_p))
fi
