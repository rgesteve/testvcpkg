#!/usr/bin/env bash

# Builds the consumable/consuming pair
INSTALLDIR=$(pwd)/install
BUILDDIR=build
rm -rf ${INSTALLDIR}
mkdir -p ${INSTALLDIR}
pushd consumablelib
rm -rf ${BUILDDIR}
cmake -S . -B ${BUILDDIR}
cmake --build build
cmake --install build --prefix ${INSTALLDIR}
# cpack --config ${BUILDDIR}/CPackConfig.cmake
popd

pushd consumingexe
rm -rf ${BUILDDIR}
cmake -S . -B ${BUILDDIR} -DCMAKE_PREFIX_PATH:STRING=${INSTALLDIR}
cmake --build build
popd

