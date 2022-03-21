#include <iostream>
#include "../src/generator.hpp"

// Example generator with one state variable and one parameter
// LCG with modulo 2^k has one state variable and two parameters, for comparison
class exampleGenerator : public simpleGenerator<int> {
public:
  int state;
  int multiplier;
  
  size_t numParameters = 2;

  //  using simpleGenerator<int>::simpleGenerator;
  
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

int identity_mixer(int val)
{
  return val;
}


int main()
{
  int n = 4;
  std::vector<int> v1 {1,2}, v2 {1, 3};

  simpleGenerator<int>* g1 = new exampleGenerator(v1);
  simpleGenerator<int>* g2 = new exampleGenerator(v2);
  combinationGenerator<int>* c1 = new combinationGenerator<int>(g1, g2, &identity_mixer);
  combinationGenerator<int>* c2 = c1->split();
  
  while(n--) {
    std::cout << c1->generateNumber() << " " << c1->generateNormalized() << std::endl;
  }

  n = 4;

  while(n--) {
    std::cout << c2->generateNumber() << " " << c2->generateNormalized() << std::endl;
  }
  

  return 0;
}
