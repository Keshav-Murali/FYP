#include <iostream>
#include <random>
#include <cstdio>
#include "../src/MRGenerator.hpp"

const int64_t m1 = INT64_C(4294967087);
const int64_t m2 = INT64_C(4294944443);
uint64_t __MRG32k3a_s10 = 1, __MRG32k3a_s11 = 1, __MRG32k3a_s12 = 1, __MRG32k3a_s20 = 1, __MRG32k3a_s21 = 1, __MRG32k3a_s22 = 1;


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
 MRG32k3a_init(rand());
 std::vector<uint64_t> v {__MRG32k3a_s10 , __MRG32k3a_s11 , __MRG32k3a_s12 , __MRG32k3a_s20 , __MRG32k3a_s21 , __MRG32k3a_s22};
 
 simpleGenerator<uint64_t> *g = new MRGenerator(v);
 while(true) {
   uint32_t val = g->generateNumber();
   fwrite((void *) &val, sizeof(val), 1, stdout); 
 }
 
 return 0;
}
