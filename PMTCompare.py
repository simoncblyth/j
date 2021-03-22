#!/usr/bin/env python
"""
PMT.py
=======

Comparing pmt categories between sim (PMTSimParamSvc) and par (PMTParamSvc)

"""
import logging
from collections import OrderedDict as odict
log = logging.getLogger(__name__)
import numpy as np

from PMTParamSvc import PMTParamSvc
from PMTParamSvc import kPMT_Unknown, kPMT_NNVT, kPMT_Hamamatsu, kPMT_HZC, kPMT_NNVT_HighQE

par_enum = [kPMT_Unknown, kPMT_NNVT, kPMT_Hamamatsu, kPMT_HZC, kPMT_NNVT_HighQE]
par_names = odict()
par_names[kPMT_Unknown]="kPMT_Unknown"
par_names[kPMT_NNVT]="kPMT_NNVT"
par_names[kPMT_Hamamatsu]="kPMT_Hamamatsu"
par_names[kPMT_HZC]="kPMT_HZC"
par_names[kPMT_NNVT_HighQE]="kPMT_NNVT_HighQE"

from PMTSimParamSvc import PMTSimParamSvc
from PMTSimParamSvc import kPMTType_Unknown, kPMTType_Hamamatsu, kPMTType_HiQENNVT, kPMTType_NormalNNVT, kPMTType_HZC

sim_enum = [kPMTType_Unknown, kPMTType_Hamamatsu, kPMTType_HiQENNVT, kPMTType_NormalNNVT, kPMTType_HZC]
sim_names = odict()
sim_names[kPMTType_Unknown]="kPMTType_Unknown"
sim_names[kPMTType_Hamamatsu]="kPMTType_Hamamatsu"
sim_names[kPMTType_HiQENNVT]="kPMTType_HiQENNVT"
sim_names[kPMTType_NormalNNVT]="kPMTType_NormalNNVT"
sim_names[kPMTType_HZC]="kPMTType_HZC"

# arrays that map enum sim->par and par->sim indices,  +1 turns the enum value into a 0-based index
sp = 1 + np.array( [kPMT_Unknown, kPMT_Hamamatsu, kPMT_NNVT_HighQE, kPMT_NNVT, kPMT_HZC], dtype=np.int32 )
ps = 1 + np.array( [kPMTType_Unknown, kPMTType_NormalNNVT, kPMTType_Hamamatsu, kPMTType_HZC, kPMTType_HiQENNVT], dtype=np.int32 )
# notice how these mappings use the order of the other type 

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)

    sim = PMTSimParamSvc()
    par = PMTParamSvc()

    num_lpmt = len(sim.a)
    pmtid = np.arange(num_lpmt)

    sim_cat = sim.getPMTCategory(pmtid)  # NB pmtid is an array with all IDs 
    par_cat = par.getPMTCategory(pmtid)

    par_cat_s = ps[par_cat+1]-1   # translate par_cat into sim lingo for comparison with sim_cat
    sim_cat_p = sp[sim_cat+1]-1   # translate sim_cat into par lingo for comparison with par_cat

    print()
    for es in sim_enum:
        ep = sp[es+1] - 1
        print(" es : %2d : sim_name %-20s : ep : %2d : par_name %-20s " % (es, sim_names[es], ep, par_names[ep]))
    pass

    print()
    for ep in par_enum:
        es = ps[ep+1] - 1
        print(" ep : %2d : par_name %-20s : es : %2d : sim_name %-20s " % (ep, par_names[ep], es, sim_names[es]))
    pass

    mismatch_sp = par_cat != sim_cat_p
    mismatch_ps = sim_cat != par_cat_s

    print("np.count_nonzero(mismatch_sp) : %d " % np.count_nonzero(mismatch_sp)) 
    print("np.count_nonzero(mismatch_ps) : %d " % np.count_nonzero(mismatch_ps)) 

    print("mismatch_sp.shape %s " % str(mismatch_sp.shape) )
    print("mismatch_ps.shape %s " % str(mismatch_ps.shape) )
    assert np.all(mismatch_sp == mismatch_ps)
    mismatch = mismatch_sp  # the mismatches match in either direction

    u_sim_cat_mismatch, u_sim_cat_mismatch_counts = np.unique(sim_cat[mismatch], return_counts=True)  
    print("u_sim_cat_mismatch       : %s " % str(u_sim_cat_mismatch))
    print("u_sim_cat_mismatch_counts: %s " % str(u_sim_cat_mismatch_counts))

    for i in range(len(u_sim_cat_mismatch)):
        es = u_sim_cat_mismatch[i]
        es_count = u_sim_cat_mismatch_counts[i]
        print( " es %2d : es_count %5s : sim_name %-20s " % (es, es_count, sim_names[es]))
    pass

    u_par_cat_mismatch, u_par_cat_mismatch_counts = np.unique(par_cat[mismatch], return_counts=True)  
    print("u_par_cat_mismatch       : %s " % str(u_par_cat_mismatch))
    print("u_par_cat_mismatch_counts: %s " % str(u_par_cat_mismatch_counts))

    for i in range(len(u_par_cat_mismatch)):
        ep = u_par_cat_mismatch[i]
        ep_count = u_par_cat_mismatch_counts[i]
        print( " ep %2d : ep_count %5s : par_name %-20s " % (ep, ep_count, par_names[ep]))
    pass


