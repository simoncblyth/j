surface_convert_from_gdml_export_diff
=======================================

Surfaces from live conversion very different in number and 
ordering than those from geocache-convert from the exported GDML. 


::

    CDTyvekSurface                                     15 
    VETOTyvekSurface                                   ## missing from GDML convert
 
    PMT_20inch_photocathode_logsurf1                   ## missing from GDML convert
    PMT_20inch_photocathode_logsurf2                   ## missing from GDML convert  
    PMT_20inch_mirror_logsurf1                         ## missing from GDML convert
    PMT_20inch_mirror_logsurf2                         ## missing from GDML convert 

    HamamatsuR12860_PMT_20inch_photocathode_logsurf1   ## missing from GDML convert
    HamamatsuR12860_PMT_20inch_photocathode_logsurf2   ## missing from GDML convert
    HamamatsuR12860_PMT_20inch_mirror_logsurf1         ## missing from GDML convert
    HamamatsuR12860_PMT_20inch_mirror_logsurf2         ## missing from GDML convert

    NNVTMCPPMT_PMT_20inch_photocathode_logsurf1        ## missing from GDML convert
    NNVTMCPPMT_PMT_20inch_photocathode_logsurf2        ## missing from GDML convert
    NNVTMCPPMT_PMT_20inch_mirror_logsurf1              ## missing from GDML convert
    NNVTMCPPMT_PMT_20inch_mirror_logsurf2              ## missing from GDML convert

    PMT_20inch_veto_photocathode_logsurf1              12*
    PMT_20inch_veto_photocathode_logsurf2              14*
    PMT_20inch_veto_mirror_logsurf1                    13*
    PMT_20inch_veto_mirror_logsurf2                    ## missing from GDML export

    NNVTMCPPMT_photocathode_logsurf1                   2*
    NNVTMCPPMT_photocathode_logsurf2                   4*
    NNVTMCPPMT_mirror_logsurf1                         3*
    NNVTMCPPMT_mirror_logsurf2                         ## missing from GDML export 

    HamamatsuR12860_photocathode_logsurf1              5*
    HamamatsuR12860_photocathode_logsurf2              7*
    HamamatsuR12860_mirror_logsurf1                    6*
    HamamatsuR12860_mirror_logsurf2                    ## missing from GDML export

    PMT_3inch_photocathode_logsurf1                    8* 
    PMT_3inch_photocathode_logsurf2                   10*
    PMT_3inch_absorb_logsurf1                          9*
    PMT_3inch_absorb_logsurf2                          ## missing from GDML export
    PMT_3inch_absorb_logsurf3                         11*
    PMT_3inch_absorb_logsurf4                         ## missing from GDML export
    PMT_3inch_absorb_logsurf5                         ## missing from GDML export   
    PMT_3inch_absorb_logsurf6                         ## missing from GDML export
    PMT_3inch_absorb_logsurf7                         ## missing from GDML export
    PMT_3inch_absorb_logsurf8                         ## missing from GDML export

    UpperChimneyTyvekSurface                          1*
    Steel_surface                                     16*

    Implicit_RINDEX_NoRINDEX_pExpHall_pTopRock
    Implicit_RINDEX_NoRINDEX_pInnerWater_pCentralDetector

    perfectDetectSurface
    perfectAbsorbSurface
    perfectSpecularSurface
    perfectDiffuseSurface



From GDML::

    UpperChimneyTyvekSurface                      1

    NNVTMCPPMT_photocathode_logsurf1              2 
    NNVTMCPPMT_mirror_logsurf1                    3
    NNVTMCPPMT_photocathode_logsurf2              4 

    HamamatsuR12860_photocathode_logsurf1         5
    HamamatsuR12860_mirror_logsurf1               6
    HamamatsuR12860_photocathode_logsurf2         7

    PMT_3inch_photocathode_logsurf1               8
    PMT_3inch_absorb_logsurf1                     9
    PMT_3inch_photocathode_logsurf2              10
    PMT_3inch_absorb_logsurf3                    11

    PMT_20inch_veto_photocathode_logsurf1        12
    PMT_20inch_veto_mirror_logsurf1              13
    PMT_20inch_veto_photocathode_logsurf2        14

    CDTyvekSurface                               15
    Steel_surface                                16 
 
    Implicit_RINDEX_NoRINDEX_pExpHall0x32b9fa0_pTopRock                 ## different name 
    Implicit_RINDEX_NoRINDEX_pOuterWaterPool0x3356e90_pPoolLining       ## missing from direct export
    Implicit_RINDEX_NoRINDEX_pInnerWater0x3358a70_pCentralDetector      ## different name 

    perfectDetectSurface
    perfectAbsorbSurface
    perfectSpecularSurface
    perfectDiffuseSurface

