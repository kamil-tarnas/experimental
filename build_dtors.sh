#!/bin/bash	 
find . -name "*global_dtors*.cpp" -exec g++ -std=c++17 -o global {} +
