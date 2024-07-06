#!/bin/bash

# проверка количества аргументов
if [ $# -lt 1 ]; then
	exit 1
fi

test_p="0"
test_f="1"

in_test=$1
in_test_name=$(basename "$in_test" .txt)
out_prog="out/out_prog.txt"
command="./app.exe"
valgrind="valgrind --quiet --leak-check=yes --error-exitcode=-1"
logfile="./out/log.txt"

args=$(cat "$2")
# echo $args
command="${command} ${args}"

# $command < "$in_test" > "$out_prog"
$command > "$out_prog"
error="$?"

valtest="${valgrind} --log-file=${logfile} ${command}"
$valtest > "out/temp.txt"
# val_error="$?"
#
# # echo $error
# # echo $val_error
# if [ "$error" == "$val_error" ]; then
#     val_error="0"
# else
#     cat "${logfile}" > "${logfile}${in_test_name}.txt"   
#     val_error="2"
# fi

var=$(cat $logfile)

# echo $var
if [[ -z "$var" ]]; then
    val_error=0
else
    val_error=2
    echo "${var}" > "${logfile}_${in_test_name}.txt"
fi

# echo $val_error

# проверка завершения программы
if [ "$error" -eq 0 ]; then								# нулевой код ошибки, то есть программа верно сработала на неверных данных, да?
	# exit "$test_f"
    exit $((test_f + val_error))
else													# не нулевой код ошибки	
	# exit "$test_p"
    exit $((test_p + val_error))
fi
