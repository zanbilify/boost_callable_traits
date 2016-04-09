#!/bin/sh

/bin/sh ./internal/build.sh            \
../../                                 \
../../build_gcc_libstdcxx              \
-DCMAKE_CXX_COMPILER=g++               \
-DCALLABLE_TRAITS_BUILD_EXPERIMENTAL=ON