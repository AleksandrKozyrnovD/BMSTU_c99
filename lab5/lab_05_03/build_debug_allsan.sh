#!/bin/bash

# gcc

cmd="./testing.sh"

./build_debug_asan.sh
$cmd
rc=$?
if [ ! $rc ]; then
    ./clean.sh
    exit 1
fi

./build_debug_msan.sh
$cmd
rc=$?
if [ ! $rc ]; then
    ./clean.sh
    exit 1
fi

./build_debug_ubsan.sh
$cmd
rc=$?
if [ ! $rc ]; then
    ./clean.sh
    exit 1
fi

./clean.sh

