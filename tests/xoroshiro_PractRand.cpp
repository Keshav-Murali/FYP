#include <iostream>
#include "../src/xoroshiro.hpp"
#include <cstdio>

int main()
{
  std::deque<uint64_t> a1{1,2}, a2{1,2};

  xoroshiroGenerator g(a1, a2);
  while(true) {
    uint64_t val = g.generateNumber();
    fwrite((void *) &val, sizeof(val), 1, stdout);
  }
  return 0;
}
