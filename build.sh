# To build vcpkg (starting from zero)
# vcpkg/bootstrap-vcpkg.sh

#!/usr/bin/env bash

BUILDDIR=build
rm -rf ${BUILDDIR}
mkdir -p ${BUILDDIR}

# This will call vcpkg install
#CMAKE_PREFIX_PATH=$HOME/projects/xgboost/build/install/lib/cmake/xgboost cmake -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -S . -B ${BUILDDIR}
#CMAKE_MODULE_PATH=build/install/lib/cmake/xgboost cmake -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -S . -B ${BUILDDIR}
cmake -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -S . -B ${BUILDDIR}
#cmake -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -DRUN_XGBOOST_KERNEL=ON -S . -B ${BUILDDIR}
cmake --build ${BUILDDIR}
cmake --install ${BUILDDIR} --prefix ${BUILDDIR}/install

# TODO -- Should add a flag to run this
# to run the test suite
#cmake --build ${BUILDDIR} --target test
