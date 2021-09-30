#
# Author: Kang Lin <kl222@126.com>
# Date  : 2021-09-29
#

cmake_minimum_required(VERSION 2.8)

project(ORZ)

set(ORZ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
option(ORZ_WITH_OPENSSL "Supporting AES, RAS and SSL with OpenSSL" OFF)

set(ORZ_MODULES codec io lego mem net sync tools utils)

if (ORZ_WITH_OPENSSL)
    LIST(APPEND ORZ_MODULES ssl)
endif (ORZ_WITH_OPENSSL)

set(ORZ_INCLUDE_FILES)
set(ORZ_SRC_FILES)
set(ORZ_SRC_INCLUDE_FILES)

foreach (module ${ORZ_MODULES})
    FILE(GLOB_RECURSE ORZ_INCLUDE_${module}_FILES ${ORZ_SOURCE_DIR}/include/orz/${module}/*.h)
    LIST(APPEND ORZ_INCLUDE_FILES ${ORZ_INCLUDE_${module}_FILES})

    FILE(GLOB_RECURSE ORZ_SRC_${module}_FILES ${ORZ_SOURCE_DIR}/src/orz/${module}/*.cpp)
    LIST(APPEND ORZ_SRC_FILES ${ORZ_SRC_${module}_FILES})

    FILE(GLOB_RECURSE ORZ_SRC_INCLUDE_${module}_FILES ${ORZ_SOURCE_DIR}/src/orz/${module}/*.h)
    LIST(APPEND ORZ_SRC_INCLUDE_FILES ${ORZ_SRC_INCLUDE_${module}_FILES})
endforeach ()

set(ORZ_INCLUDE_DIR ${ORZ_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} ${ORZ_INCLUDE_FILES} ${ORZ_SRC_INCLUDE_FILES} ${ORZ_SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${ORZ_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${ORZ_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>)
if (ORZ_WITH_OPENSSL)
    message(STATUS "Build with OpenSSL")
	find_package(OpenSSL REQUIRED)
    target_compile_definitions(${PROJECT_NAME} ORZ_WITH_OPENSSL)
    target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)
endif (ORZ_WITH_OPENSSL)

if (WIN32)
    # target_link_libraries(${PROJECT_NAME}_SHARED wininet.lib)
    target_link_libraries(${PROJECT_NAME} wininet.lib)
    # target_link_libraries(${PROJECT_NAME}_STATIC ole32.lib)
elseif (APPLE)
    # target_link_libraries(${PROJECT_NAME}_SHARED pthread)
    target_link_libraries(${PROJECT_NAME} pthread)
elseif (UNIX)
    # target_link_libraries(${PROJECT_NAME}_SHARED pthread)
    target_link_libraries(${PROJECT_NAME} pthread)
    # target_link_libraries(${PROJECT_NAME}_STATIC uuid)
endif ()

export(TARGETS ${PROJECT_NAME}
       APPEND FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
)

string(TOLOWER ${PROJECT_NAME} LOWER_PROJECT_NAME)
GENERATE_EXPORT_HEADER(${PROJECT_NAME})
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h
    DESTINATION ${CMAKE_BINARY_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(TARGETS
    ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Config
    RUNTIME DESTINATION ${ENV_RUNTIME_DIR}
        COMPONENT Runtime
    LIBRARY DESTINATION ${ENV_LIBRARY_DIR}
        COMPONENT Runtime
    ARCHIVE DESTINATION ${ENV_ARCHIVE_DIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/orz
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

# Install cmake configure files
install(
    EXPORT ${PROJECT_NAME}Config
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SeetaFace6"
    NAMESPACE
        SeetaFace6::
    )
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${BUILD_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SeetaFace6")
install(DIRECTORY ${ORZ_SOURCE_DIR}/include/
    DESTINATION ${ENV_HEADER_DIR})
