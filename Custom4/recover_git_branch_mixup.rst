recover_git_branch_mixup
=========================

Actually the 3 commits is a distraction from a bigger issues of not being
ready to start using a 0.1.9 release : as that needs more testing.

The reason I was using v0.1.8_transient branch that only differs slightly from v0.1.8
that has been in use for years is because I wanted to test just the change from templated 
to non-templated C4TrackInfo  prior to being ready to take the leap to making.



ACTUALLY : THE 3 COMMITS CAN EASILY BE MANUALLY APPLIED TO MAIN : BUT THATS NOT THE ISSUE
--------------------------------------------------------------------------------------------

::

    git show -b 93c8b31      ## MINOR : EASY TO MANUALLY REDO
    git show -b e37dc30      ## MOSTLY AUTOMATABLE REMOVAL OF TEMPLATE TYPE
    git show -b 80c8d45      ## COMMENT BLOCK IN RELEASE NOTES


Yesterday I thought:

    Have 3 commits to v0.1.8_transient that should go to main for making the v0.1.9 tag.

But thats not the main issue, the 3 commits are a minor 
from the primary issue of not being ready to release without the changes since v0.1.9 
without significant testing.  

HMM : v0.1.9 can be made from v0.1.8_transient ? Leaving main for later ? 




THREE COMMIT DISTRACTION
--------------------------


Before realizing was on the transient got push failure::

    A[blyth@localhost customgeant4]$ git push
    fatal: The current branch v0.1.8_transient has no upstream branch.
    To push the current branch and set the remote as upstream, use
        git push --set-upstream origin v0.1.8_transient
    To have this happen automatically for branches without a tracking
    upstream, see 'push.autoSetupRemote' in 'git help config'.


