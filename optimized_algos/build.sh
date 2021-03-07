#!/bin/bash
# for all the algos make the binaries with -g flag
# TODO: Make a rule for Eclipse "Build Configurations" for easy debugging
g++ binary_search_recursive.c binary_search_recursive_test.cpp -o binary_search_recursive -std=c++11 -g
