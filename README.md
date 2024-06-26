# Simulacra

A in-house rendering engine for the implementation of rendering algorithms specified in the PBR book.

Personally used for game development, visualizing data, and algorithms.

![Demo](Sandbox/assets/images/demo-1.jpg)

# Installation

## Prerequisites
* **[Conan](https://conan.io/downloads)**
* **[CMake](https://cmake.org/download/)**


## Conan 2.0
```console
conan install . --output-folder=build --settings=build_type=Debug --build=missing
```

## Prior to Conan 2.0
<debug_profile> is the conan profile set to debug mode

```console
mkdir build
cd build
conan install .. --ouptput-folder=build --profile=<debug_profile> --build=missing
```


### Roadmap
- [ ] Multi-threading
- [ ] Networking
- [ ] Profiler & Built-in Debugger 
- [ ] Physics Engine

# References

* [Physically Based Rendering: From Theory to Implentation](https://www.pbr-book.org/)
