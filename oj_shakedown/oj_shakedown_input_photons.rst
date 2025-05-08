oj_shakedown_input_photons
===========================


insitu with tut_detsim.py
--------------------------

Using "opticks" instead of "gun" switches on input photons. How does that work ?

jcv JUNODetSimModule::

	0680     def register_subparser_opticks(self, subparsers, base_parser_positioner):
	 681         parser_opticks = subparsers.add_parser("opticks", help="opticks debugging input photon  generator", parents=[base_parser_positioner])


	1305     def setup_generator(self, args, gt):
	1306         if args.gentool_mode == "gun":
	1307             self.setup_generator_gun(args, gt)
        ...
	1340         elif args.gentool_mode == "opticks":
	1341             self.setup_generator_opticks(args, gt)
	1342         elif args.gentool_mode == "genloader":
	1343             self.setup_generator_genloader(args, gt)
	1344         pass



	1730     def setup_generator_opticks(self, args, gt):
	1731         """
	1732         Former declProp controls have been removed. 
	1733         Are now using Opticks input photon machinery in order to 
	1734         profit from its automated frame transformation of input photons.
	1735 
	1736         OPTICKS_INPUT_PHOTON
	1737            selects path to .npy array of shape (n,4,4) 
	1738            with the input photons, see ana/input_photons.sh 
	1739 
	1740         MOI/INST/OPTICKS_INPUT_PHOTON_FRAME
	1741            controls target frame, see CSGFoundry::getFrameE 
	1742 
	1743         To follow how the hookup and transformation works see::
	1744 
	1745             SEvt::GetInputPhoton 
	1746             G4CXOpticks::setupFrame
	1747             CSGFoundry::getFrameE
	1748 
	1749         """
	1750         noop = os.environ.get("OPTICKS_PREFIX", None) is None
	1751         if noop:
	1752             log.fatal("setup_generator_opticks : Opticks Input Photons cannot be used when not compiled WITH_G4CXOPTICKS")
	1753             log.fatal("lack of WITH_G4CXOPTICKS is inferred by lack of OPTICKS_PREFIX envvar")
	1754             sys.exit(-1)
	1755         pass
	1756         ok = gt.createTool("GtOpticksTool/ok")
	1757         objName = ok.objName()
	1758         gt.property("GenToolNames").set([objName])
	1759         log.info("setup_generator_opticks : objName:[%s]" % (objName) )


