bash_junoenv_libs_errors
==========================


Extracts from ~/Documents/Terminal_Saved_output.txt::

     46408 ==== juno-ext-libs-make:
     46409 [python-pip-make] ===== juno-ext-libs-PKG-make: call juno-ext-libs-python-pip-make-
     46410 [python-pip-make] Traceback (most recent call last):
     46411 [python-pip-make]   File "setup.py", line 8, in <module>
     46412 [python-pip-make]     from setuptools import find_packages, setup
     46413 [python-pip-make]   File "/home/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/site-packages/setuptools/__init__.py", line 4, in <module>
     46414 [python-pip-make]     import functools
     46415 [python-pip-make]   File "/home/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/functools.py", line 18, in <module>
     46416 [python-pip-make]     from collections import namedtuple
     46417 [python-pip-make]   File "/home/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/collections/__init__.py", line 21, in <module>
     46418 [python-pip-make]     from operator import itemgetter as _itemgetter, eq as _eq
     46419 [python-pip-make] ImportError: dynamic module does not define module export function (PyInit_operator)
     46420 ==== juno-ext-libs-install:
     46421 [python-pip-install] ===== juno-ext-libs-PKG-install: call juno-ext-libs-python-pip-install-
     46422 [python-pip-install] Traceback (most recent call last):
     46423 [python-pip-install]   File "setup.py", line 8, in <module>
     46424 [python-pip-install]     from setuptools import find_packages, setup
     46425 [python-pip-install]   File "/home/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/site-packages/setuptools/__init__.py", line 4, in <module>
     46426 [python-pip-install]     import functools
     46427 [python-pip-install]   File "/home/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/functools.py", line 18, in <module>
     46428 [python-pip-install]     from collections import namedtuple
     46429 [python-pip-install]   File "/home/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/collections/__init__.py", line 21, in <module> 
     46430 [python-pip-install]     from operator import itemgetter as _itemgetter, eq as _eq
     46431 [python-pip-install] ImportError: dynamic module does not define module export function (PyInit_operator)
     46432 ==== juno-ext-libs-setup:
     46433 [python-pip-setup] ~/junotop/ExternalLibs/python-pip/20.3.4 ~/junotop/ExternalLibs ~/junotop/junoenv ~/junotop/junoenv

