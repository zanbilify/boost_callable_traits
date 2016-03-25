#!/bin/sh

/bin/sh ./internal/build.sh                         \
../../                                              \
../../build_gcc_libcxx                              \
-DCMAKE_CXX_COMPILER=g++                            \
-DCMAKE_CXX_FLAGS="-stdlib=libc++"                  \
-DCMAKE_EXE_LINKER_FLAGS="-stdlib=libc++ -lstdc++"