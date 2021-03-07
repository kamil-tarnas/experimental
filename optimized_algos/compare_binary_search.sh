#!/bin/bash

for i in {1..10000}; do
3>>binary_search_results.log perf stat --log-fd 3 --append ./binary_search_standard > /dev/null
done

numberOfLines=$(grep cycles[^-] binary_search_results.log | awk '{print $1}' | wc -l)
sumOfCycles=$(grep cycles[^-] binary_search_results.log | awk '{sum += $1} END {print sum}')

echo $numberOfLines
echo $sumOfCycles
#let value=sumOfCycles/numberOfLines

# https://stackoverflow.com/questions/12882611/how-to-get-bc-to-handle-numbers-in-scientific-aka-exponential-notation
sumOfCyclesBc=$(sed -E 's/([+-]?[0-9.]+)[eE]\+?(-?)([0-9]+)/(\1*10^\2\3)/g' <<<"$sumOfCycles")

echo "The average execution time is: $(echo "scale=2; ($sumOfCyclesBc/$numberOfLines)" | bc -l)"
