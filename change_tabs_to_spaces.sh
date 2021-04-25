#!/bin/bash
for i in $(find . -type f \( -name "*.cpp" -o -name "*.hpp" \)); do
  expand -i -t 2 "$i" | sponge "$i"
done
