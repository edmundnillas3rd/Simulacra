# Simulacra

An in-house rendering engine for playing around with ideas. Mostly used for game development, visualizing data, and algorithms.

![Demo](Sandbox/assets/images/demo-1.jpg)

# Installation

## Prerequisites
* **[Conan](https://conan.io/downloads)**
* **[CMake](https://cmake.org/download)**

## Required IDEs / Compilers
* **[Visual Studio Community / MSVC](https://visualstudio.microsoft.com/downloads/)**
* **[GCC](chatgpt.com/?oai-dm=1)**

## Conan 2.0
```console
# conanfile.txt
conan install . --output-folder=build --build=missing

# or

# conanfile.py
conan install . --build=missing

```

## Prior to Conan 2.0
`<debug_profile>` is the conan profile set to debug mode

```console
mkdir build
cd build
conan install .. --ouptput-folder=build --profile=<debug_profile> --build=missing
```

## Building and running the project

### Terminal / Console
```console
cmake -DCMAKE_TOOLCHAIN_FILE=<path-to-conan_toolchain.cmake> -S . -B build
cmake --build build


# Windows Example

# Values: 
# <build_config> - Debug, Release

cmake -DCMAKE_TOOLCHAIN_FILE=build/generators/conan_toolchain.cmake -S . -B build
cmake --build build
cd bin/<build_config>
Sandbox.exe # to run the program
```

### VSCode 
1. If the appropriate cmake tools didn't exist. Install the CMake and CMake Tools extension first.
2. Follow the conan installation procedure.
3. `CTRL + SHIFT + P` and search for `CMake: Configure in the command palette`
4. Then build `(F7)` or debug `(CTRL + F5)`

### Configure IntelliSense for VSCode
1. `CTRL + SHIFT + P` and search for `C/C++: Select IntelliSense Configuration`
2. Select `Use CMake Tools` to fix the path errors in the project

# References

## Graphics
* [Learn OpenGL](https://learnopengl.com)
* [OpenGL Superbible](http://www.openglsuperbible.com)
* [Anton's OpenGL 4 Tutorials](https://antongerdelan.net/opengl)
* [Physically Based Rendering: From Theory to Implentation](https://www.pbr-book.org)
* [Graphics Shaders Theory and Practice](https://cs.uns.edu.ar/cg/clasespdf/GraphicShaders.pdf)
* [Real-Time Rendering](https://www.realtimerendering.com/)

## Game/Rendering Engine Architecture
* [Beginning Game Programming v2.0](https://lazyfoo.net/tutorials/SDL)
* [The Cherno's Game Engine Series](https://youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&si=of_e13nO4Y_J9VWg)
* [Game Engine Architecture by Jason Gregory](https://www.gameenginebook.com)
* [Game Coding Complete](https://github.com/MikeMcShaffry/gamecode4)

## Articles
* [Implementing a simple event system in C++11](https://bastian.rieck.me/blog/2015/event_system_cxx11)
* [A Tiny OpenGL 2D Batch Renderer](https://jasonliang.js.org/batch-renderer.html)
* [OpenGL sprite sheet aka texture atlas](https://devcry.heiho.net/html/2017/20170930-opengl-spritesheet.html)
