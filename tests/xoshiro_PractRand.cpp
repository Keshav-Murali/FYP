#include <iostream>
#include "../src/xoshiro.hpp"
#include <cstdio>

int main()
{
  std::vector<uint64_t> v {12,16,30,21};
  simpleGenerator<uint64_t> *g = new xoshiroGenerator(v);

  while(true) {
    uint64_t val = g->generateNumber();
    fwrite((void *) &val, sizeof(val), 1, stdout);
  }
  return 0;
}
