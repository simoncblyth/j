#!/usr/bin/env python
"""

jcv HexagonPosBall::

    182     else{
    183     
    184     while (pmtsrc.good()) {
    185         std::getline(pmtsrc, tmp_line);
    186         if (pmtsrc.fail()) {
    187             break;
    188         }
    189 
    190         std::stringstream ss;
    191         ss << tmp_line;
    192 
    193         ss >> copyno >> theta >> phi;
    194         if (ss.fail()) {
    195             continue;
    196         }
    197     
    198         // psi: the rotation by z axis 
    199         ss >> psi;
    200         if (ss.fail()) {
    201             psi = 0.0;
    202         }
    203 
    204         theta = theta * deg;
    205         phi = phi * deg;
    206         psi = psi * deg;
    207     
    208         x = (m_ball_r) * sin(theta) * cos(phi);
    209         y = (m_ball_r) * sin(theta) * sin(phi);
    210         z = (m_ball_r) * cos(theta);
    211         G4ThreeVector pos(x, y, z);
    212         G4RotationMatrix rot;
    213         rot.rotateZ(psi);
    214         rot.rotateY(pi + theta);
    215         rot.rotateZ(phi);
    216         G4Transform3D trans(rot, pos);
    217         m_position.push_back(trans);
    218         }
    219 
    220 



"""


import numpy as np
import os 

class PosFile(object):
    @classmethod
    def Load(cls):
        confpath = os.path.expandvars("$JUNOTOP/offline/Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py")
        lines = list(filter(lambda line:line.find("data_load") > -1, open(confpath).read().splitlines() ))
        d = {}     
        for line in lines:
            elem = line.split("\"")
            key = elem[1]
            name = elem[3] 
            path = os.path.expandvars(os.path.join("$JUNOTOP/offline/Simulation/DetSimV2/DetSimOptions/data", name))
            assert os.path.exists(path)
            print("%30s %30s " % (key, path) )

            d[key] = cls(key, path, radius) 
        pass
        return d 

    def __init__(self, key, path, radius=1):
        a = np.genfromtxt(path, dtype=None, names=("copyNo","theta","phi") )

        theta = a["theta"]*np.pi/180.
        phi = a["phi"]*np.pi/180.

        x = radius*np.sin(theta)*np.cos(phi)
        y = radius*np.sin(theta)*np.sin(phi)
        z = radius*np.cos(theta)

        self.path = path 
        self.key = key 
        self.a = a 
        
        b = np.zeros( [len(a), 6, 4 ], dtype=np.float64 )

        b[:, 0, 0] = theta
        b[:, 0, 1] = phi

        b[:, 1, 0] = x 
        b[:, 1, 1] = y 
        b[:, 1, 2] = z 
        b[:, 1, 3] = 0.

        # TODO: reproduce the transform 

        self.b = b 


    def __repr__(self):
        return " %15s  : %20s : %s " % ( str(self.a.shape), self.key, self.path )   

    

if __name__ == '__main__':
    pfs = PosFile.Load()
    for k in pfs:
        print(pfs[k])
    pass


    






