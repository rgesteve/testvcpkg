#!/usr/bin/env bash

BUILDDIR=build
rm -rf ${BUILDDIR}
mkdir -p ${BUILDDIR}

cmake -S . -B ${BUILDDIR}
cmake --build ${BUILDDIR}



