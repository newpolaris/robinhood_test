#include <stdint.h>

//
// https://www.strchr.com/hash_functions
//

constexpr uint32_t multiplicative(const uint8_t* key, size_t length, uint32_t seed, uint32_t M)
{
    uint32_t hash = seed;
    for (size_t i = 0; i < length; i++)
        hash = M * hash + key[i];
    return hash;
}

constexpr uint32_t bernstein(const uint8_t* key, size_t length)
{
    constexpr uint32_t seed = 5381;
    constexpr uint32_t M = 33;
    return multiplicative(key, length, seed, M);
}

constexpr uint32_t kernighan(const uint8_t* key, size_t length)
{
    constexpr uint32_t seed = 0;
    constexpr uint32_t M = 31;
    return multiplicative(key, length, seed, M);
}
