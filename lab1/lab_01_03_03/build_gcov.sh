#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -c --coverage main.c
gcc main.o -o app.exe --coverage -lm