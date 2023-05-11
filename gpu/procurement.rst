procurement
=============


Query
--------

::

    Hi Simon,

    We are now creating a list of computing resources to purchase this year, the
    computing resources will cover the need of the next 2-3 years, including CPU,
    disk, tape, servers, GPU, ...

    The Opticks is now close to production use. Could you please list a rough
    requirement on the GPU configuration for JUNO ?

    Ziyan


General Thoughts
------------------

Hi Ziyan, All, 

Thats a difficult question. Especially at the 
moment as NVIDIA has not yet fully released its
line up for the current Ada Lovelace architecture.
Currently spec tables you find on the web have lots 
of empty fields, and there are very few reviews. 
NVIDIA started its role out of Ada at 
the GTC conference in Sept 2022. 

* (2022) Ada Lovelace, 3rd Gen RT Cores
* (2020) Ampere, 2nd Gen RT Cores 
* (2018) Turing, 1st Gen RT Cores

Given GPU ray tracing progress with factors of 2x 
in raw ray tracing performance from generation to generation
going for the latest generation is best for Opticks. 
NVIDIA claim more than 2x between generations, 
however that includes AI gains eg from DLSS (Deep Learning 
Super Sampling) which are are not relevant to Opticks 
simulation performance which depends mainly on raw ray tracing. 
The latest generation is also going to be best for 
machine learning workloads too. 

For planning a purchase of multiple units I would recommend 
a cautious approach of identifying candidates to borrow 
from NVIDIA for evaluation to make sure they work with 
the server infrastructure. 

But before approaching NVIDIA for that it is necessary 
for a set of benchmark applications to be ready and optimized 
on currently available GPUs in order to test performance to assess
throughput and estimate how many units would be needed in order
to meet simulation production targets. 

Examples from the current line up of data center GPUs (passive cooled) 
with RT cores for hardware accelerated ray tracing include.

* NVIDIA Ada L40, 18176 CUDA Cores, 142 RT Cores (3rd Gen), 48 GB GDDR6 
* NVIDIA Ada L4 , 7680 CUDA Cores, 60 RT Cores (3rd Gen), 24 GB GDDR6

Previous generation of data center GPUs with RT cores:

* NVIDIA Ampere A40, 10752 CUDA Cores, 84 RT Cores (2nd Gen), 48 GB GDDR6, 300 W
* NVIDIA Ampere A10, 8192 CUDA Cores, 72 RT Cores (2nd Gen), 24 GB GDDR6, 150 W

Note that H100 and previous generation A100 do not have RT cores. 

Simon 



Find contenders
-------------------

* https://www.techpowerup.com/review/?category=Graphics+Cards&manufacturer=NVIDIA&pp=25&order=date

* https://www.servethehome.com/category/ai-deep-learning/



GPUs offered in Google Cloud Instances : Likely the most popular server GPUs 
-------------------------------------------------------------------------------

* https://cloud.google.com/compute/docs/gpus

+-------+----------+--------+----+----+------+
| GPU   | Arch     | Launch | SM | RT | VRAM |
+=======+==========+========+====+====+======+
| L4    | Ada      | 2023   |    |    |      |
+-------+----------+--------+----+----+------+
| A100  | Ampere   |        |    |    |      |
+-------+----------+--------+----+----+------+
| T4    | Turing   | 2018   | 40 | 40 | 16G  | 
+-------+----------+--------+----+----+------+
| V100  |          |        |    |    |      |
+-------+----------+--------+----+----+------+
| P100  |          |        |    |    |      |
+-------+----------+--------+----+----+------+
| P4    |          |        |    |    |      |
+-------+----------+--------+----+----+------+
| K80   |          |        |    |    |      |
+-------+----------+--------+----+----+------+


* https://www.techpowerup.com/gpu-specs/tesla-t4.c3316


RTX/RT Core Generations
-----------------------

* 1st Turing (2018)
* 2nd Ampere (2020)
* 3rd Ada    (2022)




Find some video reviews
--------------------------

* https://www.youtube.com/results?search_query=NVIDIA+T4
* https://www.youtube.com/results?search_query=NVIDIA+L4


Ampere Generation
--------------------

* https://www.youtube.com/watch?v=FGzTV4073HE

  see table at 02:30 : A100, A30, A40, A16, A10, A2

  * A100 : 0 RT cores, 250W, 40/80 GB
  * A30 : 0 RT cores, 165W, 25 GB 
  * A40 : 84 RT cores, 300W, 48 GB
  * A16 : ? RT cores, 250W, 4*16 GB
  * A10 : 72 RT cores, 150W, 24 GB 
  * A2 : 10 RT cores, 40-60W, 16 GB 

  * RTX A5000 (workstation card but with active cooling)
 




CUDA Cores per SM
--------------------

https://www.techcenturion.com/nvidia-cuda-cores/

Nvidia’s Turing architecture brought a lot of changes to the GPUs.  The number
of CUDA cores per SM was reduced to 64 (from 128). Tensor cores and Ray Tracing
cores were added.






L4 : Data Center Ada GPU with 3rd Gen RT cores
-------------------------------------------------

* MY IMPRESSION: Not the fastest, solid performance, easy to integrate, data center GPU with RT cores

* https://nvdam.widen.net/s/rvq98gbwsw/l4-datasheet-2595652
* https://www.nvidia.com/en-gb/data-center/l4/
Accelerate Video, AI, and Graphics Workloads The NVIDIA L4 Tensor Core GPU
powered by the NVIDIA Ada Lovelace architecture delivers universal,
energy-efficient acceleration for video, AI, visual computing, graphics,
virtualization, and more. Packaged in a low-profile form factor, L4 is a
cost-effective, energy-efficient solution for high throughput and low latency
in every server, from the edge to the data center to the cloud.


* https://cloud.google.com/blog/products/compute/introducing-g2-vms-with-nvidia-l4-gpus
* https://www.servethehome.com/nvidia-l4-24gb-released-upgrading-the-nvidia-t4/

NVIDIA L4 Released 4x NVIDIA T4 Performance in a Similar Form Factor

* https://www.techpowerup.com/gpu-specs/l4.c4091


L4 vs T4 : L4 is successor to T4
------------------------------------

* :google:`NVIDIA L4 compared to T4`

* https://www.nebuly.com/blog/nvidia-l4-gpu-the-energy-and-cost-efficient-successor-to-nvidia-t4




