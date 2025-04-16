set(TARGET mennui)

set(SOURCE_FILES
	mennui.cpp
)

# Headers to be included by user-applications
set(API_HEADERS
	mennui.hpp
)

add_library(${TARGET} STATIC ${SOURCE_FILES} ${API_HEADERS})
add_library(${CMAKE_PROJECT_NAME}::${TARGET} ALIAS ${TARGET})

target_link_libraries(${TARGET}
   PRIVATE
     ${CMAKE_PROJECT_NAME}::types
     ${CMAKE_PROJECT_NAME}::math
     ${CMAKE_PROJECT_NAME}::geodetic
     ${CMAKE_PROJECT_NAME}::mechanization)

set_target_properties(${TARGET} PROPERTIES DEBUG_POSTFIX "d")


target_include_directories(${TARGET} PUBLIC
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        ./
)

# Auto-generate export header
include(GenerateExportHeader)

GENERATE_EXPORT_HEADER( ${TARGET}
             BASE_NAME ${PROJECT_NAME}
             EXPORT_MACRO_NAME ${TARGET}_EXPORT
             EXPORT_FILE_NAME ${TARGET}_Export.h
             STATIC_DEFINE ${TARGET}_BUILT_AS_STATIC
)

install (TARGETS ${TARGET} DESTINATION lib
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install (FILES ${API_HEADERS} ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_Export.h DESTINATION Include)
