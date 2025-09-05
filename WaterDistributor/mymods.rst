mymods
=======

::

    A[blyth@localhost junosw]$ git diff Examples/Tutorial/share/opticks_juno.sh
    diff --git a/Examples/Tutorial/share/opticks_juno.sh b/Examples/Tutorial/share/opticks_juno.sh
    index b6616a29..d0e5f80b 100644
    --- a/Examples/Tutorial/share/opticks_juno.sh
    +++ b/Examples/Tutorial/share/opticks_juno.sh
    @@ -75,7 +75,7 @@ oj_tessname_from_meshname()
     {
        : opticks_juno.sh
        : can only create tessname after meshname exists so needs to be a second run
    -   local oneline="import sys,re;ptn=re.compile('^(sSurftube|svacSurftube|solidSJ|solidXJ).*');print('\n'.join([('%s' if ptn.match(line) else '#%s') % line.rstrip() for line in sys.stdin.readlines()]))"
    +   local oneline="import sys,re;ptn=re.compile('^(sSurftube|svacSurftube|solidSJ|solidXJ|WaterDistributer).*');print('\n'.join([('%s' if ptn.match(line) else '#%s') % line.rstrip() for line in sys.stdin.readlines()]))"
        python -c "$oneline" -
        return 0
     }
    A[blyth@localhost junosw]$ git diff Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc
    diff --git a/Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc b/Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc
    index 294d8bc2..94fa09bc 100644
    --- a/Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc
    +++ b/Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc
    @@ -31,7 +31,9 @@ using namespace CLHEP;
     DECLARE_TOOL(UpperWaterDistributer);
     
     UpperWaterDistributer::UpperWaterDistributer(const std::string& name)
    -    : ToolBase(name)
    +    : 
    +    ToolBase(name), 
    +    logicUpperWaterDistributer(nullptr)
     {
         declProp("UseUpperWaterDistributer", m_use_UpperWaterDistributer=true);//Default: upper chimney is enabled
     }
    A[blyth@localhost junosw]$ git diff Simulation/DetSimV2/DetSimOptions/src/ExpHallConstruction.cc
    diff --git a/Simulation/DetSimV2/DetSimOptions/src/ExpHallConstruction.cc b/Simulation/DetSimV2/DetSimOptions/src/ExpHallConstruction.cc
    index a23fc2fd..b46f565e 100644
    --- a/Simulation/DetSimV2/DetSimOptions/src/ExpHallConstruction.cc
    +++ b/Simulation/DetSimV2/DetSimOptions/src/ExpHallConstruction.cc
    @@ -76,12 +76,23 @@ ExpHallConstruction::inject(std::string motherName, IDetElement* other, IDetElem
                     );
         }
         else {
    -    
    +   
    +      assert( daughtervol );
    +      G4String daughtervol_name = daughtervol->GetName();  
    +
    +      std::cout 
    +          << "ExpHallConstruction::inject"
    +          << " daughtervol_name [" << daughtervol_name << "]"
    +          << "\n"
    +          ;     
    +
    +      daughtervol_name += "_phys" ; 
    +
            while (pos->hasNext()) {
             new G4PVPlacement(
                 pos->next(),
                 daughtervol,
    -            daughtervol->GetName()+"_phys",
    +            daughtervol_name,
                 mothervol,
                 false,
                 copyno++
    A[blyth@localhost junosw]$ 


