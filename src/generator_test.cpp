#include <iostream>
#include "generator.hpp"

// Example generator with one state variable and one parameter
// LCG with modulo 2^k has one state variable and two parameters, for comparison
class exampleGenerator : public generator<int> {
public:
  const size_t state_size = 1;
  const size_t parameters_size = 1;
  
  using generator<int>::generator;
  
  int generateNumber()
  {
    int x = state.front();
    state.front() = state.front() * parameters.front();
    return x;

  }

  double generateNormalized()
  {
    int x = state.front();
    state.front() = state.front() * parameters.front();
    return (double) x / INT_MAX;
  }
};

int main()
{
  int n = 10;
  std::cout << INT_MAX << std::endl;
  std::list<int> l1, l2;
  l1.push_back(5);
  l2.push_back(2);
  exampleGenerator g(l1, l2);
  //  exampleGenerator g;
  while(n--) {
    std::cout << g.generateNumber() << " " << g.generateNormalized() << std::endl;
  }
  return 0;
}
