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

CPMAddPackage("gh:fmtlib/fmt#11.0.2")

# ------------------------------------------------------------------------------
# Create executable
# ------------------------------------------------------------------------------
add_executable(aoc_2024_app)

target_sources(aoc_2024_app
    PRIVATE
        "src/main.cpp" "src/utility/concepts.h" "src/utility/day.h" "src/utility/day.cpp" "src/utility/io.h" "src/utility/io.cpp" "src/utility/string.h" "src/utility/string.cpp" "src/utility/vec.h" "src/utility/math.h" "src/utility/math.cpp" "src/solutions/all.h" "src/solutions/day_1/day_1.h" "src/solutions/day_1/day_1.cpp"
)

target_include_directories(aoc_2024_app
    PRIVATE
        "src/"
)

target_link_libraries(aoc_2024_app
    PRIVATE
        project_options
        project_warnings
        fmt::fmt
)

# ------------------------------------------------------------------------------
# Install options
# ------------------------------------------------------------------------------
install(
    TARGETS
        aoc_2024_app
)
