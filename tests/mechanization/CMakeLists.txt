set(TARGET test_mechanization)

add_library(${TARGET} OBJECT test_ecef.cpp)
add_library(${CMAKE_PROJECT_NAME}::${TARGET} ALIAS ${TARGET})

target_link_libraries(${TARGET}
  PRIVATE
    ${CMAKE_PROJECT_NAME}::test_common
    ${CMAKE_PROJECT_NAME}::mechanization
    ${CMAKE_PROJECT_NAME}::geodetic
)
