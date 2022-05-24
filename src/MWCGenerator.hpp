#include "generator.hpp"
#define MWC_A1 0xff3a275c007b8ee6
class MWCGenerator : public simpleGenerator<uint64_t> {
public:
  size_t numParameters = 2;
  uint64_t state;
  uint64_t x, c;
  MWCGenerator(std::vector<uint64_t> &params) : simpleGenerator<uint64_t>::simpleGenerator(params) {
    if (params.size() != numParameters) {
      std::cerr << "Generator initialized with incorrect number of parameters! Expecting "
		<< numParameters << std::endl;
      std::exit(0);
    }
    if(params[1]>MWC_A1-1)
        params[1]= params[1] - MWC_A1-1;
    state = params[0];
    c = params[1] | 1;
  }

  uint64_t generateNumber()
  {
    uint64_t x = state;
    const __uint128_t t = MWC_A1 * (__uint128_t)state + c;
	  c = t >> 64;
	  state = uint64_t(t);
    return uint64_t(x);
  }

  simpleGenerator* createNewGenerator(std::vector<uint64_t> &params) {
    return new MWCGenerator(params);
  }
  
  size_t getNumParameters()
  {
    return numParameters;
  }
};