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

    jdevtoolset8()
    {
       source /opt/rh/devtoolset-8/enable
    }

    jcompiler()
    {
        : devtoolset-8 gcc not supported by ROOT 
        : so follow lint example from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-Pre0/quick-deploy-J21v2r0-Pre0.sh
        : and use JUNO gcc from cvmfs

        source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bashrc

        : sets    : JUNO_GCC_PREFIX, CC, CXX, FC
        : appends : PATH, LD_LIBRARY_PATH, MANPATH, INFOPATH
        :    
        
        source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bashrc

        : sets    : JUNO_BINUTILS_PREFIX
        : appends : PATH, LD_LIBRARY_PATH, MANPATH, INFOPATH
       
    }


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

ROOT build failing with another XrdCl undefined reference errors::

    [ROOT-install] Consolidate compiler generated dependencies of target G__NetxNG
    [ROOT-install] [ 68%] Built target G__NetxNG
    [ROOT-install] [ 68%] Linking CXX shared library ../../lib/libNetxNG.so
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGFile.cxx.o: In function `TNetXNGFile::Flush()':
    [ROOT-install] TNetXNGFile.cxx:(.text+0x3b3): undefined reference to `XrdCl::Status::ToString[abi:cxx11]() const'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGFile.cxx.o: In function `TNetXNGFile::ReadBuffer(char*, long long, int)':
    [ROOT-install] TNetXNGFile.cxx:(.text+0xa64): undefined reference to `XrdCl::Status::ToString[abi:cxx11]() const'
    [ROOT-install] TNetXNGFile.cxx:(.text+0xbba): undefined reference to `XrdCl::Status::ToString[abi:cxx11]() const'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGFile.cxx.o: In function `TNetXNGFile::ReadBuffers(char*, long long*, int*, int)':
    [ROOT-install] TNetXNGFile.cxx:(.text+0x20cb): undefined reference to `XrdCl::Status::ToString[abi:cxx11]() const'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x2712): undefined reference to `XrdCl::Status::ToString[abi:cxx11]() const'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGFile.cxx.o:TNetXNGFile.cxx:(.text+0x3098): more undefined references to `XrdCl::Status::ToString[abi:cxx11]() const' follow
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGFile.cxx.o: In function `TNetXNGFile::ReOpen(char const*)':
    [ROOT-install] TNetXNGFile.cxx:(.text+0x390f): undefined reference to `XrdCl::File::Open(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, XrdCl::OpenFlags::Flags, XrdCl::Access::Mode, unsigned short)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x3ac3): undefined reference to `XrdCl::Status::ToString[abi:cxx11]() const'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x3bce): undefined reference to `XrdCl::Status::ToString[abi:cxx11]() const'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGFile.cxx.o: In function `TNetXNGFile::GetVectorReadLimits()':
    [ROOT-install] TNetXNGFile.cxx:(.text+0x4630): undefined reference to `XrdCl::File::GetProperty(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&) const'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x4659): undefined reference to `XrdCl::URL::URL(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x46e8): undefined reference to `XrdCl::File::GetProperty(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&) const'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x4717): undefined reference to `XrdCl::URL::URL(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGFile.cxx.o: In function `TNetXNGFile::SetEnv()':
    [ROOT-install] TNetXNGFile.cxx:(.text+0x5053): undefined reference to `XrdCl::Env::PutInt(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x511f): undefined reference to `XrdCl::Env::PutInt(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x51ef): undefined reference to `XrdCl::Env::PutInt(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x52cd): undefined reference to `XrdCl::Env::PutInt(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x53a2): undefined reference to `XrdCl::Env::PutInt(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int)'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGFile.cxx.o:TNetXNGFile.cxx:(.text+0x547a): more undefined references to `XrdCl::Env::PutInt(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int)' follow
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGFile.cxx.o: In function `TNetXNGFile::SetEnv()':
    [ROOT-install] TNetXNGFile.cxx:(.text+0x5995): undefined reference to `XrdCl::Env::PutString(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x5ac4): undefined reference to `XrdCl::Env::PutString(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x5c04): undefined reference to `XrdCl::Env::PutString(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x5ca6): undefined reference to `XrdCl::Env::PutInt(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int)'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGFile.cxx.o: In function `TNetXNGFile::TNetXNGFile(char const*, char const*, char const*, char const*, int, int, bool)':
    [ROOT-install] TNetXNGFile.cxx:(.text+0x6a34): undefined reference to `XrdCl::URL::URL(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x6cad): undefined reference to `XrdCl::File::Open(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, XrdCl::OpenFlags::Flags, XrdCl::Access::Mode, XrdCl::ResponseHandler*, unsigned short)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x6dae): undefined reference to `XrdCl::Status::ToString[abi:cxx11]() const'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x6ed5): undefined reference to `XrdCl::DefaultEnv::SetLogLevel(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x6f65): undefined reference to `XrdCl::File::Open(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, XrdCl::OpenFlags::Flags, XrdCl::Access::Mode, unsigned short)'
    [ROOT-install] TNetXNGFile.cxx:(.text+0x7074): undefined reference to `XrdCl::Status::ToString[abi:cxx11]() const'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGFile.cxx.o: In function `TNetXNGFile::Close(char const*)':
    [ROOT-install] TNetXNGFile.cxx:(.text+0x7f13): undefined reference to `XrdCl::Status::ToString[abi:cxx11]() const'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGSystem.cxx.o: In function `TNetXNGSystem::GetDirEntry(void*)':
    [ROOT-install] TNetXNGSystem.cxx:(.text+0x6a): undefined reference to `XrdCl::FileSystem::DirList(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, XrdCl::DirListFlags::Flags, XrdCl::DirectoryList*&, unsigned short)'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGSystem.cxx.o: In function `TNetXNGSystem::MakeDirectory(char const*)':
    [ROOT-install] TNetXNGSystem.cxx:(.text+0x550): undefined reference to `XrdCl::FileSystem::MkDir(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, XrdCl::MkDirFlags::Flags, XrdCl::Access::Mode, unsigned short)'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGSystem.cxx.o: In function `TNetXNGSystem::Unlink(char const*)':
    [ROOT-install] TNetXNGSystem.cxx:(.text+0x722): undefined reference to `XrdCl::FileSystem::Stat(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, XrdCl::StatInfo*&, unsigned short)'
    [ROOT-install] TNetXNGSystem.cxx:(.text+0x766): undefined reference to `XrdCl::FileSystem::Rm(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, unsigned short)'
    [ROOT-install] TNetXNGSystem.cxx:(.text+0x8e2): undefined reference to `XrdCl::FileSystem::RmDir(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, unsigned short)'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGSystem.cxx.o: In function `TNetXNGSystem::GetPathInfo(char const*, FileStat_t&)':
    [ROOT-install] TNetXNGSystem.cxx:(.text+0xbfc): undefined reference to `XrdCl::FileSystem::Stat(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, XrdCl::StatInfo*&, unsigned short)'
    [ROOT-install] TNetXNGSystem.cxx:(.text+0xdf4): undefined reference to `XrdCl::StatInfo::GetId[abi:cxx11]() const'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGSystem.cxx.o: In function `TNetXNGSystem::TNetXNGSystem(char const*, bool)':
    [ROOT-install] TNetXNGSystem.cxx:(.text+0x1690): undefined reference to `XrdCl::URL::URL(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
    [ROOT-install] TNetXNGSystem.cxx:(.text+0x16e1): undefined reference to `XrdCl::URL::URL(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGSystem.cxx.o: In function `TNetXNGSystem::Stage(TCollection*, unsigned char)':
    [ROOT-install] TNetXNGSystem.cxx:(.text+0x207d): undefined reference to `XrdCl::FileSystem::Prepare(std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > const&, XrdCl::PrepareFlags::Flags, unsigned char, XrdCl::Buffer*&, unsigned short)'
    [ROOT-install] CMakeFiles/NetxNG.dir/src/TNetXNGSystem.cxx.o: In function `TNetXNGSystem::Locate(char const*, TString&)':
    [ROOT-install] TNetXNGSystem.cxx:(.text+0x23d8): undefined reference to `XrdCl::FileSystem::Locate(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, XrdCl::OpenFlags::Flags, XrdCl::LocationInfo*&, unsigned short)'
    [ROOT-install] TNetXNGSystem.cxx:(.text+0x25dc): undefined reference to `XrdCl::URL::URL(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
    [ROOT-install] collect2: error: ld returned 1 exit status
    [ROOT-install] make[2]: *** [lib/libNetxNG.so] Error 1
    [ROOT-install] make[1]: *** [net/netxng/CMakeFiles/NetxNG.dir/all] Error 2
    [ROOT-install] make: *** [all] Error 2
    [ROOT-install] /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06 /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06 /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    [ROOT-install] /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build/root-6.24.06 /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Build /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    ==== juno-ext-libs-setup:
    [ROOT-setup] /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06 /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    [ROOT-setup] ===== juno-ext-libs-PKG-setup: call juno-ext-libs-ROOT-generate-sh to generate user defined
    [ROOT-setup] ==== juno-ext-libs-generate-csh: call juno-ext-libs-ROOT-generate-csh to generate user defined
    [ROOT-setup] /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    L7[blyth@lxslc708 junoenv]$ 



Instead on L7 lxslc7 try to reuse all the externals
----------------------------------------------------- 

::

    L7[blyth@lxslc708 ~]$ t jlibs_reuse
    jlibs_reuse () 
    { 
        [ -z "$JUNO_EXTLIB_OLDTOP" ] && echo $FUNCNAME requires envvar JUNO_EXTLIB_OLDTOP && return 1;
        [ ! -d "$JUNO_EXTLIB_OLDTOP" ] && echo $FUNCNAME requires directory JUNO_EXTLIB_OLDTOP $JUNO_EXTLIB_OLDTOP && return 2;
        local libs=$(jlibs-);
        for lib in $libs;
        do
            echo $lib;
            bash junoenv libs reuse $lib || return 1;
        done;
        return 0
    }


Following along https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation
not that $JUNOTOP/bashrc.sh contains version numbers in the paths so it 
always needs to be regenerated::

    L7[blyth@lxslc701 junoenv]$ bash junoenv env resetup

    L7[blyth@lxslc701 junoenv]$ cat $JUNOTOP/bashrc.sh
    export JUNOTOP=/hpcfs/juno/junogpu/blyth/junotop
    export CMTPROJECTPATH=/hpcfs/juno/junogpu/blyth/junotop:${CMTPROJECTPATH}
    source /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Python/3.8.12/bashrc
    source /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/python-setuptools/58.0.4/bashrc
    source /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/python-pip/21.2.4/bashrc
    source /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/python-cython/0.29.24/bashrc
    source /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/python-numpy/1.21.2/bashrc
    source /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Boost/1.77.0/bashrc
    source /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Cmake/3.21.2/bashrc
    source /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Git/2.33.0/bashrc
    source /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Xercesc/3.2.2/bashrc
    ...


bash junoenv cmtlibs : cmt not found warnings : oops need to jcompiler first
------------------------------------------------------------------------------

::

    L7[blyth@lxslc701 junoenv]$ bash junoenv cmtlibs
    ...
    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/CMT/v1r26/Linux-x86_64/cmt
    ==== junoenv-EI-check-preq: setup /hpcfs/juno/junogpu/blyth/junotop/junoenv/packages/frontier.sh
    ==== junoenv-EI-check-preq: setup frontier
    ==== junoenv-EI-check-preq: check again frontier
    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/CMT/v1r26/Linux-x86_64/cmt
    /hpcfs/juno/junogpu/blyth/junotop/ExternalInterface/EIRelease/cmt /hpcfs/juno/junogpu/blyth/junotop/ExternalInterface /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    cmt: /lib64/libstdc++.so.6: version `CXXABI_1.3.9' not found (required by cmt)
    cmt: /lib64/libstdc++.so.6: version `GLIBCXX_3.4.21' not found (required by cmt)
    /hpcfs/juno/junogpu/blyth/junotop/ExternalInterface /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    L7[blyth@lxslc701 junoenv]$ 

After jcompiler "bash junoenv cmtlibs" completes without warnings.



bash junoenv sniper : download seems to be hanging
----------------------------------------------------

* it manages to complete, but warnings maybe due to wrong compiler again

::

    L7[blyth@lxslc701 junoenv]$ bash junoenv sniper
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
    == setup-juno-sniper
    === junoenv-sniper: 0
    === junoenv-sniper: SNiPER URL: https://github.com/SNiPER-Framework/sniper/archive/v2.0.3.tar.gz
    === junoenv-sniper: MT SNiPER URL: https://github.com/SNiPER-Framework/mt.sniper/archive/v0.1.1.tar.gz
    ==== junoenv-sniper-get: download the source code https://github.com/SNiPER-Framework/sniper/archive/v2.0.3.tar.gz
      % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                     Dload  Upload   Total   Spent    Left  Speed
      0     0    0     0    0     0      0      0 --:--:--  0:01:10 --:--:--     0



    ...

    ==== junoenv-sniper-get: download the source code https://github.com/SNiPER-Framework/mt.sniper/archive/v0.1.1.tar.gz
    ==== junoenv-sniper-check-preq: Pre Requirement Check
    ==== junoenv-sniper-check-preq: source /hpcfs/juno/junogpu/blyth/junotop/bashrc.sh
    /hpcfs/juno/junogpu/blyth/junotop/sniper /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    /hpcfs/juno/junogpu/blyth/junotop/sniper/build /hpcfs/juno/junogpu/blyth/junotop/sniper /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    cmake: /lib64/libstdc++.so.6: version `GLIBCXX_3.4.22' not found (required by cmake)
    cmake: /lib64/libstdc++.so.6: version `GLIBCXX_3.4.20' not found (required by cmake)
    cmake: /lib64/libstdc++.so.6: version `GLIBCXX_3.4.21' not found (required by cmake)
    cmake: /lib64/libstdc++.so.6: version `CXXABI_1.3.9' not found (required by cmake)



bash junoenv sniper : without doing a cleanup yields lots of CMake errors
----------------------------------------------------------------------------


::

    L7[blyth@lxslc701 junoenv]$ bash junoenv sniper
    = The junoenv is in /hpcfs/juno/junogpu/blyth/junotop/junoenv
    = main
    = THE JUNOTOP is /hpcfs/juno/junogpu/blyth/junotop
    = THE JUNOENVDIR is /hpcfs/juno/junogpu/blyth/junotop/junoenv
    == setup-juno-basic-preq: ================================================================
    == setup-juno-basic-preq: GLOBAL Environment Variables:
    == setup-juno-basic-preq: $JUNOTOP is "/hpcfs/juno/junogpu/blyth/junotop"
    == setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs"
    == setup-juno-basic-preq: $JUNOARCHIVEGET: ""
    == setup-juno-basic-preq: $JUNOARCHIVEURL: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
    == setup-juno-basic-preq: $CMTEXTRATAGS: ""
    == setup-juno-basic-preq: ================================================================
    == setup-juno-sniper
    === junoenv-sniper: 0
    === junoenv-sniper: SNiPER URL: https://github.com/SNiPER-Framework/sniper/archive/v2.0.3.tar.gz
    === junoenv-sniper: MT SNiPER URL: https://github.com/SNiPER-Framework/mt.sniper/archive/v0.1.1.tar.gz
    ==== junoenv-sniper-get: download the source code https://github.com/SNiPER-Framework/sniper/archive/v2.0.3.tar.gz
    ==== junoenv-sniper-get: download the source code https://github.com/SNiPER-Framework/mt.sniper/archive/v0.1.1.tar.gz
    ==== junoenv-sniper-check-preq: Pre Requirement Check
    ==== junoenv-sniper-check-preq: source /hpcfs/juno/junogpu/blyth/junotop/bashrc.sh
    /hpcfs/juno/junogpu/blyth/junotop/sniper /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    /hpcfs/juno/junogpu/blyth/junotop/sniper/build /hpcfs/juno/junogpu/blyth/junotop/sniper /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
      Compatibility with CMake < 2.8.12 will be removed from a future version of
      CMake.

      Update the VERSION argument <min> value or use a ...<max> suffix to tell
      CMake that the project does not need compatibility with older versions.


    -- cmake version 3.21.2
    -- The C compiler identification is GNU 8.3.0
    -- The CXX compiler identification is GNU 8.3.0
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working C compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/gcc - skipped
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Performing Test COMPILER_SUPPORTS_CXX11
    -- Performing Test COMPILER_SUPPORTS_CXX11 - Success
    -- Looking for include file unistd.h
    -- Looking for include file unistd.h - found
    -- Looking for include file time.h
    -- Looking for include file time.h - found
    -- Looking for include file dlfcn.h
    -- Looking for include file dlfcn.h - found
    -- Found UnixCommands: /usr/bin/bash  
    -- Found Git: /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Git/2.33.0/bin/git (found version "2.33.0") 
    -- Found CMT: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/CMT/v1r26/Linux-x86_64/cmt (found version "1.26") 
    -- Found PythonLibs: /usr/lib64/libpython2.7.so (found suitable version "2.7.5", minimum required is "2.7") 
    -- Found PythonInterp: /usr/bin/python2.7 (found suitable exact version "2.7.5") 
    -- Found Boost: /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Boost/1.77.0/lib/cmake/Boost-1.77.0/BoostConfig.cmake (found suitable version "1.77.0", minimum required is "1.53") found components: python 
    fatal: not a git repository (or any parent up to mount point /)
    Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set).
    CMake Warning at CMakeLists.txt:160 (message):
      Project version mismatch: cmake=1.3 git=


    fatal: not a git repository (or any parent up to mount point /)
    Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set).
    fatal: not a git repository (or any parent up to mount point /)
    Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set).
    fatal: not a git repository (or any parent up to mount point /)
    Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set).
    -- CMAKE_INSTALL_INCLUDEDIR="include" ; CMAKE_INSTALL_LIBDIR="lib64" ; CMAKE_INSTALL_DATADIR="share/sniper" ; CMAKE_INSTALL_PYTHONDIR="lib64/python2.7/site-packages" ; CMAKE_INSTALL_CMTPROJECTDIR="share/sniper/cmt-project/sniper"
    CMake Deprecation Warning at SniperKernel/CMakeLists.txt:1 (cmake_minimum_required):
      Compatibility with CMake < 2.8.12 will be removed from a future version of
      CMake.

      Update the VERSION argument <min> value or use a ...<max> suffix to tell
      CMake that the project does not need compatibility with older versions.


    CMake Deprecation Warning at SniperKernel/CMakeLists.txt:21 (cmake_policy):
      The OLD behavior for policy CMP0026 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.

    ...

    -- Configuring done
    CMake Error: The following variables are used in this project, but they are set to NOTFOUND.
    Please set them or make sure they are set and tested correctly in the CMake files:
    ROOT_PyROOT_LIBRARY
        linked by target "RootWriter" in directory /hpcfs/juno/junogpu/blyth/junotop/sniper/SniperSvc/RootWriter

    -- Generating done
    CMake Generate step failed.  Build files cannot be regenerated correctly.
    L7[blyth@lxslc701 junoenv]$ which cmake
    /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Cmake/3.21.2/bin/cmake
    L7[blyth@lxslc701 junoenv]$ 




bash junoenv sniper : after cleanup seems to complete OK
----------------------------------------------------------------------------

Try doing it from scratch completes with only some compilation warnings::

    L7[blyth@lxslc701 junotop]$ rm -rf sniper
    L7[blyth@lxslc701 junotop]$ rm -rf mt.sniper
    L7[blyth@lxslc701 junoenv]$ bash junoenv sniper



bash junoenv offline
----------------------

::

    L7[blyth@lxslc701 junoenv]$ jt
    /hpcfs/juno/junogpu/blyth/junotop

    L7[blyth@lxslc701 junotop]$ mv offline offline_old

    L7[blyth@lxslc701 junotop]$ je
    /hpcfs/juno/junogpu/blyth/junotop/junoenv

    L7[blyth@lxslc701 junoenv]$ bash junoenv offline 




::

    A    offline/JunoRelease/cmt
    A    offline/JunoRelease/cmt/requirements
    A    offline/JunoRelease/cmt/version.cmt
     U   offline
    Checked out revision 5174.
    /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    ==== junoenv-offline-compile: Can't find sniper/SniperRelease/cmt/setup.sh, switch from cmt to cmake mode
    /hpcfs/juno/junogpu/blyth/junotop/offline /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    /hpcfs/juno/junogpu/blyth/junotop/offline/build /hpcfs/juno/junogpu/blyth/junotop/offline /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop /hpcfs/juno/junogpu/blyth/junotop/junoenv /hpcfs/juno/junogpu/blyth/junotop/junoenv
    -- Build type: Release
    -- CMAKE_C_FLAGS_RELEASE: 
    -- CMAKE_CXX_FLAGS_RELEASE: 
    -- The C compiler identification is GNU 8.3.0
    -- The CXX compiler identification is GNU 8.3.0
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working C compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/gcc - skipped
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Found Python: /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8 (found version "3.8.12") found components: Interpreter Development Development.Module Development.Embed 
    Found Python /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Python/3.8.12/lib/libpython3.8.so
    -- Found Boost: /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Boost/1.77.0/lib/cmake/Boost-1.77.0/BoostConfig.cmake (found version "1.77.0") found components: python filesystem system regex 
    Found Boost: Boost::python;Boost::filesystem;Boost::system;Boost::regex
    -- Found XercesC: /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Xercesc/3.2.2/lib/libxerces-c.so (found version "3.2.2") 
    Found XercesC: /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Xercesc/3.2.2/include /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Xercesc/3.2.2/lib/libxerces-c.so
    The XercesC found target: XercesC::XercesC


    Found ROOT: /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libCore.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libImt.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libRIO.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libNet.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libHist.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGraf.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGraf3d.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGpad.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libROOTDataFrame.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libTree.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libTreePlayer.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libRint.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libPostscript.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMatrix.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libPhysics.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMathCore.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libThread.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMultiProc.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libROOTVecOps.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libEG.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libEve.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGeom.so;/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMathMore.so
    -- Found Python: /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8 (found suitable version "3.8.12", minimum required is "3.8.12") found components: Interpreter 
    -- Found SNiPER: /hpcfs/juno/junogpu/blyth/junotop/sniper/InstallArea/lib64/cmake/SNiPER/SNiPERConfig.cmake  



::

    083 function junoenv-offline-compile-cmake {
     84     local msg="==== $FUNCNAME: "
     85     pushd $(juno-top-dir) >& /dev/null
     86 
     87     if [ -d "$(junoenv-offline-name)" ]; then
     88         pushd $(junoenv-offline-name)
     89 
     90         # create the build directory
     91         [ -d "build" ] || mkdir build || exit -1
     92         # create the install directory
     93         [ -d "InstallArea" ] || mkdir InstallArea || exit -1
     94         local installprefix=$(juno-top-dir)/$(junoenv-offline-name)/InstallArea
     95         # start the build and install of sniper
     96         pushd build
     97         cmake .. -DCMAKE_INSTALL_PREFIX=$installprefix -DCMAKE_CXX_STANDARD=17 || exit -1
     98         make || exit -1
     99         make install || exit -1
    100         popd # build
    101 
    102         popd # $(junoenv-offline-name)
    103     fi
    104 
    105     popd >& /dev/null # $(juno-top-dir)
    106 }
    107 
    108 function junoenv-offline-compile {
    109     local msg="==== $FUNCNAME: "
    110     pushd $(juno-top-dir) >& /dev/null
    111 
    112     # if the sniper v1 (with SniperRelease) does not exist, switch to cmake
    113     if [ ! -f "sniper/SniperRelease/cmt/setup.sh" ]; then
    114         echo $msg "Can't find sniper/SniperRelease/cmt/setup.sh, switch from cmt to cmake mode"
    115         junoenv-offline-compile-cmake
    116     else
    117         junoenv-offline-compile-cmt
    118     fi
    119 
    120     popd >& /dev/null
    121 }


CMake Infrastructure
---------------------

::


    jo ; find . -name CMakeLists.txt -exec bash -c "echo {} && cat {}" \; 


    ./Reconstruction/RecCdMuonAlg/CMakeLists.txt
    PKG(RecCdMuonAlg
        DEPENDS
        RecEvent
        CalibEvent
        Identifier
        Geometry
        EvtNavigator
        DataRegistritionSvc
        BufferMemMgr
        SNiPER::RootWriterLib
        $<$<BOOL:${WITH_OEC}>:EvtStore>
        $<$<BOOL:${WITH_OEC}>:EvtDataTypes>
        $<$<BOOL:${WITH_OEC}>:OECEvent>
    )



    epsilon:offline blyth$ find . -type f -exec grep -H WITH_OEC {} \; | grep -v .svn
    ./CMakeLists.txt:if (WITH_OEC)
    ./cmake/JUNOOptionDefinitions.cmake:option (WITH_OEC "Enable OEC in offline" OFF)
    ./cmake/JUNOOptionDefinitions.cmake:if (WITH_OEC)
    ./cmake/JUNOOptionDefinitions.cmake:    add_definitions(-DWITH_OEC)
    ./OEC/OECPolicy/cmt/requirements:# The macro WITH_OEC will be available during compilation. 
    ./OEC/OECPolicy/cmt/requirements:      oec                " -DWITH_OEC "
    ./build.sh:##   - There are macros WITH_OEC in the source code
    ./build.sh:##   - An option WITH_OEC is defined in cmake
    ./build.sh:##       JUNO_WITH_OEC=1 ./build.sh
    ./build.sh:function var-withoec-envvar() { echo JUNO_WITH_OEC; }
    ./build.sh:function var-withoec-value() { echo -DWITH_OEC=ON; }
    ./build.sh:function var-withoec-value-if-disabled() { echo -DWITH_OEC=OFF; }
    ./Doc/oum/source/releasenotes/J21v2r0-Pre0.md:  * The OEC package is now also integrated. Use the cmake option WITH_OEC to enable it.
    ./Reconstruction/RecWpMuonAlg/CMakeLists.txt:        $<$<BOOL:${WITH_OEC}>:EvtStore>
    ./Reconstruction/RecWpMuonAlg/CMakeLists.txt:        $<$<BOOL:${WITH_OEC}>:EvtDataTypes>
    ./Reconstruction/RecWpMuonAlg/CMakeLists.txt:        $<$<BOOL:${WITH_OEC}>:OECEvent>
    ./Reconstruction/RecWpMuonAlg/src/RecWpMuonAlg.cc:#ifdef WITH_OEC
    ./Reconstruction/RecWpMuonAlg/src/RecWpMuonAlg.cc:#ifdef WITH_OEC
    ./Reconstruction/RecWpMuonAlg/src/RecWpMuonAlg.cc:#ifdef WITH_OEC
    ./Reconstruction/RecWpMuonAlg/src/RecWpMuonAlg.cc:#ifdef WITH_OEC 
    ./Reconstruction/RecWpMuonAlg/src/RecWpMuonAlg.h:#ifdef WITH_OEC
    ./Reconstruction/RecWpMuonAlg/src/RecWpMuonAlg.h:#ifdef WITH_OEC
    ./Reconstruction/QCtrRecAlg/CMakeLists.txt:    $<$<BOOL:${WITH_OEC}>:EvtStore>
    ./Reconstruction/QCtrRecAlg/CMakeLists.txt:    $<$<BOOL:${WITH_OEC}>:EvtDataTypes>
    ./Reconstruction/QCtrRecAlg/CMakeLists.txt:    $<$<BOOL:${WITH_OEC}>:OECEvent>
    ./Reconstruction/QCtrRecAlg/src/QCtrRecAlg.h:#ifdef WITH_OEC
    ./Reconstruction/QCtrRecAlg/src/QCtrRecAlg.h:#ifdef WITH_OEC
    ./Reconstruction/QCtrRecAlg/src/QCtrRecAlg.cc:#ifdef WITH_OEC
    ./Reconstruction/QCtrRecAlg/src/QCtrRecAlg.cc:#ifdef WITH_OEC
    ./Reconstruction/QCtrRecAlg/src/QCtrRecAlg.cc:#ifdef WITH_OEC
    ./Reconstruction/QCtrRecAlg/src/QCtrRecAlg.cc:#ifdef WITH_OEC
    ./Reconstruction/QCtrRecAlg/src/QCtrRecAlg.cc:#ifdef WITH_OEC
    ./Reconstruction/RecCdMuonAlg/CMakeLists.txt:    $<$<BOOL:${WITH_OEC}>:EvtStore>
    ./Reconstruction/RecCdMuonAlg/CMakeLists.txt:    $<$<BOOL:${WITH_OEC}>:EvtDataTypes>
    ./Reconstruction/RecCdMuonAlg/CMakeLists.txt:    $<$<BOOL:${WITH_OEC}>:OECEvent>
    ./Reconstruction/RecCdMuonAlg/src/RecCdMuonAlg.cc:#ifdef WITH_OEC
    ./Reconstruction/RecCdMuonAlg/src/RecCdMuonAlg.cc:#ifdef WITH_OEC
    ./Reconstruction/RecCdMuonAlg/src/RecCdMuonAlg.cc:#ifdef WITH_OEC
    ./Reconstruction/RecCdMuonAlg/src/RecCdMuonAlg.cc:#ifdef WITH_OEC 
    ./Reconstruction/RecCdMuonAlg/src/RecCdMuonAlg.h:#ifdef WITH_OEC
    ./Reconstruction/RecCdMuonAlg/src/RecCdMuonAlg.h:#ifdef WITH_OEC
    epsilon:offline blyth$ 



build.sh::

    111 ##   - run below with build.sh:
    112 ##       JUNO_GEN_GRAPH=1 ./build.sh
    113 ##   - run below command under build:
    114 ##       dot -Tpdf -o junooffline.pdf junooffline.dot
    115 function var-graphviz-envvar() { echo JUNO_GEN_GRAPH; }
    116 function var-graphviz-value()  { echo --graphviz=junooffline.dot; }
    117 
    118 ## Build offline with OEC
    119 ##   - There are macros WITH_OEC in the source code
    120 ##   - An option WITH_OEC is defined in cmake
    121 ##   - run below command:
    122 ##       JUNO_WITH_OEC=1 ./build.sh
    123 function var-withoec-envvar() { echo JUNO_WITH_OEC; }
    124 function var-withoec-value() { echo -DWITH_OEC=ON; }
    125 function var-withoec-value-if-disabled() { echo -DWITH_OEC=OFF; }
    126 


Hmm why do that ? Why not auto-switch macros based on whether find_package succeeds ?
Need to be sensitive to CMAKE_PREFIX_PATH and avoid stomping on it.


