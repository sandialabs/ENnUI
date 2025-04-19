from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps


class EnnuiRecipe(ConanFile):
    name = "ennui"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "with_tests": [True, False],
        "with_python": [True, False],
        "with_matlab": [True, False],
    }
    default_options = {"with_tests": True, "with_python": False, "with_matlab": False}

    def requirements(self):
        self.requires("eigen/3.4.0")
        self.requires("catch2/[>=3.4.0]")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.20]")

    def generate(self):
        tc = CMakeToolchain(self)
        if "with_tests" in self.options:
            tc.variables["BUILD_TESTS"] = self.options.with_tests
        if "with_python" in self.options:
            tc.variables["PYTHON_MODULE"] = self.options.with_python
        if "with_matlab" in self.options:
            tc.variables["MATLAB_DLL"] = self.options.with_matlab
        tc.generate()
        cmake = CMakeDeps(self)
        cmake.generate()

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.install()
