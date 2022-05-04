#include "../src/test_harness.hpp"
#include "../src/LCGenerator.hpp"
#include "../src/xoroshiro.hpp"
#include "../src/mixer.h"

int main()
{
  std::vector<uint64_t> v1 {5,2};
  std::vector<uint64_t> v2 {1,2};
  LCGenerator l(v1);
  xoroshiroGenerator x(v2);
  
  combinationGenerator<uint64_t> c(&l, &x, &lea64);
  lxm_wrap_and_set(&c);
  
  set_curr_gen(mt);
  set_curr_gen_dbl(mt_double);

  test_generator(std::string("LCG+XBG LXM"));
  
}
