#include <iostream>
#include <random>
#include <cstdio>
#include "../src/WMSGenerator.hpp"

int main()
{
  std::vector<uint64_t> v {5};
  simpleGenerator<uint64_t> *g = new WMSGenerator(v);
  while(true) {
    uint64_t val = g->generateNumber();
    fwrite((void *) &val, sizeof(val), 1, stdout); 
  }
  
  return 0;
}