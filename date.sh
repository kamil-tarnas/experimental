#!/bin/bash
#take the number of commits as parameter or take base SHA as a parameter
#generate random seeds and time offsets from the specified or current data - git diff and wc -l to see how big should be the offsets? - different offsets for added in comparison to deleted lines? weights assigning mechanism?
#normalize the weight over some hours
#search for the commits git filter branch and change the dates randomly

#getopts for parameters
#TODO: Difference between author date and commiter date?
#TODO: Exit in case of lack of arguments (or pront help and exit)
#TODO: Restrict the arguments to be SHA or SHA convertible ("HEAD", tag, branch and so on)
#TODO: Mark local variables in functions with 'local'
#TODO: Parameters ca be passed to function foo() with a call 'foo "$arg"' or 'foo arg'

: '
for i in "$@"
do
case $i in
    -e=*|--extension=*)
    EXTENSION="${i#*=}"
    shift # past argument=value
    ;;  
    -s=*|--searchpath=*)
    SEARCHPATH="${i#*=}"
    shift # past argument=value
    ;;  
    -l=*|--lib=*)
    LIBPATH="${i#*=}"
    shift # past argument=value
    ;;  
    --default)
    DEFAULT=YES
    shift # past argument with no value
    ;;  
    *)  
          # unknown option
    ;;  
esac
done
'

#print the usage of this script
help()
{
   echo "Usage: date [SHA1] [SHA2]"
}

##if there is a lack of exactly two arguments that have been passed to the script
#if ! [ -n "$1" ] || ! [ -n "$2" ]; then
#   help
#   exit
#fi

#map for holding SHA and weight pair
declare -A weights
declare -A dates
declare -A normalizedWeights
declare -A normalizedHourOffsets
declare -a shas

#checks the number of commits given by SHA range
git_commitRange()
{
   number_of_commits=$(git log --oneline $2...$1 | wc -l)

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
  
   #generate a random integer of interval [0, 32]
   let random_factor=$RANDOM/1000
   
   #the importance of the commit - base is 100
   let weight=20*number_of_deleted_lines+80*number_of_added_lines+$random_factor

   #add weight to the map
   weights[$1]=$weight

   #debug
   echo "${weights["$1"]}" #does it need to be in parentheses?
   echo "${weights[dd71784357ead796e11f3e8581db4d629ab9cfe4]}"
   echo $weight
}

#input parameters should be a range of commits
git_storeShas()
{
   echo "jou"

   #print all the commits, extract the SHA value
   #shas[0]=$(git log --oneline $2...$1 | awk '{print $1}')
  
   #TODO: No such file or directory error! How to make it read from the stdout or the command on the right side
   #readarray -t shas < "$(git log --oneline $2...$1 | awk '{print $1}')"
   
   #that one reads a file (?)
   #IFS=$'\n' read -d '' -r -a shas < $(git log --oneline $2...$1 | awk '{print $1}')
   
   #add the SHA values to the array

   #print all values of the array
   echo ${shas[@]}

   #print index zero of the array
   echo ${shas[0]}
}


#for example supported format ISO 8601 2005-04-07T22:13:13
git_changeDates()
{
   #for every commit in the weights or for the number of commits
   git filter-branch --env-filter \
      'if [ $GIT_COMMIT = bc82ece256783b864854c3e85cac69f29e6630ee ]
      then
         export GIT_AUTHOR_DATE="Fri Jan 2 21:38:53 2009 -0800"
         export GIT_COMMITTER_DATE="Sat May 19 01:01:01 2007 -0700"
      fi'
}

#need to call it with $1 equal to commit SHA
calculateDate()
{
   time_localization=" +0100"
   date=$(LC_TIME=en_US date | sed -e 's/CET //')$time_localization
   echo $date

   #add date to the map
   dates[$1]=$date

   #debug
   echo "${dates["$1"]}"
   echo "${dates[dd71784357ead796e11f3e8581db4d629ab9cfe4]}"
   echo $date
}

#pass date as $1
modifyDate()
{
   hour=$(echo $1 | awk '{print $4}')
   echo $hour
}

#pass hour as a $1 parameter
modifyHour()
{
   echo "jou"
}

#passed is the timeframe offset set by the user
normalizeWeights()
{  
   echo "jou"
   #search for the highest and the lowest and spread it across the given time-window
   #accumulate weights across 
   #weights
   for i in "${!weights[@]}"
   do
      let "accumulatedWeights+=${weights[$i]}"
      echo $accumulatedWeights
   done

   #debug
   echo $accumulatedWeights
}

git_checkLines "$1" "$2"
calculateDate "$1"
modifyDate "$date"
normalizeWeights
git_storeShas "$1" "$2"
#git_changeDates
