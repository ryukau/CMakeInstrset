#!/bin/bash
#
# This script links object files compiled by cmake.
#

g++ -std=c++17 -O3 \
  ../build/CMakeFiles/some_sse2.dir/some.cpp.o \
  ../build/CMakeFiles/some_sse41.dir/some.cpp.o \
  ../build/CMakeFiles/some_avx2.dir/some.cpp.o \
  ../build/CMakeFiles/some_avx512.dir/some.cpp.o \
  ../vcl/instrset_detect.cpp \
  ../main.cpp
