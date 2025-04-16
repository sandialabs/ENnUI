project(test)

add_subdirectory(common)
add_subdirectory(math)
add_subdirectory(geodetic)
add_subdirectory(mechanization)

# Add executable
SET( APP_EXE ${CMAKE_PROJECT_NAME}_${PROJECT_NAME} )
ADD_EXECUTABLE( ${APP_EXE} test_main.cpp )

# Link dependencies
target_link_libraries(${APP_EXE}
  PRIVATE
    Catch2::Catch2WithMain
    ${CMAKE_PROJECT_NAME}::test_mechanization
    ${CMAKE_PROJECT_NAME}::test_geodetic
    ${CMAKE_PROJECT_NAME}::test_math)

include(CTest)
include(Catch)
