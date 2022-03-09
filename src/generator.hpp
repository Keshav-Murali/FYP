#include <cstdint>
#include <cstdlib>
#include <climits>
#include <deque>

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
  simpleGenerator<T> s1, s2;
  //  mixer<T> m;
  T (*mixer)(T value);
public:
  //  combinationGenerator(simpleGenerator<T> p, simpleGenerator<T> q, mixer<T> r) :
  combinationGenerator(simpleGenerator<T> p, simpleGenerator<T> q, T (*r)(T) ) :
    s1(p), s2(q), mixer(r)
  {
  }
  
  combinationGenerator split() {
    
    return new combinationGenerator(s1, s2);
  }

  T generateNumber()
  {
    T val1 = s1.generateNumber();
    T val2 = s2.generateNumber();
    T combination = val1 + val2;

    return m(combination);
  }
};
