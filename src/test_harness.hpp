#include "../src/generator.hpp"
extern "C" {
#include "TestU01.h"
}
#include <random>
#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

// #define NUM_SEEDS x should be in the .cpp file that includes this

// uint64_t seeds[NUM_SEEDS];


// curr_gen is the current 64 bit generator
// curr_gen_dbl is the current double generator

// curr_gen is required so that we can extract and test lower and upper bits, reversed and not-reversed

// curr_gen dbl isn't really needed but is there for analogous use

uint64_t (*curr_gen)();
double (*curr_gen_dbl)();

void set_curr_gen(uint64_t (*func)())
{
  curr_gen = func;
  return;
}

void set_curr_gen_dbl(double (*func)())
{
  curr_gen_dbl = func;
}

uint32_t lower_32()
{
  return (uint32_t) curr_gen();
}

uint32_t upper_32()
{
  auto x = curr_gen();
  x = x >> 32;
  return (uint32_t) x;
}

inline uint32_t rev32(uint32_t v)
{
    // https://graphics.stanford.edu/~seander/bithacks.html
    // swap odd and even bits
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    // swap consecutive pairs
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    // swap nibbles ...
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    // swap bytes
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    // swap 2-byte-long pairs
    v = (v >> 16) | (v << 16);
    return v;
}


uint32_t lower_32_rev()
{
  return rev32(lower_32());
}

uint32_t upper_32_rev()
{
  return rev32(upper_32());
}


// wrapping our generators
generator<uint64_t>* my_gen;

uint64_t lxm_int()
{
  return my_gen->generateNumber();
}

double lxm_dbl()
{
  return my_gen->generateNormalized();
}

void lxm_wrap_and_set(generator<uint64_t>* some_gen)
{
  my_gen = some_gen;
  curr_gen = lxm_int;
  curr_gen_dbl = lxm_dbl;
}


// wrappers for mt19937_64
uint64_t mt()
{
  //  static std::mt19937 m(seed_data[0]);
  static std::mt19937_64 m;

  return m();
}

double mt_double()
{
  static std::mt19937_64 m;

  double x = m();
  x = x / m.max();

  return x;
}

void helper(unif01_Gen* x)
{
  bbattery_SmallCrush(x);
  //  bbattery_Crush(x);
  //  bbattery_BigCrush(x);
}

// Test function, execute after setting curr gen as needed
void test_generator(std::string name)
{
  std::string name1;
  
  if (fork() == 0) {
    name1 = name+"_l32";
    int myfd = open(name1.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0666);
    close(1);
    dup(myfd);

    unif01_Gen* gen32 = unif01_CreateExternGenBits((char *) name1.c_str(), lower_32);
    helper(gen32);
    unif01_DeleteExternGenBits(gen32);
    
    exit(0);
  }
  
  if (fork() == 0) {
    name1 = name+"_l32r";
    int myfd = open(name1.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0666);
    close(1);
    dup(myfd);

    unif01_Gen* genr32 = unif01_CreateExternGenBits((char *) name1.c_str(), lower_32_rev);
    helper(genr32);
    unif01_DeleteExternGenBits(genr32);
    
    exit(0);
  }
  
  
  if (fork() == 0) {
    name1 = name+"_u32";
    int myfd = open(name1.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0666);
    close(1);
    dup(myfd);
    
    unif01_Gen* genu32 = unif01_CreateExternGenBits((char *)  name1.c_str(), upper_32);
    helper(genu32);
    unif01_DeleteExternGenBits(genu32);
    
    exit(0);
  }
  

  if (fork() == 0) {
    name1 = name+"_u32r";
    int myfd = open(name1.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0666);
    close(1);
    dup(myfd);
    
    unif01_Gen* genur32 = unif01_CreateExternGenBits((char *) name1.c_str(), upper_32_rev);
    helper(genur32);
    unif01_DeleteExternGenBits(genur32);
    
    exit(0);
  }
  

  if (fork() == 0) {
    name1 = name+"_all";
    int myfd = open(name1.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0666);
    close(1);
    dup(myfd);
    
    unif01_Gen* gend = unif01_CreateExternGen01((char *) name1.c_str(), curr_gen_dbl);
    helper(gend);
    unif01_DeleteExternGen01(gend);
    
    
    exit(0);
  }
  
}
