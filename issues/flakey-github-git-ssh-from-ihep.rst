flakey-github-git-ssh-from-ihep
==================================

"git pull" works:: 

    N[blyth@localhost j]$ git pull 
    remote: Enumerating objects: 17, done.
    remote: Counting objects: 100% (17/17), done.
    remote: Compressing objects: 100% (6/6), done.
    remote: Total 10 (delta 4), reused 10 (delta 4), pack-reused 0
    Unpacking objects: 100% (10/10), done.
    From github.com:simoncblyth/j
       e346bbb..564c892  main       -> origin/main
    Updating e346bbb..564c892
    Fast-forward
     issues/blyth-88-Custom4-shakedown.rst | 137 ++++++++++---------------------------------------------------
     issues/blyth-88-cleanup-error.rst     | 249 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     issues/blyth-88-insitu-ana.rst        | 141 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     jx.bash                               |  25 ++++++++----
     ntds/ntds.py                          | 106 +++++++++++++++++++++++++++++++++++++++++++++--
     ntds/ntds.sh                          |  21 +++++++---
     6 files changed, 547 insertions(+), 132 deletions(-)
     create mode 100644 issues/blyth-88-cleanup-error.rst
     create mode 100644 issues/blyth-88-insitu-ana.rst
    N[blyth@localhost j]$ 


Now it doesnt::

    N[blyth@localhost j]$ git pull 
    ssh_exchange_identification: Connection closed by remote host
    fatal: Could not read from remote repository.

    Please make sure you have the correct access rights
    and the repository exists.
    N[blyth@localhost j]$ 

Now it works again, 1 min after the above fail::

    N[blyth@localhost j]$ git pull 
    remote: Enumerating objects: 15, done.
    remote: Counting objects: 100% (15/15), done.
    remote: Compressing objects: 100% (4/4), done.
    remote: Total 8 (delta 4), reused 8 (delta 4), pack-reused 0
    Unpacking objects: 100% (8/8), done.
    From github.com:simoncblyth/j
       564c892..c16ec78  main       -> origin/main
    Updating 564c892..c16ec78
    Fast-forward
     issues/blyth-88-insitu-ana.rst | 291 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++--
     jx.bash                        |  30 +++++++++----
     ntds/ntds.py                   |  79 ++++++++++++++++++--------------
     ntds/ntds.sh                   |  24 ++++++++--
     4 files changed, 376 insertions(+), 48 deletions(-)
    N[blyth@localhost j]$ 
    N[blyth@localhost j]$ 


