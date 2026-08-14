cmake_minimum_required(VERSION 3.20)
project(playlist-vcs)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the newly installed official libraries
find_package(libgit2 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

# Create your executable program
add_executable(PlaylistApp main.cpp)

# Link the libraries using the modern target names
target_link_libraries(PlaylistApp PRIVATE 
    libgit2::libgit2package
    nlohmann_json::nlohmann_json
    cpr::cpr
)