jcv GtOpticksTool::


	196 #ifdef WITH_G4CXOPTICKS
	197 bool GtOpticksTool::mutate(HepMC::GenEvent& event)
	198 {
	199     int event_number = event.event_number() ; // is this 0-based ? 
	200     if(m_input_photon == nullptr)
	201     {
	202         bool has_input_photon = SEvt::HasInputPhoton() ;
	203         if(has_input_photon == false) std::cerr
	204             << "GtOpticksTool::mutate WITH_G4CXOPTICKS"
	205             << " : ERROR : something is missing "
	206             << std::endl
	207             << SEvt::DescHasInputPhoton()
	208             << std::endl
	209             << firstmutate_FAIL_NOTES
	210             ;
	211 
	212         m_input_photon = SEvt::GetInputPhoton() ;
	213         std::cerr
	214             << "GtOpticksTool::mutate"
	215             << " event_number " << event_number
	216             << " deferred SEvt::GetInputPhoton "
	217             << " " << SEvt::Brief()
	218             << " m_input_photon " << ( m_input_photon ? m_input_photon->sstr() : "-" )
	219             << std::endl
	220             ;
	221     }
	222 
	223     int numPhotons = m_input_photon ? m_input_photon->shape[0] : 0 ;
	224     //LOG(info)
	225     std::cerr
	226         << "GtOpticksTool::mutate"
	227         << " event_number " << event_number
	228         << " numPhotons " << numPhotons
	229         << std::endl
	230         ;
	231 
	232     for(int idx = 0; idx < numPhotons ; ++idx) add_optical_photon(event, idx);
	233     return true;
	234 }
	235 #else



	1690 bool SEvt::HasInputPhoton(int idx)
	1691 {
	1692     return Exists(idx) ? Get(idx)->hasInputPhoton() : false ;
	1693 }
	1694 bool SEvt::HasInputPhoton()
	1695 {
	1696     return HasInputPhoton(EGPU) || HasInputPhoton(ECPU) ;
	1697 }
	1698 
	1699 NP* SEvt::GetInputPhoton() // static
	1700 {
	1701     NP* ip = nullptr ;
	1702     if(ip == nullptr && HasInputPhoton(EGPU)) ip = GetInputPhoton(EGPU) ;
	1703     if(ip == nullptr && HasInputPhoton(ECPU)) ip = GetInputPhoton(ECPU) ;
	1704     return ip ;
	1705 }


	0491 /**
	 492 SEvt::getInputPhoton_
	 493 ----------------------
	 494 
	 495 This variant always provides the untransformed input photons.
	 496 That will be nullptr unless OPTICKS_INPUT_PHOTON is defined.
	 497 
	 498 **/
	 499 NP* SEvt::getInputPhoton_() const { return input_photon ; }
	 500 bool SEvt::hasInputPhoton() const { return input_photon != nullptr ; }
	 501 
	 502 
	 503 /**
	 504 SEvt::getInputPhoton
	 505 ---------------------
	 506 
	 507 Returns the transformed input photon if present.
	 508 For the transformed photons to  be present it is necessary to have called SEvt::setFrame
	 509 That is done from on high by G4CXOpticks::setupFrame which gets invoked by G4CXOpticks::setGeometry
	 510 
	 511 The frame and corresponding transform used can be controlled by several envvars,
	 512 see CSGFoundry::getFrameE. Possible envvars include:
	 513 
	 514 +------------------------------+----------------------------+
	 515 | envvar                       | Examples                   |
	 516 +==============================+============================+
	 517 | INST                         |                            |
	 518 +------------------------------+----------------------------+
	 519 | MOI                          | Hama:0:1000 NNVT:0:1000    |
	 520 +------------------------------+----------------------------+
	 521 | OPTICKS_INPUT_PHOTON_FRAME   |                            |
	 522 +------------------------------+----------------------------+
	 523 
	 524 
	 525 **/
	 526 NP* SEvt::getInputPhoton() const {  return input_photon_transformed ? input_photon_transformed : input_photon  ; }
	 527 bool SEvt::hasInputPhotonTransformed() const { return input_photon_transformed != nullptr ; }
	 528 


	 444 /**
	 445 SEvt::initInputPhoton
	 446 -----------------------
	 447 
	 448 This is invoked by SEvt::init on instanciating the SEvt instance
	 449 The default "SEventConfig::InputPhoton()" is nullptr meaning no input photons.
	 450 This can be changed by setting an envvar in the script that runs the executable, eg::
	 451 
	 452    export OPTICKS_INPUT_PHOTON=CubeCorners.npy
	 453    export OPTICKS_INPUT_PHOTON=$HOME/somedir/path/to/inphoton.npy
	 454 
	 455 Or within the code of the executable, typically in the main prior to SEvt instanciation,
	 456 using eg::
	 457 
	 458    SEventConfig::SetInputPhoton("CubeCorners.npy")
	 459    SEventConfig::SetInputPhoton("$HOME/somedir/path/to/inphoton.npy")
	 460 
	 461 When non-null it is resolved into a path and the array loaded at SEvt instanciation
	 462 by SEvt::LoadInputPhoton
	 463 
	 464 **/
	 465 
	 466 void SEvt::initInputPhoton()
	 467 {
	 468     NP* ip = LoadInputPhoton() ;
	 469     setInputPhoton(ip);
	 470 }
	 471 
	 472 void SEvt::setInputPhoton(NP* p)
	 473 {
	 474     if(p == nullptr) return ;
	 475     input_photon = p ;
	 476     bool input_photon_expect = input_photon->has_shape(-1,4,4) ;
	 477     if(!input_photon_expect) std::raise(SIGINT) ;
	 478     assert( input_photon_expect );
	 479 
	 480     int numphoton = input_photon->shape[0] ;
	 481     bool numphoton_expect = numphoton > 0 ;
	 482     if(!numphoton_expect) std::raise(SIGINT) ;
	 483     assert( numphoton_expect  );
	 484 }



	 381 /**
	 382 SEvt::LoadInputPhoton
	 383 ----------------------
	 384 
	 385 This is invoked by SEvt::initInputPhoton which is invoked by SEvt::init at instanciation.
	 386 
	 387 Resolving the input string to a path is done in one of two ways:
	 388 
	 389 1. if the string starts with a letter A-Za-z eg "inphoton.npy" or "RandomSpherical10.npy"
	 390    it is assumed to be the name of a .npy file within the default SEvt__INPUT_PHOTON_DIR
	 391    of $HOME/.opticks/InputPhotons.
	 392 
	 393    Create such files with ana/input_photons.py
	 394 
	 395 2. if the string does not start with a letter eg /path/to/some/dir/file.npy or $TOKEN/path/to/file.npy
	 396    it is passed unchanged to  spath::Resolve
	 397 
	 398 **/
	 399 
	 400 NP* SEvt::LoadInputPhoton() // static
	 401 {
	 402     const char* spec = SEventConfig::InputPhoton();
	 403     return spec ? LoadInputPhoton(spec) : nullptr ;
	 404 }
	 405 NP* SEvt::LoadInputPhoton(const char* spec)
	 406 {
	 407     const char* path = ResolveInputArray( spec, INPUT_PHOTON_DIR );
	 408     NP* a = LoadInputArray(path);
	 409     assert( a->has_shape(-1,4,4) );
	 410     return a ;
	 411 }


	 320 const char* SEvt::INPUT_GENSTEP_DIR = spath::Resolve("${SEvt__INPUT_GENSTEP_DIR:-$HOME/.opticks/InputGensteps}") ;
	 321 const char* SEvt::INPUT_PHOTON_DIR = spath::Resolve("${SEvt__INPUT_PHOTON_DIR:-$HOME/.opticks/InputPhotons}") ;
	 322 
	 323 
	 324 const char* SEvt::ResolveInputArray(const char* spec, const char* dir) // static
	 325 {
	 326     assert(strlen(spec) > 0 && sstr::EndsWith(spec, ".npy") );
	 327     const char* path = sstr::StartsWithLetterAZaz(spec) ?  spath::Resolve(dir, spec) : spath::Resolve( spec ) ;
	 328     return path ;
	 329 }



