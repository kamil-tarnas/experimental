#!/bin/bash
#git ls-files . | grep 'global_dtors' | xargs git add
find . -name '*global_dtors*' | xargs git add
