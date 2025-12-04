cxt_min_simtrace_overlap_check/index
=====================================


Repeating overlap check by:

1. switching to the branch in question eg:origin/yupd_waterdistributor_heightfix

2. clean building OJ with ljbbc which also does geometry conversion
   (this required some transient Opticks changes for backward compatibility
   to handle JUNOSW without pmtNum in this old branch and lacking the 600 MPMT by
   changing s_pmt.h  NUM_WP_ATM_MPMT to 0 (from 600))

3. doing a simtrace with "cxt_min.sh" with MOI Waterdistributor_2:0:-2

4. plotting and overlap checking with::

PRIMTAB=1 OVERLAP=1 KEY=deeppink,honeydew cxt_min.sh pdb


Where those color keynames correspond to the below listed volumes::

           deeppink : 2570   408282      500 : HamamatsuR12860sMask_virtual 
            honeydew : 2740   276744      607 : Waterdistributor_3 

No sign of overlap is apparent, with good clearance visible. 
The 3D interactive view is much clearer that just the screenshot.



