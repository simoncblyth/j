
#include "HexagonPosBall.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

#ifdef STANDALONE
#else

#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/ToolFactory.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SniperException.h"
#include "SniperKernel/Task.h"
#include "Geometry/IPMTParamSvc.h"
#endif

#include <istream>
#include <fstream>
#include <sstream>

#include <cassert>

using namespace CLHEP;

namespace JUNO {

namespace Ball {

HexagonPosBall::HexagonPosBall(G4String filename, G4double r, G4bool lpmt)
    : m_filename(filename), m_ball_r(r),lpmt_flag(lpmt) {
    initialize();
    m_position_iter = m_position.begin();
}

#ifdef STANDALONE
#else
HexagonPosBall::HexagonPosBall(Task* scope, G4bool lpmt)
    : m_scope(scope), lpmt_flag(lpmt){
    initialize(lpmt);
    m_position_iter = m_position.begin();
}
#endif

HexagonPosBall::~HexagonPosBall() {

}

G4bool 
HexagonPosBall::hasNext() {
    return m_position_iter != m_position.end();
}

G4Transform3D
HexagonPosBall::next() {
    return *(m_position_iter++);
}


#ifdef STANDALONE
#else
void
HexagonPosBall::initialize(bool lpmt) {
    SniperPtr<IPMTParamSvc> pmtParamSvc(*m_scope, "PMTParamSvc");
    if (pmtParamSvc.invalid())
    {
        LogError << "Can't Locate  PMTParamSvc." << std::endl;
        assert(0);
    }

    int begin_pmt_id, end_pmt_id;

    if(lpmt)
    {
        begin_pmt_id = kOFFSET_CD_LPMT;
        end_pmt_id = kOFFSET_CD_LPMT + pmtParamSvc->get_NTotal_CD_LPMT();
    }else
    {   
        // spmt
        begin_pmt_id = kOFFSET_CD_SPMT;
        end_pmt_id = kOFFSET_CD_SPMT + pmtParamSvc->get_NTotal_CD_SPMT();
    }

    std::cout<<begin_pmt_id<<"\t"<<end_pmt_id<<std::endl;
    for (int i = begin_pmt_id; i<end_pmt_id; i++)
    {
        G4int copyno; 
        G4double theta; // degree
        G4double phi; // degree
        G4double psi; // degree
        G4double x;   // x
        G4double y;   // y
        G4double z;   // z

        copyno = i;
        x = pmtParamSvc->getPMTX(i);
        y = pmtParamSvc->getPMTY(i);
        z = pmtParamSvc->getPMTZ(i);
        theta = pmtParamSvc->getPMTTheta(i);
        phi = pmtParamSvc->getPMTPhi(i);
        psi = pmtParamSvc->getPMTPsi(i);

        theta = theta * deg;
        phi = phi * deg;
        psi = psi * deg;
        // Positions and rotations for regular PMT
        // construct G4Transform3D
        G4ThreeVector pos(x, y, z);
        G4RotationMatrix rot;

        rot.rotateZ(psi);
        rot.rotateY(pi+theta);
        rot.rotateZ(phi);
        G4Transform3D trans(rot, pos);
        m_position.push_back(trans);
    }
}
#endif

void
HexagonPosBall::initialize() {
    std::ifstream pmtsrc(m_filename.c_str());
    std::string tmp_line;
    G4int copyno; 
    G4double theta; // degree
    G4double phi; // degree
    G4double psi; // degree
    G4double x;   // x
    G4double y;   // y
    G4double z;   // z

    // Positions and rotations for lpmt
    if(lpmt_flag){
    while (pmtsrc.good()) {
        std::getline(pmtsrc, tmp_line);
        if (pmtsrc.fail()) {
            break;
        }

        std::stringstream ss;
        ss << tmp_line;

        ss >> copyno >> x >> y >> z >> theta >> phi;
        if (ss.fail()) {
            continue;
        }

        // psi: the rotation by z axis
         ss >> psi;
         if (ss.fail()) {
             psi = 0.0;
         }

        theta = theta * deg;
        phi = phi * deg;
        psi = psi * deg;
        
        if(copyno >= 0 && copyno <=20)
        {
              G4ThreeVector pos(x,y,z);
              G4RotationMatrix rot;
              rot.rotateY(pi);
              G4Transform3D trans(rot,pos);
            m_position.push_back(trans);
        }

        else if(copyno >= 17591 && copyno <=17611)
        { 
              G4ThreeVector pos(x,y,z);
              G4RotationMatrix rot;
              rot.rotateY(0);
              G4Transform3D trans(rot,pos);
            m_position.push_back(trans);
        }

        else{

        // Positions and rotations for regular PMT
        // construct G4Transform3D
//        G4double xx = (m_ball_r) * sin(theta) * cos(phi);
//        G4double yy = (m_ball_r) * sin(theta) * sin(phi);
//        G4double zz = (m_ball_r) * cos(theta);
        G4ThreeVector pos(x, y, z);
        G4RotationMatrix rot;
        rot.rotateZ(psi); 
        rot.rotateY(pi + theta);
        rot.rotateZ(phi); // rotate to the sphere center
        G4Transform3D trans(rot, pos);
        m_position.push_back(trans);
        }

    }
    }

    else{
    
    while (pmtsrc.good()) {
        std::getline(pmtsrc, tmp_line);
        if (pmtsrc.fail()) {
            break;
        }

        std::stringstream ss;
        ss << tmp_line;

        ss >> copyno >> theta >> phi;
        if (ss.fail()) {
            continue;
        }

        // psi: the rotation by z axis
        ss >> psi;
        if (ss.fail()) {
            psi = 0.0;
        }

        theta = theta * deg;
        phi = phi * deg;
        psi = psi * deg;

        x = (m_ball_r) * sin(theta) * cos(phi);
        y = (m_ball_r) * sin(theta) * sin(phi);
        z = (m_ball_r) * cos(theta);
        G4ThreeVector pos(x, y, z);
        G4RotationMatrix rot;
        rot.rotateZ(psi); 
        rot.rotateY(pi + theta);
        rot.rotateZ(phi);
        G4Transform3D trans(rot, pos);
        m_position.push_back(trans);
        }


        
    
    
    }

    pmtsrc.close();
}

}

}
