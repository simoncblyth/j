lxslc7-offline-build
======================

Following 

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation

Running *jlibs* to update externals::


   L7[blyth@lxslc710 junoenv]$ t jlibs
    jlibs () 
    { 
        cd $JUNOTOP/junoenv;
        local libs=$(bash junoenv libs list | perl -ne 'm, (\S*)@, && print "$1\n"' -);
        for lib in $libs;
        do
            echo $lib;
            bash junoenv libs all $lib || return 1;
        done
    }
    L7[blyth@lxslc710 junoenv]$ libs=$(bash junoenv libs list | perl -ne 'm, (\S*)@, && print "$1\n"' -)
    L7[blyth@lxslc710 junoenv]$ echo $libs
    python python-setuptools python-pip python-cython python-numpy boost cmake git xercesc gsl fftw3 sqlite3 log4cpp libxml2 LHAPDF pythia6 tbb cmt clhep xrootd ROOT hepmc geant4 genie nuwro talys libmore libmore-data mysql-connector-c mysql-connector-cpp libyaml python-yaml pacparser frontier
    L7[blyth@lxslc710 junoenv]$ 



Encounter network issue with xrootd::

    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup cmake: source /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Cmake/3.21.2/bashrc
    === junoenv-external-libs: juno-ext-libs-check-is-reused xrootd
    === junoenv-external-libs: juno-ext-libs-all xrootd
    ==== juno-ext-libs-get:
    [xrootd-conf] ===== juno-ext-libs-PKG-get: Download
    [xrootd-conf]   % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
    [xrootd-conf]                                  Dload  Upload   Total   Spent    Left  Speed
      0     0    0     0    0     0      0      0 --:--:--  0:02:00 --:--:--     0
    [xrootd-conf] curl: (35) Encountered end of file
    [xrootd-conf] rm: cannot remove 'xrootd-5.3.1.zip': No such file or directory
    [xrootd-conf] --2021-12-02 21:04:31--  https://github.com/xrootd/xrootd/archive/v5.3.1.zip
    [xrootd-conf] Resolving github.com (github.com)... 20.205.243.166
    [xrootd-conf] Connecting to github.com (github.com)|20.205.243.166|:443... connected.
    [xrootd-conf] Unable to establish SSL connection.
    [xrootd-conf] rm: cannot remove 'xrootd-5.3.1.zip': No such file or directory
    ==== juno-ext-libs-conf:
    [xrootd-conf] ===== juno-ext-libs-PKG-get: Download
    [xrootd-conf]   % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
    [xrootd-conf]                                  Dload  Upload   Total   Spent    Left  Speed
      0     0    0     0    0     0      0      0 --:--:--  0:03:03 --:--:--     0
    [xrootd-conf] curl: (35) Encountered end of file
    [xrootd-conf] rm: cannot remove 'xrootd-5.3.1.zip': No such file or directory
    [xrootd-conf] --2021-12-02 21:10:38--  https://github.com/xrootd/xrootd/archive/v5.3.1.zip
    [xrootd-conf] Resolving github.com (github.com)... 20.205.243.166
    [xrootd-conf] Connecting to github.com (github.com)|20.205.243.166|:443... failed: Connection timed out.
    [xrootd-conf] Retrying.
    [xrootd-conf] 
    [xrootd-conf] --2021-12-02 21:12:46--  (try: 2)  https://github.com/xrootd/xrootd/archive/v5.3.1.zip
    [xrootd-conf] Connecting to github.com (github.com)|20.205.243.166|:443... connected.
    [xrootd-conf] Unable to establish SSL connection.
    [xrootd-conf] rm: cannot remove 'xrootd-5.3.1.zip': No such file or directory
    ==== juno-ext-libs-make:



