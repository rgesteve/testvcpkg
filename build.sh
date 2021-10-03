# To build vcpkg (starting from zero)
# vcpkg/bootstrap-vcpkg.sh

# This will call vcpkg install
cmake -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -S . -B build/
cmake --build build/
