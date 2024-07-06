#!/bin/bash

gcc -std=c99 -Werror -Wextra -Wpedantic -Wall -Wvla -o converter.exe ./*.c
