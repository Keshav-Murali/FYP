#include "../src/test_harness.hpp"

int main()
{
  set_curr_gen(mt);
  set_curr_gen_dbl(mt_double);

  test_generator(std::string("Mersenne Twister"));
  
}
