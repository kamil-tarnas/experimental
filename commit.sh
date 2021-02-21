#!/bin/bash

# TODO: Get the gist of the commit by searching in diff
if [ $# -eq 0 ]; then
  echo "No arguments supplied, using default commit message..." >&2
  commitMsg="More development in "$(basename $(git rev-parse --show-toplevel))
  echo $commitMsg
else
  commitMsg=$1; shift
fi

# && in case of any operation fails in the chain
git add -u && git commit -m "$commitMsg" && git push

if [ $? -ne 0 ]; then
  echo "Adding, committing and pushing failed!"
fi