Switch from v0.1.8_transient to main to check the sequence of commits in the two branches::

    A[blyth@localhost customgeant4]$ git s
    On branch v0.1.8_transient
    nothing to commit, working tree clean


    A[blyth@localhost customgeant4]$ git checkout main
    Switched to branch 'main'
    Your branch is up to date with 'origin/main'.
    A[blyth@localhost customgeant4]$ git pull origin main
    Ncat: Version 7.92 ( https://nmap.org/ncat )
    Ncat: Connected to proxy 127.0.0.1:8080
    Ncat: No authentication needed.
    Ncat: Host github.com will be resolved by the proxy.
    Ncat: connection succeeded.
    From github.com:simoncblyth/customgeant4
     * branch            main       -> FETCH_HEAD
    Already up to date.



commits in v0.1.8_transient : 3 COMMITS ON TOP OF v0.1.8 INCLUDING C4TrackInfo TEMPLATE REMOVAL
--------------------------------------------------------------------------------------------------

::

    (ok) A[blyth@localhost customgeant4]$ git s
    On branch v0.1.8_transient
    nothing to commit, working tree clean

    A[blyth@localhost customgeant4]$ git lg -n10
    * 2026-01-16 80c8d45 - (HEAD -> v0.1.8_transient) notes for future release v0.1.9 (10 minutes ago) <Simon C Blyth>
    * 2026-01-16 e37dc30 - change formerly templated C4TrackInfo typically used with C4Pho template type to being non-templated with fixed C4Pho type for the label, this change is because dynamic casts do not work with templated C4TrackInfo preventing integration with code with other users of Geant4 track info (19 minutes ago) <Simon C Blyth>
    * 2026-01-16 93c8b31 - move C4OpBoundaryProcess::m_track_label behind C4_DEBUG_PIDX as only needed for debug (23 minutes ago) <Simon C Blyth>


    * 2023-10-18 49d673e - (tag: v0.1.8) minor change to ART struct to assist with tests, add test comparing with pypi tmm : find near perfect agreement (2 years, 3 months ago) <Simon C Blyth>
    * 2023-10-08 f9c9f66 - immediately following tagging of 0.1.7 bump the CMakeLists.txt version to 0.1.8 for the next release, and preview installs of that (2 years, 3 months ago) <Simon C Blyth>
    * 2023-10-08 f3f6c7d - (tag: v0.1.7) minor improvements to workflow documentation in preparation for adding tag, no change to results (2 years, 3 months ago) <Simon C Blyth>
    * 2023-08-08 8f29fc6 - debug dumping magnitudes of the ThreeVector (2 years, 5 months ago) <Simon C Blyth>
    * 2023-08-08 1f5bf00 - avoid Release build compilation warning using NDEBUG macro that when defined disables assert (2 years, 5 months ago) <Simon C Blyth>
    * 2023-08-07 6678ec4 - hide the debug behind C4_DEBUG_PIDX which is only enabled for Debug builds (2 years, 5 months ago) <Simon C Blyth>
    * 2023-08-07 84a78eb - debug logging and installation utilities (2 years, 5 months ago) <Simon C Blyth>
    A[blyth@localhost customgeant4]$ 



commits in main : 10 rather minor commits over 3 years since tag v0.1.8 : BUT IMPORTANCE OF C4 NECCESSITATES CAREFUL TEST BEFORE RELEASING THESE CHANGES
----------------------------------------------------------------------------------------------------------------------------------------------------------

::

    A[blyth@localhost customgeant4]$ git s
    On branch main
    Your branch is up to date with 'origin/main'.

    nothing to commit, working tree clean

    A[blyth@localhost customgeant4]$ git lg -n15
    * 2025-06-26 95a16f9 - (HEAD -> main, origin/main, origin/HEAD) add generation of bashrc into prefix and update default prefix path (7 months ago) <Simon C Blyth>
    * 2025-06-26 473e21f - compilation fixes regarding the implementation version switching (7 months ago) <Simon C Blyth>
    * 2025-05-28 daa7af7 - add do nothing virtual dtor needed by some compilers (8 months ago) <Simon C Blyth>
    * 2024-11-04 9f1407d - notes on the related CUDA impl (1 year, 2 months ago) <Simon C Blyth>
    * 2024-11-04 8547218 - untested modifications for implementation_version YUHAN (1) (1 year, 2 months ago) <Simon C Blyth>
    * 2024-08-16 48ad617 - prep for angular efficiency generalization (1 year, 5 months ago) <Simon C Blyth>
    * 2024-08-07 a3ad098 - facilitate separate Debug and Release builds, add explanation (1 year, 5 months ago) <Simon C Blyth>
    * 2023-10-20 9e81b3e - avoid invalid octal in the generated C4Version.h (2 years, 3 months ago) <Simon C Blyth>
    * 2023-10-20 fa6bade - try to avoid invalid digit 8 in octal constant issue (2 years, 3 months ago) <Simon C Blyth>
    * 2023-10-18 4df7b47 - bump the version to 0.1.9 for the next untagged version (2 years, 3 months ago) <Simon C Blyth>

    * 2023-10-18 49d673e - (tag: v0.1.8) minor change to ART struct to assist with tests, add test comparing with pypi tmm : find near perfect agreement (2 years, 3 months ago) <Simon C Blyth>
    * 2023-10-08 f9c9f66 - immediately following tagging of 0.1.7 bump the CMakeLists.txt version to 0.1.8 for the next release, and preview installs of that (2 years, 3 months ago) <Simon C Blyth>
    * 2023-10-08 f3f6c7d - (tag: v0.1.7) minor improvements to workflow documentation in preparation for adding tag, no change to results (2 years, 3 months ago) <Simon C Blyth>
    * 2023-08-08 8f29fc6 - debug dumping magnitudes of the ThreeVector (2 years, 5 months ago) <Simon C Blyth>
    * 2023-08-08 1f5bf00 - avoid Release build compilation warning using NDEBUG macro that when defined disables assert (2 years, 5 months ago) <Simon C Blyth>
    A[blyth@localhost customgeant4]$ 



rebase  --onto main v0.1.8 v0.1.8_transient : THIS IS A DISTRACTION : THE THREE COMMITS ARE EASY TO APPLY MANUALLY ONTO MAIN OR ELSEWHERE
-------------------------------------------------------------------------------------------------------------------------------------------

::

    A[blyth@localhost customgeant4]$ git rebase --onto main v0.1.8 v0.1.8_transient
    Auto-merging C4CustomART.h
    CONFLICT (content): Merge conflict in C4CustomART.h
    Auto-merging C4OpBoundaryProcess.cc
    error: could not apply 93c8b31... move C4OpBoundaryProcess::m_track_label behind C4_DEBUG_PIDX as only needed for debug
    hint: Resolve all conflicts manually, mark them as resolved with
    hint: "git add/rm <conflicted_files>", then run "git rebase --continue".
    hint: You can instead skip this commit: run "git rebase --skip".
    hint: To abort and get back to the state before "git rebase", run "git rebase --abort".
    hint: Disable this message with "git config advice.mergeConflict false"
    Could not apply 93c8b31... move C4OpBoundaryProcess::m_track_label behind C4_DEBUG_PIDX as only needed for debug
    A[blyth@localhost customgeant4]$ 

Cherry pick approach::


     git checkout main
     git cherry-pick 93c8b31
     git cherry-pick --abort



