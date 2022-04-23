#include <iostream>
#include <cmath>
#include "../src/LCGenerator.hpp"
#include "../src/xoroshiro.hpp"
#include "../src/mixer.h"
#include <random>

int main()
{
  std::vector<uint64_t> v1 {5,2};
  std::vector<uint64_t> v2 {1, 2};
  LCGenerator l(v1);
  xoroshiroGenerator x(v2);
  combinationGenerator<uint64_t> c(&l, &x, &lea64);
  //  combinationGenerator<uint64_t> *c2 = c.split();

  std::mt19937_64 mt;
  auto range1 = mt.max(), range2 = mt.min();
  std::cout << range1 << " " << range2 << std::endl;
  long long n = 0;

  while(true) {
    std::cout << "Enter n: ";
    std::cin >> n;

    long long x = 0;

    for(auto i = 0; i < n; i++) {

      double x1, x2;
            x1 = c.generateNormalized(); x2 = c.generateNormalized();
      //     x1 = mt(); x1 = x1/range1; x2 = mt(); x2 = x2/range1;
      if (sqrt(x1 * x1 + x2 * x2) < 1.0)
	x++;
    }

    std::cout << x << " " << n << std::endl;
    double estimate = x;
    estimate = estimate/ n;
    estimate = estimate * 4;
    
    std::cout << "For " << n << " iterations, estimate of pi is: " << estimate << std::endl;
  }
    
  return 0;
}

