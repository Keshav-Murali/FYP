#include <iostream>
#include <random>
#include "../src/LCGenerator.hpp"
#include "../src/xoroshiro.hpp"
#include "../src/mixer.h"
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <bit>

class SplitMix {
public:
  long seed = 5;
  long GAMMA_PRIME = (1L << 56) - 5,
  GAMMA_GAMMA = 0x00281E2DBA6606F3L,
  DEFAULT_SEED_GAMMA = 0xBD24B73A95FB84D9L;
  double DOUBLE_ULP = 1.0 / (1L << 53);    
  long gamma, nextSplit;
  
  long update(long s, long g) {
    // Add g to s modulo George.
    long p = s + g;
    return (p >= s) ? p
      : (p >= 0x800000000000000DL) ? p - 13L
      : (p - 13L) + g;
  }

  long mix64(long z) {
    z = (z ^ (z >> 33)) * 0xff51afd7ed558ccdL;
    z = (z ^ (z >> 33)) * 0xc4ceb9fe1a85ec53L;
    return z ^ (z >> 33);
  }
  
  long mix56(long z) {
    z = ((z ^ (z >> 33)) * 0xff51afd7ed558ccdL)
      & 0x00FFFFFFFFFFFFFFL;
    z = ((z ^ (z >> 33)) * 0xc4ceb9fe1a85ec53L)
      & 0x00FFFFFFFFFFFFFFL;
    return z ^ (z >> 33);
  }
  
  long nextRaw64() {
    return (seed = update(seed, gamma));
  }

  long nextLong() {
    return mix64(nextRaw64()); }
};

class simpleLXM {
  uint64_t initial_state = 5;
  uint64_t s0 = 1, s1 = 2;

  uint64_t p0, p1;
  const uint64_t multiplier=0xd1342543de82ef95;
  uint64_t add_param = 3;
  
public:
  uint64_t generateNumber()
  {
  //      auto t1 = initial_state;
    //    auto t2 = s0;
    
    initial_state = initial_state * multiplier + add_param;
   
    p0 = s0;
    p1 = s1;
        
    p1 ^= p0;
    p0 = leftRotate1(p0,24);
    p0 = p0 ^ p1 ^ (p1<<16);
    p1 = leftRotate1(p1,37);
    
    s0=p0;
    s1=p1;
    
//        return lea64(t1+t2);
    return lea64(initial_state + s0);
  }
};

class simpleLXM2 {
  uint64_t initial_state = 5;
  uint64_t s0 = 1, s1 = 2;

  uint64_t p0, p1;
  const uint64_t multiplier=0xd1342543de82ef95;
  uint64_t add_param = 3;
  
public:
  uint64_t generateNumber()
  {
    auto t1 = initial_state;
    auto t2 = s0;
    
    initial_state = initial_state * multiplier + add_param;
   
    p0 = s0;
    p1 = s1;
        
    p1 ^= p0;
    p0 = std::rotl(p0,24);
    p0 = p0 ^ p1 ^ (p1<<16);
    p1 = std::rotl(p1,37);
    
    s0=p0;
    s1=p1;
    
    return lea64(t1+t2);
  }
};



int main()
{
  simpleLXM l1;
  simpleLXM2 l2;
  SplitMix s;
  
  long int n = 100000000;
  std::vector<uint64_t> arr(n);
  std::vector<long> arr1(n);
  
  //    uint64_t* arr = (uint64_t *) malloc(sizeof(uint64_t) * n);
  
  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;
  
  auto t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
    arr[i] = l1.generateNumber();
  }
  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << "Time for C LXM without OoO optimization is " << ms_double.count() << "ms\n";
  std::cout << "Value: " << arr[100000] << std::endl;

  t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
    arr[i] = l2.generateNumber();
  }
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "Time for C LXM with OoO optimization is " << ms_double.count() << "ms\n";
  std::cout << "Value: " << arr[100000] << std::endl;

  /*
  t1 = high_resolution_clock::now();
  for (auto i = 0; i < n; i++) {
    arr1[i] = s.nextLong();
  }
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "Time for C SplitMix is " << ms_double.count() << "ms\n";
  std::cout << "Value: " << arr1[100000] << std::endl;
  */
  
  return 0;
}
