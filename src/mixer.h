#ifndef MIXER_H
#define MIXER_H

inline uint64_t murmur64(uint64_t z) {
    z ^= (z >> 33);
    z *= 0x85ebca6bul;
    z ^= (z >> 33);
    z *= 0xc4ceb9fe1a85ec53ull;
    return z ^ (z >> 33);
}

inline uint64_t degski64(uint64_t z){
    z ^= (z >> 32);
    z *= 0xd6e8feb86659fd93ull;
    z ^= (z >> 32);
    z *= 0xd6e8feb86659fd93ull;
    return z ^ (z >> 32);
}

inline uint64_t lea64(uint64_t z) {
    z ^= (z >> 32);
    z *= 0xdaba0b6eb09322e3ull;
    z ^= (z >> 32);
    z *= 0xdaba0b6eb09322e3ull;
    return z ^ (z >> 32); 
} 

inline uint64_t identity(uint64_t z)
{
  return z;
}

#endif

