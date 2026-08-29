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

include(CTest)

# Modules
add_subdirectory(src)
add_subdirectory(app)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()