# miniRT
This project is an introduction to the beautiful world of Raytracing. 

Once completed you will be able to render simple Computer-Generated-Images and you will never be afraid of implementing mathematical formulas again.

***Important topics to know***:

- Basics of 3D geometry and coordinate systems.
- Matrices and matrix transformations (translations, rotations, scaling).
- Vectors and Vector Arithmetic
  - http://spiff.rit.edu/classes/phys311.old/lectures/vector/vector.html
  - https://tutorial.math.lamar.edu/classes/calcii/vectorarithmetic.aspx 
- Intersection algorithms for common geometric primitives like triangles, spheres, and planes.
- Understanding the principles of light reflection, refraction, and absorption.



***Sources***:
- https://en.wikipedia.org/wiki/Ray_tracing_%28graphics%29
- https://www.youtube.com/watch?v=lFnWy0Odsh8

# 3D Rendering

When it comes to rendering 3-dimensional computer-generated images there are 2 possible approaches: 

- ***Rasterization*** - which is used by almost all graphic engines because of its efficiency.
- ***Ray Tracing***

The ***Ray Tracing*** method, developed for the first time in 1968 (but improved upon since) is even today more expensive in computation than the ***Rasterization*** method.

As a result, it is not yet fully adapted to real time use-cases but it produce a much higher degree of visual realism.

![image](https://github.com/izzypt/miniRT/assets/73948790/8ed19e66-40b5-4356-9f67-d39e60655934) ![image](https://github.com/izzypt/miniRT/assets/73948790/77aee78c-ecaf-4238-9dae-c91bba650d19)

# Ray Tracing - What is it and how it works ? (Abstract)

Ray tracing is a computer graphics rendering technique used to create highly realistic images by simulating the way light interacts with objects in a scene. 

It's named after the concept of tracing the path of rays of light as they travel through a virtual 3D environment. 

### Light Simulation

 - In ray tracing, the process begins by casting rays of light from a virtual camera into the scene.
 - Each ray represents a path that light can take.

### Intersection Testing
  -  As these rays travel through the scene, they can intersect with various objects such as polygons, spheres, or any other 3D shapes.
  -  The key task is to determine where these rays intersect with the objects.
    
### Material Interaction
  - When a ray hits an object's surface, the renderer calculates how light interacts with the material properties of that surface.
  - This involves considering factors like reflection, refraction, absorption, and diffuse scattering.

### Shadows and Lighting
  - Ray tracing also handles the computation of shadows by tracing rays from the point of intersection towards light sources.
  - This helps determine whether a point in the scene is in shadow or illuminated, contributing to realistic lighting effects.
### Global Illumination 
  - One of the strengths of ray tracing is its ability to simulate global illumination, which includes effects like soft shadows, indirect lighting (ambient occlusion), and caustics.
  - This makes scenes appear more natural and visually appealing.

![image](https://github.com/izzypt/miniRT/assets/73948790/be2110b7-6191-4b77-9a63-f5468395000a)

# Ray Tracing Algorithm

The ray-tracing algorithm builds an image by extending rays into a scene and bouncing them off surfaces and towards sources of light to approximate the color value of pixels.

![image](https://github.com/izzypt/miniRT/assets/73948790/dffdb27f-9ef8-42f2-878d-b8aca84e2c5c)

Typically, each ray must be tested for intersection with some subset of all the objects in the scene.

![image](https://github.com/izzypt/miniRT/assets/73948790/07a9f03a-1009-456b-bd8f-b5511a9d3e5c)

Once the nearest object has been identified, the algorithm will estimate the incoming light at the point of intersection, examine the material properties of the object, and combine this information to calculate the final color of the pixel.
