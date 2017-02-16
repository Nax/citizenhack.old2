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
