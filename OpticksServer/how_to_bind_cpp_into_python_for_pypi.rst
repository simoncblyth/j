how_to_bind_cpp_into_python_for_pypi
=========================================


* https://stackoverflow.com/questions/67254000/making-a-cross-platform-pypi-package-with-c-extensions-wrapped-with-pybind11

* https://github.com/grpc/grpc




C++ Python Binding and PyPI packaging example
-----------------------------------------------

* https://discuss.python.org/t/how-to-clone-and-compile-c-code-into-binaries-within-the-package-during-pip-install/25394/7


Experimental Python bindings for the OpenFace library.
----------------------------------------------------------

* https://github.com/TadasBaltrusaitis/OpenFace/pull/858
* https://github.com/TadasBaltrusaitis/OpenFace/pull/858/files
* https://github.com/TadasBaltrusaitis/OpenFace/issues/898

pybind11 (supports C++17 among others)
----------------------------------------

* https://github.com/pybind/pybind11
* https://pybind11.readthedocs.io/en/latest/



Meson and Bazel are alts to CMake with little traction
--------------------------------------------------------

* https://github.com/bazelbuild/bazel

* https://mesonbuild.com/
* https://github.com/mesonbuild/meson



pybind/cmake_example
-----------------------

* https://github.com/pybind/cmake_example
* https://github.com/pybind/cmake_example/blob/master/CMakeLists.txt

::

    git clone --recursive https://github.com/pybind/cmake_example.git


::

    A[blyth@localhost ai]$ git clone --recursive https://github.com/pybind/cmake_example.git
    Cloning into 'cmake_example'...
    remote: Enumerating objects: 646, done.
    remote: Counting objects: 100% (92/92), done.
    remote: Compressing objects: 100% (23/23), done.
    remote: Total 646 (delta 76), reused 69 (delta 69), pack-reused 554 (from 1)
    Receiving objects: 100% (646/646), 141.81 KiB | 261.00 KiB/s, done.
    Resolving deltas: 100% (387/387), done.
    Submodule 'pybind11' (https://github.com/pybind/pybind11.git) registered for path 'pybind11'
    Cloning into '/usr/local/ai/cmake_example/pybind11'...
    remote: Enumerating objects: 28073, done.        
    remote: Counting objects: 100% (361/361), done.        
    remote: Compressing objects: 100% (208/208), done.        
    remote: Total 28073 (delta 281), reused 153 (delta 153), pack-reused 27712 (from 3)        
    Receiving objects: 100% (28073/28073), 12.44 MiB | 2.61 MiB/s, done.
    Resolving deltas: 100% (19741/19741), done.
    Submodule path 'pybind11': checked out '914c06fb252b6cc3727d0eedab6736e88a3fcb01'
    A[blyth@localhost ai]$ 


::

    A[blyth@localhost cmake_example]$ uv pip install .
    Resolved 1 package in 7.63s
      × Failed to build `cmake-example @ file:///usr/local/ai/cmake_example`
      ├─▶ The build backend returned an error
      ╰─▶ Call to `setuptools.build_meta.build_wheel` failed (exit status: 1)

          [stdout]
          running bdist_wheel
          running build
          running build_ext
          -- The C compiler identification is GNU 11.5.0
          -- The CXX compiler identification is GNU 11.5.0
          -- Detecting C compiler ABI info
          -- Detecting C compiler ABI info - done
          -- Check for working C compiler: /usr/bin/cc - skipped
          -- Detecting C compile features
          -- Detecting C compile features - done
          -- Detecting CXX compiler ABI info
          -- Detecting CXX compiler ABI info - done
          -- Check for working CXX compiler: /usr/bin/c++ - skipped
          -- Detecting CXX compile features
          -- Detecting CXX compile features - done
          -- Configuring incomplete, errors occurred!

          [stderr]
          CMake Error at pybind11/CMakeLists.txt:8 (cmake_minimum_required):
            Compatibility with CMake < 3.5 has been removed from CMake.

            Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
            to tell CMake that the project requires at least <min> but has been updated
            to work with policies introduced by <max> or earlier.

            Or, add -DCMAKE_POLICY_VERSION_MINIMUM=3.5 to try configuring anyway.



::

    A[blyth@localhost cmake_example]$ CMAKE_ARGS="-DCMAKE_POLICY_VERSION_MINIMUM=3.5" uv pip install .
    Resolved 1 package in 500ms
          Built cmake-example @ file:///usr/local/ai/cmake_example
    Prepared 1 package in 3.32s
    Installed 1 package in 1ms
     + cmake-example==0.0.1 (from file:///usr/local/ai/cmake_example)
    A[blyth@localhost cmake_example]$ 







:google:`C++ CMake pybind11 pypi example`
------------------------------------------

* https://stackoverflow.com/questions/74545298/how-to-create-a-python-package-from-a-pybind11-module-created-with-cmake
* https://stackoverflow.com/questions/45225381/pybind11-cmake-how-to-install-files/76667253#76667253

::

    cmake_minimum_required(VERSION 3.0)

    project(foo)

    FILE(GLOB foo_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

    FIND_PACKAGE(pybind11 REQUIRED)
    pybind11_add_module(mylib ${foo_SRCS})

    include(GNUInstallDirs)


    find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
    ...
    install(TARGETS mylib
            COMPONENT python
            LIBRARY DESTINATION "lib/python${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}/site-packages"
            ARCHIVE DESTINATION "lib"
            RUNTIME DESTINATION "bin")



pybind11 tute
-----------------

* https://levelup.gitconnected.com/pybind11-a-beginners-guide-to-setting-up-c-and-python-projects-1de2f04465e9


* https://pypi.org/project/example-python-extension-cpp/


* https://stackoverflow.com/questions/71127446/is-passing-numpy-arrays-to-c-via-pybind-supposed-to-be-this-slow


pybind11 passing numpy array to C++ and returning one
-------------------------------------------------------

* https://zingale.github.io/phy504/cxx-python-sum.html
* https://zingale.github.io/phy504/cxx-python-array.html


::

    (cmake_example) A[blyth@localhost src]$ python -m pybind11 --includes
    /usr/local/ai/cmake_example/.venv/bin/python: No module named pybind11
    (cmake_example) A[blyth@localhost src]$ cd ..
    (cmake_example) A[blyth@localhost cmake_example]$ uv pip install pybind11
    Resolved 1 package in 1.14s
    Prepared 1 package in 766ms
    Installed 1 package in 50ms
     + pybind11==3.0.1
    (cmake_example) A[blyth@localhost cmake_example]$ python -m pybind11 --includes
    -I/usr/include/python3.9 -I/usr/local/ai/cmake_example/.venv/lib64/python3.9/site-packages/pybind11/include
    (cmake_example) A[blyth@localhost cmake_example]$ 






