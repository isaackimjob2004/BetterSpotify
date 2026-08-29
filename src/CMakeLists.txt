# Find the official libraries
find_package(libgit2 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

# Core library
add_library(core_lib Track.cpp)

target_include_directories(core_lib 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(core_lib PUBLIC cxx_std_20)

target_link_libraries(core_lib PUBLIC
    libgit2::libgit2package
    nlohmann_json::nlohmann_json
    cpr::cpr
)