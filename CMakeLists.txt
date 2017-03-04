cmake_minimum_required(VERSION 3.0)
project(citizenhack)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14 -fstrict-aliasing")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Libwish)

file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(include)

add_executable(citizenhack ${SOURCES})
target_link_libraries(citizenhack libwish)

file(GLOB_RECURSE DATA_FILES "${CMAKE_SOURCE_DIR}/data/*")
file(GLOB_RECURSE SCRIPT_FILES "${CMAKE_SOURCE_DIR}/script/**/*.rb")

add_custom_command(
    OUTPUT
    "${CMAKE_BINARY_DIR}/data"
    DEPENDS
    ${DATA_FILES}
    ${SCRIPT_FILES}
    "${CMAKE_SOURCE_DIR}/script/make_data"
    COMMAND
    "${CMAKE_SOURCE_DIR}/script/make_data"
    "${CMAKE_SOURCE_DIR}/data"
    "${CMAKE_BINARY_DIR}/data"
    COMMENT
    "Building data files"
    VERBATIM
)

add_custom_command(
    OUTPUT
    "${CMAKE_BINARY_DIR}/lib/citizenhack/data.bin"
    DEPENDS
    "${CMAKE_BINARY_DIR}/data"
    "${CMAKE_SOURCE_DIR}/script/make_archive"
    COMMAND
    "${CMAKE_SOURCE_DIR}/script/make_archive"
    "${CMAKE_BINARY_DIR}/data"
    "${CMAKE_BINARY_DIR}/lib/citizenhack/data.bin"
    COMMENT
    "Building data archive"
    VERBATIM
)

add_custom_target(
    data_files
    DEPENDS
    "${CMAKE_BINARY_DIR}/lib/citizenhack/data.bin"
)
add_dependencies(citizenhack data_files)
