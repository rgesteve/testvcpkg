#!/usr/bin/env bash

# should ensure that the binary has been built

#DATASET_PATH=$PWD/data LD_LIBRARY_PATH=/opt/intel/oneapi/tbb/latest/lib/intel64/gcc4.8 build/src/fibo
DATASET_PATH=$PWD/data build/src/onemore

