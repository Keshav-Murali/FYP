#include "../src/test_harness.hpp"
#include "../src/LCGenerator.hpp"
//#include "../src/xoroshiro.hpp"
#include "../src/xoshiro.hpp"
#include "../src/mixer.h"
#include <cstdlib>

int main()
{
  std::vector<uint64_t> v1 {static_cast<uint64_t>(rand()), static_cast<uint64_t>(rand())};
  std::vector<uint64_t> v2 {static_cast<uint64_t>(rand()), static_cast<uint64_t>(rand()),
			    static_cast<uint64_t>(rand()), static_cast<uint64_t>(rand())};
  LCGenerator l(v1);
  xoshiroGenerator x(v2);
  
  combinationGenerator<uint64_t> c(&l, &x, &lea64);
  combinationGenerator<uint64_t> *c2 = c.split();
  
  lxm_wrap_and_set(&c);
  
  //  set_curr_gen(mt);
  //  set_curr_gen_dbl(mt_double);

  test_generator(std::string("LCG+xoshiro_lea64"));
  //  test_generator(std::string("test"));
  
}


/*
Tested tabs:
lea64, lower 32 bits
same, lower 32 reversed
same, upper 32
same, upper 32 reversed
degski64, all bits
degski64, all bits, after split
 */
