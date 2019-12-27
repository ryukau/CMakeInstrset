#include "some.hpp"

#include <iostream>

#if INSTRSET >= 10
#define SOME_NAME Some_AVX512
#pragma message("Some_AVX512")
#elif INSTRSET >= 8
#define SOME_NAME Some_AVX2
#pragma message("Some_AVX2")
#elif INSTRSET >= 7
#define SOME_NAME Some_AVX
#pragma message("Some_AVX")
#else
#error Unsupported instruction set
#endif

void SOME_NAME::set(float value) { runner.set(value); }
float SOME_NAME::sum() { return runner.sum(); }
