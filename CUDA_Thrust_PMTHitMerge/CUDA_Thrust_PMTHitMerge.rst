CUDA_Thrust_PMTHitMerge
==========================


Thoughts
---------

Q: How important is it to know the exact earliest time within the bucket, 
   or it it enough to just know the bucket ?


Grok
-----

PMT hit merging is a technique to reduce hit data volume by effectively
combining hits onto the same PMT by changing the hittime to the first and
incrementing a hitcount within the hit. Hits are obtained using CUDA thrust by
selecting photons which have a flagmask corresponding to hits. Any suggestions
for how to implement hit merging with CUDA Thrust or just CUDA. The CPU
implemetation is based on using std::map so a very different approach is needed
on GPU. The simplified CPU impl snippet::  

    bool PMTHitMerger::doMerge(int pmtid, double hittime) 
    {
        std::map<int, std::vector<junoHit_PMT*> >::iterator pmt = m_PMThit.find(pmtid);
        if (pmt != m_PMThit.end()) 
        {
            int time1 = static_cast<int>(hittime/m_time_window);
            std::vector<junoHit_PMT*>::iterator it = pmt->second.begin();
            for ( ; it != pmt->second.end(); ++it) 
            {
                // compare the time
                if (time1 == static_cast<int>((*it)->GetTime()/m_time_window)) 
                {
                    if (hittime < (*it)->GetTime()) (*it)->SetTime(hittime);
                    // === update the count
                   (*it)->SetCount(1 + (*it)->GetCount());
                   return true;
                }
            }
        }
        return false ;
    }



::







