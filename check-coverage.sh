#!/bin/bash --

## Build and measure the coverage with running tests
CXXFLAGS='-coverage' make test
./run_decbench.sh 

## Capture the coverage
lcov --capture --directory ./ --base-directory ./ --output-file coverage.info

## Exculude std library
lcov --remove coverage.info /usr/include/\* --output-file integer-encoding-lib-coverage.info

## Generate html
#genhtml --title integer_encoding_library --output-directory ./coverage integer-encoding-lib-coverage.info

