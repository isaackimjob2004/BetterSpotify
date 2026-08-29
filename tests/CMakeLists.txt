# Unit tests
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
)

if(MSVC)
    set(gtest_forced_shared_crt ON CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests TrackConstructorTest.cpp)
target_link_libraries(unit_tests PRIVATE core_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)