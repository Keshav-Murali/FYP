
#include "generator.hpp"

// Example generator with one state variable and one parameter
// LCG with modulo 2^k has one state variable and two parameters, for comparison
uint64_t leftRotate(uint64_t n, unsigned int d)
{
    return (n << d)|(n >> (64 - d));
}
class xoroshiroGenerator : public simpleGenerator<uint64_t> {
public:
  const size_t state_size = 2;
  const size_t parameters_size = 2;
  
  using simpleGenerator<uint64_t>::simpleGenerator;
  
  uint64_t generateNumber()
  {
    uint64_t x = state[0];

    parameters[0]=state[0];
    parameters[1]=state[1];

    parameters[1] ^= parameters[0];
    parameters[0] = leftRotate(parameters[0],24);
    parameters[0] = parameters[0] ^ parameters[1] ^ (parameters[1]<<16);
    parameters[1] = leftRotate(parameters[1],37);

    state[0]=parameters[0];
    state[1]=parameters[1];

    return x;

  }

  double generateNormalized()
  {
   uint64_t x = state[0];

    parameters[0]=state[0];
    parameters[1]=state[1];

    parameters[1] ^= parameters[0];
    parameters[0] = leftRotate(parameters[0],24);
    parameters[0] = parameters[0] ^ parameters[1] ^ (parameters[1]<<16);
    parameters[1] = leftRotate(parameters[1],37);

    state[0]=parameters[0];
    state[1]=parameters[1];

    return (double) x / UINT64_MAX;
  }
};