#!/usr/bin/env python
"""
ipython -i PMTAngular.py 

PMTAngular::get_pmt_ce pmtcat -1 pmtidx 0 qe_type 0 pmt_type 0 ce_cat  100 ce    1.00000 volname kPMT_Unknown
PMTAngular::get_pmt_ce pmtcat  0 pmtidx 1 qe_type 0 pmt_type 0 ce_cat    5 ce    1.00000 volname NNVTMCPPMT_PMT_20inch_body_phys
PMTAngular::get_pmt_ce pmtcat  1 pmtidx 2 qe_type 0 pmt_type 1 ce_cat    4 ce    0.91100 volname HamamatsuR12860_PMT_20inch_body_phys
PMTAngular::get_pmt_ce pmtcat  2 pmtidx 3 qe_type 0 pmt_type 0 ce_cat  100 ce    1.00000 volname kPMT_HZC
PMTAngular::get_pmt_ce pmtcat  3 pmtidx 4 qe_type 1 pmt_type 0 ce_cat    6 ce    0.00000 volname NNVTMCPPMT_PMT_20inch_body_phys

"""
import os, logging, numpy as np
import matplotlib.pyplot as plt
log = logging.getLogger(__name__)

class PMTAngular(object):
    FOLD = "/tmp/PMTAngular"

    def __init__(self):
        theta = np.load(os.path.join(self.FOLD, "theta.npy"))
        ce = np.load(os.path.join(self.FOLD, "ce.npy"))

        

        ce_names = "kPMT_Unknown,kPMT_NNVT,kPMT_Hamamatsu,kPMT_HZC,kPMT_NNVT_HighQE".split(",")
        ce_order = [2,1,4]    # Ham, NNVT, NNVT_HighQE
        gce_names = ["gCE_R12860","gCE_NNVTMCP","gCE_NNVTMCP_HiQE"] 

        #gce_names = list(filter(lambda name:name.startswith("gCE_"), os.listdir(self.FOLD)))
        gce = {}
        for name in gce_names:
            gce[name] = np.load(os.path.join(self.FOLD, "%s.npy"%name))
        pass
 
        self.theta = theta 
        self.ce = ce
        self.ce_names = ce_names
        self.ce_order = ce_order
        self.gce = gce
        self.gce_names = gce_names
       


if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    t = PMTAngular()

    title = "~/j/PMTAngular/PMTAngular.py"
    color = "rgbcmyk"

    fig1, ax = plt.subplots(figsize=[12.8,7.2])
    fig1.suptitle(title)
    for j,p in enumerate(t.ce):
        ax.plot(  t.theta, t.ce[j], label=t.ce_names[j],color=color[j]  ) 
        if j in t.ce_order:       
            i = t.ce_order.index(j)
            cname = t.gce_names[i]
            gce = t.gce.get(cname, None)
            if not gce is None and len(gce.shape)>1:
                ax.scatter(  gce[:,0], gce[:,1], label=cname, color=color[j]  ) 
            pass 
            ax.axvspan(14, 35, color='grey', alpha=0.3, lw=0)
        pass
    pass
    ax.plot( [t.theta[0], t.theta[-1]], [1,1], linestyle="dotted", color="red" )
    ax.legend()
    fig1.show()

    fig1path = os.path.join(t.FOLD, "PMTAngular_fig1.png") 
    log.info(fig1path)
    fig1.savefig(fig1path)



    fig2, axs = plt.subplots(3, figsize=[12.8,7.2])
    fig2.suptitle(title)

    for i, j in enumerate(t.ce_order):
        ax = axs[i]
        ax.plot(  t.theta, t.ce[j], label=t.ce_names[j], color=color[j] ) 
        cname = t.gce_names[i]
        gce = t.gce.get(cname, None)
        if not gce is None:
            ax.scatter(  gce[:,0], gce[:,1], label=cname, color=color[j]  ) 
        pass 
        ax.plot( [t.theta[0], t.theta[-1]], [1,1], linestyle="dotted", color="red" )
        #ax.set_ylim(0,1.1)
        ax.legend()

        if i == 1:
            ax.axvspan(14, 35, color='grey', alpha=0.3, lw=0)
        pass
    pass
    fig2.show()
    fig2path = os.path.join(t.FOLD, "PMTAngular_fig2.png") 
    log.info(fig2path)
    fig2.savefig(fig2path)




