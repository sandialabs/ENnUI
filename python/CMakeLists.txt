
# Try to import all Python components potentially needed by nanobind
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module
OPTIONAL_COMPONENTS Development.SABIModule)

# Import nanobind
find_package(nanobind CONFIG REQUIRED)

# Import Eigen3
find_package(Eigen3 CONFIG REQUIRED)

# We are now ready to compile the actual extension module
nanobind_add_module(
  # Name of the extension
  pyennui

  # Target the stable ABI for Python 3.12+, which reduces
  # the number of binary wheels that must be built. This
  # does nothing on older Python versions
  STABLE_ABI

  # Build libnanobind statically and merge it into the
  # extension (which itself remains a shared library)
  #
  # If your project builds multiple extensions, you can
  # replace this flag by NB_SHARED to conserve space by
  # reusing a shared libnanobind across libraries
  NB_STATIC

  # Link time optimization
  LTO
  NOMINSIZE

  # Source code goes here
  pyennui.cpp
)

# Link Eigen
target_link_libraries(pyennui PUBLIC
Eigen3::Eigen
${CMAKE_PROJECT_NAME}::types
${CMAKE_PROJECT_NAME}::math
${CMAKE_PROJECT_NAME}::mechanization
${CMAKE_PROJECT_NAME}::geodetic)

# Install directive for scikit-build-core
install(TARGETS pyennui LIBRARY DESTINATION .)
