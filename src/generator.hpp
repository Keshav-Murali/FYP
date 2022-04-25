#include <cstdint>
#include <cstdlib>
#include <climits>
#include <vector>
#include <limits>
#include <exception>

#ifndef GENERATOR_H
#define GENERATOR_H

// Interface for Random Number Generator
template <class T>
class generator {
public:
  // Returns an n-bit value. For eg: if T is uint64_t, then return 64-bit value
  virtual T generateNumber() = 0;

  // Returns value in [0, 1]
  virtual double generateNormalized()
  {
    return (double) generateNumber() / std::numeric_limits<T>::max();
  }

};

// Interface for a simple generator
template <class T>
class simpleGenerator : public generator<T> {
public:
  simpleGenerator(std::vector<T> &params) {} 
  virtual simpleGenerator* createNewGenerator(std::vector<T> &params) = 0;
  virtual size_t getNumParameters() = 0;
};


// Template for a combination generator
template <class T>
class combinationGenerator : public generator<T> {
private:
  simpleGenerator<T>* s1, *s2;
  T (*mixer)(T value);
  
public:
  combinationGenerator(simpleGenerator<T> *p, simpleGenerator<T> *q, T (*r)(T) ) :
    s1(p), s2(q), mixer(r)
  {
  }
  
  combinationGenerator<T>* split() {
    size_t x = s1->getNumParameters(), y = s2->getNumParameters();
    std::vector<T> v1, v2;
    
    for(size_t i = 0; i < x; i++)
      v1.push_back(this->generateNumber());
    
    
    for(size_t i = 0; i < y; i++)
      v2.push_back(this->generateNumber());
    
    simpleGenerator<T> *p = s1->createNewGenerator(v1);
    simpleGenerator<T> *q = s2->createNewGenerator(v2);

    return new combinationGenerator<T>(p, q, mixer);
  }  
  
  T generateNumber()
  {
    T val1 = s1->generateNumber();
    T val2 = s2->generateNumber();
    T combination = val1 + val2;

    return mixer(combination);
  }

};

#endif
