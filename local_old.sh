local_ok_externals_pre_release()
{
   : ~/local.sh
   : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy versions matching JUNOSW
   : NB versions need to match those used by gitlab-ci build when using the gitlab cvmfs release

   local_unset

   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Xercesc/3.2.4/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/CLHEP/2.4.7.1/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/custom4/0.1.8/bashrc

   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Python/3.9.19/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/python-numpy/1.23.5/bashrc

   export VIP_MODE=ok_externals
   export VIP_DESC="Opticks JUNOSW externals in common manually setup from cvmfs : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy"
}

