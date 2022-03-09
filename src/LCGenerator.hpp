#include "generator.hpp"

// Example generator with one state variable and one parameter
// LCG with modulo 2^k has one state variable and two parameters, for comparison
class LCGenerator : public simpleGenerator<uint64_t> {
public:
  const size_t state_size = 1;
  const size_t parameters_size = 1;
  const long multiplier=0xd1342543de82ef95L;
  
  using simpleGenerator<uint64_t>::simpleGenerator;
  
  uint64_t generateNumber()
  {
    uint64_t x = state[0];
    state[0] = state[0] * multiplier +parameters[0];
    return x;

  }

  double generateNormalized()
  {
    uint64_t x = state[0];
    state[0] = state[0] * multiplier + parameters[0];
    return (double) x / UINT64_MAX;
  }
};