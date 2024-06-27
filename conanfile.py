import os

from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import cmake_layout

class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("sdl/2.24.0")
        self.requires("spdlog/1.12.0")
        self.requires("glm/cci.20230113")
        self.requires("glad/0.1.36")
        self.requires("stb/cci.20240213")

    def configure(self):
        self.options['glad'].gl_profile = 'core'
        self.options['glad'].gl_version = '4.6'

    def build_requirements(self):
        if self.settings.os != "Windows":
            self.tool_requires("cmake/3.26")

    def layout(self):
        cmake_layout(self)

    def validate(self):
        if self.settings.os == "Macos":
            raise ConanInvalidConfiguration("MacOS is not supported")