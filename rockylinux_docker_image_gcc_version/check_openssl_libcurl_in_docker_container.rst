check_openssl_libcurl_in_docker_container
===========================================



::

    A[blyth@localhost ~]$ docker images simoncblyth/cuda
    REPOSITORY         TAG                              IMAGE ID       CREATED         SIZE
    simoncblyth/cuda   12.4.1-runtimeplus-rockylinux9   8c10f253f281   13 months ago   7.89GB





    A[blyth@localhost ~]$ docker run -it simoncblyth/cuda:12.4.1-runtimeplus-rockylinux9 /bin/bash
    ...
    [juno@0fd85ff30c7f ~]$ which curl-config
    /usr/bin/curl-config
    [juno@0fd85ff30c7f ~]$ which openssl
    /usr/bin/openssl
    [juno@0fd85ff30c7f ~]$ curl-config --version
    libcurl 7.76.1
    [juno@0fd85ff30c7f ~]$ openssl version
    OpenSSL 3.2.2 4 Jun 2024 (Library: OpenSSL 3.2.2 4 Jun 2024)
    [juno@0fd85ff30c7f ~]$ 


    [juno@0fd85ff30c7f ~]$ ldd $(which curl)
        linux-vdso.so.1 (0x00007ffd6cfb8000)
        libcurl.so.4 => /lib64/libcurl.so.4 (0x00007f3ee296b000)
        libc.so.6 => /lib64/libc.so.6 (0x00007f3ee2764000)
        libnghttp2.so.14 => /lib64/libnghttp2.so.14 (0x00007f3ee273a000)
        libssl.so.3 => /lib64/libssl.so.3 (0x00007f3ee2654000)
        libcrypto.so.3 => /lib64/libcrypto.so.3 (0x00007f3ee213b000)
        libgssapi_krb5.so.2 => /lib64/libgssapi_krb5.so.2 (0x00007f3ee20e2000)
        libkrb5.so.3 => /lib64/libkrb5.so.3 (0x00007f3ee2007000)
        libk5crypto.so.3 => /lib64/libk5crypto.so.3 (0x00007f3ee1fee000)
        libcom_err.so.2 => /lib64/libcom_err.so.2 (0x00007f3ee1fe7000)
        libz.so.1 => /lib64/libz.so.1 (0x00007f3ee1fcd000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f3ee2a27000)
        libkrb5support.so.0 => /lib64/libkrb5support.so.0 (0x00007f3ee1fbc000)
        libkeyutils.so.1 => /lib64/libkeyutils.so.1 (0x00007f3ee1fb3000)
        libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f3ee1f9f000)
        libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f3ee1f72000)
        libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f3ee1ed6000)



