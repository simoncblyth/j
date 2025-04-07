oj_script_in_junosw
=====================

Need to install oj script into InstallArea/bin to 
prevent duplication of geometry config.

Did this with opticks_juno.sh 

::

    A[blyth@localhost junosw]$ find . -name CMakeLists.txt -exec grep -H SCRIPTS {} \;
    ./Examples/RawAnalysis/CMakeLists.txt:    SCRIPTS
    ./Examples/Tutorial/CMakeLists.txt:    SCRIPTS
    ./RootIO/RootIOTools/CMakeLists.txt:    SCRIPTS
    A[blyth@localhost junosw]$ 

