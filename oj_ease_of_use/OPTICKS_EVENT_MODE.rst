OPTICKS_EVENT_MODE
====================

::

    A[blyth@localhost ~]$ l /tmp/blyth/opticks/GEOM/J_2025_mar24/python3.11/ALL0_none/
    total 48
    4 drwxr-xr-x.  2 blyth blyth 4096 Mar 24 16:51 A009
    4 -rw-r--r--.  1 blyth blyth 2386 Mar 24 16:51 run_meta.txt
    4 -rw-r--r--.  1 blyth blyth  132 Mar 24 16:51 run.npy
    0 drwxr-xr-x. 12 blyth blyth  161 Mar 24 16:51 .
    4 drwxr-xr-x.  2 blyth blyth 4096 Mar 24 16:51 A008
    4 drwxr-xr-x.  2 blyth blyth 4096 Mar 24 16:51 A007
    4 drwxr-xr-x.  2 blyth blyth 4096 Mar 24 16:51 A006
    4 drwxr-xr-x.  2 blyth blyth 4096 Mar 24 16:51 A005
    4 drwxr-xr-x.  2 blyth blyth 4096 Mar 24 16:51 A004
    4 drwxr-xr-x.  2 blyth blyth 4096 Mar 24 16:51 A003
    4 drwxr-xr-x.  2 blyth blyth 4096 Mar 24 16:51 A002
    4 drwxr-xr-x.  2 blyth blyth 4096 Mar 24 16:51 A001
    4 drwxr-xr-x.  2 blyth blyth 4096 Mar 24 16:51 A000
    0 drwxr-xr-x.  3 blyth blyth   23 Mar 24 16:51 ..
    A[blyth@localhost ~]$ 


::

    export OPTICKS_SCRIPT=$FUNCNAME        # avoid default sproc::_ExecutableName of python3.9 

::

    255 /**
    256 sproc::ExecutableName
    257 ----------------------
    258 
    259 In embedded running with python "main" the 
    260 initial executable name is eg "python3.9".
    261 That can be overridden with envvar OPTICKS_SCRIPT 
    262 
    263 **/
    264 
    265 inline char* sproc::ExecutableName()
    266 {
    267     char* exe0 = sproc::_ExecutableName() ;
    268     bool is_python = sproc::StartsWith(exe0, "python") ;
    269     char* script = getenv("OPTICKS_SCRIPT");
    270     char* exe = ( is_python && script ) ? script : exe0 ;
    271     return exe ;
    272 }



