set(TARGET test_math)

#add_library(${TARGET} INTERFACE)
add_library(${TARGET} OBJECT test_rotation.cpp test_quaternion.cpp)
add_library(${CMAKE_PROJECT_NAME}::${TARGET} ALIAS ${TARGET})

target_include_directories(${TARGET} INTERFACE .)

target_link_libraries (${TARGET}
PRIVATE
  ${CMAKE_PROJECT_NAME}::test_common
  ${CMAKE_PROJECT_NAME}::math
     )
