#include <iostream>
#include <random>
#include "../src/LCGenerator.hpp"
int main()
{
  int n = 10;
  std::random_device randDev;
  int rDev=randDev();
  std::cout << INT_MAX << std::endl;
  std::deque<uint64_t> s{5}, p{rDev};

  LCGenerator g(s, p);
  while(n--) {
    std::cout << g.generateNumber() << " " << g.generateNormalized() << std::endl;
  }
  return 0;
}