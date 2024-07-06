#!/bin/bash

home_path="./*.sh"
scripts="./func_tests/scripts/*.sh"

for file in $home_path $scripts ; do
	shellcheck "$file"
done
