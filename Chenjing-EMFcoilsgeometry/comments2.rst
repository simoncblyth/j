comments2
===============






Checking solid names
--------------------

Please use consistent solid name prefix eg "s_EMF" for all the solid names. Your
"u_section*" names do not have such a prefix.::

    (ok) A[blyth@localhost CSGFoundry]$ pwd
    /home/blyth/junosw/InstallArea/Chenjing-EMFcoilsgeometry/.opticks/GEOM/J25_7_2_opticks_Debug/CSGFoundry

    (ok) A[blyth@localhost CSGFoundry]$ egrep "u_section|EMF" meshname.txt
    s_EMFsupport_ring1
    s_EMFsupport_ring2
    s_EMFsupport_ring3
    s_EMFsupport_ring4
    s_EMFsupport_ring5
    s_EMFsupport_ring6
    s_EMFsupport_ring7
    s_EMFsupport_ring8
    s_EMFsupport_ring9
    s_EMFsupport_ring10
    s_EMFsupport_ring11
    s_EMFsupport_ring12
    s_EMFsupport_ring13
    s_EMFsupport_ring14
    s_EMFsupport_ring15
    s_EMFsupport_ring16
    s_EMFsupport_ring17
    s_EMFsupport_ring18
    s_EMFsupport_ring19
    s_EMFsupport_ring20
    s_EMFsupport_ring21
    s_EMFsupport_ring22
    s_EMFsupport_ring23
    u_section_0
    u_section_1
    u_section_2
    u_section_3
    u_section_4
    u_section_5
    u_section_6
    u_section_7
    u_section_8
    ...

    (ok) A[blyth@localhost CSGFoundry]$ egrep "u_section|EMF" meshname.txt  | wc -l 
    642

    (ok) A[blyth@localhost CSGFoundry]$ cat meshname.txt | wc -l
    986


Comparing to other branch shows you now add 642 solids, almost trebling the total to 986::

    (ok) A[blyth@localhost junosw]$ GEOM cf
    cd /home/blyth/junosw/InstallArea/yupd-8inch-pmt/.opticks/GEOM/J25_7_2_opticks_Debug/CSGFoundry

    (ok) A[blyth@localhost CSGFoundry]$ wc -l meshname.txt 
    348 meshname.txt

    (ok) A[blyth@localhost CSGFoundry]$ echo $(( 348 + 642 ))
    990

    (ok) A[blyth@localhost CSGFoundry]$ echo "scale=3; 986/348" | bc
    2.833



Check volume numbers
-----------------------

::

    (ok) A[blyth@localhost CSGFoundry]$  ~/o/CSG/tests/CSGFoundryLoadTest.sh | egrep "s_EMF|u_section"  | wc -l 
    1096

Names
-------

::

     s_EMFsupport_ring1-23
     MOI=s_EMFsupport_ring1:0:-2 cxr_min.sh    # highest Z horizontal support ring
     MOI=s_EMFsupport_ring23:0:-2 cxr_min.sh   # lowest Z horizontal support ring
     
     u_section_0-16   # radial sticks

     s_EMFcoil_holder_ring_mod    # equatorial slanted
     s_EMFcoil_holder_ring        # slanted  




Check volume sizes
--------------------