::

    L7[blyth@lxslc710 junoenv]$ bash junoenv libs list
    = The junoenv is in /hpcfs/juno/junogpu/blyth/junotop/junoenv
    = main
    = THE JUNOTOP is /hpcfs/juno/junogpu/blyth/junotop
    = THE JUNOENVDIR is /hpcfs/juno/junogpu/blyth/junotop/junoenv
    == setup-juno-basic-preq: ================================================================
    == setup-juno-basic-preq: GLOBAL Environment Variables:
    == setup-juno-basic-preq: $JUNOTOP is "/hpcfs/juno/junogpu/blyth/junotop"
    == setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: ""
    == setup-juno-basic-preq: $JUNOARCHIVEGET: ""
    == setup-juno-basic-preq: $JUNOARCHIVEURL: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
    == setup-juno-basic-preq: $CMTEXTRATAGS: ""
    == setup-juno-basic-preq: ================================================================
    == setup-juno-external-libs
    === junoenv-external-libs: allpkgs will be loaded
    === junoenv-external-libs: python python-setuptools python-pip python-cython python-numpy boost cmake git xercesc gsl fftw3 sqlite3 log4cpp libxml2 LHAPDF pythia6 tbb cmt clhep xrootd ROOT hepmc geant4 genie nuwro talys libmore libmore-data mysql-connector-c mysql-connector-cpp libyaml python-yaml pacparser frontier
    === junoenv-external-libs: command: list
    === junoenv-external-libs: packages: python python-setuptools python-pip python-cython python-numpy boost cmake git xercesc gsl fftw3 sqlite3 log4cpp libxml2 LHAPDF pythia6 tbb cmt clhep xrootd ROOT hepmc geant4 genie nuwro talys libmore libmore-data mysql-connector-c mysql-connector-cpp libyaml python-yaml pacparser frontier
    ==== juno-ext-libs-list: [x] python@3.8.12 
    ==== juno-ext-libs-list: [x] python-setuptools@58.0.4 -> python
    ==== juno-ext-libs-list: [x] python-pip@21.2.4 -> python python-setuptools
    ==== juno-ext-libs-list: [x] python-cython@0.29.24 -> python
    ==== juno-ext-libs-list: [x] python-numpy@1.21.2 -> python python-setuptools python-cython
    ==== juno-ext-libs-list: [x] boost@1.77.0 -> python python-numpy
    ==== juno-ext-libs-list: [x] cmake@3.21.2 
    ==== juno-ext-libs-list: [x] git@2.33.0 
    ==== juno-ext-libs-list: [x] xercesc@3.2.2 
    ==== juno-ext-libs-list: [x] gsl@2.5 
    ==== juno-ext-libs-list: [x] fftw3@3.3.8 
    ==== juno-ext-libs-list: [x] sqlite3@3.35.5 
    ==== juno-ext-libs-list: [x] log4cpp@1.1.3 
    ==== juno-ext-libs-list: [x] libxml2@2.9.12 -> python
    ==== juno-ext-libs-list: [x] LHAPDF@6.3.0 -> python
    ==== juno-ext-libs-list: [x] pythia6@6.4.28 -> python
    ==== juno-ext-libs-list: [x] tbb@2019_U8 
    ==== juno-ext-libs-list: [x] cmt@v1r26 
    ==== juno-ext-libs-list: [x] clhep@2.4.1.0 -> cmake
    ==== juno-ext-libs-list: [ ] xrootd@5.3.1 -> python cmake
    ==== juno-ext-libs-list: [ ] ROOT@6.24.06 -> python boost cmake +git +gccxml xercesc +qt4 gsl fftw3 tbb xrootd +sqlite3 pythia6
    ==== juno-ext-libs-list: [x] hepmc@2.06.09 
    ==== juno-ext-libs-list: [ ] geant4@10.04.p02.juno -> python boost cmake xercesc +qt4 +clhep ROOT
    ==== juno-ext-libs-list: [ ] genie@3.00.06 -> python log4cpp libxml2 LHAPDF pythia6 ROOT
    ==== juno-ext-libs-list: [ ] nuwro@19.02.2 -> libxml2 pythia6 ROOT
    ==== juno-ext-libs-list: [ ] talys@1.95 -> pythia6 ROOT
    ==== juno-ext-libs-list: [x] libmore@0.8.3 
    ==== juno-ext-libs-list: [x] libmore-data@20140630 -> libmore
    ==== juno-ext-libs-list: [x] mysql-connector-c@6.1.9 -> cmake
    ==== juno-ext-libs-list: [ ] mysql-connector-cpp@1.1.12 -> boost cmake mysql-connector-c
    ==== juno-ext-libs-list: [ ] libyaml@0.2.4 
    ==== juno-ext-libs-list: [ ] python-yaml@5.4.1.1 -> python python-cython libyaml
    ==== juno-ext-libs-list: [x] pacparser@1.3.7 
    ==== juno-ext-libs-list: [x] frontier@2.9.1 -> pacparser
    L7[blyth@lxslc710 junoenv]$ 




