#
# BUILD & LINK
#

# compile the lib file and make the .so
# you may need -fPIC here on some platforms. add that if you get an
# error
cc -c libex29.c -o libex29.o -fPIC
cc -shared -o libex29.so libex29.o

# make the loader program
cc -Wall -g -DNDEBUG ex29.c -ldl -o ex29


#
# TESTS
#

./ex29 ./libex29.so print_a_message "hello there" 0
# -> should fail with some error message(s)

./ex29 ./libex29.so print_a_message "hello there" 5
# -> should fail with some error message(s)

./ex29 ./libex29.so print_a_message "hello there" 12
# -> should fail with some error message(s)

# try it out with some things that work
./ex29 ./libex29.so print_a_message "hello there" 11
# -> `A STRING: hello there`

./ex29 ./libex29.so uppercase "hello there" 11
# -> `HELLO THERE`

./ex29 ./libex29.so lowercase "HELLO tHeRe" 11
# -> `hello there`

./ex29 ./libex29.so fail_on_purpose "i fail" 6
# -> should fail with some error message(s)

# try to give it bad args
./ex29 ./libex29.so fail_on_purpose
# -> should fail with some error message(s)

# try calling a function that is not there
./ex29 ./libex29.so adfasfasdf asdfadff 8
# -> should fail with some error message(s)

# try loading a .so that is not there
./ex29 ./libex.so adfasfasdf asdfadfas 9
# -> should fail with some error message(s)
