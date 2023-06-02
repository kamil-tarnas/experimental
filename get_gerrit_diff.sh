#!/bin/bash

### Part 0: The description of the script and possible tasks to do
# Usage:
# ./get_gerrit_diff <url_address>
# ./get_gerrit_diff https://review.gerrithub.io/c/GerritForge/gerrit/+/541215/1..2

# ./get_gerrit_diff <url_addres> -- <file_1> <file_2> <file_x>
# When being on 7d0a986b0cd2584e887c90a7087f1c729e6b91fe (for the ChangeRebuilderIT.java to be present in repo):
# ./get_gerrit_diff.sh https://review.gerrithub.io/c/GerritForge/gerrit/+/536286/2..3 -- ChangeRebuilderIT.java

# The command is here:
# cd ~/gerrit && ../get_gerrit_diff/get_gerrit_diff.sh https://review.gerrithub.io/c/GerritForge/gerrit/+/536286/2..3 -- AbstractDaemonTest.java

# Maybe we can use any command to get the two versions from gerrit? Like, we can use the copy-pasted 'git checkout', 'git cherry-pick' and so on?
# The format is as follows:
# https://review.gerrithub.io/c/GerritForge/gerrit/+/541215/1..2
# Which means we are comparing the PS2 diff against the PS1
# That means that it is opposite to the actual get command...
# So, maybe we can just get the "changes" and the "state"? (But the state is just the "base commit")
# We do not need to bind any HTML or the JS to do this kind of things...
# Have the --reverse option (like in git)
# Have the '--' separator (like in git)
# Maybe search for the files in an intelligent way (not providing the path, but the file name - use find)
# Yeah, so, try to find the file in the path provided, if not found then search for the file with "find" on the base catalog of the repo (get this by some git command - "git rev-parse --show-toplevel")
#TODO: redirect the output to /dev/null and substitute it with only the script-specific output (?)

# Unit testing of this script:
# https://advancedweb.hu/unit-testing-bash-scripts/
# a mock repo would be needed for the tests?
# divide it to : ONLINE suite and OFFLINE suite (???)

# TODO: Principles:
# 1. Use locals as much as possible
# 2. Have the functionalities separated as much as possible
# 3. Build it with makefile or something? -> simplify the all functions? Merge it to one big block?
# 4. Have a MOCK repo attached to the repo
# 5. Have a possibility to just fetch the latest working script that is already built...
# 6. The big task of defining the arguments passed - only one array could be passed to a function and it should be the last arg:
#    explanation can be found here: https://askubuntu.com/questions/674333/how-to-pass-an-array-as-function-argument


# Parse args - if we have the '--' then process the files (paths) into arguments of files

# TODO: Do all the declaration here?
# TODO: How to call the flag to ignore-rebase-changes
# --no-ignore-rebase
# --ignore-rebase (which will be a default?)

# Switch all the porcelain commands to plumbing commands 
# (which are more suitable for scripting - there is not need to additionally parse the output or get rid of unnecessary things, text or colors and so on)

### Part 1: Setting some value constants and functional constants (to control or hardcode the program behaviour) and getting the command line params

ignoreRebase=true

# TODO: Bind those to the commands
# Define the Gerrit commit space
gerritCommitSpace="refs/changes/"
revParse="git rev-parse"

# Get the arguments and shift the thingy...
declare url=$1; shift

# Now (without any flags) only '--' can be at the $1 position, check it to see if we need to be in a file mode... 
# filename separator (or pathspec separator) is what this thingy is called
declare filenameSeparator=$1; shift


### Part 2: Getting the URL decomposed

# URL regex should cover all (most?) Gerrit addresses
urlRe="https:\/\/(.*)\/.+\/(.+)\/([0-9]+)..([0-9]+)"

if [[ $url =~ $urlRe ]]; 
then
  changeNumber=${BASH_REMATCH[2]}
  changeNumberSpace=${changeNumber: -2} # changeNumberSpace are the last two digits of the change number
  firstPatchSetNumber=${BASH_REMATCH[3]}
  secondPatchSetNumber=${BASH_REMATCH[4]}
  echo $changeNumber $changeNumberSpace $firstPatchSetNumber $secondPatchSetNumber 
  # And we need to construct the number space, the last two digits of the change number...
fi



#### Part 3: Getting the filenames that need to be saved - for the filename mode
#TODO: How to parse the "--"? Does git have its own way to do it? How to make this unambigous?

declare -a filenames


