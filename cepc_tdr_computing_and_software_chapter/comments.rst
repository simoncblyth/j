comments on cepc_tdr_computing_and_software_chapter
========================================================

* https://latex.ihep.ac.cn/project/66b9ac05dace1b0099d5eaa9/invite/token/723c4430e2c7cdb413b585a3781f7f39fdf853a2dcf2c9e8


GENERAL::

   inconsistent past/present/future tense in many places, 
   makes reader unclear on what has been done and what is planned to do

   "this study" not appropriate in TDR, need to identify which study via
   references or elaboration



Track Reconstruction::

   %TODO: add references for ACTS and TRACC

Time-of-Flight in the Outer Tracker::

   %TODO : add reference for AC-LGAD technique

Analysis software::

    % TODO: suggest rename of RDFAnalysis to RDataFrameAnalysis (RDFA) 
    % to avoid acronym clash with "RDF:Resource Description Framework"
    % TODO: "and shedding the modern computing technologies"  means
    % getting rid of modern techniques ? What do you mean ? 


Simulation on Gaussino::

    As there is no detector response implemented, the Geant4 stepping verbose
    information are printed to verify whether the simulation works. Multi-threading
    is also tested with multiple cores.

    % TODO: printing verbose stepping info is not a realistic way to verify something in detail, 
    % its only the starting point of validation : REPHRASE


Fast calorimeter simulation::

    % TODO: references to GAN studies are needed


    To investigate the application of GAN to fast simulation of the CEPC ECAL with
    silicon tungsten we simulated single photons with various energies and incident
    angles. Some preliminary results are shown in Figure \ref{fig_CEPC_GAN_XYZ}. It
    shows the GAN has capability to simulate the calorimeter and give high fidelity
    simulation results.  
    % TODO: needs a reference or more details to explain the approach


    To further enhance the accuracy and speed of simulations, photon tracing using
    NVIDIA OptiX\cite{10.1145/1778765.1778803} can be employed in the digitization
    process to achieve improved energy deposition feedback.
    %TODO: elaboration needed (OptiX deals in rays not photons)


Gaseous detector simulation::

    ...combination of Geant4 and Garfield++...
    % TODO: "this study" Which study ? add reference


    % TODO: add TrackHeed reference here

    ...Normalizing flow...
    % TODO: "In this study" ? Which Study ? Add reference.



Open Data::

    % TODO: while ensuring [what?] security/safety ?

