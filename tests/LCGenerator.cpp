#include <iostream>
#include <random>
#include "../src/LCGenerator.hpp"
#include <chrono>
int main()
{
  int n = 25;
  std::vector<uint64_t> v {5, 0};
  simpleGenerator<uint64_t> *g = new LCGenerator(v);
  LCGenerator g1(v);

  std::cout << "Passed: " << v[0] << " " << v[1] << std::endl;
  std::cout << "Parameters: " << g1.state << " " << g1.additive_constant << std::endl;
  
  while(n--) {
    std::cout << g->generateNumber() << " " << g->generateNormalized() << std::endl;
  }

  n = 100000000;
  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;
  
  auto t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
          g->generateNumber();
	  //    g1.generateNumber();
  }
  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << "Time to generate 10^8 numbers for LCG: " << ms_double.count() << "ms\n";

  n = 1000000000;
  t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
        g->generateNormalized();
	//    g1.generateNormalized();
  }
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "Time to generate 10^8 fractions for LCG: " << ms_double.count() << "ms\n";

  
  return 0;
}
