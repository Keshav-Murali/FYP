#include <iostream>
#include <random>
#include <cstdio>
#include "../src/LCGenerator.hpp"

int main()
{
  int n = 10;
  std::random_device randDev;
  int rDev=randDev();
  std::deque<uint64_t> s{5}, p{rDev};

  LCGenerator g(s, p);
  while(true) {
    uint64_t val = g.generateNumber();
    fwrite((void *) &val, sizeof(val), 1, stdout); 
  }
  return 0;
}
