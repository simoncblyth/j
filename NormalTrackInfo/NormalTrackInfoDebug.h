
// ———————————————————————————————— DEBUG REGISTRY ————————————————————————————————
#ifdef NORMALTRACKINFO_DEBUG
#include <mutex>
#include <unordered_map>
#include <iostream>
#include <iomanip>

class NormalTrackInfo ;

static std::mutex g_nti_mutex;
static std::unordered_map<const NormalTrackInfo*, std::string> g_nti_registry;

struct NormalTrackInfoDebug {

    static void register_obj(const NormalTrackInfo* ptr, const char* where) 
    {
        std::lock_guard<std::mutex> lock(g_nti_mutex); std::cerr << "NormalTrackInfoDebug::register_obj " << ptr << " where " << where << " count " << g_nti_registry.size() << "\n" ;
        auto result = g_nti_registry.emplace(ptr, where);
        auto placed = result.first ;
        bool added = result.second ;

        if (!added)   
        {
            std::cerr << "\n=== NORMALTRACKINFO DOUBLE CONSTRUCTION (ptr already registered) at " << ptr
                      << " ===\n"
                      << "First created (first where): " << placed->second << "\n"
                      << "Second attempt: " << where << "\n"
                      << "=== ABORTING ===\n";
            std::abort();
        }
    }


    static void unregister_obj(const NormalTrackInfo* ptr, const char* where) 
    {
        std::lock_guard<std::mutex> lock(g_nti_mutex); std::cerr << "NormalTrackInfoDebug::unregister_obj " << ptr << " where " << where << " count " << g_nti_registry.size() << "\n" ;
        auto it = g_nti_registry.find(ptr);
        if (it == g_nti_registry.end()) {
            std::cerr << "\n=== NORMALTRACKINFO DESTROYED TWICE (ptr not registered) at " << ptr
                      << " ===\n"
                      << "Destroyed from: " << where << "\n"
                      << "But it was NEVER constructed (or already removed)\n"
                      << "=== ABORTING ===\n";
            std::abort();
        }

        // Detect the classic bug: manual delete + Geant4 delete
        bool created_by_user   = (it->second.find("G4Track") == std::string::npos);
        bool destroyed_by_g4   = (std::string(where).find("G4Track") != std::string::npos);

        if (created_by_user && destroyed_by_g4) {
            std::cerr << "\n=== NORMALTRACKINFO DOUBLE DELETE DETECTED ===\n"
                      << "Object       : " << ptr << "\n"
                      << "Created      : " << it->second << "\n"
                      << "Deleted from : " << where << "\n"
                      << "This is the classic Geant4 user-track-info bug!\n"
                      << "=== ABORTING ===\n";
            std::abort();
        }
        g_nti_registry.erase(it);
    }


    static void final_check(const char* where) 
    {
        std::lock_guard<std::mutex> lock(g_nti_mutex); std::cerr << "NormalTrackInfoDebug::final_check where " << where << " count " << g_nti_registry.size() << "\n" ;
        if (!g_nti_registry.empty()) {
            std::cerr << "\n=== NORMALTRACKINFO LEAK: " << g_nti_registry.size()
                      << " objects still alive ===\n";
            for (const auto& p : g_nti_registry)
                std::cerr << "  " << p.first << " ← created at " << p.second << "\n";
        }
    }
};

#endif
// —————————————————————————————————————————————————————————————————————————————


