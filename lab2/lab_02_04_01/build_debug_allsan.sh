#!/bin/bash

# gcc
clang -std=c99 -Wall -fsanitize=address -fno-omit-frame-pointer -g main.c -o app.exe

cmd="./testing.sh"

$cmd
rc=$?
if [ ! $rc ]; then
    ./clean.sh
    exit 1
fi

clang -std=c99 -Wall -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g main.c -o app.exe
$cmd
rc=$?
if [ ! $rc ]; then
    ./clean.sh
    exit 1
fi

clang -std=c99 -Wall -fsanitize=undefined -fno-omit-frame-pointer -g main.c -o app.exe
$cmd
rc=$?
if [ ! $rc ]; then
    ./clean.sh
    exit 1
fi

./clean.sh

