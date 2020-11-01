#!/bin/bash
gcc restrict.c -o restrict -O3; gcc restrict.c -S -O3; objdump -d restrict | tee restrict.dump