# Do we have any searching if the files is not found (???)
# If we have filenames provided then process the filenames firstly (name it somehow...)
# Now if each and every file is not found ---> then it will print the whole diff
# TODO: Need to find the filename separator in the arguments, rather than just assuming it is on a certain position
# TODO: What in case a file is found AND it is modified by the rebase between PSes BUT the file IS not modified by any of the commits?
if [[ $filenameSeparator == "--" ]]
then
  echo "Filenamme sep found!"
  # We are in the filemode

  # For all the parameters left (non-shifted) check if specified file exists
  # If it is - cool - pass it to the git command
  # If it does not - then search for it going from the top repo level...
  while (( "$#" ))
  do
    if [[ -e "$1" ]]
    then
      filenames+=($1)
      echo "Filename found"
    else
      # Need to search the file starting from the top-level repo directory
      # Strip provided location/filename to only a filename - anything that is left after the last '/' character
      if [[ $1 =~ ".+\/(.+)$" ]]
      then
        filenameToSearch=${BASH_REMATCH[1]}
        echo $filenameToSearch
      else
        # If we did not find the last '/' and the file is not found - then the argument was given as a filename, use it directly
        filenameToSearch=$1
      fi
      # More than one file might be found
      # Handle regex matching here, for example for file "example.c" we can search just "example"
      # TODO: Introduce a verbose case for the file not being found...
      # TODO: To be able to take the intersection we need to have the filename in the following fromat:
      # /home/kamil/gerrit/java/com/google/gerrit/acceptance/AbstractDaemonTest.java
      # AND NOT the following:
      # java/com/google/gerrit/acceptance/AbstractDaemonTest.java
      # Complicated solution of the realpath util
      # find $(git rev-parse --show-toplevel) -iname AbstractDaemonTest.java -exec realpath --relative-to $(git rev-parse --show-toplevel) {} \;
      filenames+=($(find $(git rev-parse --show-toplevel) -iname $filenameToSearch -exec realpath --relative-to $(git rev-parse --show-toplevel) {} \; | head -n 1))
      #filenames+=($(find $(git rev-parse --show-toplevel) -iname $filenameToSearch | head -n 1))
      # Yeah, it works, but it is pretty complicated...
      echo $filenames
    fi
  shift
  done
fi

# Have a quick "HAPPY" path, because all of this is getting pretty complicated...

# And here at this point we need to have all the varaibles from the address in a valid state...


### Part 4: Fetch the commits from different remotes...

# Remotes should be an array of remote repo addresses that we will try to connect to to get the commits from remote repo
# Read in as an array
remotes=($(git remote -v | awk '{print $2}' | tr '\n' ' '))

echo ${remotes[@]}
echo ${remotes[0]}

# Try the first repo address now...

# TODO: We can have an array of changes (SHAs) and compare them offline...
# TODO: We can fail at - 1. connecting to the repo, 2. not finding the commit, 3. rev-parse failure (?)
# NAME: getShaFromGerrit()

# getSha="git rev-parse --verify FETCH_HEAD"
# $getSha

# getCommits

# AND, to define all globals that we are going to be working on we can do a declare -l

# How to not pollute the names?
# To have the red lines on gerrit deleted and greed lines on gerrit added we need to swap the references - firstCommit is the secondPatchSetNumber
firstCommit=$(git fetch ${remotes[0]} refs/changes/$changeNumberSpace/$changeNumber/$secondPatchSetNumber && \
  git rev-parse --verify FETCH_HEAD)
  
secondCommit=$(git fetch ${remotes[0]} refs/changes/$changeNumberSpace/$changeNumber/$firstPatchSetNumber && \
  git rev-parse --verify FETCH_HEAD)

# If first commit is not empty (need to do it for both commits)
if [ -z "$firstCommit" ]
then 
  echo "Failure to get the SHA"
  # TODO: Try to connect to the other address from remotes[]
fi

# have an error code that would be passed somewhere... and then read at the end?

# TODO: If we set up a routine here -- the output owuld be the two commits (so, those cannot be local)

