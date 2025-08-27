2025_08_27_Ncat_TIMEOUT_kex_exchange_identification_Connection_closed_by_remote_host
=======================================================================================

Overview
---------

Some GFW security transition happened today (2025-08-27) 
exposing mis-configuration on Ada workstation that prevented
git ssh connections to github.com. Correcting the config
to use the bastion tunnel regained the connection.


A : Ada Linux Workstation
---------------------------


git/ssh config that has been working for months has today stopped working on workstation and lxlogin. 
But git connection continues to work from laptop::

    [blyth@localhost np]$ git pull
    Ncat: Version 7.92 ( https://nmap.org/ncat )
    Ncat: TIMEOUT.
    kex_exchange_identification: Connection closed by remote host
    Connection closed by UNKNOWN port 65535
    fatal: Could not read from remote repository.

    Please make sure you have the correct access rights
    and the repository exists.
    A[blyth@localhost np]$ 


HMM : LOOKS LIKE WAS NOT USING THE TUNNEL::

    Host *github.com
        User git 
        ProxyCommand nc -v %h %p
    #    ProxyCommand nc -v -x 127.0.0.1:8080 %h %p
    #    the above dumps a file "127.0.0.1:8080" on Alma Linux when doing "git pull"
    #    ProxyCommand nc -v --proxy 127.0.0.1:8080 --proxy-type socks5 %h %p
    #    #ssh -vvv -T git@github.com

Changing the config to the below succeeds::

    Host *github.com
        User git 
        ProxyCommand nc -v --proxy 127.0.0.1:8080 --proxy-type socks5 %h %p

Giving::

    A[blyth@localhost np]$ git pull 
    Ncat: Version 7.92 ( https://nmap.org/ncat )
    Ncat: Connected to proxy 127.0.0.1:8080
    Ncat: No authentication needed.
    Ncat: Host github.com will be resolved by the proxy.
    Ncat: connection succeeded.
    Already up to date.
    A[blyth@localhost np]$ l


man nc::

     ncat [OPTIONS...] [hostname] [port]

    -v, --verbose          Set verbosity level (can be used several times)
    --proxy <addr[:port]>  Specify address of host to proxy through
    --proxy-type <type>    Specify proxy type ("http", "socks4", "socks5") 


Checking Zeta : macOS laptop using ~/np "git pull"
------------------------------------------------------

* "spb" running opening tunnel to bastion on port 8080
* ~/ssh/config using::

   Host *github.com
        User git
        ProxyCommand nc -v -x 127.0.0.1:8080 %h %p


Commenting the above also fails::

    zeta:np blyth$ git pull

    ssh: connect to host github.com port 22: Operation timed out
    fatal: Could not read from remote repository

    Please make sure you have the correct access rights
    and the repository exists.


Putting it back, works::

    zeta:np blyth$ git pull

    Connection to github.com port 22 [tcp/ssh] succeeded!
    Already up to date



Checking lxlogin
----------------------

With GFW elevated and the correct ~/.ssh/config ProxyCommand::

    Host *github.com
        User git 
        ProxyCommand nc -v --proxy 127.0.0.1:8080 --proxy-type socks5 %h %p

But omitting to start the socks5 proxy::

    U[blyth@lxlogin004 np]$ git pull
    Ncat: Version 7.92 ( https://nmap.org/ncat )
    Ncat: Proxy connection failed: Connection refused.
    kex_exchange_identification: Connection closed by remote host
    Connection closed by UNKNOWN port 65535
    fatal: Could not read from remote repository.

    Please make sure you have the correct access rights
    and the repository exists.
    U[blyth@lxlogin004 np]$ 


Try to start proxy (no sshpass on lxlogin so try to use ssh keys) with vkk::

    U[blyth@lxlogin004 ~]$ vkk
    === vip-agent-info :        SSH_AUTH_SOCK /tmp/ssh-XXXXXXG0lhBf/agent.3797135 
    === vip-agent-info :        SSH_AGENT_PID 3797141 
    === vip-agent-info :       LIVE_AGENT_PID  
    === soks-fg : 0 Wed Aug 27 04:59:10 PM CST 2025
    ssh -C -ND localhost:8080 BB
    ssh: connect to host bastion.cnaf.infn.it port 22: Connection timed out
    === soks-fg : 1 Wed Aug 27 05:01:19 PM CST 2025
    ssh -C -ND localhost:8080 BB
    ssh: connect to host bastion.cnaf.infn.it port 22: Connection timed out
    === soks-fg : 2 Wed Aug 27 05:03:31 PM CST 2025
    ssh -C -ND localhost:8080 BB

Maybe missing the key on other end? No seems not. But connection using keys times out.

Even after local install of ~/.ssh/sshpass cannot connect to bastion from lxlogin ?





