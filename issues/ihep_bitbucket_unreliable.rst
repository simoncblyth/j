ihep_bitbucket_unreliable
==========================


Overview
-----------

* 23 Aug 2022 : take pragmatic approach of switching to https urls for opticks repo, which still works::

    git remote set-url origin https://bitbucket.org/simoncblyth/opticks.git

* 23 Aug 2022 : attempt to use socks proxy not working well, and its would be a pain anyhow
* ~20-22 Aug 2022 : bitbucket git clone with ssh urls becomes unreliable


seems github git clone with ssh urls is still working
-------------------------------------------------------

::

    N[blyth@localhost j]$ git remote -v
    origin	git@github.com:simoncblyth/j.git (fetch)
    origin	git@github.com:simoncblyth/j.git (push)
    N[blyth@localhost j]$ git pull 
    Already up to date.
    N[blyth@localhost j]$ 



problem using git via proxy
-----------------------------

::

    N[blyth@localhost ~]$ git config --global http.proxy 'socks5://127.0.0.1:8080'
    N[blyth@localhost ~]$ vi ~/.gitconfig
    N[blyth@localhost ~]$ git clone https://bitbucket.org/simoncblyth/intro_to_cuda.git
    Cloning into 'intro_to_cuda'...
    fatal: unable to access 'https://bitbucket.org/simoncblyth/intro_to_cuda.git/': Failed to receive SOCKS5 connect request ack.
    N[blyth@localhost ~]$ 
    N[blyth@localhost ~]$ 



Change remote url from ssh to https
--------------------------------------

::

    N[blyth@localhost opticks]$ git remote -v
    origin	git@bitbucket.org:simoncblyth/opticks.git (fetch)
    origin	git@bitbucket.org:simoncblyth/opticks.git (push)
    N[blyth@localhost opticks]$ 

    N[blyth@localhost opticks]$ git remote set-url origin https://bitbucket.org/simoncblyth/opticks.git
    N[blyth@localhost opticks]$ git remote -v
    origin	https://bitbucket.org/simoncblyth/opticks.git (fetch)
    origin	https://bitbucket.org/simoncblyth/opticks.git (push)
    N[blyth@localhost opticks]$ 

    N[blyth@localhost opticks]$ git pull 
    remote: Enumerating objects: 7, done.
    remote: Counting objects: 100% (7/7), done.
    remote: Compressing objects: 100% (5/5), done.
    remote: Total 5 (delta 2), reused 0 (delta 0), pack-reused 0
    Unpacking objects: 100% (5/5), 1.75 KiB | 357.00 KiB/s, done.
    From https://bitbucket.org/simoncblyth/opticks
       05ebc01ec..b9d802827  master     -> origin/master
    Updating 05ebc01ec..b9d802827
    Fast-forward
     bin/log.py | 129 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     bin/log.sh |  18 ++++++++++++++++++
     2 files changed, 147 insertions(+)
     create mode 100755 bin/log.py
     create mode 100755 bin/log.sh
    N[blyth@localhost opticks]$ 




Clone from github and bitbucket over https works without proxy
----------------------------------------------------------------

::

    N[blyth@localhost ~]$ git clone https://github.com/simoncblyth/cfbase.git
    Cloning into 'cfbase'...
    remote: Enumerating objects: 4, done.
    remote: Counting objects: 100% (4/4), done.
    remote: Compressing objects: 100% (4/4), done.
    remote: Total 4 (delta 0), reused 4 (delta 0), pack-reused 0
    Receiving objects: 100% (4/4), 2.43 MiB | 1.92 MiB/s, done.
    N[blyth@localhost ~]$ 

    N[blyth@localhost ~]$ git clone https://bitbucket.org/simoncblyth/intro_to_cuda.git
    Cloning into 'intro_to_cuda'...
    remote: Enumerating objects: 203, done.
    remote: Counting objects: 100% (203/203), done.
    remote: Compressing objects: 100% (119/119), done.
    remote: Total 203 (delta 90), reused 176 (delta 79), pack-reused 0
    Receiving objects: 100% (203/203), 176.52 KiB | 328.00 KiB/s, done.
    Resolving deltas: 100% (90/90), done.
    N[blyth@localhost ~]$ 



Git clone over ssh socks proxy
------------------------------


* https://www.linuxwave.info/2021/07/git-clone-over-ssh-socks-proxy.html


Thursday, July 1, 2021

This is useful for a machine that needs to clone some repository from github, but does not having internet connection.

First, we must identify another machine that can access github.com, we can call this server proxy-server.

Then, establish a socks proxy from our no-internet-server

    $ ssh -qN -D 1234 proxy-server

