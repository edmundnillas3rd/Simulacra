import os

from conan import ConanFile # type: ignore
from conan.errors import ConanInvalidConfiguration # type: ignore
from conan.tools.cmake import cmake_layout # type: ignore

class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("sdl/2.24.0")
        self.requires("spdlog/1.12.0")
        self.requires("glm/cci.20230113")

    def configure(self):
        self.options["glad"].gl_profile = "core"
        self.options["glad"].gl_version = "4.6"

    def build_requirements(self):
        if self.settings.os != "Windows":
            self.tool_requires("cmake/3.26")

    def layout(self):
        cmake_layout(self)

    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.settings.os} is not supported")