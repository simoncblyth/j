~/j/zepeng_apptainer/index.rst
================================

Yes, I’m using an Aptainer container to set up the environment for Opticks. I
attached two definition files below. 

I tried to install most of the software in apptainer_cuda_opticks_large.def,
including ROOT, Geant4, CLHEP, and their dependencies, so the resulting image
is very large. However, I could not get Optix installed since there isn’t a way
to download the installation file with wget. But you can download the file and
attach to the definition. 

The other definition file does not include ROOT, Geant4, or CLHEP. I bind a
local directory into the container and install them in the local directory.


