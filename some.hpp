#include <array>
#include <iostream>

#include "vcl/vectorclass.h"

struct SomeInterface {
  virtual ~SomeInterface() {}
  virtual void set(float value) = 0;
  virtual float sum() = 0;
};

constexpr size_t dataSize = 10000;

struct alignas(64) Runner {
  std::array<Vec16f, dataSize> data;

  void set(float value)
  {
    for (size_t i = 0; i < dataSize; ++i) data[i] = value;
  }

  float sum()
  {
    Vec16f result(0.0f);
    for (size_t i = 0; i < dataSize; ++i) {
      result += data[i];
    }
    return horizontal_add(result);
  }
};

#define SOME_CLASS(INSTRSET)                                                             \
  struct Some_##INSTRSET : public SomeInterface {                                        \
  public:                                                                                \
    /* Somehow this causes segfault. Even with `alignas(64)`. */                         \
    /* std::array<Vec16f, dataSize> data; */                                             \
                                                                                         \
    Runner runner;                                                                       \
                                                                                         \
    void set(float value) override;                                                      \
    float sum() override;                                                                \
  };

SOME_CLASS(SSE41)
SOME_CLASS(AVX)
SOME_CLASS(AVX2)
SOME_CLASS(AVX512)
