#include <iostream>
#include "../src/LCGenerator.hpp"
#include "../src/xoroshiro.hpp"
#include "../src/mixer.h"
#include <cstdio>
#include <cstdlib>

int main()
{
  std::vector<uint64_t> v1 {rand(),rand()};
  std::vector<uint64_t> v2 {rand(), rand()};
  LCGenerator l(v1);
  xoroshiroGenerator x(v2);
  
  combinationGenerator<uint64_t> c(&l, &x, &lea64);
  
  while(true) {
    auto o = c.generateNumber();
    fwrite((void *) &o, sizeof(o), 1, stdout);
  }

  return 0;
}
