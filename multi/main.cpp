#include <iostream>
#include <vector>
#include <murmur/wiki.h>
#include <cityhash/city.h>
#include "multi.h"

static std::vector<uint32_t> results[4];

void foo()
{
    int count[] = { 3, 4 };
    std::vector<const char*> samples[] = {
        { "too", "top", "tor", "tpp" },
        { "a000", "a001", "a003", "a004" }
    };
    for (int i = 0; i < sizeof(samples)/sizeof(samples[0]); i++)
    {
        for (auto word : samples[i]) {
            results[0].push_back(bernstein((uint8_t*)word, count[i]));
            results[1].push_back(kernighan((uint8_t*)word, count[i]));
            results[2].push_back(wiki::utils::hash::murmur3_32((uint8_t*)word, count[i], 0));
            results[3].push_back(CityHash32(word, count[i]));
        }
    }
}

void bar()
{
}

int main()
{
    foo();
    bar();

    return 0;
}
