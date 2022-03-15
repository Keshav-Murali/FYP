#include <cstdint>
#include <cstdlib>
#include <climits>
#include <deque>
#include <limits>

#ifndef GENERATOR_H
#define GENERATOR_H

// Interface for Random Number Generator
template <class T>
class generator {
public:
  // Returns an n-bit value. For eg: if T is uint64_t, then return 64-bit value
  virtual T generateNumber() = 0;

  // Returns value in [0, 1]
  virtual double generateNormalized() = 0;
};

template <class T>
class simpleGenerator : public generator<T> {
public:
  const size_t state_size = 0;
  const size_t parameters_size = 0;
  
  simpleGenerator(std::deque<T>& s, std::deque<T>& p) : state(s), parameters(p) {
  }
  
protected:
  std::deque<T> state;
  std::deque<T> parameters;  
};

/*template <class T>
class mixer {
public:
  virtual T mix(T value) = 0;
};
*/

template <class T>
class combinationGenerator : public generator<T> {
private:
  simpleGenerator<T>& s1, &s2;
  //  mixer<T> m;
  T (*mixer)(T value);
public:
  //  combinationGenerator(simpleGenerator<T> p, simpleGenerator<T> q, mixer<T> r) :
  combinationGenerator(simpleGenerator<T> &p, simpleGenerator<T> &q, T (*r)(T) ) :
    s1(p), s2(q), mixer(r)
  {
  }
  
  /*  combinationGenerator<T> split() {
    std::deque<T> l11, l12, l21, l22;
    for(auto i = 0; i < s1.state_size; i++) {
      l11.push_back(this->generateNumber());
    }
    
    for(auto i = 0; i < s1.parameters_size; i++) {
      l12.push_back(this->generateNumber());
    }
    
    for(auto i = 0; i < s2.state_size; i++) {
      l21.push_back(this->generateNumber());
    }
    
    for(auto i = 0; i < s2.parameters_size; i++) {
      l22.push_back(this->generateNumber());
    }
		
    auto s3 = new *decltype(s1)(l11, l12);
    decltype(s2) s4(l21, l22);
    return combinationGenerator(s3, s4, mixer);
  }
  */

  T generateNumber()
  {
    T val1 = s1.generateNumber();
    T val2 = s2.generateNumber();
    T combination = val1 + val2;

    return mixer(combination);
  }

  double generateNormalized()
  {
    return (double) generateNumber() / std::numeric_limits<T>::max();
  }

};

#endif
