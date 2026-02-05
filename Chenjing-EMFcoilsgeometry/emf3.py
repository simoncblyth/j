#!/usr/bin/env python
"""
emf3.py
==========

Prepare moi specification strings using constants pulled from WaterPoolConstructionEMF
that define slanted global frames suitable for simtracing the slanted EMF rings
in order to look for overlaps in a more systematic way.

::

    ELV=^s_EMF EYE=0,0,-2 UP=0,1,0 MOI=AXIS:56,-54,-21271,3843 cxr_min.sh


    // EMF_ZC_32 / EMF_RC_32:
    //   32 tilted rings (holders) defined in cylindrical coordinates around
    //   the tilted axis a (θ = 56°, φ = −54°).
    //   - Zc : coordinate along axis a, measured from the world origin (m).
    //   - Rc : radial distance from axis a to the “neutral layer” of the ring (m).
    const double WaterPoolConstructionEMF::EMF_ZC_32[WaterPoolConstructionEMF::kHolderRingCount] = {
        21.271,  20.602,  19.554,  18.555,
        17.077,  15.600,  14.122,  12.644,
        11.166,   9.685,   8.207,   6.729,
         5.251,   3.773,   2.295,   0.817,
        -0.821,  -2.299,  -3.777,  -5.255,
        -6.733,  -8.210,  -9.688, -11.166,
       -12.644, -14.122, -15.600, -17.077,
       -18.555, -19.554, -20.602, -21.271
    };

    const double WaterPoolConstructionEMF::EMF_RC_32[WaterPoolConstructionEMF::kHolderRingCount] = {
        3.843,   6.509,   9.185,  11.053,
       13.210,  14.924,  16.325,  17.495,
       18.465,  19.282,  19.951,  20.502,
       20.930,  21.240,  21.450,  21.559,
       21.559,  21.450,  21.240,  20.930,
       20.502,  19.951,  19.282,  18.465,
       17.495,  16.325,  14.924,  13.210,
       11.053,   9.185,   6.509,   3.843
    };




void WaterPoolConstructionEMF::makeEMFCoilHolders_Polycone()
{
    if (!m_logicWaterPool) {
        LogError << "[EMF] m_logicWaterPool is null." << std::endl;
        assert(0);
    }

    const double L_leg_mm  = 56.0;
    const double t_mm      = 4.0;
    const double eps_r_mm  = 2.0;
    const double alpha_vis = 0.35;

    LogInfo << "[EMF][Optical] makeEMFCoilHolders_Polycone() property m_emfSteelReflectivity="
            << m_emfSteelReflectivity << std::endl;

    SetEMFSteelReflectivity(m_emfSteelReflectivity);

    // Offset from "web-bottom" to geometric center along the tilted axis.
    // (L/2 - t) = 28 - 4 = 24 mm
    const double holder_center_offset_m = (L_leg_mm*0.5 - t_mm) * 1e-3;




"""

import numpy as np

zc = np.fromstring("""
        21.271,  20.602,  19.554,  18.555,
        17.077,  15.600,  14.122,  12.644,
        11.166,   9.685,   8.207,   6.729,
         5.251,   3.773,   2.295,   0.817,
        -0.821,  -2.299,  -3.777,  -5.255,
        -6.733,  -8.210,  -9.688, -11.166,
       -12.644, -14.122, -15.600, -17.077,
       -18.555, -19.554, -20.602, -21.271
        """, sep="," ) 


rc = np.fromstring("""
        3.843,   6.509,   9.185,  11.053,
       13.210,  14.924,  16.325,  17.495,
       18.465,  19.282,  19.951,  20.502,
       20.930,  21.240,  21.450,  21.559,
       21.559,  21.450,  21.240,  20.930,
       20.502,  19.951,  19.282,  18.465,
       17.495,  16.325,  14.924,  13.210,
       11.053,   9.185,   6.509,   3.843
       """, sep="," )


L_leg_mm  = 56.0;
t_mm      = 4.0;

# Offset from "web-bottom" to geometric center along the tilted axis.
# (L/2 - t) = 28 - 4 = 24 mm

holder_center_offset_mm = L_leg_mm*0.5 - t_mm 



for i in range(32):
    moi = f"#moi=AXIS:56,-54,{zc[i]*1000},{rc[i]*1000},{holder_center_offset_mm} # {i}"
    print(moi)
pass



