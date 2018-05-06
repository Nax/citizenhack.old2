set(GAME "citizenhack")
set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/share" CACHE STRING "The directory where static game data will be stored.")
set(RUNTIME_DIR "/var" CACHE STRING "The directory where runtime data will be stored.")
set(GAME_DATA_DIR "${DATA_DIR}/${GAME}")
set(GAME_RUNTIME_DIR "${RUNTIME_DIR}/${GAME}")

configure_file(config.h.in "${CMAKE_BINARY_DIR}/include/hack/config.h")

file(GLOB_RECURSE SOURCES "*.cpp")
add_executable(citizenhack ${SOURCES})
target_include_directories(citizenhack PRIVATE "${CMAKE_SOURCE_DIR}/src" "${CMAKE_BINARY_DIR}/include")
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
    "${CMAKE_BINARY_DIR}/include/hack"
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
