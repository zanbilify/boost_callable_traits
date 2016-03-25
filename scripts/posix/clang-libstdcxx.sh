#!/bin/sh

/bin/sh ./internal/build.sh                         \
../../                                              \
../../build_clang_libstdcxx                         \
-DCMAKE_CXX_COMPILER=clang++                        \
-DCMAKE_CXX_FLAGS="-stdlib=libstdc++"               \
-DCMAKE_EXE_LINKER_FLAGS="-stdlib=libstdc++ -lstdc++" 
