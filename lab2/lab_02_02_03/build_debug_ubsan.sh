#!/bin/bash

# gcc
clang -std=c99 -Wall -fsanitize=undefined -fno-omit-frame-pointer -g main.c -o app.exe
