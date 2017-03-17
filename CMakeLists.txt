cmake_minimum_required(VERSION 3.0)
project(citizenhack)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14 -fstrict-aliasing")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Libwish)

file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(include)
include_directories(${CMAKE_BINARY_DIR}/include)

set(GAME "citizenhack")
set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/share" CACHE STRING "The directory where static game data will be stored.")
set(RUNTIME_DIR "/var" CACHE STRING "The directory where runtime data will be stored.")

set(GAME_DATA_DIR "${DATA_DIR}/${GAME}")
set(GAME_RUNTIME_DIR "${RUNTIME_DIR}/${GAME}")

configure_file(src/config.h.in ${CMAKE_BINARY_DIR}/include/config.h)
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
    "${CMAKE_BINARY_DIR}/include"
    COMMENT
    "Building data files"
    VERBATIM
)

add_custom_command(
    OUTPUT
    "${CMAKE_BINARY_DIR}/share/citizenhack/data.bin"
    DEPENDS
    "${CMAKE_BINARY_DIR}/data"
    "${CMAKE_SOURCE_DIR}/script/make_archive"
    COMMAND
    "${CMAKE_SOURCE_DIR}/script/make_archive"
    "${CMAKE_BINARY_DIR}/data"
    "${CMAKE_BINARY_DIR}/share/citizenhack/data.bin"
    COMMENT
    "Building data archive"
    VERBATIM
)

add_custom_target(
    data_files
    DEPENDS
    "${CMAKE_BINARY_DIR}/share/citizenhack/data.bin"
)

add_dependencies(citizenhack data_files)

install(TARGETS citizenhack DESTINATION bin)
install(DIRECTORY "${CMAKE_BINARY_DIR}/share/citizenhack/" DESTINATION "${GAME_DATA_DIR}")
