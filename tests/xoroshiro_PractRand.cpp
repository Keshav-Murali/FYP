#include <iostream>
#include "../src/xoroshiro.hpp"
#include <cstdio>

int main()
{
  std::vector<uint64_t> v {12, 16};
  simpleGenerator<uint64_t> *g = new xoroshiroGenerator(v);

  while(true) {
    uint64_t val = g->generateNumber();
    fwrite((void *) &val, sizeof(val), 1, stdout);
  }
  return 0;
}