There was a zero size zip::

    L7[blyth@lxslc701 Build]$ pwd
    /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build
    L7[blyth@lxslc701 Build]$ l xrootd*
       0 -rw-r--r--  1 blyth dyw       0 Dec  2 21:32 xrootd-5.3.1.zip
    3720 -rw-r--r--  1 blyth dyw 3807229 Mar 19  2021 xrootd-4.12.6.zip


Repeating seems to work::

    L7[blyth@lxslc710 junoenv]$ bash junoenv libs all xrootd



::

    L7[blyth@lxslc710 junoenv]$ bash junoenv libs all ROOT
    ...

    [ROOT-install] Consolidate compiler generated dependencies of target G__ROOTDataFrame
    [ROOT-install] [ 86%] Built target G__ROOTDataFrame
    [ROOT-install] Consolidate compiler generated dependencies of target ROOTDataFrame
    [ROOT-install] [ 86%] Building CXX object tree/dataframe/CMakeFiles/ROOTDataFrame.dir/src/RDFInterfaceUtils.cxx.o
    [ROOT-install] /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/src/RDFInterfaceUtils.cxx: In lambda function:
    [ROOT-install] /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/src/RDFInterfaceUtils.cxx:155:39: error: call of overloaded 'basic_string(std::remove_reference<TString&>::type)' is ambiguous
    [ROOT-install]        return std::string(std::move(ss));
    [ROOT-install]                                        ^
    [ROOT-install] In file included from /opt/rh/devtoolset-8/root/usr/include/c++/8/string:52,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/core/meta/inc/TSchemaHelper.h:17,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/core/meta/inc/TGenericClassInfo.h:21,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/core/base/inc/Rtypes.h:191,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/inc/ROOT/RDF/RColumnReaderBase.hxx:14,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/inc/ROOT/RDF/ColumnReaderUtils.hxx:14,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/inc/ROOT/RDF/RAction.hxx:14,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/inc/ROOT/RDF/InterfaceUtils.hxx:14,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/src/RDFInterfaceUtils.cxx:11:
    [ROOT-install] /opt/rh/devtoolset-8/root/usr/include/c++/8/bits/basic_string.h:3571:7: note: candidate: 'std::basic_string<_CharT, _Traits, _Alloc>::basic_string(std::basic_string<_CharT, _Traits, _Alloc>&&) [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]'
    [ROOT-install]        basic_string(basic_string&& __str)
    [ROOT-install]        ^~~~~~~~~~~~
    [ROOT-install] /opt/rh/devtoolset-8/root/usr/include/c++/8/bits/basic_string.h:3554:7: note: candidate: 'std::basic_string<_CharT, _Traits, _Alloc>::basic_string(const _CharT*, const _Alloc&) [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]'
    [ROOT-install]        basic_string(const _CharT* __s, const _Alloc& __a = _Alloc());
    [ROOT-install]        ^~~~~~~~~~~~
    [ROOT-install] /opt/rh/devtoolset-8/root/usr/include/c++/8/bits/basic_string.h:3507:7: note: candidate: 'std::basic_string<_CharT, _Traits, _Alloc>::basic_string(const std::basic_string<_CharT, _Traits, _Alloc>&) [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]'
    [ROOT-install]        basic_string(const basic_string& __str);
    [ROOT-install]        ^~~~~~~~~~~~
    [ROOT-install] /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/src/RDFInterfaceUtils.cxx: In function '{anonymous}::ParsedExpression {anonymous}::ParseRDFExpression(const string&, const ColumnNames_t&, const ColumnNames_t&, const ColumnNames_t&, const std::map<std::basic_string<char>, std::basic_string<char> >&)':
    [ROOT-install] /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/src/RDFInterfaceUtils.cxx:173:31: error: invalid operands of types 'const char [3]' and 'void' to binary 'operator+'
    [ROOT-install]        TPRegexp replacer("\\b" + escapeDots(colOrAlias) + "\\b"); // watch out: need to replace colOrAlias, not col
    [ROOT-install]                          ~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
    [ROOT-install] /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/src/RDFInterfaceUtils.cxx:177:63: error: call of overloaded 'basic_string(std::remove_reference<TString&>::type)' is ambiguous
    [ROOT-install]     return ParsedExpression{std::string(std::move(exprWithVars)), std::move(usedCols), std::move(varNames)};
    [ROOT-install]                                                                ^
    [ROOT-install] In file included from /opt/rh/devtoolset-8/root/usr/include/c++/8/string:52,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/core/meta/inc/TSchemaHelper.h:17,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/core/meta/inc/TGenericClassInfo.h:21,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/core/base/inc/Rtypes.h:191,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/inc/ROOT/RDF/RColumnReaderBase.hxx:14,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/inc/ROOT/RDF/ColumnReaderUtils.hxx:14,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/inc/ROOT/RDF/RAction.hxx:14,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/inc/ROOT/RDF/InterfaceUtils.hxx:14,
    [ROOT-install]                  from /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/tree/dataframe/src/RDFInterfaceUtils.cxx:11:
    [ROOT-install] /opt/rh/devtoolset-8/root/usr/include/c++/8/bits/basic_string.h:3571:7: note: candidate: 'std::basic_string<_CharT, _Traits, _Alloc>::basic_string(std::basic_string<_CharT, _Traits, _Alloc>&&) [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]'
    [ROOT-install]        basic_string(basic_string&& __str)
    [ROOT-install]        ^~~~~~~~~~~~
    [ROOT-install] /opt/rh/devtoolset-8/root/usr/include/c++/8/bits/basic_string.h:3554:7: note: candidate: 'std::basic_string<_CharT, _Traits, _Alloc>::basic_string(const _CharT*, const _Alloc&) [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]'
    [ROOT-install]        basic_string(const _CharT* __s, const _Alloc& __a = _Alloc());
    [ROOT-install]        ^~~~~~~~~~~~
    [ROOT-install] /opt/rh/devtoolset-8/root/usr/include/c++/8/bits/basic_string.h:3507:7: note: candidate: 'std::basic_string<_CharT, _Traits, _Alloc>::basic_string(const std::basic_string<_CharT, _Traits, _Alloc>&) [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]'
    [ROOT-install]        basic_string(const basic_string& __str);
    [ROOT-install]        ^~~~~~~~~~~~
    [ROOT-install] make[2]: *** [tree/dataframe/CMakeFiles/ROOTDataFrame.dir/build.make:230: tree/dataframe/CMakeFiles/ROOTDataFrame.dir/src/RDFInterfaceUtils.cxx.o] Error 1
    [ROOT-install] make[1]: *** [CMakeFiles/Makefile2:28944: tree/dataframe/CMakeFiles/ROOTDataFrame.dir/all] Error 2
    [ROOT-install] make: *** [Makefile:156: all] Error 2
    [ROOT-install] /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06 /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06 /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    [ROOT-install] /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/ro



