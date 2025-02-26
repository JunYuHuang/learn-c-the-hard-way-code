# compile the lib file and make the .so
# you may need -fPIC here on some platforms. add that if you get an
# error
cc -c libex29.c -o libex29.o -fPIC
cc -shared -o libex29.so libex29.o

# make the loader program
cc -Wall -g -DNDEBUG ex29.c -ldl -o ex29

# try it out with some things that work
ex29 ./libex29.so print_a_message "hello there"
# -> -bash: ex29: command not found
./ex29 ./libex29.so uppercase "hello there"
# -> HELLO THERE
./ex29 ./libex29.so lowercase "HELLO tHeRe"
# -> hello there
./ex29 ./libex29.so fail_on_purpose "i fail"
# -> [ERROR] (ex29.c:23: errno: None) Function fail_on_purpose return 1 for data: i fail

# try to give it bad args
./ex29 ./libex29.so fail_on_purpose
# -> [ERROR] (ex29.c:11: errno: None) USAGE: ex29 libex29.so function data

# try calling a function that is not there
./ex29 ./libex29.so adfasfasdf asdfadff
# -> [ERROR] (ex29.c:20: errno: None) Did not find adfasfasdf function in the library libex29.so: dlsym(0x1076009b0, adfasfasdf):symbol not found

# try loading a .so that is not there
./ex29 ./libex.so adfasfasdf asdfadfas
# -> [ERROR] (ex29.c:17: errno: No such file or directory) Failed to open the library libex.so: dlopen(libex.so, 2): image not found
