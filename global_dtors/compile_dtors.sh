#!/bin/bash
#git ls-files . | grep 'global_dtors' | xargs git add
find . -name '*global_dtors*.cpp' | xargs g++ -o global_dtors

#Try different linkers and see the result
