#include "some.hpp"

#include <iostream>

#if INSTRSET >= 10
#define SOME_NAME Some_AVX512
#warning Some_AVX512
#elif INSTRSET >= 8
#define SOME_NAME Some_AVX2
#warning Some_AVX2
#elif INSTRSET >= 5
#define SOME_NAME Some_SSE41
#warning Some_SSE41
#else
#error Unsupported instruction set
#endif

void SOME_NAME::set(float value) { runner.set(value); }
float SOME_NAME::sum() { return runner.sum(); }
