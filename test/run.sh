#!/bin/bash
#
# `../CMakeLists.txt` was translated from this script.
#
# Segfaults with:
# - g++     : -O0
# - clang++ : -O0 -O1 -Og
#

CXX=clang++
OPT=-O3

echo Compiling some program.

$CXX -v -std=c++17 $OPT -msse2 \
  -o some_sse2.o -c ../some.cpp
$CXX -v -std=c++17 $OPT -msse4.1 \
  -o some_sse41.o -c ../some.cpp
$CXX -v -std=c++17 $OPT -mavx2 -mfma \
  -o some_avx2.o -c ../some.cpp
$CXX -v -std=c++17 $OPT -mavx512f -mfma -mavx512vl -mavx512bw -mavx512dq \
  -o some_avx512.o -c ../some.cpp

$CXX -v -std=c++17 -O3 \
  some_sse2.o \
  some_sse41.o \
  some_avx2.o \
  some_avx512.o \
  ../vcl/instrset_detect.cpp \
  ../main.cpp

ls -la

echo Executing some program.
./a.out
