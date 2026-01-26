atm.rst : tips to get started submitting Opticks+JUNOSW to IHEP GPU using Slurm with sbatch command
====================================================================================================


Starting script in my *j* git repository, see::

    https://code.ihep.ac.cn/blyth/j/-/blob/main/atm/simple.sh

Your IHEP SSO account should get you thru to that.
Study the script and try it out. You can get the full repo with::

    cd /hpcfs/juno/junogpu/$USER
    git clone git@code.ihep.ac.cn:blyth/j.git

For that to work you will need ssh keys and ssh-agent setup to authenticate
with the server.

A few things to note about the script:

1. redefines HOME to /hpcfs/juno/junogpu/$USER as that avoids AFS token complications,
   you could also do that in your lxlogin .bash_profile for convenience and to minimize
   the need to enter AFS passwords

2. running ~/j/atm/simple.sh writes $HOME/ENVSET.sh in which the OJ release version
   is defined.  This facilitates comparison between releases without changing
   the main script as output directories include the $ENVSET_NAME eg OJ_059

3. the script takes arguments that do different things eg::

   ~/j/atm/simple.sh info   # lists info including output dir
   ~/j/atm/simple.sh usage  # slurm usage tips
   ~/j/atm/simple.sh sub    # submits to slurm

Once simple.sh slurm submission is working, take a look at::

    https://code.ihep.ac.cn/blyth/j/-/tree/main/zhenning_double_muon/

The scripts in that directory like detsim.sh are based on double muon
scripts from Zhenning. However it is setup for just local usage not slurm
submission.

I suggest you copy simple.sh to "mu2.sh" and integrate the tut_detsim.py
commandline from zhenning_double_muon/detsim.sh into it.



