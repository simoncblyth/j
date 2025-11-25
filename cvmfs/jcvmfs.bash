jcvmfs_usage(){ cat << EOU

   . ~/j/cvmfs/jcvmfs.bash

https://cvmfs.readthedocs.io/en/stable/cpt-configure.html

::

    lsof -c cvmfs2

cvmfs alien cache cleanup


EOU
}

jcvmfs_cachedir(){ echo /scratch/cvmfs_cache ; }
jcvmfs_repo(){     echo juno.ihep.ac.cn ; }

jcvmfs(){

cvmfs_config showconfig $(jcvmfs_repo) | grep -E "CACHE_BASE|QUOTA_LIMIT|HTTP_PROXY"

}


jcvmfs_config(){

   local cfg=/etc/cvmfs/config.d/juno.ihep.ac.cn.conf
   jcvmfs_config_ > $cfg

   local dir=$(jcvmfs_cachedir)

   mkdir -p $dir
   chmod 1777 $dir
   cvmfs_config reload   # Apply immediately
}


jcvmfs_config_(){ cat << EOC
CVMFS_CACHE_BASE=$(jcvmfs_cachedir)
CVMFS_QUOTA_LIMIT=40000
CVMFS_HTTP_PROXY=DIRECT
CVMFS_SHARED_CACHE=yes
EOC
}

