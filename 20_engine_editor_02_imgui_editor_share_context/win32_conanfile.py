import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy


class LearningComputationGeometry(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("glfw/3.4")
        self.requires("glad/0.1.36")
        self.requires("glm/cci.20230113")
        self.requires("stb/cci.20230920")
        self.requires("rapidxml/1.13")
        self.requires("rttr/0.9.6")
        self.requires("freetype/2.13.2")
        self.requires("spdlog/1.14.1")
        self.requires("easy_profiler/2.1.0")
        self.requires("sol2/3.3.1")
        self.requires("spscqueue/1.1")
        self.requires("imgui/cci.20230105+1.89.2.docking")
    def generate(self):
        os.makedirs("./external",exist_ok=True)
        copy(self, "*glfw*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "./external/bindings"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "./external/bindings"))

    def layout(self):
        cmake_layout(self)