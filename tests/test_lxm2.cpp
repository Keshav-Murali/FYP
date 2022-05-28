#include "../src/test_harness.hpp"
#include "../src/xoroshiro.hpp"
#include "../src/mixer.h"
#include <cstdlib>
#include "../src/MRGenerator.hpp"

const int64_t m1 = INT64_C(4294967087);
const int64_t m2 = INT64_C(4294944443);
int64_t __MRG32k3a_s10 = 1, __MRG32k3a_s11 = 1, __MRG32k3a_s12 = 1, __MRG32k3a_s20 = 1, __MRG32k3a_s21 = 1, __MRG32k3a_s22 = 1;


inline int64_t staffordMix13(int64_t z) {
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return (z >> 1) ^ (z >> 32);
}

inline void MRG32k3a_init(int64_t s) {
	__MRG32k3a_s10 = staffordMix13(s += 0x9e3779b97f4a7c15) % m1;
	__MRG32k3a_s11 = staffordMix13(s += 0x9e3779b97f4a7c15) % m1;
	__MRG32k3a_s12 = staffordMix13(s += 0x9e3779b97f4a7c15) % m1;
	__MRG32k3a_s20 = staffordMix13(s += 0x9e3779b97f4a7c15) % m2;
	__MRG32k3a_s21 = staffordMix13(s += 0x9e3779b97f4a7c15) % m2;
	__MRG32k3a_s22 = staffordMix13(s += 0x9e3779b97f4a7c15) % m2;
}

int main()
{
  std::vector<uint64_t> v1 {static_cast<uint64_t>(rand()), static_cast<uint64_t>(rand())};
  
  xoroshiroGenerator x(v1);
  MRG32k3a_init(rand());
  std::vector<uint64_t> v {static_cast<uint64_t>(__MRG32k3a_s10) ,static_cast<uint64_t>( __MRG32k3a_s11) , static_cast<uint64_t>(__MRG32k3a_s12) , static_cast<uint64_t>(__MRG32k3a_s20) , static_cast<uint64_t>(__MRG32k3a_s21) , static_cast<uint64_t>(__MRG32k3a_s22)};
  
  MRGenerator m(v);
  
  combinationGenerator<uint64_t> c(&m, &x, &identity);
  
  lxm_wrap_and_set(&c);
  
  test_generator(std::string("MRG+XBG_nomixer"));
  return 0;
}


