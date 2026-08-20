Build cmd:
cmake -B build -S . -G Ninja -DCMAKE_TOOLCHAIN_FILE=[PATH_TO_VCPKG]/scripts/buildsystems/vcpkg.cmake

Compile cmd:
cmake --build build
cmake --build build --target main_app
cmake --build build --target test_app

Delete compiled files:
cmake --build build --target clean

Run cmd:
./build/PlaylistApp

How to run tests: (compile first)
./build/unit_tests
ctest --test-dir build --output-on-failure