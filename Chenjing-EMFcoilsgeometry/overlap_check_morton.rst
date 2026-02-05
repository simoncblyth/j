overlap_check_morton
========================

I have a Geant4 detector geometry of the JUNO detector that is converted to an
NVIDIA OptiX geometry by Opticks.  I want to check for unintended overlaps
between sibling volumes in that geometry. My input for the checking is point
clouds of intersect positions and outward normals labelled with the volume
indices. I have used kdTree techniques to pairwise check overlaps between point
clouds but this approach is too expensive for the initial scanning for overlaps
between thousands of siblings.  What do you suggest for efficient scanning for
overlaps. The intersect data is available in GPU buffers or on CPU. An idea I
had is to use Morton codes to interleave the 3D coordinates of intersects into
a 1D code that is more amenable to interval checking to find overlaps. 


I have a CSGPrim struct which provides "float*  CSGPrim::AABB()" please suggest
how to do bbox overlap checks between those. There are about 4000 distinct
CSGPrim. But a subtlety is the instanced geometry (the PMTs and other very
repeated solids reuse CSGPrim with instance transforms) so the total number of
volumes is something like 400k. I could start by considering just the global
non-instanced geometry : overlaps are more common with this geometry anyhow. 




