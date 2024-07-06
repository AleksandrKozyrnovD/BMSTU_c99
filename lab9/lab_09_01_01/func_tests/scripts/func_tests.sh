#!/bin/bash


#Цвета
RESET='\033[0m' #reset colors
RED='\033[1;31m'
GREEN="\033[1;32m"


# количество ошибочных тестов (служебная информация)
count_errors=0
pos=0
neg=0

# Коды ошибок
valgrind="0" #Смотрим использование валгринд
if [ "$1" == "--valgrind" ]; then
    valgrind="1"
fi
# echo $1
# echo $offset
test_p="0" #val passed
test_f="1" #val passed
test_p_val_n="2"
test_f_val_n="3"

# обработка позитивных тестов
# наша маска на положительные тесты
files="./func_tests/data/pos_??_in.txt"
for file_in in $files; do

	# находим номер теста
	number=$(echo "$file_in" | grep -o "[0-9]*")

	# проверка на наличие тестов (то есть если есть цифра в файле)
	if [ -z "$number" ]; then
		break
	fi

	# если мы дошли до этой строчки, значит, есть положительные файлы, поэтому меняем флаг.
	pos=1

	# названия выходного тестового файла
	file_out="./func_tests/data/pos_""$number""_out.txt"
	file_args="./func_tests/data/pos_""$number""_args.txt"

	# если выходной файл существует, передаем входной и выходной файлы 
	# в pos_case.sh

	# если не существует, то считаем тест проваленным и переходим к
	# следующему тесту

	if [ -f "$file_out" ]; then
		command="./func_tests/scripts/pos_case.sh ""$file_in ""$file_out"
	else
		echo "POS_""$number"": FAILED"
		count_errors=$((count_errors + 1))
		continue
	fi

	# если существует файл с аргументами, добавляем его в pos_case.sh
	if [ -f "$file_args" ]; then 
		command="$command ""$file_args"
	fi
	
	$command
    error="$?"
    # echo $error

	# выводим результат в соответствии с кодом ошибки ./pos_case.sh
    if [ "$valgrind" == "1" ]; then
        if [ "$error" -eq "$test_p" ]; then
            echo -e "POS_""$number"": ${GREEN}PASSED${RESET}"" ==<--->== Memory: ${GREEN}PASSED${RESET}"
        fi
        if [ "$error" -eq "$test_f" ]; then
            echo -e "POS_""$number"": ${RED}FAILED${RESET}"" ==<--->== Memory: ${GREEN}PASSED${RESET}"
            count_errors=$((count_errors + 1))
        fi
        if [ "$error" -eq "$test_p_val_n" ]; then
            echo -e "POS_""$number"": ${GREEN}PASSED${RESET}"" ==<--->== Memory: ${RED}FAILED${RESET}"
            count_errors=$((count_errors + 1))
        fi
        if [ "$error" -eq "$test_f_val_n" ]; then
            echo -e "POS_""$number"": ${RED}FAILED${RESET}"" ==<--->== Memory: ${RED}FAILED${RESET}"
            count_errors=$((count_errors + 1))
        fi
    else
        if [ "$error" -eq "$test_p" ]; then
            echo -e "POS_""$number"": ${GREEN}PASSED${RESET}"
        fi
        if [ "$error" -eq "$test_f" ]; then
            echo -e "POS_""$number"": ${RED}FAILED${RESET}"
            count_errors=$((count_errors + 1))
        fi
        if [ "$error" -eq "$test_p_val_n" ]; then
            echo -e "POS_""$number"": ${RED}FAILED${RESET}"
            count_errors=$((count_errors + 1))
        fi
        if [ "$error" -eq "$test_f_val_n" ]; then
            echo -e "POS_""$number"": ${RED}FAILED${RESET}"
            count_errors=$((count_errors + 1))
        fi
    fi

done

# обработка негативных тестов 
# маска отрицательных тестов
files="./func_tests/data/neg_??_in.txt"
for file_in in $files; do

	# находим номер теста
	number=$(echo "$file_in" | grep -o "[0-9]*")

	# проверка на наличие тестов (то есть наличие цифры в тесте)
	if [ -z "$number" ]; then
		break
	fi

	# если мы дошли до этой строчки, значит, есть отрицательные файлы, поэтому меняем флаг.
	neg=1

	# передаем входной тестовый файл в ./neg_case.sh
	command="./func_tests/scripts/neg_case.sh ""$file_in"
	file_args="./func_tests/data/neg_""$number""_args.txt"

	if [ -f "$file_args" ]; then 
		command="$command ""$file_args"
	fi
    
    # echo $command
	$command
	error="$?"
    # echo $error

	# выводим результат в соответствии с кодом ошибки ./neg_case.sh
    if [ "$valgrind" == "1" ]; then
        if [ "$error" -eq "$test_p" ]; then
            echo -e "NEG_""$number"": ${GREEN}PASSED${RESET}"" ==<--->== Memory: ${GREEN}PASSED${RESET}"
        fi
        if [ "$error" -eq "$test_f" ]; then
            echo -e "NEG_""$number"": ${RED}FAILED${RESET}"" ==<--->== Memory: ${GREEN}PASSED${RESET}"
            count_errors=$((count_errors + 1))
        fi
        if [ "$error" -eq "$test_p_val_n" ]; then
            echo -e "NEG_""$number"": ${GREEN}PASSED${RESET}"" ==<--->== Memory: ${RED}FAILED${RESET}"
            count_errors=$((count_errors + 1))
        fi
        if [ "$error" -eq "$test_f_val_n" ]; then
            echo -e "NEG_""$number"": ${RED}FAILED${RESET}"" ==<--->== Memory: ${RED}FAILED${RESET}"
            count_errors=$((count_errors + 1))
        fi
    else
        if [ "$error" -eq "$test_p" ]; then
            echo -e "NEG_""$number"": ${GREEN}PASSED${RESET}"
        fi
        if [ "$error" -eq "$test_f" ]; then
            echo -e "NEG_""$number"": ${RED}FAILED${RESET}"
            count_errors=$((count_errors + 1))
        fi
        if [ "$error" -eq "$test_p_val_n" ]; then
            echo -e "NEG_""$number"": ${GREEN}FAILED${RESET}"
            count_errors=$((count_errors + 1))
        fi
        if [ "$error" -eq "$test_f_val_n" ]; then
            echo -e "NEG_""$number"": ${RED}FAILED${RESET}"
            count_errors=$((count_errors + 1))
        fi
    fi
done

# вспомогательная информация

if [ "$count_errors" -eq 0 ]; then
	echo "All tests passed." 
else
	echo "Failed $count_errors tests." 
fi

if [ "$pos" -eq 0 ]; then
	echo "No positive tests." 
fi

if [ "$neg" -eq 0 ]; then 
	echo "No negative tests."
fi

exit "$count_errors"
