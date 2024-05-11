#
# TLDR:
# - for each C binary test file `i` in `./tests` that matches the
# pattern `*_tests`
# - if file `i` exists and is a regular file,
#   - runs each C binary file in Valgrind
#   - if C binary run successfully in Valgrind,
#       - print `PASS`
#   - else print error with logs
#

echo "Running unit tests:"

for i in tests/*_tests
do
    if test -f $i
    then
        if $VALGRIND ./$i 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
        fi
    fi
done

echo ""
