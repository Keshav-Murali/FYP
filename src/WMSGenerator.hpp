#include "generator.hpp"

class WMSGenerator : public simpleGenerator<uint64_t> {
public:
  size_t numParameters = 1;
  uint64_t state;
   uint64_t x1 = 0, w1 = 0, s1 = 0xb5ad4eceda1ce2a9;
   uint64_t x2 = 0, w2 = 0, s2 = 0x278c5a4d8419fe6b;

  WMSGenerator(std::vector<uint64_t> &params) : simpleGenerator<uint64_t>::simpleGenerator(params) {
    if (params.size() != numParameters) {
      std::cerr << "Generator initialized with incorrect number of parameters! Expecting "
		<< numParameters << std::endl;
      std::exit(0);
    }
    state = params[0];
  }

  uint64_t generateNumber()
  {
    uint64_t x = state;
    uint64_t xx;
    x1 *= x1; xx = x1 += (w1 += s1); x1 = (x1 >> 32) | (x1 << 32);
    x2 *= x2; x2 += (w2 += s2); x2 = (x2 >> 32) | (x2 << 32);
    state = xx ^ x2;
    return x;
  }

  simpleGenerator* createNewGenerator(std::vector<uint64_t> &params) {
    return new WMSGenerator(params);
  }
  
  size_t getNumParameters()
  {
    return numParameters;
  }
};