cmake_minimum_required(VERSION 3.29)
project(advent_of_code_2024
    LANGUAGES CXX
    VERSION 1.0.0
)

# Check for in-source builds
include("cmake/ban_in_source_builds.cmake")

# Turn off compiler specific extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------------------
# Create target for specifying the C++ standard and compiler specific options
# ------------------------------------------------------------------------------
add_library(project_options INTERFACE)
target_compile_features(project_options
    INTERFACE
        cxx_std_23
)

# Enable multi-processor compilation on MSVC
if(MSVC)
    target_compile_options(project_options
        INTERFACE
            /MP
    )
endif()

# ------------------------------------------------------------------------------
# Create target for compiler warnings
# ------------------------------------------------------------------------------
include("cmake/compiler_warnings.cmake")
add_library(project_warnings INTERFACE)

option(project_warnings_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
set_project_warnings(project_warnings
    "${project_warnings_WARNINGS_AS_ERRORS}"
    ""
    ""
    ""
)

# ------------------------------------------------------------------------------
# Manage dependencies
# ------------------------------------------------------------------------------
file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.2/CPM.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake"
    EXPECTED_HASH SHA256=c8cdc32c03816538ce22781ed72964dc864b2a34a310d3b7104812a5ca2d835d
)
include("${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake")

CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY "fmtlib/fmt"
    GIT_TAG "11.0.2"
)
CPMAddPackage(
    NAME ctre
    GITHUB_REPOSITORY "hanickadot/compile-time-regular-expressions"
    GIT_TAG "v3.9.0"
)

# ------------------------------------------------------------------------------
# Create executable
# ------------------------------------------------------------------------------
add_executable(aoc_2024_app)

target_sources(aoc_2024_app
    PRIVATE
        "src/main.cpp" "src/utility/day.h" "src/utility/day.cpp" "src/utility/io.h" "src/utility/io.cpp" "src/utility/string.h" "src/utility/string.cpp" "src/utility/vec.h" "src/utility/math.h" "src/utility/math.cpp" "src/solutions.h" "src/solutions/day_1/day_1.h" "src/solutions/day_1/day_1.cpp" "src/solutions/day_2/day_2.h" "src/solutions/day_2/day_2.cpp" "src/solutions/day_3/day_3.h" "src/solutions/day_3/day_3.cpp" "src/solutions/day_4/day_4.h" "src/solutions/day_4/day_4.cpp" "src/solutions/day_5/day_5.h" "src/solutions/day_5/day_5.cpp" "src/solutions/day_6/day_6.h" "src/solutions/day_6/day_6.cpp" "src/solutions/day_7/day_7.h" "src/solutions/day_7/day_7.cpp" "src/solutions/day_8/day_8.h" "src/solutions/day_8/day_8.cpp" "src/solutions/day_9/day_9.h" "src/solutions/day_9/day_9.cpp" "src/solutions/day_10/day_10.h" "src/solutions/day_10/day_10.cpp" "src/solutions/day_11/day_11.h" "src/solutions/day_11/day_11.cpp" "src/solutions/day_12/day_12.h" "src/solutions/day_12/day_12.cpp" "src/solutions/day_13/day_13.h" "src/solutions/day_13/day_13.cpp" "src/solutions/day_14/day_14.h" "src/solutions/day_14/day_14.cpp" "src/solutions/day_15/day_15.h" "src/solutions/day_15/day_15.cpp" "src/solutions/day_15/warehouse.h" "src/solutions/day_15/warehouse.cpp" "src/solutions/day_16/day_16.h" "src/solutions/day_16/day_16.cpp" "src/solutions/day_17/day_17.h" "src/solutions/day_17/day_17.cpp" "src/solutions/day_18/day_18.h" "src/solutions/day_18/day_18.cpp" "src/solutions/day_19/day_19.h" "src/solutions/day_19/day_19.cpp" "src/solutions/day_20/day_20.h" "src/solutions/day_20/day_20.cpp" "src/solutions/day_21/day_21.h" "src/solutions/day_21/day_21.cpp" "src/solutions/day_22/day_22.h" "src/solutions/day_22/day_22.cpp" "src/solutions/day_23/day_23.h" "src/solutions/day_23/day_23.cpp")

target_include_directories(aoc_2024_app
    PRIVATE
        "src/"
)

target_link_libraries(aoc_2024_app
    PRIVATE
        project_options
        project_warnings
        fmt::fmt
        ctre::ctre
)

# ------------------------------------------------------------------------------
# Install options
# ------------------------------------------------------------------------------
install(
    TARGETS
        aoc_2024_app
)
