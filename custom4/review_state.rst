custom4/review_state.rst
=========================


Overview
----------

2026 Mar 31
   * reviewed branches : main and v0.1.8_transient
   * created v0.1.9_release starting from v0.1.8_transient with cherry-pick additions from main



Details
--------

::

    A[blyth@localhost customgeant4]$ git branch -a
    * main
      v0.1.8_transient
      remotes/origin/HEAD -> origin/main
      remotes/origin/main



::

    A[blyth@localhost customgeant4]$ git diff v0.1.8 v0.1.8_transient --stat
     .gitignore             |   3 +++
     C4CustomART.h          | 328 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++---------------------------------------------------------------------------------------------------------------
     C4OpBoundaryProcess.cc |   2 +-
     C4OpBoundaryProcess.hh |  30 +++++++++++-----------
     C4Track.h              | 136 +++++++++++++++++++++++++++++++++++++++++++++++++-------------------------------------------------
     C4TrackInfo.h          | 140 +++++++++++++++++++++++++++++++++++++++++++++++++---------------------------------------------------
     CMakeLists.txt         |  44 ++++++++++++++++----------------
     RELEASE_NOTES.rst      |  28 ++++++++++++--------
     addtag.sh              |  60 +++++++++++++++++++++----------------------
     9 files changed, 398 insertions(+), 373 deletions(-)
    A[blyth@localhost customgeant4]$ 






