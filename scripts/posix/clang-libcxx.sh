#!/bin/sh

/bin/sh ./internal/build.sh                         \
../../                                              \
../../build_clang_libcxx                            \
-DCMAKE_CXX_COMPILER=clang++                        \
-DCMAKE_CXX_FLAGS="-stdlib=libc++"                  \
-DCMAKE_EXE_LINKER_FLAGS="-stdlib=libc++ -lc++ -lc++abi" 
