#include <iostream>
#include <random>
#include <cstdio>
#include <chrono>
#include <vector>
#include <bit>
#include <functional>
#include <cstdlib>
#include "../src/xoroshiro.hpp"
#include "../src/xoshiro.hpp"
#include "../src/xorshift.hpp"
#include "../src/mixer.h"
#include "../src/LCGenerator.hpp"
#include "../src/MRGenerator.hpp"
#include "../src/MWCGenerator.hpp"
#include "../src/WMSGenerator.hpp"


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

enum subgen1 {LCG=0, MRG, MWC, WMS};
enum subgen2 {roshiro=0, shiro, shift};
enum mixer {id=0, lea, deg, murmur};


uint64_t (*mixers[])(uint64_t) = {identity, lea64, degski64, murmur64};

const char* subgen1_names[] = { "LCG", "MRG", "MWC", "WMS" };
const char* subgen2_names[] = {"xoroshiro", "xoshiro", "xorshift"};
const char* mixer_names[] = {"identity", "lea64", "degski64", "murmur64"};
			  
struct container {
  std::array<simpleGenerator<uint64_t> *, 4> sg1;
  std::array<simpleGenerator<uint64_t> *, 3> sg2;
};

int main()
{
  container cont;

  MRG32k3a_init(rand());
  std::vector<uint64_t> v0 {static_cast<uint64_t>(__MRG32k3a_s10) ,static_cast<uint64_t>( __MRG32k3a_s11) , static_cast<uint64_t>(__MRG32k3a_s12) , static_cast<uint64_t>(__MRG32k3a_s20) , static_cast<uint64_t>(__MRG32k3a_s21) , static_cast<uint64_t>(__MRG32k3a_s22)};
  
  std::vector<uint64_t> v1 {static_cast<uint64_t>(rand()), static_cast<uint64_t>(rand())};
  std::vector<uint64_t> v2 {static_cast<uint64_t>(rand()), static_cast<uint64_t>(rand()),
			    static_cast<uint64_t>(rand()), static_cast<uint64_t>(rand())};
  std::vector<uint64_t> v3 {static_cast<uint64_t>(rand())};
  
  LCGenerator l(v1); cont.sg1[LCG] = &l;
  MRGenerator mr(v0); cont.sg1[MRG] = &mr;
  MWCGenerator mw(v1); cont.sg1[MWC] = &mw;
  WMSGenerator w(v3); cont.sg1[WMS] = &w;
  
  xoroshiroGenerator x(v1); cont.sg2[roshiro] = &x;
  xorshiftGenerator xst(v1); cont.sg2[shift] = &xst;
  xoshiroGenerator xs(v2); cont.sg2[shiro] = &xs;

  //  cont.mix[id] = &identity; cont.mix[lea] = &lea64; cont.mix[deg] = &degski64;
  //  cont.mix[murmur] = &murmur64;
  
  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;
  
  for (auto i = 0; i < 4; i++) {
    for (auto j = 0; j < 3; j++) {
      for (auto k = 0; k < 3; k++) {
	combinationGenerator<uint64_t> c(cont.sg1[i], cont.sg2[j], mixers[k]);
	long int n = 100000000;
	//	std::string name = std::string(subgen1_names[i]) + std::string("_") + subgen2_names[j] + "_" + mixer_names[k];
	std::vector<uint64_t> arr(n);
	
	auto t1 = high_resolution_clock::now();
	for (auto i = 0; i < n; i++) {
	  arr[i] = c.generateNumber();
	}
	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> ms_double = t2 - t1;
	std::cout << "Time for " << subgen1_names[i] << "_" << subgen2_names[j] << "_"
		  << mixer_names[k] << ": "  << ms_double.count() << "ms\n";
	std::cout << "Value: " << arr[100000] << std::endl;
  	
      }
    }

    std::cout << std::endl;
  }
  
  return 0;
}



