usage(){ cat << EOU
   source ~/j/oj_client/check.sh
EOU

}

# careful to use clean env without "lco" conda, as that brings in another libcurl
source /usr/local/ExternalLibs/openssl/openssl-3.2.0/bashrc
source /usr/local/ExternalLibs/libcurl/curl-8.12.1/bashrc
env | grep JUNO
ldd $JUNO_EXTLIB_libcurl_HOME/lib64/libcurl.so





