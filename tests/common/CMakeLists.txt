set(TARGET test_common)

# Static required for extern struct
add_library(${TARGET} STATIC landmarks.cpp)
add_library(${CMAKE_PROJECT_NAME}::${TARGET} ALIAS ${TARGET})

target_include_directories(${TARGET} INTERFACE .)

target_link_libraries (${TARGET} PUBLIC ${CMAKE_PROJECT_NAME}::types
     Catch2::Catch2
     )
