read_rootfile_without_root
=============================


::

    epsilon:~ blyth$ find $JUNOTOP -name PMTParam_CD_LPMT.root
    /Users/blyth/junotop/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root
    epsilon:~ blyth$ 




/usr/local/opticks_externals/root_6.22.06.build/root-6.22.06/io/io/src/TFile.cxx::

    A ROOT file is a suite of consecutive data records (TKey instances) with
    a well defined format.

    If the key is located past the 32 bit file limit (> 2 GB) then some fields will
    be 8 instead of 4 bytes:

    Byte Range      | Member Name | Description
    ----------------|-----------|--------------
    1->4            | Nbytes    | Length of compressed object (in bytes)
    5->6            | Version   | TKey version identifier
    7->10           | ObjLen    | Length of uncompressed object
    11->14          | Datime    | Date and time when object was written to file
    15->16          | KeyLen    | Length of the key structure (in bytes)
    17->18          | Cycle     | Cycle of key
    19->22 [19->26] | SeekKey   | Pointer to record itself (consistency check)
    23->26 [27->34] | SeekPdir  | Pointer to directory header
    27->27 [35->35] | lname     | Number of bytes in the class name
    28->.. [36->..] | ClassName | Object Class Name
    ..->..          | lname     | Number of bytes in the object name
    ..->..          | Name      | lName bytes with the name of the object
    ..->..          | lTitle    | Number of bytes in the object title
    ..->..          | Title     | Title of the object
    ----->          | DATA      | Data bytes associated to the object

    The first data record starts at byte fBEGIN (currently set to kBEGIN).
    Bytes 1->kBEGIN contain the file description, when fVersion >= 1000000
    it is a large file (> 2 GB) and the offsets will be 8 bytes long and
    fUnits will be set to 8:
    Byte Range      | Record Name | Description
    ----------------|-------------|------------
    1->4            | "root"      | Root file identifier
    5->8            | fVersion    | File format version
    9->12           | fBEGIN      | Pointer to first data record
    13->16 [13->20] | fEND        | Pointer to first free word at the EOF
    17->20 [21->28] | fSeekFree   | Pointer to FREE data record
    21->24 [29->32] | fNbytesFree | Number of bytes in FREE data record
    25->28 [33->36] | nfree       | Number of free data records

    29->32 [37->40] | fNbytesName | Number of bytes in TNamed at creation time
    33->33 [41->41] | fUnits      | Number of bytes for file pointers
    34->37 [42->45] | fCompress   | Compression level and algorithm

    38->41 [46->53] | fSeekInfo   | Pointer to TStreamerInfo record
    42->45 [54->57] | fNbytesInfo | Number of bytes in TStreamerInfo record

    46->63 [58->75] | fUUID       | Universal Unique ID


::

    epsilon:root-6.22.06 blyth$ find . -name TDirectory.h
    ./core/base/inc/TDirectory.h


/usr/local/opticks_externals/root_6.22.06.build/root-6.22.06/core/base/inc/Bytes.h::

     15 //////////////////////////////////////////////////////////////////////////
     16 //                                                                      //
     17 // Bytes                                                                //
     18 //                                                                      //
     19 // A set of inline byte handling routines.                              //
     20 //                                                                      //
     21 // The set of tobuf() and frombuf() routines take care of packing a     //
     22 // basic type value into a buffer in network byte order (i.e. they      //
     23 // perform byte swapping when needed). The buffer does not have to      //
     24 // start on a machine (long) word boundary.                             //
     25 //                                                                      //
     26 // For __GNUC__ on linux on i486 processors and up                      //
     27 // use the `bswap' opcode provided by the GNU C Library.                //
     28 //                                                                      //
     29 // The set of host2net() and net2host() routines convert a basic type   //
     30 // value from host to network byte order and vice versa. On BIG ENDIAN  //
     31 // machines this is a no op.                                            //
     32 //                                                                      //
     33 //////////////////////////////////////////////////////////////////////////


The TCP/IP standard network byte order is big-endian.

