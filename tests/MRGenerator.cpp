#include <iostream>
#include <random>
#include "../src/MRGenerator.hpp"
#include <chrono>
uint64_t __MRG32k3a_s10 = 1, __MRG32k3a_s11 = 1, __MRG32k3a_s12 = 1, __MRG32k3a_s20 = 1, __MRG32k3a_s21 = 1, __MRG32k3a_s22 = 1;
const int64_t m1 = INT64_C(4294967087);
const int64_t m2 = INT64_C(4294944443);

inline uint64_t staffordMix13(uint64_t z) {
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return (z >> 1) ^ (z >> 32);
}

inline void MRG32k3a_init(uint64_t s) {
	__MRG32k3a_s10 = staffordMix13(s += 0x9e3779b97f4a7c15) % m1;
	__MRG32k3a_s11 = staffordMix13(s += 0x9e3779b97f4a7c15) % m1;
	__MRG32k3a_s12 = staffordMix13(s += 0x9e3779b97f4a7c15) % m1;
	__MRG32k3a_s20 = staffordMix13(s += 0x9e3779b97f4a7c15) % m2;
	__MRG32k3a_s21 = staffordMix13(s += 0x9e3779b97f4a7c15) % m2;
	__MRG32k3a_s22 = staffordMix13(s += 0x9e3779b97f4a7c15) % m2;
}
int main()
{
  int n = 500;
  MRG32k3a_init(rand());
  std::vector<uint64_t> v {__MRG32k3a_s10 , __MRG32k3a_s11 , __MRG32k3a_s12 , __MRG32k3a_s20 , __MRG32k3a_s21 , __MRG32k3a_s22};
  simpleGenerator<uint64_t> *g = new MRGenerator(v);
  MRGenerator g1(v);

  std::cout << "Passed: " << v[0] << " " << v[1] << " " << v[2] <<" " << v[3] <<" " << v[4] <<" " << v[5] <<" " << v[6] <<std::endl;
  //std::cout << "Parameters: " << g1.state << " " << g1.additive_constant << std::endl;
  
  while(n--) {
        std::cout << g->generateNumber() << " " << g->generateNormalized() << std::endl;
    //    std::cout << g->generateNumber() << std::endl;
    //    std::cout << g->generateNormalized() << std::endl;
  }


  /*
  n = 100000000;
  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;
  
  auto t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
          g->generateNumber();
	  //    g1.generateNumber();
  }
  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << "Time to generate 10^8 numbers for MRG: " << ms_double.count() << "ms\n";

  n = 1000000000;
  t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
        g->generateNormalized();
	//    g1.generateNormalized();
  }
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "Time to generate 10^8 fractions for MRG: " << ms_double.count() << "ms\n";

  */
  return 0;
}
