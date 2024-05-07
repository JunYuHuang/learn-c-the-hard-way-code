#!/bin/bash

c_binary=logfind

# Note: below if-clause runs into `Permission denied` issue
# delete the binary output file if it exists
# if [[ -f "$c_binary" ]]; then
#     rm $c_binary
# fi

clear
echo ">>>>>>>>>>> Running tests for '$c_binary.c'"
echo ""

# compile it
echo "> Compile it"
echo "\$ make $c_binary"
make $c_binary
echo ""

# Feature 1: run it with no (extra) arguments
echo "> Feature 1: run it with no (extra) arguments"
echo "\$ ./$c_binary"
./"$c_binary"
echo ""

# Feature 1: run it with 1 (extra) argument
echo "> Feature 1: run it with 1 (extra) argument"
echo "\$ ./$c_binary MAX"
./"$c_binary" MAX
echo ""

# Feature 1: run it with 2 (extra) arguments
echo "> Feature 1: run it with 2 (extra) arguments"
echo "\$ ./$c_binary MAX error"
./"$c_binary" MAX error
echo ""

# Feature 2: run it with 1 (extra) argument
echo "> Feature 2: run it with 1 (extra) argument"
echo "\$ ./$c_binary -o"
./"$c_binary" -o
echo ""

# Feature 3: run it with 2 (extra) arguments
echo "> Feature 2: run it with 2 (extra) arguments"
echo "\$ ./$c_binary -o MAX ERROR"
./"$c_binary" -o MAX ERROR
echo ""

# Feature 3: run it with 1 (extra) argument
echo "> Feature 2: run it with 2 (extra) argument"
echo "\$ ./$c_binary -o ERROR"
./"$c_binary" -o ERROR
echo ""