From looking at /usr/local/opticks_externals/root_6.22.06.build/root-6.22.06/core/base/inc/Bytes.h 
see that TFile uses network byte order (big endian)::

    In [17]: np.c_[4*np.arange(100),a.reshape(-1,4)[:100],a.reshape(-1,4)[:100].view(">i4")   ]
    Out[17]: 
    array([[          0,         114,         111,         111,         116,  1919905652],
           [          4,           0,           0,         243,         198,       62406],
           [          8,           0,           0,           0,         100,         100],
           [         12,           0,          25,          80,         216,     1659096],
           [         16,           0,          25,          80,         151,     1659031],
           [         20,           0,           0,           0,          65,          65],
           [         24,           0,           0,           0,           1,           1],
           [         28,           0,           0,           0,          78,          78],
           [         32,           4,           0,           0,           0,    67108864],
           [         36,         101,           0,          25,          61,  1694505277],
           [         40,         173,           0,           0,          18, -1392508910],
           [         44,         117,           0,           1,          68,  1962934596],
           [         48,          26,         235,         230,         152,   451667608],
           [         52,         117,          17,         236,         179,  1964108979],
           [         56,          47,         197,          33,         122,   801448314],
           [         60,         202,         190,         239,           0,  -893456640],
           [         64,           0,           0,           0,           0,           0],
           [         68,           0,           0,           0,           0,           0],
           [         72,           0,           0,           0,           0,           0],
           [         76,           0,           0,           0,           0,           0],
           [         80,           0,           0,           0,           0,           0],
           [         84,           0,           0,           0,           0,           0],
           [         88,           0,           0,           0,           0,           0],
           [         92,           0,           0,           0,           0,           0],
           [         96,           0,           0,           0,           0,           0],
           [        100,           0,           0,           0,         138,         138],
           [        104,           0,           4,           0,           0,      262144],
           [        108,           0,          83,         108,         185,     5467321],




::

    In [1]: f = np.fromfile("PMTParam_CD_LPMT.root", dtype=np.int8 )

    In [2]: f.shape
    Out[2]: (1659096,)

    In [3]: f[0]
    Out[3]: 114

    In [4]: f[:10]
    Out[4]: array([114, 111, 111, 116,   0,   0, -13, -58,   0,   0], dtype=int8)


* https://root.cern.ch/root/html524/TFile.html


gbarrand
-----------

* https://github.com/gbarrand/inexlib_rio/blob/master/inexlib/inlib/inlib/rroot/file



Via uproot into python
--------------------------


::

    In [10]: tt = uproot.open("PMTParam_CD_LPMT.root")["data"]

    In [11]: tt                                                                                                                                                     
    Out[11]: <TTree 'data' (18 branches) at 0x000119f11f10>

    In [12]: aa = tt.arrays()

    In [13]: aa                                                                                                                                                     
    Out[13]: <Array [{pmtID: 0, ... afterPulseProb: 0.103}] type='17612 * {"pmtID": int32, "S...'>

    In [14]: aa[0]                                                                                                                                                  
    Out[14]: <Record ... afterPulseProb: 0.102} type='{"pmtID": int32, "SN": string, "Gain": ...'>

    In [15]: aa['pmtID']                                                                                                                                            
    Out[15]: <Array [0, 1, 2, 3, ... 17609, 17610, 17611] type='17612 * int32'>

    In [16]: uproot.version.version_info[0]
    Out[16]: '4'

    In [17]: aa = tt.arrays(library='np')

    In [18]: aa
    Out[18]: 
    {'pmtID': array([    0,     1,     2, ..., 17609, 17610, 17611], dtype=int32),
     'SN': array(['EA6277', 'EA3262', 'PA2006-1094', ..., 'EA3449', 'EA7099', 'EA5215'], dtype=object),
     'Gain': array([10005900., 10249800., 10599600., ..., 10090600.,  9882690.,  9750590.]),
     'Resolution': array([0.289, 0.231, 0.353, ..., 0.302, 0.278, 0.306]),
     'PDE': array([30.31 , 31.38 , 36.6  , ..., 30.853, 30.664, 31.813]),
     'DCR': array([ 5.656,  6.782, 13.828, ...,  6.525,  6.7  ,  7.661]),
     'TTS': array([6.53, 6.91, 8.21, ..., 6.08, 7.47, 6.15]),
     'TTS_SS': array([1.321, 1.356, 5.533, ..., 1.134, 1.237, 1.561]),
     'HV': array([1941., 1777., 1679., ..., 1959., 1746., 2029.]),
     'Amplitude': array([ 6.515,  6.582, 13.751, ...,  6.675,  1.265,  5.704]),
     'PvsV': array([3.816, 5.032, 3.055, ..., 3.395, 3.436, 3.513]),
     'SvsN': array([0.071, 0.071, 0.069, ..., 0.075, 0.072, 0.077]),
     'RiseTime': array([7.302, 6.915, 4.527, ..., 6.626, 7.112, 6.933]),
     'FallTime': array([10.725,  9.803, 17.868, ...,  9.685, 11.289,  9.321]),
     'FWHM': array([11.589, 11.383,  7.607, ..., 11.29 , 11.865, 10.97 ]),
     'timeOffset': array([41.898, 39.286, 65.928, ..., 38.131, 36.97 , 42.785]),
     'prePulseProb': array([0.001, 0.001, 0.009, ..., 0.001, 0.003, 0.001]),
     'afterPulseProb': array([0.102, 0.096, 0.032, ..., 0.095, 0.104, 0.103])}

    In [19]: aa['pmtID']
    Out[19]: array([    0,     1,     2, ..., 17609, 17610, 17611], dtype=int32)

    In [20]: aa['SN']
    Out[20]: array(['EA6277', 'EA3262', 'PA2006-1094', ..., 'EA3449', 'EA7099', 'EA5215'], dtype=object)

    In [21]: aa['pmtID'].shape
    Out[21]: (17612,)

    In [22]: aa['SN'].shape
    Out[22]: (17612,)

    In [23]: aa['Gain'].shape
    Out[23]: (17612,)

    In [24]: aa['Resolution'].shape
    Out[24]: (17612,)

    In [25]: aa['PDE'].shape
    Out[25]: (17612,)


