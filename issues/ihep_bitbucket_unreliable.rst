ihep_bitbucket_unreliable
==========================


Review the proxy machinery and add a few commands : incase have to start using it
------------------------------------------------------------------------------------

Note that cnaf connection still working::

    ssh B 

Not yet tested by expect the commands to config and start socks proxy are::

    git-
    git-socks

    socks-
    socks--


env/git/git.bash::

    1534 git-socks(){ socks- ;  git config --global http.proxy "socks5://127.0.0.1:$(socks-port)" ; cat $(git-config) ;  }
    1535 git-socks-unset(){     git config --global --unset http.proxy  ; cat $(git-config) ; }
    1536 git-config(){          echo $HOME/.gitconfig ; }
    1537 git-e(){               vi $(git-config) ; }
    1538 
    1539 
    1540 git-socks-notes(){ cat << EON
    1541 
    1542 Adds the below to ~/.gitconfig::
    1543 
    1544     [http]
    1545         proxy = socks5://127.0.0.1:8080
    1546 
    1547 EON
    1548 }

::

    epsilon:opticks blyth$ socks-
    epsilon:opticks blyth$ t socks--
    socks-- () 
    { 
        local msg="=== $FUNCNAME :";
        local ps=$(socks-ps);
        if [ "$ps" == "" ]; then
            echo $msg starting socks proxy;
            socks-start;
            socks-ps;
        else
            echo $msg socks proxy is already running : perhaps you need to reload the PAC file in Firefox Preferences;
            echo $ps;
        fi
    }





Aug 22, 2022 : bitbucket access from IHEP over past few days has become unreliable
------------------------------------------------------------------------------------

::

    N[blyth@localhost opticks]$ git remote -v
    origin  git@bitbucket.org:simoncblyth/opticks.git (fetch)
    origin  git@bitbucket.org:simoncblyth/opticks.git (push)
    N[blyth@localhost opticks]$ 

    N[blyth@localhost opticks]$ git pull 
    Connection closed by 104.192.141.1 port 22
    fatal: Could not read from remote repository.

    Please make sure you have the correct access rights
    and the repository exists.




    N[blyth@localhost opticks]$ git pull 
    remote: Enumerating objects: 49, done.
    remote: Counting objects: 100% (49/49), done.
    remote: Compressing objects: 100% (27/27), done.
    remote: Total 27 (delta 25), reused 0 (delta 0), pack-reused 0
    Unpacking objects: 100% (27/27), 3.98 KiB | 127.00 KiB/s, done.
    From bitbucket.org:simoncblyth/opticks
       977637965..05ebc01ec  master     -> origin/master
    Updating 977637965..05ebc01ec
    Fast-forward
     CSG/CSGFoundry.cc                                                    | 38 +++++++++++++++++++++++++++-----------
     CSG/CSGFoundry.h                                                     | 17 +++++++++--------
     CSGOptiX/CSGOptiX.cc                                                 | 10 ++++++++--
     g4cx/G4CXOpticks.cc                                                  | 33 ++++++++++++++++++++-------------
     g4cx/gxr.sh                                                          |  1 +
     g4cx/gxs.sh                                                          | 10 +++++-----
     g4cx/gxt.sh                                                          | 15 ++++++++-------
     g4cx/tests/G4CXSimulateTest.cc                                       |  3 +--
     notes/issues/review_QEvent_SEvt_sevent_lifecycle_allocations_etc.rst | 24 ++++++++++++++++++++++++
     qudarap/QEvent.cc                                                    | 13 ++-----------
     sysrap/SEvt.cc                                                       | 10 ++++++----
     sysrap/sevent.h                                                      |  4 ++--
     sysrap/sqat4.h                                                       | 14 +++++++++++++-
     13 files changed, 126 insertions(+), 66 deletions(-)
    N[blyth@localhost opticks]$ 




Get git proxy setup to go via 
--------------------------------


::

    N[blyth@localhost opticks]$ ssh B   ## gets thru to eg login03.cnaf.infn.it







