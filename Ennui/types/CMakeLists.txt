# Units library
set(TARGET types)

# This library
add_library(${TARGET} INTERFACE)
add_library(${CMAKE_PROJECT_NAME}::${TARGET} ALIAS ${TARGET})

# Ensure access to headers
target_include_directories(${TARGET} INTERFACE .)

# Dependencies
target_link_libraries (${TARGET} INTERFACE Eigen3::Eigen)
