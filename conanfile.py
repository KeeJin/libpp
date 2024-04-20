from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class libppRecipe(ConanFile):
    name = "libpp"
    version = "0.1.0"

    # Optional metadata
    license = "MIT License"
    author = "Cheo Kee Jin <yoplocheo@gmail.com>"
    url = "https://github.com/KeeJin/libpp.git"
    description = "Generic C++ library for implementing path planning algorithms"
    topics = ("c++", "algorithms", "path-planning")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*"
    
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
            
    def requirements(self):
        self.requires("spdlog/1.13.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["libpp"]