#ifndef XOR_H
#define XOR_H

#include "generator.hpp"
#include <random>
#include <bit>

inline uint64_t leftRotate2(uint64_t n, unsigned int d)
{
    return (n << d)|(n >> (64 - d));
}

class xorshiftGenerator : public simpleGenerator<uint64_t> {
public:
  size_t numParameters = 2;
  uint64_t s0, s1;
  
  size_t getNumParameters()
  {
    return numParameters;
  }
  
  xorshiftGenerator(std::vector<uint64_t> &params) : simpleGenerator<uint64_t>::simpleGenerator(params) {
    if (params.size() != numParameters) {
      std::cerr << "Generator initialized with incorrect number of parameters! Expecting "
		<< numParameters << std::endl;
      std::exit(0);
    }

    s0 = params[0];
    s1 = params[1];

    while (s0 == s1 && s0 == 0) {
      std::random_device r;
      s0 = (uint64_t) r(); 
    }
  }
  
  uint64_t generateNumber()
  {
    uint64_t t1 = s0;
    const uint64_t t0 = s1;
    const uint64_t x = t0 + t1;
    s0 = t0;
    t1 ^= t1 << 23; // a
    s1 = t1 ^ t0 ^ (t1 >> 18) ^ (t0 >> 5); // b, c
    return x; 
  }
  
  simpleGenerator* createNewGenerator(std::vector<uint64_t> &params) {
    return new xorshiftGenerator(params);
  }
  
};

#endif
