# miniRT
This project is an introduction to the beautiful world of Raytracing. 

Once completed you will be able to render simple Computer-Generated-Images and you will never be afraid of implementing mathematical formulas again.

# ***Important topics to know***

- Basics of 3D geometry and coordinate systems.
- Matrices and matrix transformations (translations, rotations, scaling).
- Vectors and Vector Arithmetic (+ Dot product, Cross Product..)
- Intersection algorithms for common geometric primitives like triangles, spheres, and planes.
- Understanding the principles of light reflection, refraction, and absorption.



***Sources***:
- https://en.wikipedia.org/wiki/Ray_tracing_%28graphics%29
- https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/how-does-it-work.html
- https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class
- https://gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html
- https://blog.devgenius.io/a-passion-for-pixels-building-a-ray-tracer-from-scratch-449651509fa0
- https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html

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

### Projecting Rays
- Ray-tracing algorithm is a recursive algorithm that consists on projecting - from the observer - a vector (ray) for each one of the pixels that make up the image.
- This vector will intersect with the object(s) that are part of the image.
### Intersecting Rays
- The intersections that each vector goes through must be confirmed by every object in the scene/image , in order to determine which object is the nearest from the observer.
- If a ray does not intersect with any object throught its path, it is given to the pixel - that the ray goes through - the background color of the scene/image.
- If a ray does intersect with some object - and after confirming that this intersection is the closest to the observer for that ray - it is necessary to determine which color we should assign to the pixel.
### Determining pixel color
- In order to to determine which color we should assign to the pixel, we must calculate the ilumination at the point of the image/scene where the ray impacts.
- This illumination might come from different sources of light and to analyze the point, the algorithm uses 3 different rays (secundary rays) :
  - Reflected rays
  - Refracted rays
  - Shadow rays


![image](https://github.com/izzypt/miniRT/assets/73948790/dffdb27f-9ef8-42f2-878d-b8aca84e2c5c)

Typically, each ray must be tested for intersection with some subset of all the objects in the scene.

![image](https://github.com/izzypt/miniRT/assets/73948790/07a9f03a-1009-456b-bd8f-b5511a9d3e5c)

Once the nearest object has been identified, the algorithm will estimate the incoming light at the point of intersection, examine the material properties of the object, and combine this information to calculate the final color of the pixel.

![image](https://github.com/izzypt/miniRT/assets/73948790/0fd5b4cd-69ec-4845-a11e-ab098dc302eb)

# Light

There are 3 main types of light we must know :

- ### Point Lights
  - Point lights emit light from a fixed point in 3D space.
  - They emit light equally in every direction; 
- ### Directional Lights
  - Like point lights, directional lights have an intensity, but unlike them, they don’t have a position;
  - instead, they have a fixed direction.
  - You can think of them as infinitely distant point lights located in the specified direction. 
- ### Ambient Light
  - light can come not only from light sources, but also from objects that get light from light sources and scatter part of it back into the scene.
  - The scattered light will in turn hit some other object, part of it will be absorbed, and part of it will be scattered back into the scene.
  - And so on, until all of the energy of the original light has been absorbed by the surfaces in the scene.  

# Reflections

- ### Diffuse Reflection
  - When a ray of light hits a matte object (smooth even surface), the ray is scattered back into the scene equally in every direction, a process called diffuse reflection;
  - this is what makes matte objects look matte. 
- ### Specular Reflection
  -  Unlike matte objects, shiny objects look slightly different depending on where you’re looking from.
  -  Unlike matte objects, the way you perceive the surface of these objects does actually depend on your point of view. 
