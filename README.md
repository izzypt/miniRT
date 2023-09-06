# miniRT
This project is an introduction to the beautiful world of Raytracing. 

Once completed you will be able to render simple Computer-Generated-Images and you will never be afraid of implementing mathematical formulas again.

***Sources***:
- https://en.wikipedia.org/wiki/Ray_tracing_%28graphics%29
- https://www.youtube.com/watch?v=lFnWy0Odsh8

# 3D Rendering

When it comes to rendering 3-dimensional computer-generated images there are 2 possible approaches: 

- ***Rasterization*** - which is used by almost all graphic engines becauseof its efficiency.
- ***Ray Tracing***

The ***Ray Tracing*** method, developed for the first time in 1968 (but improved upon since) is even today more expensive in computation than the ***Rasterization*** method.

As a result, it is not yet fully adapted to real time use-cases but it produce a much higher degree of visual realism.

![image](https://github.com/izzypt/miniRT/assets/73948790/8ed19e66-40b5-4356-9f67-d39e60655934) ![image](https://github.com/izzypt/miniRT/assets/73948790/77aee78c-ecaf-4238-9dae-c91bba650d19)

# Ray Tracing Algorithm

The ray-tracing algorithm builds an image by extending rays into a scene and bouncing them off surfaces and towards sources of light to approximate the color value of pixels.

![image](https://github.com/izzypt/miniRT/assets/73948790/dffdb27f-9ef8-42f2-878d-b8aca84e2c5c)

Typically, each ray must be tested for intersection with some subset of all the objects in the scene.

![image](https://github.com/izzypt/miniRT/assets/73948790/07a9f03a-1009-456b-bd8f-b5511a9d3e5c)

Once the nearest object has been identified, the algorithm will estimate the incoming light at the point of intersection, examine the material properties of the object, and combine this information to calculate the final color of the pixel.
