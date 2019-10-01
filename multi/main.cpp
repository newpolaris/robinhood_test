#include <iostream>
#include <vector>
#include "multi.h"

void foo()
{
    std::vector<uint32_t> bern;
    std::vector<uint32_t> kern;
    for (auto word : { "too", "top", "tor", "tpp" })
    {
        bern.push_back(bernstein((uint8_t*)word, 3));
        kern.push_back(kernighan((uint8_t*)word, 3));
    }
}

void bar()
{
    std::vector<uint32_t> bern;
    std::vector<uint32_t> kern;
    for (auto word : { "a000", "a001", "a003", "a004" })
    {
        bern.push_back(bernstein((uint8_t*)word, 4));
        kern.push_back(kernighan((uint8_t*)word, 4));
    }
}

int main()
{
    foo();
    bar();

    return 0;
}
