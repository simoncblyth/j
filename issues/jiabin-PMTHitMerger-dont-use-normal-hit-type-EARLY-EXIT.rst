Hi Jiabin, 

Thank you for the problem reports.  When you report issues
it is best to use copy/pasted plain text not png images.

> Now I can use the GPU to running script.However, some errors occurred in the
> output file, like the one below,::
> 
>     Error in cling:: AutoLoadingVisitor:: InsertIntoAutoLoadingState:
>     Missing FileEntry for Event/EventObject.h requested to autoload type JM:: EventObject
>     Error in cling:: AutoLoadingVisitor:: InsertIntoAutoLoadingState:
>     Missing FileEntry for Event/HeaderObject.h requested to autoload type JM: :HeaderObject
>     Error in cling:: AutoLoadingVisitor:: InsertIntoAutoLoadingState:
>     Missing FileEntry for /builds/JUNO/offline/junosw/DataModel/EDMUtil/EDMUtil/FileMetaData.h requested to autoload type JM::TreeMetaData
>     Error in cling:: AutoLoadingVisitor::InsertIntoAutoLoadingState:
>     Missing FileEntry for /builds/JUNO/offline/junosw/DataModel/EDMUtil/EDMUtil/FileMetaData.h requested to autoload type JM:: FileMetaData
>     Error in cling:: AutoLoadingVisitor:: InsertIntoAutoLoadingState:
>     Missing FileEntry for /builds/JUNO/offline/junosw/DataModel/EDMUtil/EDMUtil/JobInfo.h requested to autoload type JobInfo
>     Error in cling:: AutoLoadingVisitor: :InsertIntoAutoLoadingState:


These cling errors comes from JUNOSW, if I recall correctly the cause is related to a minor
change in compiler version and do not cause problems.


> along with a large number of warnings::
> 
>      WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted
>      WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted
>      WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted
>      WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted
>      WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted
> 
> Is there any way to eliminate these
> warnings because it has over 20 million lines

This issue is a new one to me. 
The problem suggests somehow the PMTHitMerger::init is not
being called to setup the hitCollection. I need to do some
debugging to investigate this.

Did your job save any hits ? Did the job complete normally ?

The "WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted" 
message comes from PMTHitMerger::saveHit, shown below. The early exit results in hits 
not being saved::


     79 bool
     80 PMTHitMerger::saveHit(junoHit_PMT* hit_photon) {
     81   if (not hasNormalHitType()) {
     82     std::cerr << "WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted."
     83           << std::endl;
     84     return false;
     85   }
     86 
     87   if (m_merge_flag) {
     88     int pmtid = hit_photon->GetPMTID();
     89     std::map<int, std::vector<junoHit_PMT*> >::iterator pmt = m_PMThit.find(pmtid);
     90     if (pmt == m_PMThit.end()) {
     91       m_PMThit[pmtid].clear();
     92       m_PMThit[pmtid].push_back(hit_photon);
     93     }
     94     else pmt->second.push_back(hit_photon);
     95   }
     96   hitCollection->insert(hit_photon);
     97 
     98   return true;
     99 }


     44     bool hasNormalHitType() { return hitCollection != 0; }
     45     bool hasMuonHitType() { return hitCollection_muon != 0; }



    125 bool
    126 PMTHitMerger::init(junoHit_PMT_Collection* hitcol) {
    127 
    128   assert(m_time_window > 0);
    129 
    130   // during event begin, retrieve the hit collection
    131   hitCollection = hitcol;
    132 
    133   // clear all vectors but saving pmts number
    134 
    135   std::map<int, std::vector<junoHit_PMT*> >::iterator pmt = m_PMThit.begin();
    136   for ( ; pmt != m_PMThit.end(); ++pmt) pmt->second.clear();
    137 
    138   return true;
    139 }
    140 



> 
> For the script I ran, I put it in the attachment::
> 
> 
>     #! /bin/bash
> 
>     #================== Part 1 : job parameters =====================
>     #SBATCH --partition=gpu
>     #SBATCH --qos=normal
>     #SBATCH --account=junogpu
>     #SBATCH --job-name=detsim_muon
>     #SBATCH --ntasks=1
>     #SBATCH --mem-per-cpu=20480
>     #SBATCH --gpus=v100:1
> 
>     source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.4/el9_amd64_gcc11/2025_09_30/envset.sh
> 
>     i0=$1
>     i=$((i0+0))
> 
>     DetPath=/hpcfs/juno/junogpu/wangjiabin/opticks/detsim
>     log_path=/hpcfs/juno/junogpu/wangjiabin/opticks/log
>     GenPath=/hpcfs/juno/junogpu/wangjiabin/opticks
>     odir=/hpcfs/juno/junogpu/wangjiabin/opticks
>     mkdir -p "$log_path" "$DetPath" "$GenPath" "$odir"
> 
>     inf="${DetPath}/detsim_user-${i}.root"
> 
>     logging(){
>        type "${FUNCNAME}" || true
>        export G4CXOpticks=INFO
>        export SSim=INFO
>        export SEvt=INFO
>        export SEventConfig=INFO
>     }
> 
>     export SEvt__MINTIME=1     # dump kernel launch times
>     # export CUDA_VISIBLE_DEVICES=0
> 
>     export OPTICKS_MAX_BOUNCE=63
>     evtmax=5
>     seed="${i}"
> 
>     echo "Input (will be produced): $inf"
>     echo "Output dir: $odir"
> 
>     echo "######--- Generator:"
> 
>     srun -n 1 Muon.exe -seed "${seed}" -o "${GenPath}/gen-${i}.txt" -n "${evtmax}" -s juno -v WP -r Yes -wpo
> 
> 
>     echo "######--- detsim start"
> 
>     srun -n 1 /usr/bin/time -vv \
>       python "${TUTORIALROOT}/share/tut_detsim.py" \
>         --no-gdml --anamgr-tt --anamgr-muon \
>         --EnableUserOutput --evtmax "${evtmax}" --seed "${i}" \
>         --pmtsd-v2 --pmt-hit-type 2 --pmtsd-merge-twindow 1.0 \
>         --event-split --event-split-maxhits 300 \
>         --output "${DetPath}/detsim-${i}.root" \
>         --user-output "${DetPath}/detsim_user-${i}.root" \
>         --detoption Acrylic hepevt --exe Muon --file ${GenPath}/gen-${i}.txt \
>       2>&1 | tee "${odir}/detsim_${i}.log"
> 
>     echo "######--- detsim done"
> 


Simon
