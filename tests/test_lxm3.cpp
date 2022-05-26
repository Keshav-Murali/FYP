#include "../src/test_harness.hpp"
#include "../src/xoroshiro.hpp"
#include "../src/mixer.h"
#include <cstdlib>
#include "../src/MWCGenerator.hpp"

int main()
{
  std::vector<uint64_t> v1 {rand(), rand()};
  std::vector<uint64_t> v2 {rand(), rand()};

  xoroshiroGenerator x(v2);
  MWCGenerator m(v1);
  
  combinationGenerator<uint64_t> c(&m, &x, &degski64);
  
  lxm_wrap_and_set(&c);
  
  test_generator(std::string("MWC+XBG_LXM"));
  return 0;
}
