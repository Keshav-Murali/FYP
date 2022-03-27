#include "generator.hpp"

class LCGenerator : public simpleGenerator<uint64_t> {
public:
  size_t numParameters = 2;
  uint64_t state, additive_constant;
  const uint64_t multiplier=0xd1342543de82ef95;

  LCGenerator(std::vector<uint64_t> &params) : simpleGenerator<uint64_t>::simpleGenerator(params) {
    if (params.size() != numParameters) {
      std::cerr << "Generator initialized with incorrect number of parameters! Expecting "
		<< numParameters << std::endl;
      std::exit(0);
    }

    state = params[0];
    additive_constant = params[1] | 1;
  }

  uint64_t generateNumber()
  {
    uint64_t x = state;
    state = state * multiplier + additive_constant;
    return x;
  }

  simpleGenerator* createNewGenerator(std::vector<uint64_t> &params) {
    return new LCGenerator(params);
  }
  
  size_t getNumParameters()
  {
    return numParameters;
  }
};