I note you have avoided the very small solids::

    (ok) A[blyth@localhost CSGFoundry]$  ~/o/CSG/tests/CSGFoundryLoadTest.sh | egrep "s_EMF|u_section" 
     234 :  ; ce = np.array([     0.000,     0.000,    37.500, 21448.000])  ; bb = np.array([-21448.000,-21448.000,     0.000, 21448.000, 21448.000,    75.000])  # CSGPrim::descRangeNumPy  lvid  54 ridx    0 pidx   234 so[s_EMFsupport_ring12]
     235 :  ; ce = np.array([     0.000,     0.000, -3077.956, 21322.898])  ; bb = np.array([-21322.898,-21322.898, -3115.456, 21322.898, 21322.898, -3040.456])  # CSGPrim::descRangeNumPy  lvid  55 ridx    0 pidx   235 so[s_EMFsupport_ring13]
     233 :  ; ce = np.array([     0.000,     0.000,  3245.450, 21309.240])  ; bb = np.array([-21309.240,-21309.240,  3207.950, 21309.240, 21309.240,  3282.950])  # CSGPrim::descRangeNumPy  lvid  53 ridx    0 pidx   233 so[s_EMFsupport_ring11]
     236 :  ; ce = np.array([     0.000,     0.000, -6234.198, 20616.525])  ; bb = np.array([-20616.525,-20616.525, -6271.698, 20616.525, 20616.525, -6196.698])  # CSGPrim::descRangeNumPy  lvid  56 ridx    0 pidx   236 so[s_EMFsupport_ring14]
     232 :  ; ce = np.array([     0.000,     0.000,  6336.013, 20608.428])  ; bb = np.array([-20608.428,-20608.428,  6298.513, 20608.428, 20608.428,  6373.513])  # CSGPrim::descRangeNumPy  lvid  52 ridx    0 pidx   232 so[s_EMFsupport_ring10]
     237 :  ; ce = np.array([     0.000,     0.000, -9125.520, 19504.275])  ; bb = np.array([-19504.275,-19504.275, -9163.020, 19504.275, 19504.275, -9088.020])  # CSGPrim::descRangeNumPy  lvid  57 ridx    0 pidx   237 so[s_EMFsupport_ring15]
     231 :  ; ce = np.array([     0.000,     0.000,  9288.095, 19463.059])  ; bb = np.array([-19463.059,-19463.059,  9250.595, 19463.059, 19463.059,  9325.595])  # CSGPrim::descRangeNumPy  lvid  51 ridx    0 pidx   231 so[s_EMFsupport_ring9]
     238 :  ; ce = np.array([     0.000,     0.000,-11904.396, 17938.121])  ; bb = np.array([-17938.121,-17938.121,-11941.896, 17938.121, 17938.121,-11866.896])  # CSGPrim::descRangeNumPy  lvid  58 ridx    0 pidx   238 so[s_EMFsupport_ring16]
     230 :  ; ce = np.array([     0.000,     0.000, 12037.634, 17899.379])  ; bb = np.array([-17899.379,-17899.379, 12000.134, 17899.379, 17899.379, 12075.134])  # CSGPrim::descRangeNumPy  lvid  50 ridx    0 pidx   230 so[s_EMFsupport_ring8]
     239 :  ; ce = np.array([     0.000,     0.000,-14321.239, 16069.143])  ; bb = np.array([-16069.143,-16069.143,-14358.739, 16069.143, 16069.143,-14283.739])  # CSGPrim::descRangeNumPy  lvid  59 ridx    0 pidx   239 so[s_EMFsupport_ring17]
     229 :  ; ce = np.array([     0.000,     0.000, 14469.818, 16003.342])  ; bb = np.array([-16003.342,-16003.342, 14432.318, 16003.342, 16003.342, 14507.318])  # CSGPrim::descRangeNumPy  lvid  49 ridx    0 pidx   229 so[s_EMFsupport_ring7]
     240 :  ; ce = np.array([     0.000,     0.000,-16416.420, 13916.468])  ; bb = np.array([-13916.468,-13916.468,-16453.920, 13916.468, 13916.468,-16378.920])  # CSGPrim::descRangeNumPy  lvid  60 ridx    0 pidx   240 so[s_EMFsupport_ring18]
     228 :  ; ce = np.array([     0.000,     0.000, 16555.607, 13840.499])  ; bb = np.array([-13840.499,-13840.499, 16518.107, 13840.499, 13840.499, 16593.107])  # CSGPrim::descRangeNumPy  lvid  48 ridx    0 pidx   228 so[s_EMFsupport_ring6]
     ...









Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstructionEMF.hh

Your "WaterPoolConstructionEMF.hh" is not a standalone header, it is
rather a piece of code that must be included into a specific place 
in some other code. That is the ultimate in being non-flexible.

There is no justification to define this code like that. You should
define via a struct or class like::

   #pragma once

   struct WaterPoolConstructionEMF
   {
       

   };




















::

     310         # --- EMF coils system (single switch) ---
     311         # --emf-coils-system / --no-emf-coils-system
     312         grp_det_comp.add_argument(
     313             "--emf-coils-system",
     314             dest="emf_coils_system_enabled",
     315             default=False,
     316             action=argparse.BooleanOptionalAction,
     317             help=mh("Enable the full EMF coil-and-support system.")
     318         )
     319 


Why default of 0?::

     320         # --- EMF steel reflectivity parameter ---
     321         # --emf-steel-reflectivity <float>
     322         grp_det_comp.add_argument(
     323             "--emf-steel-reflectivity",
     324             dest="emf_steel_reflectivity",
     325             default=0.0,
     326             type=float,
     327             help=mh("Set the reflectivity coefficient of EMF steel structures.")
     328         )

