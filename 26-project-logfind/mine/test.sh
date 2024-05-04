#!/bin/bash

c_binary=logfind

# Note: below if-clause runs into `Permission denied` issue
# delete the binary output file if it exists
# if [[ -f "$c_binary" ]]; then
#     rm $c_binary
# fi

# compile it
make $c_binary

# run it
./"$c_binary"
