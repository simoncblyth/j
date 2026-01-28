vr/nvidia_cloudxr_server_client.rst
======================================

Refs
-----

* https://developer.nvidia.com/cloudxr-sdk

* https://github.com/picoxr/OpenXR_CloudXR_Client_Demo

* https://developer.picoxr.com/resources/#sdk


Q
--

My Opticks JUNO detector geometry rendering uses NVIDIA OptiX ray tracing with
most of the geometry using custom analytic solids with no triangle
approximation. Opticks aims to reproduce Geant4 optical simulation results so
avoiding triangle approximation is important. I expect Omniverse is triangle
based without flexibility to use custom NVIDIA OptiX analytic geometry ?


Gemini
-------

Your intuition is correct: **NVIDIA Omniverse is fundamentally built on a
USD-centric pipeline** that prioritizes industry-standard geometric primitives
(triangles, curves, and points). It does not currently allow you to "inject"
custom OptiX intersection shaders for analytic solids into its standard RTX
Renderers.

If you tried to bring JUNO's analytic geometry into Omniverse, the standard
workflow would force you to tessellate those solids into triangles, which
defeats your goal of replicating Geant4 results without approximation errors.

However, since you are working with an **RTX 6000 Blackwell** in a data center,
you have a much more powerful "Scientific Visualization" path that avoids these
limitations.


## 1. The Conflict: Omniverse vs. Opticks

* **Omniverse RTX Renderer:** This is a closed-loop path tracer optimized for
  MDL materials and USD geometry. While it uses OptiX under the hood, the
  **intersection programs are fixed** to handle triangles, spheres, and cylinders
  as defined by the USD schema.

* **Opticks (JUNO):** You are using "User-Defined Primitives" in OptiX. This
  requires a custom **Intersection Program** and **Bounding Box Program** (in
  OptiX 7+) to mathematically define the JUNO PMTs and other detector volumes.

## 2. The Solution: "Headless" Opticks + CloudXR

Since you cannot easily port your analytic OptiX code *into* Omniverse, you
should instead bring the **network streaming capability** to your Opticks
application.

### A. The "Vulkan Interop" Strategy

If your Opticks implementation has a GUI (likely using GLFW or similar for the
OpenGL/Vulkan viewport), you can stream that specific application window over
the network without using Omniverse at all.

* **For Desktop (Debugging):** Use **NVIDIA Frame SDK** or **NiceDCV**. These
  will capture the buffer directly from the Blackwell GPU and send it to your
  workstation.

* **For VR (Usage):** You can use **NVIDIA CloudXR** as a standalone SDK. You
  wrap your Opticks "Render Loop" in the CloudXR Server API. It will take your
  analytic OptiX frames and stream them to your HMD.

### B. The "Omniverse Scientific" Path (NVIDIA IndeX)

There is one exception within Omniverse called **NVIDIA IndeX**. It is a
plug-in designed specifically for massive scientific datasets (like JUNO).

* It allows for **Volumetric** and **non-standard** geometry visualization.
* **Note:** This still requires converting your Opticks logic into an
  IndeX-compatible format, which may be more work than simply streaming your
  existing C++/OptiX app.


## 3. Recommended Architecture for JUNO

Given the Blackwell's power, I recommend a **Hybrid Streaming Approach**:

1. **Keep Opticks Native:** Do not port to USD/Omniverse. Maintain your custom
   OptiX analytic intersection programs to ensure 100% parity with Geant4.

2. **Server-Side Rendering:** Run the Opticks binary on the Blackwell server.

3. **The Bridge:** Install **HP Anyware (Teradici)** on the server. It has a
   "High Performance" mode that detects 3D hardware-accelerated windows and treats
   them with priority.

4. **The VR Path:** Use the **CloudXR Server SDK** sample code to wrap your
   Opticks viewport. This allows you to walk through the JUNO detector while the
   Blackwell GPU calculates the analytic ray-surface intersections in real-time.

### A Quick Reality Check on Blackwell

The Blackwell architecture features **4th Generation RT Cores**. These cores
have hardware-level acceleration for **Displaced Micro-Meshes** and **Opacity
Micromaps**. While these are "triangle-adjacent," they are designed to handle
extreme complexity. However, for a physics-pure simulation like JUNO, sticking
to your custom OptiX analytic shaders is the only way to maintain the
scientific integrity of the optical photon propagation.

**Would you like me to look up the latest NVIDIA CloudXR 4.0 integration guide to see how to "wrap" a custom C++/OptiX application for VR streaming?**

The following video showcases the latest advancements in NVIDIA's ray tracing
technology and how it's being applied to complex visualization tasks.  [NVIDIA
OptiX Ray Tracing Performance and
Features](https://www.youtube.com/watch?v=LaUNeP_wV18)



Streaming Remote Rendering
---------------------------

Crucial Note for Blackwell: One reason to look at Sunshine/Moonlight or the
latest HP Anyware updates is that they support AV1 Encoding. Your Blackwell GPU
is one of the few that can encode 4K 3D streams in AV1, which offers
significantly better image quality at the same bandwidth compared to the older
H.264/H.265 used by standard DCV.


* https://moonlight-stream.org/
* https://github.com/LizardByte/Sunshine
* https://www.reddit.com/r/MoonlightStreaming/comments/1fo1mvn/moonlight_sunshine_is_av1_better/
* https://netflixtechblog.com/av1-now-powering-30-of-netflix-streaming-02f592242d80

* https://en.wikipedia.org/wiki/AV2



