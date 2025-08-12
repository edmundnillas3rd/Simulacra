import os

from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy

class SimulacraDepsRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    project_engine_name = "Simulacra"
    project_vendor_dir = "vendor"

    def requirements(self):
        self.requires("sdl/2.24.0")
        self.requires("spdlog/1.12.0")
        self.requires("glm/cci.20230113")
        self.requires("imgui/1.90.5-docking")

    def generate(self):
        copy(self, "*sdl*", os.path.join(self.dependencies["imgui"].package_folder, "res", "bindings"), os.path.join(self.source_folder, self.project_engine_name, self.project_vendor_dir, "imgui_bindings"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder, "res", "bindings"), os.path.join(self.source_folder, self.project_engine_name, self.project_vendor_dir, "imgui_bindings"))
        copy(self, "*imgui_demo.cpp*", os.path.join(self.dependencies["imgui"].package_folder, "res", "src"), os.path.join(self.source_folder, self.project_engine_name, self.project_vendor_dir, "imgui_bindings"))

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