::

    145 static ParsedExpression ParseRDFExpression(const std::string &expr, const ColumnNames_t &treeBranchNames,
    146                                            const ColumnNames_t &customColNames, const ColumnNames_t &dataSourceColNames,
    147                                            const std::map<std::string, std::string> &aliasMap)
    148 {
    149    const auto usedColsAndAliases = FindUsedColumns(expr, treeBranchNames, customColNames, dataSourceColNames, aliasMap);
    150 
    151    auto escapeDots = [](const std::string &s) {
    152       TString ss(s);
    153       TPRegexp dot("\\.");
    154       dot.Substitute(ss, "\\.", "g");
    155       return std::string(std::move(ss));
    156    };
    157 
    158    ColumnNames_t varNames;
    159    ColumnNames_t usedCols;
    160    TString exprWithVars(expr); // same as expr but column names will be substituted with the variable names in varNames
    161    for (const auto &colOrAlias : usedColsAndAliases) {
    162       const auto col = ResolveAlias(colOrAlias, aliasMap);
    163       unsigned int varIdx; // index of the variable in varName corresponding to col
    164       if (!IsStrInVec(col, usedCols)) {
    165          usedCols.emplace_back(col);
    166          varIdx = varNames.size();
    167          varNames.emplace_back("var" + std::to_string(varIdx));
    168       } else {
    169          // colOrAlias must be an alias that resolves to a column we have already seen.
    170          // Find back the corresponding varName
    171          varIdx = std::distance(usedCols.begin(), std::find(usedCols.begin(), usedCols.end(), col));
    172       }
    173       TPRegexp replacer("\\b" + escapeDots(colOrAlias) + "\\b"); // watch out: need to replace colOrAlias, not col
    174       replacer.Substitute(exprWithVars, varNames[varIdx], "g");
    175    }
    176 
    177    return ParsedExpression{std::string(std::move(exprWithVars)), std::move(usedCols), std::move(varNames)};
    178 }


