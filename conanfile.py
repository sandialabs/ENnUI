from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.cmake import CMakeToolchain


class EnnuiRecipe(ConanFile):
    name = "ennui"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("eigen/3.4.0")
        self.requires("catch2/3.4.0")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.20]")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def layout(self):
        cmake_layout(self)
