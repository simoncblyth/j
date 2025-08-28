NVIDIA_Dynamo
================


Initial impression
--------------------

Dynamo is solving in some sense an inverted problem compared to
the one of sharing limited GPU resources across many CPU only nodes.
Dynamo is designed to split an LLM across multiple GPU nodes, not
simply route queries from CPU nodes to a small pool of GPU nodes.

Nevertheless there are some similarities and could inevitably learn
lots from getting Dynamo to work and studying its implementation.


Refs
-----

* https://github.com/ai-dynamo/dynamo

  implemented in Rust 

* https://www.networkworld.com/article/3849341/what-is-nvidia-dynamo-and-why-it-matters-to-enterprises.html

* https://www.theregister.com/2025/03/23/nvidia_dynamo/


::

    At its heart, the open source inference suite is designed to better optimize
    inference engines such as TensorRT LLM, SGLang, and vLLM to run across large
    quantities of GPUs as quickly and efficiently as possible.



Frameworks dynamo integrates with
-------------------------------------

* https://docs.vllm.ai/en/latest/
* https://www.digitalocean.com/community/tutorials/how-to-deploy-nvidia-dynamo-for-llm-inference

