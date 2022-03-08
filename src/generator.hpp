#include <cstdint>
#include <cstdlib>
#include <climits>
#include <list>

// Interface for Random Number Generator
template <class T>
class generator {
public:
  const size_t state_size = 0;
  const size_t parameters_size = 0;
  
  generator(std::list<T>& s, std::list<T>& p) : state(s), parameters(p) {
  }
  
  // Returns an n-bit value. For eg: if T is uint64_t, then return 64-bit value
  virtual T generateNumber() = 0;

  // Returns value in [0, 1]
  virtual double generateNormalized() = 0;

protected:
  std::list<T> state;
  std::list<T> parameters;
};

