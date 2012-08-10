#!/bin/bash --

## Build and measure the coverage with running tests
CXXFLAGS='-coverage' make test

for TEST in `find ./ -name "*_utest" -type f`; do
  ./$TEST
done;

lcov --capture --directory ./ --base-directory ./ \
         --output-file integer_coding.info
lcov --remove integer_coding.info /usr/include/\* \
         .utest/gtest-1.6.0/\* \
         --output-file integer_coding-coverage.info
genhtml --title integer_coding --output-directory \
         ./coverage integer_coding-coverage.info

make clean

## Code policy checker
# which cpplint.py && find ./src ./tool -name '*.cpp' -type f | xargs cpplint.py

