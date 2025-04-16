# Units library
set(TARGET mechanization)

add_library(${TARGET} INTERFACE)
add_library(${CMAKE_PROJECT_NAME}::${TARGET} ALIAS ${TARGET})

# Ensure access to headers
target_include_directories(${TARGET} INTERFACE .)

# Dependencies
target_link_libraries(${TARGET} INTERFACE
  ${CMAKE_PROJECT_NAME}::types
  ${CMAKE_PROJECT_NAME}::math
)
