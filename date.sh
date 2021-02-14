#!/bin/bash
#take the number of commits as parameter or take base SHA as a parameter
#generate random seeds and time offsets from the specified or current data - git diff and wc -l to see how big should be the offsets? - different offsets for added in comparison to deleted lines? weights assigning mechanism?
#normalize the weight over some hours
#search for the commits git filter branch and change the dates randomly
#TODO: Make debug flag that could enable specific logs (like --debug flag) 
#https://stackoverflow.com/questions/5972491/how-to-enable-or-disable-multiple-echo-statements-in-bash-ecript

#Currently supporting only one commit (?)

#getopts for parameters
#TODO: Difference between author date and commiter date?
#TODO: Exit in case of lack of arguments (or pront help and exit)
#TODO: Restrict the arguments to be SHA or SHA convertible ("HEAD", tag, branch and so on)
#TODO: Mark local variables in functions with 'local'
#TODO: Parameters ca be passed to function foo() with a call 'foo "$arg"' or 'foo arg'

# API design:
# MVP version:
# ./date SHA1 SHA2 18:00-19:00
# distribute the work over the hours...
# Need to distribute muliple commits over the hours

#                   TOP COMMIT (newer one)                  BOTTOM COMMIT (the older one)
# ./date.sh 1e17200de52e03f47f99bfe8e358f102ad593eba dab17a71eef29c6091d660c80eb03ef0a510db3f
# ./date.sh e9888fe52a7056abae4eb30c862fc04893f03a38 ae0bd2f096ab2d14f5bf982dd7433fc57c7ee081

: '

kamil@kamil-TP300LA:~/experimental$ ./date.sh 1e17200de52e03f47f99bfe8e358f102ad593eba dab17a71eef29c6091d660c80eb03ef0a510db3f

#here - to the git log command the order of commits does not matter...
kamil@kamil-TP300LA:~/experimental$ git log --oneline dab17a71eef29c6091d660c80eb03ef0a510db3f...1e17200de52e03f47f99bfe8e358f102ad593eba
1e17200 Making overflow_calculator.cpp compile
853212c Renaming sin, adding precoding and Barnsley plot
196c56d Adding ready #define_inside_macro
1f48006 Adding empty #define_inside_macro.cpp
dab17a7 (parent one)
'

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

#The map for holding SHA and weight pair
declare -A weights
declare -A dates

declare -A normalizedWeights
declare -A normalizedHourOffsets

#The array of SHAs in the range of requested commits (first index is the parent of the first commit that is processed)
declare -a shas

#Reading parameters
sha1=$1
sha2=$2
staring_hour=$3
ending_hour=$4

#checks the number of commits given by SHA range
git_commitRange()
{
   number_of_commits=$(git log --oneline $2...$1 | wc -l)

   #debug
   echo "Number of commits is: "$number_of_commits
   echo $number_of_commits
}

#checks the number of lines added in between commits given by SHA arguments, third argument is a 
git_checkLines()
{
  echo "Checking lines..."
  number_of_deleted_lines=$(git diff $2...$1 | grep "^\-[^-].*" | wc -l)
  number_of_added_lines=$(git diff $2...$1 | grep "^\+[^+].*" | wc -l)

  #debug
  echo "Number of deleted lines is: "$number_of_deleted_lines
  echo "Number of added lines is: "$number_of_added_lines
  
  #generate a random integer of interval [0, 32] #TODO: Random factor should probably be added later
  let random_factor=$RANDOM/1000
   
  #the importance of the commit - base is 100 - is not normalized currently
  let weight=20*number_of_deleted_lines+80*number_of_added_lines+$random_factor

  #add weight to the map
  weights[$1]=$weight

  #debug
  echo "Weight of the commit $1 is: ""${weights["$1"]}" #does it need to be in parentheses?
  #echo "${weights[dd71784357ead796e11f3e8581db4d629ab9cfe4]}"
}

