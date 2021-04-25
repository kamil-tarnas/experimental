#!/bin/bash

isSpongeInstalled=$(which sponge)

if [ -n "$isSpongeInstalled" ]
then
  for i in $(find . -type f \( -name "*.cpp" -o -name "*.hpp" \)); do
    expand -i -t 2 "$i" | sponge "$i"
  done
else
   echo "'sponge' from moreutils is not installed!"
fi
