function(ban_in_source_builds)

    # Gets the real path of both directories so we can't use symlinks as a workaround
    get_filename_component(SRC_DIR ${CMAKE_SOURCE_DIR} REALPATH)
    get_filename_component(BIN_DIR ${CMAKE_BINARY_DIR} REALPATH)

    if (${SRC_DIR} STREQUAL ${BIN_DIR})
        message(FATAL_ERROR "In-source builds are not allowed. Run CMake from a separate build directory")
    endif()
endfunction()

ban_in_source_builds()