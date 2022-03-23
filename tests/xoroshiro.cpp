#include <iostream>
#include "../src/xoroshiro.hpp"
#include <random>
#include <chrono>

int main()
{
  int n = 25;
  std::vector<uint64_t> v {1, 2};
  simpleGenerator<uint64_t> *g = new xoroshiroGenerator(v);
  xoroshiroGenerator g1(v);
  
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
	//	      g1.generateNumber();
  }
  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << "Time to generate 10^8 numbers for Xoro: " << ms_double.count() << "ms\n";

  n = 1000000000;
  t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
            g->generateNormalized();
    //    g1.generateNormalized();
  }
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "Time to generate 10^8 fractions for Xoro: " << ms_double.count() << "ms\n";

  
  return 0;
}
