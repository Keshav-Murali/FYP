#include <iostream>
#include <cmath>
#include "../src/LCGenerator.hpp"
#include "../src/xoroshiro.hpp"
#include "../src/mixer.h"
#include <random>

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


  std::mt19937_64 mt;

  long long n, acc1 = 0, acc2 = 0;
  long long i = 0;
  double estimate1, estimate2;
  
  for(n = 1000; n <= 10000000000; n*=10) {
    for(; i < n; i++) {
      double x1, x2, y1, y2;
      x1 = c.generateNormalized(); x2 = c.generateNormalized();
      y1 = mt(); y1 = y1 / mt.max(); y2 = mt(); y2 = y2 / mt.max();
      
      acc1 += check(x1,x2); acc2 += check(y1,y2);
    }

    estimate1 = (double) acc1 / n; estimate1 *= 4;
    estimate2 = (double) acc2 / n; estimate2 *= 4;
    
    double err1 = ((PI - estimate1)/estimate1) * 100;
    double err2 = ((PI - estimate2)/estimate2) * 100;

    if (err1 < 0)
      err1 *= -1;
    if (err2 < 0)
      err2 *= -1;
    
    if ((err1 < 0.0001) || (err2 < 0.0001)) {
      cout << "Estimate from LXM after " << i << " iterations: " << estimate1 << " with error: " << err1 << "%" << endl;
      cout << "Estimate from MT after " << i << " iterations: " << estimate2 << " with error: " << err2 << "%" << endl;
      break;
    }
    
    cout << "Estimate from LXM after " << i << " iterations: " << estimate1 << " with error: " << err1 << "%" << endl;
    cout << "Estimate from MT after " << i << " iterations: " << estimate2 << " with error: " << err2 << "%" << endl;
    cout << endl;
  }

  return 0;
}

