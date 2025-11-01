PMTHitMerger
=============


::

     26 class PMTHitMerger {
     27 public:
     28     PMTHitMerger();
     29   
     30     bool doMerge(int pmtid, double hittime);
     31     bool saveHit(junoHit_PMT* hit);
     32     bool saveHit(junoHit_PMT_muon* hit);
     33   
     34     // call init at begin of event
     35     bool init(junoHit_PMT_Collection* hitcol);
     36     bool init(junoHit_PMT_muon_Collection* hitcol);
     37   
     38     void setMergeFlag(bool flag) { m_merge_flag = flag; }
     39     bool getMergeFlag() { return m_merge_flag; }
     40 
     41     void setTimeWindow(double tw) { m_time_window = tw; }
     42     double getTimeWindow() { return m_time_window; }
     43 
     44     bool hasNormalHitType() { return hitCollection != 0; }
     45     bool hasMuonHitType() { return hitCollection_muon != 0; }
     46 private:
     47 
     48   // bool doMerge_normal(int pmtid, double hittime);
     49   // bool doMerge_muon(int pmtid, double hittime);
     50 
     51   junoHit_PMT_Collection* hitCollection;
     52   junoHit_PMT_muon_Collection* hitCollection_muon;
     53   // copy from junoSD_PMT_v2
     54   bool m_merge_flag;
     55   double m_time_window;
     56 
     57   std::map<int, std::vector<junoHit_PMT*> > m_PMThit;
     58   std::map<int, std::vector<junoHit_PMT_muon*> > m_PMThit_muon;
     59 }; 



jcv junoHit_PMT::

    146 // junoHit_PMT_Collection is a vector of hits
    147 typedef G4THitsCollection<junoHit_PMT> junoHit_PMT_Collection;
    148 
    149 extern G4ThreadLocal G4Allocator<junoHit_PMT>* junoHit_PMT_Allocator;
    150 
    151 inline void* junoHit_PMT::operator new(size_t)
    152 {
    153   void *aHit;
    154   if (!junoHit_PMT_Allocator) {
    155       junoHit_PMT_Allocator = new G4Allocator<junoHit_PMT>;
    156   }
    157   aHit = (void *) junoHit_PMT_Allocator->MallocSingle();
    158   return aHit;
    159 }
    160 
    161 inline void junoHit_PMT::operator delete(void *aHit)
    162 {
    163   junoHit_PMT_Allocator->FreeSingle((junoHit_PMT*) aHit);
    164 }





* https://en.cppreference.com/w/cpp/container/unordered_map/try_emplace.html




grok::


    class PMTHitMerger {
    private:
        struct Key {
            int pmtid;
            int time_bucket;
            bool operator==(const Key& o) const = default;
        };

        struct KeyHash {
            std::size_t operator()(const Key& k) const {
                return std::hash<uint64_t>{}(
                    (static_cast<uint64_t>(k.pmtid) << 32) ^ 
                    static_cast<uint64_t>(k.time_bucket)
                );
            }
        };

        // Use absl::flat_hash_map if possible, else unordered_map
        absl::flat_hash_map<Key, std::pair<double, uint32_t>, KeyHash> merged;

        double m_time_window;
        bool m_merge_flag;

    public:
        bool doMerge(int pmtid, double hittime) {
            if (!m_merge_flag) return false;

            int bucket = static_cast<int>(hittime / m_time_window);
            Key key{pmtid, bucket};

            auto [it, inserted] = merged.try_emplace(key, hittime, 1);
            if (!inserted) {
                auto& [time, count] = it->second;
                if (hittime < time) time = hittime;
                count++;
            }
            return !inserted;
        }

        // Call at end of event
        void finalize(std::vector<junoHit_PMT*>& output) {
            output.clear();
            output.reserve(merged.size());
            for (auto& [key, val] : merged) {
                auto* hit = new junoHit_PMT();
                hit->SetPMTID(key.pmtid);
                hit->SetTime(val.first);
                hit->SetCount(val.second);
                output.push_back(hit);
            }
            merged.clear();
        }
    };




