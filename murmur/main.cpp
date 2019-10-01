#include <iostream>
#include <chrono>

#include "tnt.h"
#include "wiki.h"

int main()
{
    const uint8_t text[] = "Hello world";
    auto hash0 = wiki::utils::hash::murmur3_32(text, 8, 123);
    auto hash1 = tnt::utils::hash::murmur3(text, 8, 123);
    assert(hash0 == hash1);

    return 0;
}
