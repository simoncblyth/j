

[Thread 0x7fffcd5ff640 (LWP 748706) exited]
HepEvt2HepMC Dtor called begin
HepEvt2HepMC Dtor called end
Delete G4SvcRunManager
double free or corruption (!prev)

Thread 1 "python" received signal SIGABRT, Aborted.
0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
(gdb) bt
#0  0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
#1  0x00007ffff743eb46 in raise () from /lib64/libc.so.6
#2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
#3  0x00007ffff7429172 in __libc_message.cold () from /lib64/libc.so.6
#4  0x00007ffff7495f87 in malloc_printerr () from /lib64/libc.so.6
#5  0x00007ffff7497c7c in _int_free () from /lib64/libc.so.6
#6  0x00007ffff749a2c5 in free () from /lib64/libc.so.6
#7  0x00007ffff79b0b2a in _PyObject_Free (ctx=<optimized out>, p=<optimized out>) at Objects/obmalloc.c:2285
#8  _PyObject_Free (ctx=<optimized out>, p=<optimized out>) at Objects/obmalloc.c:2276
#9  0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
#10 dict_dealloc (mp=0x7ffff7770d80) at Objects/dictobject.c:2378
#11 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#12 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#13 insertdict (mp=mp@entry=0x7ffff7793440, key=0x7ffff76b56b0, hash=2349690666635389043, value=value@entry=0x7ffff7c5dca0 <_Py_NoneStruct>) at Objects/dictobject.c:1304
#14 0x00007ffff799b2f2 in _PyDict_SetItem_Take2 (value=0x7ffff7c5dca0 <_Py_NoneStruct>, key=<optimized out>, mp=0x7ffff7793440) at Objects/dictobject.c:1886
#15 0x00007ffff79aa917 in _PyModule_ClearDict (d=0x7ffff7793440) at Objects/moduleobject.c:613
#16 0x00007ffff79aabfe in _PyModule_Clear (m=m@entry=0x7ffff76efc40) at Objects/moduleobject.c:582
#17 0x00007ffff7a8fcea in finalize_modules_clear_weaklist (verbose=0, weaklist=0x7ffff7e6b280, interp=0x7ffff7d5f3b8 <_PyRuntime+58936>) at Python/pylifecycle.c:1499
#18 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1581
#19 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
#20 Py_FinalizeEx () at Python/pylifecycle.c:1751
#21 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
#22 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffefde0) at Modules/main.c:714
#23 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
#24 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
#25 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
#26 0x0000000000401075 in _start ()
(gdb) 


