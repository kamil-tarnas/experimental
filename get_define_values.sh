#!/bin/bash

# Usage:
# get_define_values.sh <the file with defines>
# get_define_values.sh pin_ids.h

# Result:
# You'll get the file *_unenigmatic, for example pin_ids.h_unenigmatic, which will contain
# the #define literal along with its decimal value

# Create directory for all temporary files
mkdir temp

# First of all strip the file of everything expect the #defines
cat $1 | sed -e '/#define.*/!d' > temp/$1_only_defines.c

# Get also the list of pure #define literals (the names, not the values)
cat temp/$1_only_defines.c | awk 'NR==1 {print;next};{print $2}' > temp/$1_without_defines.c

# Remove any leftover #defines not connected to defining a literal value (for example #ifndef counterparts)
sed -i '/#define/d' temp/$1_without_defines.c

# Concatenate the #define declarations with the just plain list of defines to feed 'gcc -E'
cat temp/$1_only_defines.c temp/$1_without_defines.c > temp/$1_gcc_feed.c

# Preprocess the $1_gcc_feed by the 'gcc -E' command (expanding the macros) and remove the fluff from the begining (#)
gcc -E temp/$1_gcc_feed.c | sed -e '/#/d' > temp/$1_preprocessed.c

# Prepend and append with std::cout call syntax
sed -e 's/^/std::cout<</' -e 's/$/<<std::endl;/' temp/$1_preprocessed.c > temp/$1_gcc_feed_pass_two.c

# Add main() and headers to compile the generated $1_gcc_feed_pass_two.c and run the compiled program
cat <(printf "#include <iostream>\nint main()\n{\n") temp/$1_gcc_feed_pass_two.c > temp/$1_gcc_feed_pass_two_final.c
echo "}" >> temp/$1_gcc_feed_pass_two_final.c

# Compile and run the program
g++ temp/$1_gcc_feed_pass_two_final.c -o temp/$1.out
temp/./$1.out > temp/$1_gcc_dump.c

# Merge line-by-line the #define names and decimal #define values
paste -d " " temp/$1_without_defines.c temp/$1_gcc_dump.c > $1_unenigmatic

# Remove the temporary directory
rm -rf temp