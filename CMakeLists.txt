#
# Author: Kang Lin <kl222@126.com>
# Date  : 2021-09-30
#

cmake_minimum_required(VERSION 2.8)

project(ORZ)

option(ORZ_INSTALL "Supporting install script" ON)

# global root dir
set(SOLUTION_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# dir for common cmake files
list(APPEND CMAKE_MODULE_PATH ${SOLUTION_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${SOLUTION_DIR}/cmake)

# option for platform
set(PLATFORM "auto" CACHE STRING "auto, x86 or x64")
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Debug or Release")
set(CONFIGURATION ${CMAKE_BUILD_TYPE})

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(GenerateExportHeader)
# set common compiler flags
include(LOCAL_FLAGS)
include(LOCAL_ENV)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install CACHE STRING "set install prefix")
install(CODE "MESSAGE(\"Installing into ${CMAKE_INSTALL_PREFIX}\")")

set(LOCAL_OUTPUT_DIR ${PROJECT_BINARY_DIR})

if (LOCAL_OUTPUT_DIR)
    set(EXECUTABLE_OUTPUT_PATH ${LOCAL_OUTPUT_DIR}/${ENV_RUNTIME_DIR})
    set(LIBRARY_OUTPUT_PATH ${LOCAL_OUTPUT_DIR}/${ENV_LIBRARY_DIR})
endif ()

add_subdirectory(src)

# project files for clion
#FILE(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
FILE(GLOB_RECURSE TOOL_FILES ${PROJECT_SOURCE_DIR}/tools/*.cpp)

foreach (path ${TEST_FILES})
    string(REGEX MATCH "[^/]*.[(c)|(cc)|(cpp)]$" file_ext ${path})
    string(REGEX MATCH "^[^.]*" file ${file_ext})
    add_executable(test_${file} ${path})
    set_target_properties(test_${file} PROPERTIES OUTPUT_NAME test_${file}${ENV_SUFFIX})
    target_link_libraries(test_${file} ORZ)
    # set_target_properties(test_${file} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LOCAL_OUTPUT_DIR}/lib)
endforeach ()

foreach (path ${TOOL_FILES})
    string(REGEX MATCH "[^/]*.[(c)|(cc)|(cpp)]$" file_ext ${path})
    string(REGEX MATCH "^[^.]*" file ${file_ext})
    add_executable(tool_${file} ${path})
    set_target_properties(tool_${file} PROPERTIES OUTPUT_NAME ${file}${ENV_SUFFIX})
    target_link_libraries(tool_${file} ORZ)
    install(TARGETS tool_${file}
		RUNTIME DESTINATION ${ENV_RUNTIME_DIR}
	)
endforeach ()