Big change is getting rid of templated track info anti-pattern::


    git diff -b v0.1.8 v0.1.8_transient


    diff --git a/C4OpBoundaryProcess.cc b/C4OpBoundaryProcess.cc
    index 24b7b60..b855ccb 100644
    --- a/C4OpBoundaryProcess.cc
    +++ b/C4OpBoundaryProcess.cc
    @@ -199,8 +199,8 @@ C4OpBoundaryProcess::~C4OpBoundaryProcess(){}
     G4VParticleChange*
     C4OpBoundaryProcess::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
     {
    -        m_track_label = C4TrackInfo<C4Pho>::GetRef(&aTrack);
     #ifdef C4_DEBUG_PIDX
    +        m_track_label = C4TrackInfo::GetRef(&aTrack);
             m_track_dump = ( m_track_label != nullptr && m_track_label->id == PIDX && PIDX_ENABLED ) || PIDX == -2  ; 
     #endif
     
    diff --git a/C4OpBoundaryProcess.hh b/C4OpBoundaryProcess.hh
    index a968792..f42da69 100644
    --- a/C4OpBoundaryProcess.hh
    +++ b/C4OpBoundaryProcess.hh
    @@ -252,8 +252,8 @@ public:
     
             char           m_custom_status ;
             C4CustomART*   m_custom_art ;
    -        C4Pho*         m_track_label ; 
     #ifdef C4_DEBUG_PIDX
    +        C4Pho*         m_track_label ;
             bool           m_track_dump ;
     #endif
     

    diff --git a/C4Track.h b/C4Track.h
    index ce0d45b..3d90423 100644
    --- a/C4Track.h
    +++ b/C4Track.h
    @@ -53,7 +53,7 @@ struct C4Track
     
     inline int C4Track::GetLabelVA( const G4Track* track, int i )
     {
    -    const C4Pho* label = C4TrackInfo<C4Pho>::GetRef(track); 
    +    const C4Pho* label = C4TrackInfo::GetRef(track);
         return label ? label->get_va(i) : -1 ;
     }



    +0.1.9 : 2026/01/16
    +---------------------
    +
    +* change formerly templated C4TrackInfo typically used with C4Pho template type to being non-templated
    +  with fixed C4Pho type for the label, this change is because dynamic casts do not work with templated C4TrackInfo
    +  preventing integration with code with other users of Geant4 track info
    +* move C4OpBoundaryProcess::m_track_label behind C4_DEBUG_PIDX as only needed for debug
    +





::

    A[blyth@localhost customgeant4]$ git log v0.1.8..v0.1.8_transient --oneline
    80c8d45 (v0.1.8_transient) notes for future release v0.1.9
    e37dc30 change formerly templated C4TrackInfo typically used with C4Pho template type to being non-templated with fixed C4Pho type for the label, this change is because dynamic casts do not work with templated C4TrackInfo preventing integration with code with other users of Geant4 track info
    93c8b31 move C4OpBoundaryProcess::m_track_label behind C4_DEBUG_PIDX as only needed for debug
    A[blyth@localhost customgeant4]$ 




custom4 overview
----------------

* recent track info template change only in v0.1.8_transient


git lg v0.1.8_transient
------------------------


::

    A[blyth@localhost customgeant4]$ git lg v0.1.8_transient
    * 2026-01-16 80c8d45 - (v0.1.8_transient) notes for future release v0.1.9 (2 months ago) <Simon C Blyth>
    * 2026-01-16 e37dc30 - change formerly templated C4TrackInfo typically used with C4Pho template type to being non-templated with fixed C4Pho type for the label, this change is because dynamic casts do not work with templated C4TrackInfo preventing integration with code with other users of Geant4 track info (2 months ago) <Simon C Blyth>
    * 2026-01-16 93c8b31 - move C4OpBoundaryProcess::m_track_label behind C4_DEBUG_PIDX as only needed for debug (2 months ago) <Simon C Blyth>
  
    * 2023-10-18 49d673e - (tag: v0.1.8) minor change to ART struct to assist with tests, add test comparing with pypi tmm : find near perfect agreement (2 years, 5 months ago) <Simon C Blyth>
    * 2023-10-08 f9c9f66 - immediately following tagging of 0.1.7 bump the CMakeLists.txt version to 0.1.8 for the next release, and preview installs of that (2 years, 6 months ago) <Simon C Blyth>
    * 2023-10-08 f3f6c7d - (tag: v0.1.7) minor improvements to workflow documentation in preparation for adding tag, no change to results (2 years, 6 months ago) <Simon C Blyth>
    * 2023-08-08 8f29fc6 - debug dumping magnitudes of the ThreeVector (2 years, 8 months ago) <Simon C Blyth>
    * 2023-08-08 1f5bf00 - avoid Release build compilation warning using NDEBUG macro that when defined disables assert (2 years, 8 months ago) <Simon C Blyth>
    * 2023-08-07 6678ec4 - hide the debug behind C4_DEBUG_PIDX which is only enabled for Debug builds (2 years, 8 months ago) <Simon C Blyth>


git lg main
------------


::


    A[blyth@localhost customgeant4]$ git lg main

Infrastructure script changes can go into 0.1.9::

    * 2025-06-26 95a16f9 - (HEAD -> main, origin/main, origin/HEAD) add generation of bashrc into prefix and update default prefix path (9 months ago) <Simon C Blyth>

        RELEASE_NOTES.rst
        build.sh
        build_Debug.sh
        build_Release.sh
        generate_bashrc.sh

        * change to default prefix, convenience bashrc generation

        git cherry-pick 95a16f9


Too consequential, not ready for 0.1.9::

    * 2025-06-26 473e21f - compilation fixes regarding the implementation version switching (9 months ago) <Simon C Blyth>
        * C4CustomART.h
        * CONSEQUENTIAL : ADDITION OF PLACEHOLDER TO ENUM
        git show -b 473e21f   # white space changes, including to C4Pho.h


Essentially a bug fix to keep some compilers happy, do this manually if the compiler complains::

    * 2025-05-28 daa7af7 - add do nothing virtual dtor needed by some compilers (10 months ago) <Simon C Blyth>
         * C4IPMTAccessor.h : literally just addition of "    virtual ~C4IPMTAccessor(){} ;"
         * HMM: THATS A SMALL CHANGE TO HEADER THATS ALSO CHANGED IN NON-READY COMMITS, SO JUST DO IT MANUALLY

Too consequential to add to 0.1.9 without extensive testing together with JUNOSW::

    * 2024-11-04 9f1407d - notes on the related CUDA impl (1 year, 5 months ago) <Simon C Blyth>
         * custom4_explained.rst

    * 2024-11-04 8547218 - untested modifications for implementation_version YUHAN (1) (1 year, 5 months ago) <Simon C Blyth>
         * ORIGINAL/TRANSIENT/YUHAN

    * 2024-08-16 48ad617 - prep for angular efficiency generalization (1 year, 7 months ago) <Simon C Blyth>
        * C4CustomART.h add implementation_version (which is obtained from accessor) and localPoint (updated by C4CustomART::update_local_position) 
        * CONSEQUENTIAL : ANGULAR IMPL WHICH REQUIRES JUNOSW ADAPTION TO USE

        C4CustomART.h
        C4CustomART_Debug.h
        C4IPMTAccessor.h
        C4OpBoundaryProcess.cc
        angular_generalization.rst
        custom4_explained.rst
        tests/C4OpBoundaryProcessTest.cc




Infrastructure machinery changes do not need extensive testing, and can go directly into 0.1.9::

    * 2024-08-07 a3ad098 - facilitate separate Debug and Release builds, add explanation (1 year, 8 months ago) <Simon C Blyth>
        * script change to default installation prefix

        build.sh
        build_Debug.sh
        build_Release.sh
        custom4_explained.rst

        git cherry-pick a3ad098    ## DONE CLEANLY


    * 2023-10-20 9e81b3e - avoid invalid octal in the generated C4Version.h (2 years, 5 months ago) <Simon C Blyth>

        CMakeLists.txt

        git cherry-pick 9e81b3eA   ## DONE CLEANLY


    * 2023-10-20 fa6bade - try to avoid invalid digit 8 in octal constant issue (2 years, 5 months ago) <Simon C Blyth>
        * avoid 00 in C4Version.h.in and CMakeLists.txt

        C4Version.h.in
        issues/Custom4_VERSION_NUMBER_invalid_digit_8_in_octal_constant_issue_in_g4cx.rst
        tests/V_test.cc

        git cherry-pick fa6bade  ## DONE CLEANLY 


    * 2023-10-18 4df7b47 - bump the version to 0.1.9 for the next untagged version (2 years, 5 months ago) <Simon C Blyth>
         * change the preprocessor const CMakeLists.txt

        CMakeLists.txt
        addtag.sh

        git cherry-pick 4df7b47  ## DONE WITH CONFLICT FIXES

  
    * 2023-10-18 49d673e - (tag: v0.1.8) minor change to ART struct to assist with tests, add test comparing with pypi tmm : find near perfect agreement (2 years, 5 months ago) <Simon C Blyth>
    * 2023-10-08 f9c9f66 - immediately following tagging of 0.1.7 bump the CMakeLists.txt version to 0.1.8 for the next release, and preview installs of that (2 years, 6 months ago) <Simon C Blyth>
    * 2023-10-08 f3f6c7d - (tag: v0.1.7) minor improvements to workflow documentation in preparation for adding tag, no change to results (2 years, 6 months ago) <Simon C Blyth>
    * 2023-08-08 8f29fc6 - debug dumping magnitudes of the ThreeVector (2 years, 8 months ago) <Simon C Blyth>
    * 2023-08-08 1f5bf00 - avoid Release build compilation warning using NDEBUG macro that when defined disables assert (2 years, 



How to make v0.1.9 selecting just the fixes and infrastructure enhancements from v0.1.8_transient and main, while excluding consequential impl changes in main ?
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

Q:
I want to make a new 0.1.9 release incorporating the few commits in
0.1.8_transient plus a handful of the commits to main. What is the best
approach to do that ? Essentially several of the commits in main are not ready
for release.

Gemini:
The best approach here is to use "git cherry-pick". This allows you to
hand-pick specific commits from main and "apply" them onto your new release
branch without bringing along the unfinished work.

Suggested workflow::

    git checkout -b v0.1.9_release v0.1.8_transient   # creating fresh branch based on v0.1.8_transient
    git log main --oneline   # identity the ready commits from main

While on v0.1.9_release branch cherry-pick the commits from main that are ready::

    git cherry-pick deadbeef   
    git cherry-pick --abort  ## if get lots of conflict

Once verified v0.1.9_release tag it::

    git tag -a v0.1.9 -m "Release version 0.1.9"
    git push origin v0.1.9


When deciding if a commit is ready, consider if it has dependencies on changes
that are not-ready if so then it is also not-ready.  


Q:
The cherry picking approach seems doable.  But what about the down the line
when I am ready for so far skipped commits in main together with the commits
already released ?

Gemini:
When you eventually merge the "rest" of main into your release line (or vice versa), 
Git uses a process called Patch ID matching. Even though the cherry-picked commit 
has a different "ID" (hash) than the original on main, Git
recognizes that the content of the changes is identical.

The "Clean Up" Strategy

If you want to keep your history pristine and avoid "duplicate" 
looking commits in your log, you have two professional options:

* A: The Merge Back: Once v0.1.9 is officially released, merge that release
branch back into main. This tells main, "Hey, these specific fixes are now
officially part of the history." Git will mark those changes as 'seen.'

* B: Rebase main: If you are the only one working on the project, you can
rebase main onto the new release tag. This "shuffles" the unfinished commits to
the very top of the stack, sitting neatly on top of the new v0.1.9 foundation.


Summary of the "Down the Line" Workflow:

* Release v0.1.9 (contains cherry-picks).
* Merge v0.1.9 back into main immediately   [SCB: or rebase?]
* Continue working on main for the unfinished features.

When those features are ready, they will sit on top of a history that already
includes the v0.1.9 fixes.


2026 Mar 31 : cherry-pick to form v0.1.9_release
--------------------------------------------------

::

    A[blyth@localhost customgeant4]$ git checkout -b v0.1.9_release v0.1.8_transient
    Switched to a new branch 'v0.1.9_release'

    A[blyth@localhost customgeant4]$ git status
    On branch v0.1.9_release
    nothing to commit, working tree clean


with conflict fixes : git cherry-pick 4df7b47
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    A[blyth@localhost customgeant4]$ git cherry-pick 4df7b47
    Auto-merging CMakeLists.txt
    CONFLICT (content): Merge conflict in CMakeLists.txt
    Auto-merging addtag.sh
    CONFLICT (content): Merge conflict in addtag.sh
    error: could not apply 4df7b47... bump the version to 0.1.9 for the next untagged version
    hint: After resolving the conflicts, mark them with
    hint: "git add/rm <pathspec>", then run
    hint: "git cherry-pick --continue".
    hint: You can instead skip this commit with "git cherry-pick --skip".
    hint: To abort and get back to the state before "git cherry-pick",
    hint: run "git cherry-pick --abort".
    hint: Disable this message with "git config advice.mergeConflict false"
    A[blyth@localhost customgeant4]$ git s
    On branch v0.1.9_release
    You are currently cherry-picking commit 4df7b47.
      (fix conflicts and run "git cherry-pick --continue")
      (use "git cherry-pick --skip" to skip this patch)
      (use "git cherry-pick --abort" to cancel the cherry-pick operation)

    Unmerged paths:
      (use "git add <file>..." to mark resolution)
        both modified:   CMakeLists.txt
        both modified:   addtag.sh

    A[blyth@localhost customgeant4]$ vi CMakeLists.txt 
    A[blyth@localhost customgeant4]$ git add CMakeLists.txt
    A[blyth@localhost customgeant4]$ vi addtag.sh
    A[blyth@localhost customgeant4]$ git add addtag.sh
    A[blyth@localhost customgeant4]$ git cherry-pick --continue
    [v0.1.9_release 730f4fd] bump the version to 0.1.9 for the next untagged version and resolve cherry-pick conflicts
     Date: Wed Oct 18 16:17:47 2023 +0800
     2 files changed, 5 insertions(+), 4 deletions(-)
    A[blyth@localhost customgeant4]$ git s
    On branch v0.1.9_release
    nothing to commit, working tree clean
    A[blyth@localhost customgeant4]$ 
    A[blyth@localhost customgeant4]$ vi addtag.sh 



CLEAN : git cherry-pick fa6bade
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    A[blyth@localhost customgeant4]$ git cherry-pick fa6bade
    [v0.1.9_release 1248f9d] try to avoid invalid digit 8 in octal constant issue
     Date: Fri Oct 20 11:22:47 2023 +0800
     3 files changed, 43 insertions(+), 11 deletions(-)
     create mode 100644 issues/Custom4_VERSION_NUMBER_invalid_digit_8_in_octal_constant_issue_in_g4cx.rst
    A[blyth@localhost customgeant4]$ 



WITH CONFLICT FIXES : git cherry-pick 95a16f9
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    A[blyth@localhost customgeant4]$ git cherry-pick 95a16f9
    Auto-merging RELEASE_NOTES.rst
    CONFLICT (content): Merge conflict in RELEASE_NOTES.rst
    error: could not apply 95a16f9... add generation of bashrc into prefix and update default prefix path
    hint: After resolving the conflicts, mark them with
    hint: "git add/rm <pathspec>", then run
    hint: "git cherry-pick --continue".
    hint: You can instead skip this commit with "git cherry-pick --skip".
    hint: To abort and get back to the state before "git cherry-pick",
    hint: run "git cherry-pick --abort".
    hint: Disable this message with "git config advice.mergeConflict false"
    A[blyth@localhost customgeant4]$ 

    A[blyth@localhost customgeant4]$ git s
    On branch v0.1.9_release
    You are currently cherry-picking commit 95a16f9.
      (all conflicts fixed: run "git cherry-pick --continue")
      (use "git cherry-pick --skip" to skip this patch)
      (use "git cherry-pick --abort" to cancel the cherry-pick operation)

    Changes to be committed:
        modified:   RELEASE_NOTES.rst
        modified:   build.sh
        modified:   build_Debug.sh
        modified:   build_Release.sh
        new file:   generate_bashrc.sh

    A[blyth@localhost customgeant4]$ git cherry-pick --continue
    [v0.1.9_release 1bbf118] add generation of bashrc into prefix and update default prefix path : plus fix conflict in RELEASE_NOTES.rst
     Date: Thu Jun 26 20:09:38 2025 +0800
     5 files changed, 97 insertions(+), 40 deletions(-)
     create mode 100755 generate_bashrc.sh
    A[blyth@localhost customgeant4]$ 


NOTE THE FUNNY TIME ORDER
~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    A[blyth@localhost customgeant4]$ git lg
    * 2025-06-26 1bbf118 - (HEAD -> v0.1.9_release) add generation of bashrc into prefix and update default prefix path : plus fix conflict in RELEASE_NOTES.rst (2 minutes ago) <Simon C Blyth>
    * 2024-08-07 3a1fead - facilitate separate Debug and Release builds, add explanation (6 minutes ago) <Simon C Blyth>
    * 2023-10-20 21d8fd3 - avoid invalid octal in the generated C4Version.h (7 minutes ago) <Simon C Blyth>
    * 2023-10-20 1248f9d - try to avoid invalid digit 8 in octal constant issue (9 minutes ago) <Simon C Blyth>
    * 2023-10-18 730f4fd - bump the version to 0.1.9 for the next untagged version and resolve cherry-pick conflicts (12 minutes ago) <Simon C Blyth>
    * 2026-01-16 80c8d45 - (v0.1.8_transient) notes for future release v0.1.9 (2 months ago) <Simon C Blyth>
    * 2026-01-16 e37dc30 - change formerly templated C4TrackInfo typically used with C4Pho template type to being non-templated with fixed C4Pho type for the label, this change is because dynamic casts do not work with templated C4TrackInfo preventing integration with code with other users of Geant4 track info (2 months ago) <Simon C Blyth>
    * 2026-01-16 93c8b31 - move C4OpBoundaryProcess::m_track_label behind C4_DEBUG_PIDX as only needed for debug (2 months ago) <Simon C Blyth>
    * 2023-10-18 49d673e - (tag: v0.1.8) minor change to ART struct to assist with tests, add test comparing with pypi tmm : find near perfect agreement (2 years, 5 months ago) <Simon C Blyth>
    * 2023-10-08 f9c9f66 - immediately following tagging of 0.1.7 bump the CMakeLists.txt version to 0.1.8 for th


jcv DsPhysConsOptical
-----------------------

::

    383 C4OpBoundaryProcess* DsPhysConsOptical::CreateCustomG4OpBoundaryProcess()
    384 {
    385     SniperPtr<IPMTSimParamSvc> psps_ptr(*getParent(), "PMTSimParamSvc");
    386 
    387     if(psps_ptr.invalid())
    388     {
    389         std::cout << "invalid" << std::endl ;
    390         return nullptr ;
    391     }
    392 
    393     IPMTSimParamSvc* ipsps = psps_ptr.data();
    394     PMTSimParamData* pspd = ipsps->getPMTSimParamData() ;
    395 
    396     C4IPMTAccessor* accessor = new PMTAccessor(pspd) ;
    397     C4OpBoundaryProcess* boundproc = new C4OpBoundaryProcess(accessor) ;
    398     std::cout << "DsPhysConsOptical::CreateCustomG4OpBoundaryProcess" << std::endl ;
    399 
    400     return boundproc ;
    401 }




jcv PMTAccessor
-----------------

::

     42 struct PMTAccessor : public C4IPMTAccessor
     43 {
     44     static constexpr const char* TypeName = "PMTAccessor" ;
     45 
     46     const PMTSimParamData* data ;
     47 
     48     const G4Material*          Pyrex  ;
     49     const G4Material*          Vacuum ;
     50     G4MaterialPropertiesTable* PyrexMPT ;
     51     G4MaterialPropertiesTable* VacuumMPT ;
     52     G4MaterialPropertyVector*  PyrexRINDEX ;
     53     G4MaterialPropertyVector*  VacuumRINDEX ;
     54 
     55     static std::string Desc();
     56 
     57     static const PMTSimParamData* LoadData(const char* base, const char* relp="PMTSimParamData");
     58     static const PMTAccessor* Load(const char* base );
     59     static const PMTAccessor* Create(const PMTSimParamData* data );
     60 
     61     PMTAccessor(const PMTSimParamData* data);
     62     PMTAccessor(const PMTSimParamData* data, G4MaterialPropertyVector* PyrexRINDEX, G4MaterialPropertyVector* VacuumRINDEX );
     63     std::string desc() const ;
     64 
     65 
     66     // C4IPMTAccessor interface
     67     int    get_num_lpmt() const ;
     68     double get_pmtid_qe( int pmtid, double energy ) const ;
     69     double get_qescale(  int pmtid ) const ;
     70     int    get_pmtcat( int pmtid  ) const ;
     71     void   get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const ;
     72     const char* get_typename() const ;
     73 
     74     // HMM: is the argument really energy_eV or energy (factor of 1e-6 between them)
     75 };


NB that does not fulfil main/C4IPMTAccessor, missing the implementation_version and qe_angular methods::

      5 struct C4IPMTAccessor
      6 {
      7     virtual int    get_num_lpmt() const = 0 ;
      8     virtual double get_pmtid_qe( int pmtid, double energy ) const = 0 ;
      9     virtual double get_qescale( int pmtid ) const = 0 ;
     10     virtual int    get_pmtcat( int pmtid  ) const = 0 ;
     11     virtual void   get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const = 0 ;
     12 
     13     virtual void   get_stackspec_pmtid_theta_deg( std::array<double, 16>& ss, int pmtcat, int pmtid, double energy_eV, double theta_deg ) const = 0 ;
     14 
     15 
     16     virtual const char* get_typename() const = 0 ;
     17 
     18     virtual double get_pmtid_qe_angular(int pmtid,double energy, double lposcost, double minus_cos_theta_aoi) const = 0 ;
     19     virtual int    get_implementation_version() const = 0 ;
     20     virtual void   set_implementation_version(int v) = 0 ;
     21 
     22     virtual ~C4IPMTAccessor(){} ;
     23 
     24 };






HMM this old install is too old compared to source
---------------------------------------------------------

::

    A[blyth@localhost 0.1.9]$ l include/Custom4/
    total 116
     4 drwxr-xr-x. 2 blyth blyth  4096 Jun 26  2025 .
     4 -rw-r--r--. 1 blyth blyth  2589 Jun 26  2025 C4Version.h
    20 -rw-r--r--. 1 blyth blyth 16413 Jun 26  2025 C4CustomART.h
     4 drwxr-xr-x. 3 blyth blyth  4096 Jun 26  2025 ..
     8 -rw-r--r--. 1 blyth blyth  6003 Jun  5  2025 C4Pho.h
     4 -rw-r--r--. 1 blyth blyth   887 May 28  2025 C4IPMTAccessor.h
     4 -rw-r--r--. 1 blyth blyth   721 May 28  2025 C4CustomART_Debug.h
     4 -rw-r--r--. 1 blyth blyth  2079 May 28  2025 C4GS.h
    24 -rw-r--r--. 1 blyth blyth 23440 May 28  2025 C4MultiLayrStack.h
    16 -rw-r--r--. 1 blyth blyth 12290 May 28  2025 C4OpBoundaryProcess.hh
     4 -rw-r--r--. 1 blyth blyth   442 May 28  2025 C4Sys.h
     8 -rw-r--r--. 1 blyth blyth  5451 May 28  2025 C4Touchable.h
     8 -rw-r--r--. 1 blyth blyth  5483 May 28  2025 C4Track.h
     4 -rw-r--r--. 1 blyth blyth  3831 May 28  2025 C4TrackInfo.h
    A[blyth@localhost 0.1.9]$ vi include/Custom4/C4Version.h 
    A[blyth@localhost 0.1.9]$ pwd
    /data1/blyth/local/custom4_Debug/0.1.9
    A[blyth@localhost 0.1.9]$ find . -type f
    ./lib64/Custom4-0.1.9/Custom4Config.cmake
    ./lib64/Custom4-0.1.9/Custom4ConfigVersion.cmake
    ./lib64/libCustom4.so
    ./include/Custom4/C4OpBoundaryProcess.hh
    ./include/Custom4/C4CustomART_Debug.h
    ./include/Custom4/C4Version.h
    ./include/Custom4/C4Pho.h
    ./include/Custom4/C4Sys.h
    ./include/Custom4/C4TrackInfo.h
    ./include/Custom4/C4CustomART.h
    ./include/Custom4/C4Track.h
    ./include/Custom4/C4GS.h
    ./include/Custom4/C4IPMTAccessor.h
    ./include/Custom4/C4Touchable.h
    ./include/Custom4/C4MultiLayrStack.h
    ./bashrc
    A[blyth@localhost 0.1.9]$ 












