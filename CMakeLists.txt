cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Ennui
        LANGUAGES CXX C
        VERSION "0.0.1")

message("================================================================================")
message("${CMAKE_PROJECT_NAME} v${CMAKE_PROJECT_VERSION}, macro definitions:")
message("================================================================================")

# Default to build tests, unless building a binding
if (NOT DEFINED BUILD_TESTS)
        if ((DEFINED PYTHON_MODULE AND PYTHON_MODULE ) OR (DEFINED MATLAB_DLL AND MATLAB_DLL))
                set(BUILD_TESTS false)
        else()
                set(BUILD_TESTS true)
        endif()
endif()

# Cannot generate both python and matlab bindings at same time because python defaults to row-major storage
# Set matrix storage here
if(DEFINED PYTHON_MODULE AND PYTHON_MODULE)
if(DEFINED MATLAB_DLL AND MATLAB_DLL)
   message( FATAL_ERROR "Cannot build both python and MATLAB libraries as the languages utilize ROW_MAJOR and COLUMN_MAJOR layouts, respectively. Please build bindings separately.")
endif()
add_definitions(-DENNUI_MATRIX_ROW_MAJOR)
endif()

if(MSVC)
        message("   ...MSVC selected. MSVC-specific macros...")

        if (DEFINED PYTHON_MODULE AND PYTHON_MODULE)
                # Building python binding
                set(DEFAULT_PROJECT_NAME pyennui)
        elseif (DEFINED MATLAB_DLL AND MATLAB_DLL)
                # Building matlab binding
                set(DEFAULT_PROJECT_NAME ${CMAKE_PROJECT_NAME}::mennui)
        else()
                # Otherwise, build test by default
                set(DEFAULT_PROJECT_NAME ${CMAKE_PROJECT_NAME}_test)
        endif()

        # Startup project will be set later, here we just establish project name
        if(NOT DEFINED VS_STARTUP_PROJECT)
        set(
        VS_STARTUP_PROJECT
        ${DEFAULT_PROJECT_NAME}
        )
        endif()
        message("   VS_STARTUP_PROJECT=${VS_STARTUP_PROJECT}")
endif()

message("================================================================================")

option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)" ON)

SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")

if(UNIX)
  include(GNUInstallDirs)
else()
  if (WIN32)
    set(CMAKE_INSTALL_LIBDIR "lib")
    set(CMAKE_INSTALL_DATADIR "share")
    set(CMAKE_INSTALL_INCLUDEDIR "include")
    set(CMAKE_INSTALL_BINDIR "bin")
    message(STATUS "Setting installation destination on Windows to: ${CMAKE_INSTALL_PREFIX}")
  else()
    message(FATAL_ERROR "System not UNIX nor WIN32 - not implemented yet")
  endif()
endif()

find_package(Eigen3 REQUIRED)

# Assume main source code in subfolder with project name
add_subdirectory(${CMAKE_PROJECT_NAME})

################################
# Make python binding
################################
if(DEFINED PYTHON_MODULE AND PYTHON_MODULE)
        message("Generating python module.")
        add_subdirectory(python)
else()
        message("Excluding python module.")
endif()

################################
# Make MATLAB binding
################################
if(DEFINED MATLAB_DLL AND MATLAB_DLL)
        message("Generating MATLAB dll.")
        add_subdirectory(matlab)
else()
        message("Excluding matlab dll.")
endif()

################################
# Make the tests project
################################
if (DEFINED BUILD_TESTS AND BUILD_TESTS)
    if (NOT DEFINED Eigen3_FOUND)
        find_package(Eigen3 REQUIRED)
    endif()
    if (NOT DEFINED Catch2_FOUND)
        find_package(Catch2 REQUIRED)
    endif()
    add_subdirectory(tests)
endif()

IF(MSVC)
    # Set Startup project -
    #
    # Note, modifying the startup project will have no affect if the user has the solution open in Visual Studio.
    #
    # Details: here we ensure CMake will list selected project first in the resulting *.sln. In turn, Visual Studio will identify the first project in the *.sln file as the Startup Project the *first* time the solution is loaded. However, as soon as the user opens the solution file, Visual Studio will create a separate user file (*.suo) retaining the user-selected Startup Project. Any subsequent reordering of projects in the *.sln file (e.g. re-running CMAKE) will not affect *.suo or the Startup Project unless the *.suo file is deleted.

    # Delecting the cashe only works if user does not currently have project open in visual studio.
    file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/.vs/)

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${VS_STARTUP_PROJECT})

ENDIF(MSVC)
