#map for holding SHA and weight pair
declare -A weights

git_commitRange()
{
   number_of_commits=$(git log $2...$1 | wc -l)

   #debug
   echo $number_of_commits
}

#checks the number of lines added in between commits given by SHA arguments, third argument is a 
git_checkLines()
{
   number_of_deleted_lines=$(git diff $2...$1 | grep "^\-[^-].*" | wc -l)
   number_of_added_lines=$(git diff $2...$1 | grep "^\+[^+].*" | wc -l)

   #debug
   echo $number_of_deleted_lines
   echo $number_of_added_lines
   
   #the importance of the commit - base is 100
   let weight=20*number_of_deleted_lines+80*number_of_added_lines

   #add weight to the map
   weights[$1]=$weight

   #debug
   echo "${weights["$1"]}"
   echo "${weights[dd71784357ead796e11f3e8581db4d629ab9cfe4]}"
   echo $weight
}

#normalizeWeitght()
#{
#   #search for the highest and the lowest and spread it across the given time-window
#}

git_checkLines "$1" "$2"
