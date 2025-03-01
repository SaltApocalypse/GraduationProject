from conan import ConanFile
from conan.tools.cmake import cmake_layout


class GraduationProjectRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("spdlog/1.15.1")

    def layout(self):
        cmake_layout(self)