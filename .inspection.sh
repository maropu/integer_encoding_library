#!/bin/bash --

## Build and measure the coverage with running tests
CXXFLAGS='-coverage -g' make test

for TEST in `find ./ -name "*_utest" -type f`; do
  ./$TEST
done;

## Colloct test statistics
which lcov

if [ $? = 0 ]; then
lcov --capture --directory ./ --base-directory ./ \
         --output-file integer_coding.info
lcov --remove integer_coding.info /usr/include/\* \
         .utest/gtest-1.6.0/\* \
         --output-file integer_coding-coverage.info
genhtml --title integer_coding --output-directory \
         ./coverage integer_coding-coverage.info
fi

make clean

## Code policy checker
# which cpplint.py && find ./src ./tool -name '*.cpp' -type f | xargs cpplint.py

## Heap profiler
# if type -P valgrind > /dev/null; then
# CXXFLAGS='-g' make
# valgrind --tool=massif --max-snapshots=512 \
#                 --massif-out-file=massif.log \
#                 ./do_something
# ms_print massif.log > massif.profile
# make clean
# fi

