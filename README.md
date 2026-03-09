# COMP3015 - Coursework 1 - OpenGL Shader Prototype

## Development Environment
- Visual Studio Version 2022
- Operating System: Windows 64-bit
- OpenGL Version 4.6

## How the Prototype Works

This prototype demonstrates a custom Blinn–Phong shading model implemented in GLSL, applied to two textured 3D models inside a fog‑based environment.
The scene includes a cube‑mapped skybox, distance fog, rim lighting, and a rotating camera.
Fog can be toggled on/off using the F key, and camera rotation can be toggled on/off with the space bar.

The camera loads in to a foggy plain, only to see 5 zombies up ahead. When the camera turns to show your possible escape route, something is blocking the way!

The scene is rendered using two shader programs:
- "basic_uniform" - used for all 3D models
- "skybox" - used for the skybox
  
Lighting is implemented using a single Blinn–Phong light with ambient, diffuse, and specular components. 
Rim lighting is added to emphasise silhouettes and further emphasise the moody atmosphere.

Fog blends object colour with a fog colour based on distance from the camera. The fog can be toggled on/off using the F key.

## Code Structure

scenebasic_uniform.cpp is where the main scene logic is and includes rendering of the objects and textures, camera movement, fog toggle, and model transforms.

basic_uniform.vert / basic_uniform.frag are the vertex and fragment shaders for all 3D models. They also contains Blinn–Phong shading, rim lighting, and fog for the models.

skybox.vert / skybox.frag are the vertex and fragment shaders for the cube mapped skybox and also contain the general scene fog.

All other .cpp and .h files are helper files, with the only changes being made in scene.h and scenerunner.h for the logic on key presses.


## AI Usage

This was the Assisted Work Sections that my AI usage fell under:

A8 - I was having problems understanding an error with a variable not being recognised. It helped me understand why I was getting the error and where I needed to move the variable to. 
The prompt and response can be seen here: https://copilot.microsoft.com/shares/WLerBNcmcbx7syVhCBB8f