#input parameters should be a range of commits
git_storeShas()
{
  echo "Storing SHAs..."
  
  #Get the parent of the first commit to be processed
  parent=$(git log --oneline $2~1...$2 | awk '{print $1}')
  
  #Read the SHAs to the array in reverse order, so the last element in the array is the commit on the top
  commits=($(git log --reverse --oneline $2...$1 | awk '{print $1}'))
  
  #Merge the parent and commits to be processed into one array
  shas=("$parent" "${commits[@]}")
  
  #Get the parent of the first commit and push it into the begining of the array
  #git log --oneline ae0bd2f096ab2d14f5bf982dd7433fc57c7ee081~1..ae0bd2f096ab2d14f5bf982dd7433fc57c7ee081
  
  echo "The processed commits are: "${shas[@]}" (first ${shas[0]} is a parent of all the changes, ${shas[-1]} is the latest, top commit)"
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
  echo "Calulating date..."
  
  #Calculate the current date
  time_localization=" +0100"
  date=$(LC_TIME=en_US date | sed -e 's/CET //')$time_localization
  
  #Sun Feb 14 14:01:04 2021 +0100 as in git log (?)
  echo $date
  
  declare -a dateDecomposed
  dateDecomposed=($date)
  
  #dateDecomposed[3]+=1;
  echo "Decomposed date is: "${dateDecomposed[@]}""
  
  declare -a hourDecomposed
  IFS=":" read -a hourDecomposed <<< ${dateDecomposed[3]}
  echo "Decomposed hour is       : "${hourDecomposed[@]}""
  
  #Calculate the interval to seconds and distribute over the commits...
  #Calculate the new decomposed hour #TODO: Calculate the exact value...
  let "hourDecomposed[0]+=1"
  let "hourDecomposed[1]+=30"
  let "hourDecomposed[2]+=23"
  echo "New decomposed hour is   : "${hourDecomposed[@]}""
  
  #dateDecomposed
  #newDate
  
  #add date to the map #TODO: Needs calculations of the new date!!!
  dates[$1]=$date

  #debug
  echo "The [date of the commit is] THE CURRENT DATE IS: ""${dates["$1"]}"
}

#pass date as $1
modifyDate()
{
  #$ date -u -d @360 +'%-Mm %-Ss'
  #6m 0s

  #This is extracting the hour currently
  hour=$(echo $1 | awk '{print $4}')
  echo $hour
}

#pass hour as a $1 parameter
modifyHour()
{
   echo "Modifying hour..."
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
      echo "Accumulated weight during iteration $i is: "$accumulatedWeights
   done

   #debug
   echo "The final results for weight accululation is: "$accumulatedWeights
   
   #Print the share of every commit in the total workload #TODO: Add it into the -A map of normalized weights?
   for i in "${!weights[@]}"
   do
     echo "The share of weight of $i commit in total weight is $(echo "scale=2; 
          (100*${weights[$i]}/$accumulatedWeights)" | bc -l)%"
   done

}

#Check the range of commits to be processed
git_commitRange "$sha1" "$sha2"

#Firstly, extract the commits to be processed
git_storeShas "$sha1" "$sha2"

#The next operation is to get the weights of the commits #TODO:Wrap it in a function...
for i in "${!shas[@]}"
do 
  if [[ $i -eq 0 ]]; then # [[ "$i" == '0' ]] less efficient because needs expanding the variable?
    continue
  fi
  echo "Calling git_checkLines() with: ""${shas[$i]}" "(commit)" "${shas[$i-1]}" "(the parent of that commit)"
  git_checkLines "${shas[$i]}" "${shas[$i-1]}" 
done

for i in "${!shas[@]}"
do 
  if [[ $i == 0 ]]; then
    continue
  fi
  echo "Calling calculateDate with: ""${shas[$i]}"
  calculateDate "${shas[$i]}"
done

#Extracts the hour currently
modifyDate "$date"
normalizeWeights

#git_changeDates
