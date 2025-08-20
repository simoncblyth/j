
This pipeline fail and others was due to the Opticks+JUNOSW (OJ) InstallArea artifact exceeding a size limit that is unclear how to increase. 

As the OJ build InstallArea includes libraries with Debug symbols its large, more than 300MB.

To get pipeline checks to succeed the MR !962 (which was merged this afternoon)
avoids the need for the large artifact by doing the OJ initialization
within the build job instead of in a separate test job.

In order to avoid the pipeline fails from the large OJ artifacft I suggest you rebase in 
order to pull in my changes which have been merged into main.





