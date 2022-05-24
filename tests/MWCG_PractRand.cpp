#include <iostream>
#include <random>
#include <cstdio>
#include "../src/MWCGenerator.hpp"

int main()
{
  std::vector<uint64_t> v {5, 0};
  simpleGenerator<uint64_t> *g = new MWCGenerator(v);
  while(true) {
    uint64_t val = g->generateNumber();
    fwrite((void *) &val, sizeof(val), 1, stdout); 
  }
  
  return 0;
}
