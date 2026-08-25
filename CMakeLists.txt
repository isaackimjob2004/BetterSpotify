cmake_minimum_required(VERSION 3.25)

# Makes sure timestamps of extracted files are set properly
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

project(playlist-vcs LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find the official libraries
find_package(libgit2 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

# Core library. So probably all backend code in src
add_library(core_lib src/Track.cpp)
target_include_directories(core_lib PUBLIC include)
target_compile_features(core_lib PUBLIC cxx_std_20)
target_link_libraries(core_lib PUBLIC
    libgit2::libgit2package
    nlohmann_json::nlohmann_json
    cpr::cpr
)

# Main executable program
add_executable(PlaylistApp src/main.cpp)
target_link_libraries(PlaylistApp PRIVATE core_lib)

# Unit tests
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(unit_tests tests/test_track.cpp)
target_link_libraries(unit_tests PRIVATE core_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)