# Do something for every file
#!/bin/bash

while read file
do
  name="${file##*/}"
  echo Processing file "$name"
  # Do stuff here
  cat $name
done < <( find . -iname '*.cpp*' )

# find -type f -print0 | xargs -n 1 -0 echo "your file: {} !"
# find . -exec <command> {} \;