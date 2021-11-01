zcut_pmt
===========



::

    epsilon:PMTSim blyth$ ./run.sh 
    Hamamatsu_R12860_PMTSolid::Hamamatsu_R12860_PMTSolid m_polycone_neck 1 --pmt20inch-polycone-neck ENABLED 
    PMTSim::GetSolid name PMTSim_Z  mode [Z]
    /Users/blyth/j/PMTSim/Hamamatsu_R12860_PMTSolid.cc:182
    [Ellipse_Intersect_Circle 
    ]Ellipse_Intersect_Circle (  142.9671,  -162.0446) 
    ZSolids::makeUnionSolid
      0  label            zdelta      0.000 z1    190.000 z0      0.000 az      0.000 az1    190.000 az0      0.000
      1  label       _1_2 zdelta     -2.500 z1      2.500 z0     -2.500 az      0.000 az1      0.000 az0     -5.000
      2  label       _1_3 zdelta     -5.000 z1      0.000 z0   -190.000 az     -2.500 az1     -7.500 az0   -197.500
      3  label       _1_4 zdelta   -179.216 z1     17.171 z0    -30.784 az     -7.500 az1   -169.545 az0   -217.500
      4  label       _1_5 zdelta   -242.500 z1     32.500 z0    -32.500 az   -186.716 az1   -396.716 az0   -461.716
      5  label       _1_6 zdelta   -275.000 z1     32.500 z0    -32.500 az   -429.216 az1   -671.716 az0   -736.716
      6  label       _1_8 zdelta   -385.000 z1     35.000 z0    -35.000 az   -704.216 az1  -1054.216 az0  -1124.216
      7  label       _1_9 zdelta   -420.000 z1      0.000 z0    -30.000 az  -1089.216 az1  -1509.216 az0  -1539.216
    NP::save path [/tmp/ZSolids.npy]
     solid 0x7f829ef012d0
    epsilon:PMTSim blyth$ 
    i


Hmm smth wrong with absolute Z, but geom in Z mode looks ok::

    2021-11-01 16:11:38.239 INFO  [12849949] [NNodeNudger::dump_prim_bb@131] 
     i   0 zor   7 pbb  mi (   -254.000  -254.000     0.000) mx (    254.000   254.000   190.000) si (    508.000   508.000   190.000)
     i   1 zor   6 pbb  mi (   -254.000  -254.000    -5.000) mx (    254.000   254.000     0.000) si (    508.000   508.000     5.000)
     i   2 zor   5 pbb  mi (   -190.000  -190.000  -195.000) mx (    190.000   190.000    -5.000) si (    380.000   380.000   190.000)
     i   3 zor   4 pbb  mi (   -142.967  -142.967  -210.000) mx (    142.967   142.967  -162.045) si (    285.934   285.934    47.955)
     i   4 zor   3 pbb  mi (   -127.000  -127.000  -275.000) mx (    127.000   127.000  -210.000) si (    254.000   254.000    65.000)
     i   5 zor   2 pbb  mi (    -95.000   -95.000  -365.000) mx (     95.000    95.000  -275.000) si (    190.000   190.000    90.000)
     i   6 zor   1 pbb  mi (    -37.500   -37.500  -420.000) mx (     37.500    37.500  -350.000) si (     75.000    75.000    70.000)
     i   7 zor   0 pbb  mi (    -25.750   -25.750  -450.000) mx (     25.750    25.750  -420.000) si (     51.500    51.500    30.000)



::

   .
                     un 
   
             un 

       un        zs
                (-5)
   zs    cy      
        (-2.5)



Not accumulating the zdelta does better::

    epsilon:PMTSim blyth$ ./run.sh 
    Hamamatsu_R12860_PMTSolid::Hamamatsu_R12860_PMTSolid m_polycone_neck 1 --pmt20inch-polycone-neck ENABLED 
    PMTSim::GetSolid name PMTSim_Z  mode [Z]
    /Users/blyth/j/PMTSim/Hamamatsu_R12860_PMTSolid.cc:182
    [Ellipse_Intersect_Circle 
    ]Ellipse_Intersect_Circle (  142.9671,  -162.0446) 
    ZSolids::makeUnionSolid
      0  label            zdelta      0.000 z1    190.000 z0      0.000 az      0.000 az1    190.000 az0      0.000
      1  label       _1_2 zdelta     -2.500 z1      2.500 z0     -2.500 az      0.000 az1      0.000 az0     -5.000
      2  label       _1_3 zdelta     -5.000 z1      0.000 z0   -190.000 az     -2.500 az1     -5.000 az0   -195.000
      3  label       _1_4 zdelta   -179.216 z1     17.171 z0    -30.784 az     -7.500 az1   -162.045 az0   -210.000
      4  label       _1_5 zdelta   -242.500 z1     32.500 z0    -32.500 az   -186.716 az1   -210.000 az0   -275.000
      5  label       _1_6 zdelta   -275.000 z1     32.500 z0    -32.500 az   -429.216 az1   -242.500 az0   -307.500
      6  label       _1_8 zdelta   -385.000 z1     35.000 z0    -35.000 az   -704.216 az1   -350.000 az0   -420.000
      7  label       _1_9 zdelta   -420.000 z1      0.000 z0    -30.000 az  -1089.216 az1   -420.000 az0   -450.000
    NP::save path [/tmp/ZSolids.npy]
     solid 0x7fbf05c1d5c0
    epsilon:PMTSim blyth$ 



Cutting existing solids::

    G4Ellipsoid::SetZCuts

    G4Tubs::SetZHalfLength
          will need to adjust the offset 

    G4Polycone::SetOriginalParameters(G4PolyconeHistorical* pars)

Note its public::

     47 class G4PolyconeHistorical
     48 { 
     49   public:
     50     G4PolyconeHistorical();
     51     G4PolyconeHistorical( G4int z_planes );
     52     ~G4PolyconeHistorical();
     53     G4PolyconeHistorical( const G4PolyconeHistorical& source );
     54     G4PolyconeHistorical& operator=( const G4PolyconeHistorical& right );
     55     
     56     G4double Start_angle;
     57     G4double Opening_angle;
     58     G4int   Num_z_planes;
     59     G4double *Z_values;
     60     G4double *Rmin;
     61     G4double *Rmax;
     62 };
     63 


Cutting G4Tubs::


   zd0+hz0  +---------+               +---------+     zd1 + hz1 
            |         |               |         |  
            |         |               |         |
            |         |               |         |
            |         |             __|_________|__   zd1
            |         |               |         |
     zd0  --|---------|--             |         |
            |         |               |         |
            |         |               |         |
         .  | . . . . | . .zcut . . . +---------+ . . zd1 - hz1  . . . . . .
            |         | 
            |         |
    zd0-hz0 +---------+ 


     original height:  2*hz0,                         
      
     cut height :     

          2*hz1 = 2*hz0 - (zcut-zd0+hz0) = hz0 + zd0 - zcut 

                     (hz0 + zd0) - zcut  
            hz1 =  ----------------------
                             2
          
     cut position

          zcut = zd1 - hz1 

           zd1 = zcut + hz1  





