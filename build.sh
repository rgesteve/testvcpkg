# To build vcpkg (starting from zero)
# vcpkg/bootstrap-vcpkg.sh

#!/usr/bin/env bash

BUILDDIR=build
rm -rf ${BUILDDIR}
mkdir -p ${BUILDDIR}

# This will call vcpkg install
cmake -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -S . -B ${BUILDDIR}
cmake --build ${BUILDDIR}

# TODO -- Should add a flag to run this
# to run the test suite
#cmake --build ${BUILDDIR} --target test
