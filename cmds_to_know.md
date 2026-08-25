Config Build Sys cmd:
cmake --preset default

Compile cmd:
cmake --build --preset default
cmake --build --preset app-only
cmake --build --preset test-only
cmake --build --preset clean-build

Delete compiled files:
cmake --build build --target clean

Run executables cmd:
./build/PlaylistApp
./build/unit_tests

How to run tests: (compile first)
ctest --preset default