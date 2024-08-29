alma-linux-9.4 July 30 2024
============================



::

    Dear all,

    Please notice that IHEP computing platform had been upgraded to Alma Linux 9.4. 
    Here are the major changes:

    1. Login nodes have been changed from lxslc7.ihep.ac.cn to lxlogin.ihep.ac.cn. The default OS is Alma Linux 9.4.

        The jobs submitted on lxslc7 will not be executed. 

    2. The hepjob is deployed under:

        /cvmfs/common.ihep.ac.cn/software/hepjob/bin
        So please update your PATH environment variables:

        export PATH=/cvmfs/common.ihep.ac.cn/software/hepjob/bin:$PATH 
    3. If you need to run the job with the previous operation system CentOS 7, please add hepcontainer to your PATH environment variables:

        export PATH=/cvmfs/container.ihep.ac.cn/bin:$PATH

        To start the CentOS 7 container in the login nodes:

        hep_container shell CentOS7

        To submit the CentOS 7 jobs:

        hep_sub -os CentOS7 job.sh

    4. For the latest version of JUNOSW, you can find both deployments for Alma Linux 9 and CentOS 7:

        AlmaLinux 9: source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.1.2/setup.sh
        CentOS 7: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Release/J24.1.2/setup.sh
    5. For your existing development environments, if you switch to AlmaLinux9, you need to clean your "build" and "InstallArea".

    Please let me know if you encounter any issues. Thank you. 
    Tao

