#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -c --coverage ./*.c
gcc ./*.o -o app.exe --coverage -lm