set(TARGET test_geodetic)

add_library(${TARGET} OBJECT test_geodetic.cpp)
add_library(${CMAKE_PROJECT_NAME}::${TARGET} ALIAS ${TARGET})

target_link_libraries(${TARGET}
  PRIVATE
    ${CMAKE_PROJECT_NAME}::test_common
    ${CMAKE_PROJECT_NAME}::geodetic
)
