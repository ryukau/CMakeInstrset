#include "some.hpp"

#include <chrono>
#include <iostream>
#include <memory>

std::unique_ptr<SomeInterface> getSome()
{
  std::unique_ptr<SomeInterface> some;

  auto iset = instrset_detect();
  if (iset >= 10) {
    some = std::make_unique<Some_AVX512>();
  } else if (iset >= 8) {
    some = std::make_unique<Some_AVX2>();
  } else if (iset >= 5) {
    some = std::make_unique<Some_SSE41>();
  } else {
    std::cerr
      << "\nError: Instruction set SSE4.1 or higher not supported on this computer";
    exit(EXIT_FAILURE);
  }

  std::cout << std::to_string(iset) << "\n";

  return some;
}

constexpr size_t N_LOOP = 1024;

void run(std::unique_ptr<SomeInterface> some, const char *name)
{
  double sumElapsed = 0.0;

  float result = 0.0f;
  for (size_t i = 0; i < N_LOOP; ++i) {
    auto start = std::chrono::high_resolution_clock::now();

    some->set(i);
    result += some->sum();

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = finish - start;
    sumElapsed += elapsed.count();
  }

  std::cout << name << "\n"
            << "Total[ms]" << std::to_string(sumElapsed) << "\n"
            << "Average[ms]" << std::to_string(sumElapsed / N_LOOP) << "\n"
            << std::to_string(result) << "\n\n";
}

int main()
{
  run(std::make_unique<Some_SSE41>(), "Dry run");

  run(getSome(), "Runtime");

  // run(std::make_unique<Some_SSE41>(), "SSE4.1");
  // run(std::make_unique<Some_AVX2>(), "AVX2");
  // run(std::make_unique<Some_AVX512>(), "AVX512");
  return 0;
}
