#!/bin/bash

# gcc
clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-conversion -Wfloat-equal -fsanitize=address -fno-omit-frame-pointer -g ./*.c -o app.exe
