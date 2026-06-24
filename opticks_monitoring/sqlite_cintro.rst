sqlite_cintro.rst
====================

* https://sqlite.org/cintro.html

::

    A[blyth@localhost opticks_monitoring]$ rpm -ql sqlite-devel
    /usr/include/sqlite3.h
    /usr/include/sqlite3ext.h
    /usr/lib64/libsqlite3.so
    /usr/lib64/pkgconfig/sqlite3.pc



    A[blyth@localhost opticks_monitoring]$ sudo dnf repoquery -l sqlite-devel
    [sudo] password for blyth: 
    runner_gitlab-runner                                                                                                                                                                                             1.0 kB/s | 1.5 kB     00:01    
    /usr/include/sqlite3.h
    /usr/include/sqlite3ext.h
    /usr/lib/libsqlite3.so
    /usr/lib/pkgconfig/sqlite3.pc
    /usr/include/sqlite3.h
    /usr/include/sqlite3ext.h
    /usr/lib64/libsqlite3.so
    /usr/lib64/pkgconfig/sqlite3.pc



