#ifndef XO_H
#define XO_H

#include "generator.hpp"
#include <random>
#include <bit>

inline uint64_t leftRotate(uint64_t n, unsigned int d)
{
    return (n << d)|(n >> (64 - d));
}

class xoshiroGenerator : public simpleGenerator<uint64_t> {
public:
  size_t numParameters = 4;
  uint64_t s0, s1, s2, s3;
  
  size_t getNumParameters()
  {
    return numParameters;
  }
  
  xoshiroGenerator(std::vector<uint64_t> &params) : simpleGenerator<uint64_t>::simpleGenerator(params) {
    if (params.size() != numParameters) {
      std::cerr << "Generator initialized with incorrect number of parameters! Expecting "
		<< numParameters << std::endl;
      std::exit(0);
    }

    s0 = params[0];
    s1 = params[1];
    s2 = params[2];
    s3 = params[3];

    while (s0 == s1 && s1==s2 && s2==s3 && s0 == 0 ) {
      std::random_device r;
      s0 = (uint64_t) r(); 
    }
  }
  
  uint64_t generateNumber()
  {
    uint64_t x = leftRotate(s0 + s3, 23) + s0;

	uint64_t t = s1 << 17;

	s2 ^= s0;
	s3 ^= s1;
	s1 ^= s2;
	s0 ^= s3;

	s2 ^= t;

	s3 = leftRotate(s3, 45);

	return x;

  }

  simpleGenerator* createNewGenerator(std::vector<uint64_t> &params) {
    return new xoshiroGenerator(params);
  }
  
};

#endif
