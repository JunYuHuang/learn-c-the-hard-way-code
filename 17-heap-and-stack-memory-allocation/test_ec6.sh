#!/usr/bin/env bash

# stop script if any command has an error
set -e

# compile
echo "> Compile the source code"
make ec6

# variables
db="ec6.db"

# create the database if needed
echo "> Create the database if needed"
./ec6 $db c

# reset the database
echo "> Reset the database"
./ec6 $db d 0
./ec6 $db d 1
./ec6 $db d 2

# test set row
echo "> Test setting database rows"
./ec6 $db s 0 lol he@he.xd
./ec6 $db s 1 zed zed@zedshaw.com
./ec6 $db s 2 frank frank@zedshaw.com
./ec6 $db l

# test get row
echo "> Test getting a database row"
./ec6 $db g 0

# test delete row
echo "> Test deleting a database row"
./ec6 $db d 1
./ec6 $db l
