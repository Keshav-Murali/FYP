#include "generator.hpp"
#include <random>

uint64_t leftRotate(uint64_t n, unsigned int d)
{
    return (n << d)|(n >> (64 - d));
}

class xoroshiroGenerator : public simpleGenerator<uint64_t> {
public:
  size_t numParameters = 2;
  uint64_t s0, s1, t0, t1;
  
  size_t getNumParameters()
  {
    return numParameters;
  }
  
  //  using simpleGenerator<uint64_t>::simpleGenerator;

  xoroshiroGenerator(std::vector<uint64_t> &params) : simpleGenerator<uint64_t>::simpleGenerator(params) {
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
    uint64_t x = s0;

    t0=s0;
    t1=s1;

    t1 ^= t0;
    t0 = leftRotate(t0,24);
    t0 = t0 ^ t1 ^ (t1<<16);
    t1 = leftRotate(t1,37);

    s0=t0;
    s1=t1;

    return x;

  }

  simpleGenerator* createNewGenerator(std::vector<uint64_t> &params) {
    return new xoroshiroGenerator(params);
  }
  


};

