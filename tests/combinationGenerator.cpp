#include <iostream>
#include "../src/generator.hpp"

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

int identity_fn(int val)
{
  return val;
}


int main()
{
  int n = 5;
  std::vector<int> v1 {1,2}, v2 {1,3};

  simpleGenerator<int>* g1 = new exampleGenerator(v1);
  simpleGenerator<int>* g2 = new exampleGenerator(v2);
  combinationGenerator<int>* c1 = new combinationGenerator<int>(g1, g2, &identity_fn);
  combinationGenerator<int>* c2 = c1->split();

  std::cout << "Testing combination generator: " << std::endl;
  while(n--) {
    std::cout << c1->generateNumber() << " " << c1->generateNormalized() << std::endl;
  }

  n = 5;
  std::cout << "Testing splitted generator: " << std::endl;
  while(n--) {
    std::cout << c2->generateNumber() << " " << c2->generateNormalized() << std::endl;
  }
  

  return 0;
}
