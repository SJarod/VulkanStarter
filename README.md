# **Introduction to Vulkan**
##### Jarod Sengkeo

# Description
This project is made to discover how Vulkan works using modern OpenGL in a Vulkan way.
 
# Features
- demo_renderer_basic
- demo_renderer_onevao
    - drawing every meshes using a single VAO
- demo_renderer_modelvao
    - attempt to use the multidraw function to draw every meshes using one draw call
    - based on [wip.md](wip.md), every model matrices are passed to the shader once
- demo_renderer_multidraw
    - copy of demo_renderer_onevao
    - meant to draw every meshes using one draw call

# Work in progress and future features
WIP
---
- drawing every meshes with multidraw function
    - demo_renderer_multidraw is a copy of demo_renderer_onevao
        - no changes have been made yet
    - demo_renderer_modelvao was at first supposed to be the multidraw demo
        - passing every model matrices as vertex attributes is useless since attributes are updated at each vertex or instance, we are not using instanced draw

# Problems/Bugs
- some memory leaks due to the materials

# References
OpengGL :
---
- The Khronos Group : https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/
- LearnOpenGL : https://learnopengl.com

C++ :
---
- C++ references: https://en.cppreference.com/