* https://root-forum.cern.ch/t/root-6-24-06-not-compiling-with-c-17/47913

* https://root-forum.cern.ch/t/devtoolset-gcc-toolset-compatibility/38286

* https://root-forum.cern.ch/t/weird-error-std-basic-string-with-root-6-08-04/23754/6


pcanal
Feb '17

Hi,

Cling does not (yet?) support devtoolset (due to limitation in clang).

To get ROOT to work, you will need to install a full fledged version of the compiler.

Cheers,
Philippe.



Axel
Feb '17

Hi,

My bet is that you / we switched the ABI for ROOT 6.08, and to satisfy symbol
requests for that new ABI GCC needs to resolve symbols from the static library
of the devtoolset - which is exactly what we don’t support.

And indeed - in the past you needed some specific code (code involving
std::error_code was one example) to see a failure due to the way devtoolset is
set up. Now, with the new ABI, it’s everywhere.

I’m afraid that you will have to grab a compiler from EPEL until we implement
support for devtoolset… which we haven’t gotten to for the last three years
:frowning:

Cheers, Axel.





Hi Simon,

Yes, we also encounter such problem before. You can use the GCC 8.3.0 provided
by JUNO.  You can have a look at my installation script to see how to reuse the
external libraries::

    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-Pre0/quick-deploy-J21v2r0-Pre0.sh

BTW: As I mentioned in the last meeting, I had setup a new CVMFS repository for nightly build::

     /cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc830/b

The nightly build consists a shell script and a crontab::

    [junopub@cvmfspublisher ~]$ crontab -l
    25 17 * * * bash <<< "$(bash /cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc830/b/build-tools/build.sh deployit)"

The software is built in a container on the cvmfspublisher. The reason why I
use '<<<' is because the CVMFS will check any file belong this repository is
used or not. If the shell script is still used, then the publish will be
failed. 

If I remember correctly, you had the access to the opticks CVMFS repository. So
you can create a directory for such usage.  I think one missing part is the
CUDA is not included inside the container. I am not sure is that easy to deploy
it inside the container. 

Maybe we can contact with Jingyan Shi and Ran Du for the help. 

Tao



Config to use the JUNO gcc as hinted by Tao
--------------------------------------------------------------

::

    #source /opt/rh/devtoolset-8/enable
    # devtoolset not supported by ROOT
    #  /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-Pre0/quick-deploy-J21v2r0-Pre0.sh

    # COMPILER
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bashrc
    export CC=${JUNO_GCC_PREFIX}/bin/gcc
    export CXX=${JUNO_GCC_PREFIX}/bin/g++

::

    L7[blyth@lxslc708 junoenv]$ which gcc
    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/gcc
    L7[blyth@lxslc708 junoenv]$ gcc --version
    gcc (GCC) 8.3.0
    Copyright (C) 2018 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.



But rerun yields same error with sign that devtoolset gcc still being used : presumably need to start from scratch with the other compiler
----------------------------------------------------------------------------------------------------------------------------------------------

::

    L7[blyth@lxslc708 junoenv]$ rm -rf /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06
    L7[blyth@lxslc708 junoenv]$ bash junoenv libs all ROOT








