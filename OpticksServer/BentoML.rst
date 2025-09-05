BentoML
=========

Interesting but does look to be specialized to handling models. 


Good Terse Overviews
---------------------

* https://www.gocodeo.com/post/how-bentoml-enables-scalable-model-packaging-and-serving



Refs
-----

https://pypi.org/project/bentoml/

https://github.com/bentoml/BentoML

https://docs.bentoml.com/en/latest/examples/overview.html

https://docs.bentoml.com/en/latest/get-started/packaging-for-deployment.html

https://docs.bentoml.com/en/latest/build-with-bentoml/gpu-inference.html
https://docs.bentoml.com/en/latest/build-with-bentoml/gpu-inference.html

https://docs.bentoml.com/en/latest/build-with-bentoml/parallelize-requests.html


https://github.com/bentoml/BentoDiffusion/tree/main/sd3-medium  

https://github.com/bentoml/comfy-pack


https://www.datacamp.com/tutorial/deploy-llms-with-bentoml

https://docs.zenml.io/stacks/stack-components/model-deployers/bentoml


https://docs.bentoml.com/en/latest/build-with-bentoml/services.html

https://www.bentoml.com/blog/building-rag-with-open-source-and-custom-ai-models


Scaling
--------

https://www.bentoml.com/blog/scaling-ai-model-deployment



BentoML Alt
------------

* https://northflank.com/blog/bentoml-alternatives

* https://getindata.com/blog/machine-learning-model-serving-tools-comaprison-kserve-seldon-core-bentoml/


Community
-----------

* https://medium.com/@rizqi.okta/bentoml-is-all-you-need-creating-machine-learning-service-into-deployment-with-ease-367f440f0a05


Examples
---------

* https://github.com/search?q=BentoML&type=repositories

* https://docs.bentoml.com/en/latest/examples/overview.html

* https://github.com/bentoml/gallery


* https://github.com/bentoml/OpenLLM


HMM BentoML with C++ libs ? Packaging issue ? 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* https://github.com/bentoml/BentoLlamaCpp
* https://github.com/bentoml/BentoLlamaCpp/blob/main/service.py

::

      from llama_cpp import Llama, ChatCompletionFunction




BentoClip example
~~~~~~~~~~~~~~~~~~

* https://github.com/bentoml/BentoClip
* https://github.com/bentoml/BentoClip
* https://docs.bentoml.org/en/latest/use-cases/embeddings/clip-embeddings.html


BentoBlip example
~~~~~~~~~~~~~~~~~~~~~


* https://github.com/bentoml/BentoBlip
* https://huggingface.co/Salesforce/blip-image-captioning-large
* https://arxiv.org/abs/2201.12086


* https://huggingface.co/Salesforce/blip2-opt-2.7b
* https://arxiv.org/abs/2301.12597



BentoDiffusion
~~~~~~~~~~~~~~~

* https://github.com/bentoml/BentoDiffusion
* https://github.com/bentoml/BentoDiffusion/tree/main/flux-timestep-distilled
* https://github.com/bentoml/BentoDiffusion/blob/main/flux-timestep-distilled/service.py


BentoVLLM
~~~~~~~~~~

* https://github.com/bentoml/BentoVLLM



Could BentoML be used for "preprocessing" tasks like OpticalPhotonPropagation ?
---------------------------------------------------------------------------------

* https://docs.bentoml.com/en/latest/build-with-bentoml/services.html

BentoML Services are defined using class-based definitions. Each class
represents a distinct Service that can perform certain tasks, such as
preprocessing data or making predictions with an ML model. You use the
decorator @bentoml.service to annotate a class, indicating that it is a BentoML
Service. By convention, you define a Service (or multiple Services) in a
service.py file. For more information, see Service decorator


* https://www.geeksforgeeks.org/machine-learning/bentoml-helping-deploy-ml-models/

Multi Framework Support: It supports a wide variety of machine learning and
deep learning libraries such as scikit-learn, TensorFlow, PyTorch, XGBoost,
LightGBM, Hugging Face Transformers and even custom Python models. 

BentoML with custom python model
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* https://docs.bentoml.com/en/latest/reference/bentoml/frameworks/picklable_model.html

* https://docs.bentoml.com/en/latest/get-started/model-composition.html

* https://www.reddit.com/r/MachineLearning/comments/g1cfre/p_bentoml_an_opensource_platform_for/

BentoML keeps the Python runtime in serving time, making it possible to do
pre-processing and post-processing in serving endpoints. 



https://www.reddit.com/r/mlops/comments/w4vl6r/hello_from_bentoml/

Q:

we build systems with cascades of neural nets (for example, one net for finding
the region of interest, and two other nets that perform different tasks after
that) and some CPU-heavy preprocessing and postprocessing. we want to scale
them separately, so at this point we split them into microservices that form a
DAG and communicate with each other within Kunernetes cluster. transfer of data
between services is done via Redis or Redis + saving to disk, which in some
cases can slow down the system (we were also thinking about grpc). does BentoML
support this kind of systems? 

A:

That's a good question. Let me rephrase it, so I can make sure I understand.


Your current workflow is pre-processing -> model A inferencing -> model b and
model c inferencing (in parallel) -> post-processing. Is that correct?

You guys want to have better resource utilization, one way to do it scale them
separately. By deploying them into the microservices way, you are running into
over system and latency slow down, because of the data transfer speed and
serialization and deserialization cost.

Yes, BentoML supports that. :)

With the new runner architecture from the 1.0 version. BentoML will create
multiple instances of runners based on the available system resources. This
gets around the python GIL issue.
https://docs.bentoml.org/en/latest/concepts/service.html#runners


Instead of writing different services and chaining them together, you could
write everything in one bento service

::

    import asyncio

    import bentoml
    from bentoml.io import Image, Text

    preprocess_runner = bentoml.Runner(MyPreprocessRunnable)
    model_a_runner = bentoml.xgboost.get('model_a:latest').to_runner()
    model_b_runner = bentoml.pytorch.get('model_b:latest').to_runner()
    postprocess_runner = bentoml.Runner(MyPostprocessRunnerable)

    svc = bentoml.Service('inference_graph_demo', runners=[
        preprocess_runner,
        model_a_runner,
        model_b_runner,
        model_c_runner,
       postprocess_runner
    ])

    @svc.api(input=Image(), output=Text())
    async def predict(input_image: PIL.Image.Image) -> str:
        model_input = await preprocess_runner.async_run(input_image)
        output = await model_a_runner.async_run(model_input)

        results = await asyncio.gather(
            model_b_runner.async_run(output),
            model_c_runner.async_run(output),
        )

        return postprocess_runner.run(
            results[0], # model a result
            results[1], # model b result
        )


And when you deploy this bento to Kubernetes using Yatai
(https://github.com/bentoml/yatai). Yatai will automatically deploy this as
microservices. We are working on adding better support for serialization and
deserialization support between those microservices to reduce latency costs.


* https://bentoml.com/blog/breaking-up-with-flask-amp-fastapi-why-ml-model-serving-requires-a-specialized-framework
  
* https://stackoverflow.com/questions/63169865/how-to-do-multiprocessing-in-fastapi