numAttempts=0
# Check if we have both non-empty second and first commit SHAs
# while  && ${#ArrayName[@]} < the internal counter 
# do it untill both variable representing commit SHAs are not not filled with data and we still have remotes to try to connect to 
while [[ (-z "$firstCommit" || -z "$secondCommit") && (($numAttempts < ${#remotes[@]})) ]] # do it untill both variable representing commit SHAs are not not filled with data
do
  # Call getCommits (or GetCommits)
  echo "test"
  ((numAttempts=numAttempts+1))
done


### Part 5: Getting the diff only from the wanted files


# TODO: in the present form it also shows the differences between baseline IF THE PARENT WAS CHANGED...
# https://bugs.chromium.org/p/gerrit/issues/detail?id=551
# https://groups.google.com/g/repo-discuss/c/jCFPnrIIdLI/m/vczDFrdspdcJ
# https://gerrit-review.googlesource.com/c/gerrit/+/57086

# How to exclude the files that were modified by ONLY the user (and not by the rebase that is modifying the files)
# How to do it on my side (?)
# Have an internal list of modified files (by both PSes) and just take a sum of those (?)
# Some git command would be useful, like list files of 'git show SHA --stat'

# Have a thing to try to connect to the repo - like a case of failure in Bash script... and handle the failure somewhere?
# THE ISSUE OF FILES SHOW WHEN THE PS WAS REBASED
# Handling of root is needed?
#git diff-tree --no-commit-id --name-only -r $firstCommit > /dev/null
#git diff-tree --no-commit-id --name-only -r $secondCommit > /dev/null
# push it to one array or something and then do a sort uniq 

#TODO: 'files' ---> are the files modified by both patchsets...
# TODO: This would also fail in case we do not have the internet connection - so, we should exit the script (prematurely, or, early return) at the time 
# of knowing that we cannot connect to the remote repository
files=($({ git diff-tree --no-commit-id --name-only -r $firstCommit; git diff-tree --no-commit-id --name-only -r $secondCommit; } | \
   sort | uniq | tr '\n' ' '))
   
   
# Put the values into an array - can we do it better or do we need to call 'tr' every time (???)
echo "Echoing the files: " ${files[@]}

# Check if the filenames have been provided - if they have been - then we need to take the intersection of both...
if [ -n "$filenames" ]
then
  # we need to take the INTERSECTION of both of the filenames...
  intersection_files=$(echo ${filenames[@]} ${files[@]} | sed 's/ /\n/g' | sort | uniq -d)
fi


echo "Echoing the intersection_files: " ${intersection_files[@]}
############




# If non-existing patch-set ---> one of the variables would be empty (the base of diff-to one...)
# If could not connect to the repo ---> then we would have empty remotes (or the remote count would be zero...)

#call with different repository (remote) addresses

# TODO: IMPORTANT - if files are searched on the top repository level - then we need to call the diff also there! (check if it is actually true...)
# TODO: paste the desired files if those are present - if not - then go with a "default" version of diffing

# We need to handle such case - the file have been found, but only in the DIFF THAT IS A RESULT OF REBASE (and is not contained in the PSes)
# In such case we need to print and exit the script
# TODO: In case of no internet connection ---> the communicate is also showing up ---> it should not 
if [[ -n "$filenames" && -n "$ignoreRebase" && -z "$intersection_files" ]]
then
  echo "The file/files given by command line argument have been found only in the diff that is a RESULT OF REBASE between patch sets, exiting script"
  exit 1
fi


### Part 6: The gist of it - getting the diffs between the commits...

# TODO: The inverse flag SHOULD NOT be passed to this funcion - it can swap the arguments beforehand (before calling this fucntion)

# TODO: Yeah, need to get this logic right - a combination of input args and the 
if [[ -n "$filenames" && -n "$ignoreRebase" ]] # AND IF THE --ignore-rebase was given ---> shoud be a default... # TODO: double [[]] are bad?
then
  git diff $firstCommit..$secondCommit -- ${intersection_files[@]} #TODO: a case in which "files" have been provided andn
  git diff $firstCommit..$secondCommit > diff # TODO: Just do 'tee'
  git diff $secondCommit..$firstCommit > diff_reverse # TODO: Just do 'tee'
elif [[ -n "$filenames" ]]
then
  git diff $firstCommit..$secondCommit -- ${filenames[@]}
  git diff $firstCommit..$secondCommit -- ${filenames[@]} > diff # TODO: Just do 'tee'
  git diff $secondCommit..$firstCommit -- ${filenames[@]} > diff_reverse # TODO: Just do 'tee'
elif [[ -n "$ignoreRebase" ]]
then
  git diff $firstCommit..$secondCommit -- ${files[@]}
  git diff $firstCommit..$secondCommit -- ${files[@]} > diff # TODO: Just do 'tee'
  git diff $secondCommit..$firstCommit -- ${files[@]} > diff_reverse # TODO: Just do 'tee'
fi

# For doing a reverse you can just follow this (?)
# The easiest way of getting the opposite would be to switch the arguments I think

# Any other idea on how to create the --invert version?

# TODO: Save the diff as a commit (is that peasible to do - probably could be needed by the noobs, that do not know "git apply" command on the diff)
# TODO: Yeah, we can save it as the diff or we can save it in a separate commit
# TODO: Much of the confilicts will be then due to the version difference, so I dunno, maybe it is better to save it in some other format?

# Okay - let's assume everything was calculated correctly

# Check if we have valid SHAs, both firstCommit and secondCommit should be valid... (Can we check it inside the commit?)