::

    -q : quiet 
    -N : Do not execute a remote command  

    -D [bind_address:]port
       Specifies a local ``dynamic'' application-level port forwarding.  This works by allocating a socket to listen to port on the local side, optionally bound to the speci-
       fied bind_address.  Whenever a connection is made to this port, the connection is forwarded over the secure channel, and the application protocol is then used to deter-
       mine where to connect to from the remote machine.  Currently the SOCKS4 and SOCKS5 protocols are supported, and ssh will act as a SOCKS server.  Only root can forward
       privileged ports.  Dynamic port forwardings can also be specified in the configuration file.

       IPv6 addresses can be specified by enclosing the address in square brackets.  Only the superuser can forward privileged ports.  By default, the local port is bound in
       accordance with the GatewayPorts setting.  However, an explicit bind_address may be used to bind the connection to a specific address.  The bind_address of
       ``localhost'' indicates that the listening port be bound for local use only, while an empty address or `*' indicates that the port should be available from all inter-
       faces.




The above command will create a socks proxy at localhost port 1234

Use the git command with socks proxy. Let's say we want to clone the 30-seconds-of-code repository, run below command in a new shell

    $ git -c http-proxy=socks5h://localhost:1234 clone https://github.com/30-seconds/30-seconds-of-code


Once done, press ctrl-c in the first shell, to terminate the socks proxy

::

    N[blyth@localhost ~]$ git clone https://github.com/30-seconds/30-seconds-of-code
    Cloning into '30-seconds-of-code'...
    remote: Enumerating objects: 44486, done.
    remote: Counting objects: 100% (530/530), done.
    remote: Compressing objects: 100% (32/32), done.
    ^Cfetch-pack: unexpected disconnect while reading sideband packet

    N[blyth@localhost ~]$ 
    N[blyth@localhost ~]$ git clone https://bitbucket.org/simoncblyth/intro_to_cuda
    Cloning into 'intro_to_cuda'...
    fatal: unable to access 'https://bitbucket.org/simoncblyth/intro_to_cuda/': Failed to receive SOCKS5 connect request ack.
    N[blyth@localhost ~]$ 
    N[blyth@localhost ~]$ git clone https://github.com/30-seconds/30-seconds-of-code
    Cloning into '30-seconds-of-code'...
    remote: Enumerating objects: 44486, done.
    remote: Counting objects: 100% (530/530), done.
    remote: Compressing objects: 100% (32/32), done.
    ^Cfetch-pack: unexpected disconnect while reading sideband packet

    N[blyth@localhost ~]$ git clone https://bitbucket.org/simoncblyth/intro_to_cuda.git
    Cloning into 'intro_to_cuda'...
    fatal: unable to access 'https://bitbucket.org/simoncblyth/intro_to_cuda.git/': Failed to receive SOCKS5 connect request ack.
    N[blyth@localhost ~]$ 





Or this
----------


* https://gist.github.com/ozbillwang/005bd1dfc597a2f3a00148834ad3e551


when no need set username and proxy for your proxy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set ssh config::

    Host github.com
        Hostname github.com
        ServerAliveInterval 55
        ForwardAgent yes
        ProxyCommand /usr/bin/corkscrew <replace_with_your_company_proxy_server> <3128> %h %p


when need username and password for your proxy::

    cat ~/.ssh/myauth
    proxyUsername:proxyPassword
    set ssh config

set ssh config::

    Host github.com
        Hostname github.com
        ServerAliveInterval 55
        ForwardAgent yes
        ProxyCommand /usr/bin/corkscrew <replace_with_your_company_proxy_server> <3128> %h %p ~/.ssh/myauth





Perhaps this : Getting github access on a firewalled system
-------------------------------------------------------------

HMM: problem with this is that my connection already complicatedly going thru tunnel 

* https://gist.github.com/freifrauvonbleifrei/baf0c0d53ab98e0c56ad6411ec875e47


This approach, based on [0] and [1] lets me reverse-tunnel through the local machine, 
to get github (and other) access on protected machines, such as HPC compute systems.

I put these lines in my local ~/.ssh/config file::

    Host somehpcsocks
      ProxyCommand ssh -D 2020 localhost nc -q 1 localhost 22

    Host HPCSystem
      HostName hpcsystem.com
      ForwardAgent yes
      ProxyCommand ssh -W %h:%p somehpcsocks

and these here in the HPC system's ~/.ssh/config file::

    Host * 
        User                    git
        ProxyCommand            nc -x localhost:2020 %h %p


Now all ssh connections are tunneled through my local machine, enabling me to e.g.

    git clone git@github.com:spack/spack.git

[0] https://rse.shef.ac.uk/blog/2019-01-31-ssh-forwarding/
[1] http://cms-sw.github.io/tutorial-proxy.html



Trial Run
------------

::

    N[blyth@localhost opticks]$ ssh -C -fND localhost:8080 B2
    Warning: Permanently added 'bastion.cnaf.infn.it,131.154.8.7' (ECDSA) to the list of known hosts.
    blyth@bastion.cnaf.infn.it's password: 
    N[blyth@localhost opticks]$ ps aux | grep 8080
    blyth     58728  0.0  0.0 185584  1376 ?        Ss   00:10   0:00 ssh -C -fND localhost:8080 B2
    blyth     58741  0.0  0.0 112848  1012 pts/0    S+   00:11   0:00 grep --color=auto 8080
    N[blyth@localhost opticks]$ 



Check connection without trying to pull
-----------------------------------------

::

    N[blyth@localhost opticks]$ git ls-remote
    Connection closed by 104.192.141.1 port 22
    fatal: Could not read from remote repository.

    Please make sure you have the correct access rights
    and the repository exists.
    N[blyth@localhost opticks]$ 



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







