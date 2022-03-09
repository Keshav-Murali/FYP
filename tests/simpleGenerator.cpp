#include <iostream>
#include "../src/generator.hpp"

// Example generator with one state variable and one parameter
// LCG with modulo 2^k has one state variable and two parameters, for comparison
class exampleGenerator : public simpleGenerator<int> {
public:
  const size_t state_size = 1;
  const size_t parameters_size = 1;
  
  using simpleGenerator<int>::simpleGenerator;
  
  int generateNumber()
  {
    int x = state[0];
    state[0] = state[0] * parameters[0];
    return x;

  }

  double generateNormalized()
  {
    int x = state[0];
    state[0] = state[0] * parameters[0];
    return (double) x / INT_MAX;
  }
};

int main()
{
  int n = 10;
  std::cout << INT_MAX << std::endl;
  std::deque<int> a1{5}, a2{2};

  exampleGenerator g(a1, a2);
  while(n--) {
    std::cout << g.generateNumber() << " " << g.generateNormalized() << std::endl;
  }
  return 0;
}
