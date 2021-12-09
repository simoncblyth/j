#!/usr/bin/env python
"""
opts.py
=========

Testing an easier to maintain way of contolling switches 
for use with::

    jcv JUNODetSimModule     # shortcut: jdsm 
    jcv JUNOApplication 

"""

import os, textwrap, argparse, logging
log = logging.getLogger(__name__)

class Opts(object):

    switch = textwrap.dedent("""

    --pmt20inch-polycone-neck 
        Use economical polycone 20inch PMT neck shape replacing cylinder-torus.

    --pmt20inch-simplify-csg 
        Simplify CSG modelling of 20inch PMTs, avoiding Inner_Separator anti-pattern, see HamamatsuR12860PMTManager + NNVTMCPPMTManager 

    --additionacrylic-simplify-csg 
        Do not excavate cavities for daugter volumes 

    --debug-disable-sticks         
        Debug only 

    """)


    def register_switch_options(self, group, debug=False):
        """
        Parses self.switch adding the listed arguments and help text to the argparse group 
        """
        lines = self.switch.split("\n")
        for i in range(1,len(lines)):
            if lines[i-1][:2] == "--":
                argument = lines[i-1].rstrip()
                argdesc = lines[i].lstrip().rstrip() 
                assert not "_" in argument, argument  
                key = "JUNO_%s" % argument[2:].upper().replace("-","_") 
                argdesc += " (sets internal envvar %s )" % key 
                if debug:
                    print("[%s]"% argument)
                    print("[%s]"% argdesc)
                pass
                group.add_argument(argument, default=False, action="store_true", help=argdesc)
            pass
        pass

    def init_switch_envvars(self, args, debug=False):
        """  
        This sets internal envvar when some commandline switches are used.
        Note that externally set envvars with these keys **ARE IGNORED**.
        Messaging via internal envvars has the advantages:

        1. instanciation order is unchanged 
        2. requires a minimum of code
        3. works in standalone manner for convenient testing

        Constraints followed/imposed:

        * command line arguments use "-" not "_", hence "_" are disallowed in switch 
        * argparser args uses "_" not "-" for attributes
        * envvar keys start with "JUNO_" and use "_" not "-"

        """
        for line in self.switch.split("\n"):
            if not line[:2] == "--": continue
            attn = line[2:].rstrip().replace("-","_")
            att = getattr( args, attn, None )

            if debug:
                log.info("attn:[%s] att:[%s]" % (attn, att))
            pass

            key = "JUNO_%s" % attn.upper().replace("-","_") 
            # assert att, key 
            if att == True:
                log.info("setting key %s from args.%s  " % (key, attn))
                os.environ[key] = "ENABLED"
            else:
                ## prevent sensitivity to external envvars with these keys 
                if key in os.environ:
                    log.info("un-setting key %s from args.%s  " % (key, attn))
                    os.environ.pop(key)
                pass
            pass
        pass


def mh(txt):
    return txt


if __name__ == '__main__':

     logging.basicConfig(level=logging.INFO)
     opts = Opts()
     print(opts.switch)

     parser = argparse.ArgumentParser()
     group = parser.add_argument_group(mh("pmtop"), mh("PMT and Optical Progress"))


     debug = False

     opts.init_switch_options(group, debug=debug)
     args = parser.parse_args()

     opts.init_switch_envvars(args, debug=debug)



