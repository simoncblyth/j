#!/bin/bash


sudo pkill -9 -f cvmfs2

sudo umount -l /cvmfs/juno.ihep.ac.cn
sudo umount -l /cvmfs/opticks.ihep.ac.cn

sudo systemctl restart autofs
sudo systemctl status autofs

ls -alst /cvmfs/juno.ihep.ac.cn
ls -alst /cvmfs/opticks.ihep.ac.cn



