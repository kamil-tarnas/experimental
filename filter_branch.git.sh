#!/bin/bash
git filter-branch --force --env-filter   \
   'if [ $GIT_COMMIT = ae756f419d57fa30bd1862d751283d8a8bc71cc7 ] || [$GIT_COMMIT = e000df676396737e4be51a86aef225db800a875d ]
    then
      export GIT_AUTHOR_DATE="Fri Jan 2 21:38:53 2009 -0800"
      export GIT_COMMITTER_DATE="Sat May 19 01:01:01 2007 -0700"
    fi'

