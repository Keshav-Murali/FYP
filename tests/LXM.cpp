#include <iostream>
#include "../src/LCGenerator.hpp"
#include "../src/xoroshiro.hpp"
#include "../src/mixer.h"
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

uint64_t identity_mixer(uint64_t val)
{
  return val;
}

int main()
{
  int n = 10;

  std::vector<uint64_t> v1 {5,2};
  std::vector<uint64_t> v2 {1, 2};
  LCGenerator l(v1);
  xoroshiroGenerator x(v2);
  
  combinationGenerator<uint64_t> c(&l, &x, &lea64);
  combinationGenerator<uint64_t> *c2 = c.split();
  
  while(n--) {
    std::cout << c.generateNumber() << " " << c.generateNormalized() << std::endl;
  }
 
  n = 10;
  while(n--) {
    std::cout << c2->generateNumber() << " " << c2->generateNormalized() << std::endl;
  }
  
  n = 100000000;
  auto t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
    c.generateNumber();
  }
  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << "Time to generate 10^8 numbers for LXM: " << ms_double.count() << "ms\n";

  t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
    c.generateNormalized();
  }
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "Time to generate 10^8 fractions for LXM: " << ms_double.count() << "ms\n";

  t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
    c2->generateNumber();
  }
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "Time to generate 10^8 numbers for splitted: " << ms_double.count() << "ms\n";
  
  t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
    c2->generateNormalized();
  }
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "Time to generate 10^8 fractions for splitted LXM: " << ms_double.count() << "ms\n";

  

  
  return 0;
}
