#!/bin/bash --

## Build and measure the coverage with running tests
CXXFLAGS='-coverage' make check
./test_run.sh

## Capture the coverage
lcov --capture --directory ./ --base-directory ./ --output-file temp.info

## Exculude std library
lcov --remove temp.info /usr/include/\* --output-file integer-encoding-lib-coverage.info

## Generate html
genhtml --title integer-encoding-lib --output-directory ./coverage integer-encoding-lib-coverage.info