DONE : create InputPhotons tarball within ana/input_photons.sh and deploy it to CVMFS
--------------------------------------------------------------------------------------



TODO : incorporate below env into OJ release
----------------------------------------------

With OJ release running, it would be convenient to set the below to some non-release CVMFS directory::

    export SEvt__INPUT_PHOTON_DIR=/cvmfs/opticks.ihep.ac.cn/.opticks/InputPhotons 


::

	A[blyth@localhost Latest]$ cat envset.sh 
	#!/bin/bash
	# generated from .gitlab-ci.yml of JUNO/offline/junosw
	# .gitlab-ci/oj_helper.sh EMIT_ENVSET

	HERE=$(dirname $(realpath $BASH_SOURCE))
	DEFAULT_PREFIX=$HERE
	PREFIX=${OJ_PREFIX:-$DEFAULT_PREFIX}

	source $PREFIX/ENV.bash             ## define JUNOTOP and JUNO_OPTICKS_PREFIX 
	source $JUNOTOP/setup.sh            ## hookup many JUNOSW externals excluding Opticks
	source $JUNO_OPTICKS_PREFIX/bashrc  ## hookup for Opticks and its externals

	source $PREFIX/bin/opticks_juno.sh  ## oj bash functions 
	oj_geomsetup

	export CMAKE_PREFIX_PATH=$PREFIX:${CMAKE_PREFIX_PATH}
	export PATH=$PREFIX/bin:${PATH}
	export LD_LIBRARY_PATH=$PREFIX/lib64:${LD_LIBRARY_PATH}
	export PYTHONPATH=$PREFIX/lib64:${PYTHONPATH}
	export PYTHONPATH=$PREFIX/python:${PYTHONPATH}


::

	P[blyth@localhost junosw]$ find . -name opticks_juno.sh
	./Examples/Tutorial/share/opticks_juno.sh
	./InstallArea/bin/opticks_juno.sh
	P[blyth@localhost junosw]$ 


Doing within oj_geomsetup makes most sense. But test it first manually.  


Does opticks-full run ana/input_photons.sh ? YES
--------------------------------------------------


::

	2641 opticks-prepare-InputPhotons-notes(){ cat << EON
	2642 opticks-prepare-InputPhotons-notes
	2643 ------------------------------------
	2644 
	2645 opticks-prepare-InputPhotons is run during installation by opticks-full-prepare
	2646 so it is done just after the build and before opticks environment is setup.
	2647 So it sets PYTHONPATH to opticks-fold which is the folder above opticks-home
	2648 in order to be able to import python modules from the source tree which
	2649 are needed to generate the input photons.
	2650 
	2651 EON
	2652 }
	2653 
	2654 
	2655 opticks-prepare-InputPhotons()
	2656 {
	2657     local msg="=== $FUNCNAME :"
	2658     mkdir -p $HOME/.opticks/InputPhotons
	2659     echo $msg used by some tests
	2660 
	2661     PYTHONPATH=$(opticks-fold) $(opticks-home)/ana/input_photons.sh
	2662 }
	2663 
	2664 
	2665 opticks-prepare-installation()
	2666 {
	2667     local msg="=== $FUNCNAME :"
	2668     echo $msg
	2669 
	2670     #qudarap-
	2671     #qudarap-prepare-installation
	2672     : following move to Philox no more need to prepare curandState files
	2673 
	2674     opticks-prepare-InputPhotons
	2675 }



WIP : InputPhotons tarball create and deploy to cvmfs script
---------------------------------------------------------------

::

	A[blyth@localhost InputPhotons]$ ls -1 | wc -l 
	124
	A[blyth@localhost InputPhotons]$ ls *.npy | wc -l 
	62
	A[blyth@localhost InputPhotons]$ ls *.json | wc -l 
	62
	A[blyth@localhost InputPhotons]$ pwd
	/home/blyth/.opticks/InputPhotons






with G4CXTest or other Opticks executables
-------------------------------------------





