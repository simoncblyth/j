#ifndef HexagonPosBall_hh
#define HexagonPosBall_hh

#ifdef STANDALONE
#include "G4Transform3D.hh"
#else
#include "DetSimAlg/IDetElementPos.h"
#endif

#include "globals.hh"
#include <string>
#include <vector>
#include "G4String.hh"

class Task;

namespace JUNO {

namespace Ball {

#ifdef STANDALONE
#define private public 
class HexagonPosBall {
#else
class HexagonPosBall: public IDetElementPos {
#endif
public:
    // this r is the distance between center of ball
    // and the center of PMT Equator
    HexagonPosBall(G4String filename, G4double r, G4bool lpmt);

#ifdef STANDALONE
#else
    HexagonPosBall(Task* scope, G4bool lpmt);
#endif

    ~HexagonPosBall();

    G4bool hasNext();
    G4Transform3D next();
private:
    void initialize();
#ifdef STANDALONE
#else
    void initialize(G4bool lpmt);
#endif
private:
    G4String m_filename;
    G4double m_ball_r;
    std::vector< G4Transform3D > m_position;
    std::vector< G4Transform3D >::iterator m_position_iter;
    
    G4bool lpmt_flag;
#ifdef STANDALONE
#else
    Task* m_scope;
#endif
};

}

}

#endif
