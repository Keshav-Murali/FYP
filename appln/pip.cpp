#include <iostream>
#include <cmath>
#include "../src/LCGenerator.hpp"
#include "../src/xoroshiro.hpp"
#include "../src/mixer.h"
#include <random>
#include <omp.h>

using namespace std;

#define PI 3.14159265

long long check(double x1, double x2)
{
  if ((x1 * x1 + x2 * x2) < 1.0)
    return 1;
  return 0;
}

int main()
{
  std::vector<uint64_t> v1 {1, 2};
  std::vector<uint64_t> v2 {1, 2};
  LCGenerator l(v1);
  xoroshiroGenerator x(v2);
  combinationGenerator<uint64_t> c(&l, &x, &lea64);

  omp_set_num_threads(8);

  std::mt19937_64 mt;

  long long n;
  double estimate1, estimate2;

  for(n = 1000; n <= 1000000000; n*=10) {
    long long acc1 = 0, acc2 = 0;
#pragma omp parallel
    {
      std::mt19937_64 my_mt(mt());
#pragma omp for reduction(+ : acc2)
      for(auto i = 0; i < n; i++) {
	double y1, y2;

	y1 = mt(); y1 = y1 / mt.max(); y2 = mt(); y2 = y2 / mt.max();      
	acc2 += check(y1,y2);
      }
    }
#pragma omp parallel
    {
      auto my_gen = c.split();
#pragma omp for reduction(+ : acc1)
      for(auto i = 0; i < n; i++) {
	double x1, x2;
	x1 = my_gen->generateNormalized(); x2 = my_gen->generateNormalized();
	acc1 += check(x1,x2); 
      }
    }
    
    estimate1 = (double) acc1 / n; estimate1 *= 4;
    estimate2 = (double) acc2 / n; estimate2 *= 4;
    
    double err1 = ((PI - estimate1)/estimate1) * 100;
    double err2 = ((PI - estimate2)/estimate2) * 100;

    if (err1 < 0)
      err1 *= -1;
    if (err2 < 0)
      err2 *= -1;
    
    if ((err1 < 0.01) || (err2 < 0.01)) {
      cout << "Estimate from LXM for " << n << " iterations: " << estimate1 << " with error: " << err1 << "%" << endl;
      cout << "Estimate from MT for " << n << " iterations: " << estimate2 << " with error: " << err2 << "%" << endl;
      break;
    }
    
    cout << "Estimate from LXM for " << n << " iterations: " << estimate1 << " with error: " << err1 << "%" << endl;
    cout << "Estimate from MT for " << n << " iterations: " << estimate2 << " with error: " << err2 << "%" << endl;
    cout << endl;
  }

  
  return 0;
}

