stack_candidates for OpticksServer
===================================

uvicorn
   ASGI web server https://www.uvicorn.org/
  
   * https://www.uvicorn.org/deployment/#supervisor
   * https://uvloop.readthedocs.io/ uvloop : replace asyncio event loop

FastAPI
   ASGI web framework


pybind11
    https://pybind11.readthedocs.io/en/stable/index.html

    Lite alt to Boost.Python

    Actually the API I need to expose is very simple, could 
    wrap the Opticks C++ API with  C-API to allow direct 
    integration with CPython.



streamlit : HTML rendering

    * https://streamlit.io/
 

torch
   https://docs.pytorch.org/docs/stable/generated/torch.nn.parallel.DistributedDataParallel.html

   https://docs.pytorch.org/docs/stable/generated/torch.nn.DataParallel.html


