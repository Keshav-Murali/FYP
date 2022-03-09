#include <iostream>
#include "../src/xoroshiro.hpp"
int main()
{
  int n = 10;
  std::cout << INT_MAX << std::endl;
  std::deque<uint64_t> a1{1,2}, a2{1,2};

  xoroshiroGenerator g(a1, a2);
  while(n--) {
    std::cout << g.generateNumber() << " " << g.generateNormalized() << std::endl;
  }
  return 0;
}