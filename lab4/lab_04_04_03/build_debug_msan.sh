#!/bin/bash

# gcc
clang -std=c99 -Wall -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g ./*.c -o app.exe
