NVIDIA_RTX/index
===================


2026 Jan
-----------

* NVIDIA RTX 5000 Ada Generation,  32GB


::

    Model                 Architecture      VRAM (ECC)       RT Cores  RT Gen      Release Date     Approx. Cost (USD)

    RTX 6000 Blackwell    Blackwell         96GB GDDR7       190       4th         June 2025        "$9,500 - $11,500"
    RTX 5000 Blackwell    Blackwell         48GB / 72GB*     110       4th         March 2025       "$4,500 - $5,500"
    RTX 5090              Blackwell         32GB GDDR7       170       4th         Jan 2025         "$1,999 - $2,500"

    RTX 5000 Ada Gen      Ada Lovelace      32GB GDDR6       100       3rd         Aug 2023         "$3,800 - $4,200"   [currently used]





    All the 2025 GPUs have "D" China variants that are compute throttled.
    It is preferable to use vendors who can source non-capped versions 
    from 3rd countries. 

    RTX 6000 Blackwell has power draw of 600W, as does the RTX 5090
    which has reputation for spiky power draw. That compares with 300W for the 5000.

    Unfortunately the Dell Precision 7960 on my desk has PSU of 1400W which
    Google Gemini suggests is not sufficient for reliable use of the 600W GPUs.
  
    So the best RTX GPU for use with my Workstation would be: "RTX 5000 Blackwell (72GB)" 

    The RTX 6000 and 5000 have server variants that can be rack mounted, however
    computing center experts with rack server provisioning expertise 
    are needed to advise on how to setup a GPU server with RTX server GPUs
    with for the 6000 high power requirements.







::

    Feature      RTX 6000 Blackwell      RTX 6000D (China)       RTX 5090              RTX 5090D (China)         L20 (Export)
    VRAM         96GB GDDR7              96GB GDDR7              32GB GDDR7            32GB GDDR7                48GB GDDR6
    RT Cores     190                     190                     170                   170                       142
    RT Gen       4th Gen                 4th Gen                 4th Gen               4th Gen                   3rd Gen
    Compute Cap  Full                    Capped (TPP)            Full                  Capped (TPP)              Restricted
    Cooling      Active or Passive       Active or Passive       Active (Triple Fan)   Active (Triple Fan)       Passive
    Target Use   High-End Compute        China Workstation       Consumer Flagship     China Consumer            Data Center Infer.




* https://www.techpowerup.com/gpu-specs/?q=RTX&f=year_2025~rt_Yes

* https://www.techpowerup.com/gpu-specs/rtx-pro-5000-72-gb-blackwell.c4357

* https://www.nvidia.com/en-us/products/workstations/professional-desktop-gpus/rtx-pro-6000-max-q/

* https://www.techpowerup.com/gpu-specs/rtx-pro-6000-blackwell-max-q.c4273



