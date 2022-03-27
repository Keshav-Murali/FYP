#include <iostream>
#include "../src/generator.hpp"

// Example generator with one state variable and one parameter
// LCG with modulo 2^k has one state variable and two parameters, for comparison
class exampleGenerator : public simpleGenerator<int> {
public:
  int state;
  int multiplier;
  
  size_t numParameters = 2;
  
  exampleGenerator(std::vector<int> &params) : simpleGenerator<int>::simpleGenerator(params) {
    if (params.size() != numParameters) {
      std::cerr << "Generator initialized with incorrect number of parameters! Expecting "
		<< numParameters << std::endl;
      std::exit(0);
    }

    state = params[0];
    multiplier = params[1];
  }

  simpleGenerator* createNewGenerator(std::vector<int> &params) {
    return new exampleGenerator(params);
  }

  size_t getNumParameters()
  {
    return numParameters;
  }
  
  int generateNumber()
  {
    int x = state;
    state = state * multiplier;
    return x;
  }
};

int main()
{
  int n = 15;

  std::vector<int> v1 {5,2};
  std::vector<int> v3 {1};
  
  simpleGenerator<int>* g1 = new exampleGenerator(v1);
  simpleGenerator<int>* g2 = g1->createNewGenerator(v1);

  while(n--) {
    std::cout << g1->generateNumber() << " " << g2->generateNormalized() << std::endl;
  }

  simpleGenerator<int>* g3 = g2->createNewGenerator(v3);
  
  return 0;
}
