cmake_minimum_required(VERSION 3.10)

set(CMAKE_VERBOSE_MAKEFILE on)

project(test_vcl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# macOS environment on GitHub Actions doesn't seem to have support for SSE3 or lower.
# With -msse2 or -msse3, clang++ just compiles into SSE4.1 code.
add_library(some_sse41 OBJECT some.cpp)
add_library(some_avx2 OBJECT some.cpp)
add_library(some_avx512 OBJECT some.cpp)
add_executable(test_vcl vcl/instrset_detect.cpp main.cpp)

if(MSVC)
  target_compile_options(some_sse41 PRIVATE
    /O2 /fp:fast)
  target_compile_options(some_avx2 PRIVATE
    /O2 /fp:fast /arch:AVX2)
  target_compile_options(some_avx512 PRIVATE
    /O2 /fp:fast /arch:AVX512)

  target_compile_options(test_vcl PRIVATE
    /O2 /fp:fast)
elseif(UNIX)
  # ./test_vcl segfaults with following optimization options:
  # - g++     : -O0
  # - clang++ : -O0 -O1 -Og
  target_compile_options(some_sse41 PRIVATE
    -O3 -msse4.1)
  target_compile_options(some_avx2 PRIVATE
    -O3 -mavx2 -mfma)
  target_compile_options(some_avx512 PRIVATE
    -O3 -mavx512f -mfma -mavx512vl -mavx512bw -mavx512dq)

  target_compile_options(test_vcl PRIVATE
    -O3 -Wall)
endif()

# Do not change order of some_* targets. Changing order cause illegal instruction.
target_link_libraries(test_vcl
  some_sse41 some_avx2 some_avx512)
