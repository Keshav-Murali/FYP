#include "generator.hpp"

// Example generator with one state variable and one parameter
// LCG with modulo 2^k has one state variable and two parameters, for comparison
class LCGenerator : public simpleGenerator<uint64_t> {
public:
  const size_t state_size = 1;
  const size_t parameters_size = 1;
  const uint64_t multiplier=0xd1342543de82ef95;

  using simpleGenerator<uint64_t>::simpleGenerator;
  
  LCGenerator(std::deque<uint64_t>& s, std::deque<uint64_t>& p) : simpleGenerator{s, p} {
    parameters[0] = parameters[0] | 1;
  }

  
  uint64_t generateNumber()
  {
    uint64_t x = state[0];
    state[0] = state[0] * multiplier + parameters[0];
    return x;

  }

  double generateNormalized()
  {
    return (double) this->generateNumber() / UINT64_MAX;
  }
};
