merge_huyuxiang_bitbucket_fork
================================


https://support.atlassian.com/bitbucket-cloud/docs/resolve-merge-conflicts/


https://bitbucket.org/simoncblyth/opticks/commits/

https://bitbucket.org/huyuxiang-bit/opticks/commits/


https://stackoverflow.com/questions/9944898/bitbucket-update-a-fork-to-merge-changes-of-master-repo



Hi Yuxiang, 

About the NP.hh conflict : you need to sync the fork with the original
before you can succeed at making a pull request on bitbucket.

To do that follow  something like:

     https://www.freecodecamp.org/news/how-to-sync-your-fork-with-the-original-git-repository/

Essentially you define alias for upstream if there is none already and then "git fetch" the changes, 
which grabs them without doing merge yet.   Then you do the merge. To resolve the conflict
you can just accept the original NP.hh that already has your changes in it. 
A guide for that

     https://phoenixnap.com/kb/how-to-resolve-merge-conflicts-in-git 

As there is only one file in conflict and the origin repo version of it 
has all your changes anyway you can just

     git merge --strategy-option theirs


Simon


