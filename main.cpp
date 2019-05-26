#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>
#include <graphics_input_layout.h>
#include "tsl/robin_map.h"


using namespace std;
using namespace el;

/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TNT_UTILS_HASH_H
#define TNT_UTILS_HASH_H

#include <stdint.h>
#include <stddef.h>

namespace utils {
namespace hash {

inline uint32_t murmur3(const uint32_t* key, size_t wordCount, uint32_t seed) {
    uint32_t h = seed;
    size_t i = wordCount;
    do {
        uint32_t k = *key++;
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        h ^= k;
        h = (h << 13) | (h >> 19);
        h = (h * 5) + 0xe6546b64;
    } while (--i);
    h ^= wordCount;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

template<typename T>
struct MurmurHashFn {
    uint32_t operator()(const T& key) const {
        static_assert(0 == (sizeof(key) & 3), "Hashing requires a size that is a multiple of 4.");
        return murmur3((const uint32_t*) &key, sizeof(key) / 4, 0);
    }
};

} // namespace hash
} // namespace utils

#endif // TNT_UTILS_HASH_H

struct Vertex
{
    float x, y, z;
    float nx, ny, nz;
    float tu, tv;
    static GraphicsInputAttributes getAttributeDescription(int k)
    {
        GraphicsInputAttributes attrib(3);
        attrib[0] = GraphicsInputAttribute(0, "vPosition", 0, GraphicsVertexFormat::Float3, offsetof(Vertex, x));
        attrib[1] = GraphicsInputAttribute(0, "vNormal", 1, GraphicsVertexFormat::Float3, offsetof(Vertex, nx));
        attrib[2] = GraphicsInputAttribute(0, "vTexcoord", k, GraphicsVertexFormat::Float2, offsetof(Vertex, tu));
        return attrib;
    }

    static GraphicsInputBindings getBindingDescription(int k)
    {
        GraphicsInputBindings bindings(1);
        bindings[0] = GraphicsInputBinding(k, sizeof(Vertex));
        return bindings;
    }
};

const int numTest = 1'000'000 * 10;

void test0()
{
    int64_t sum = 0;
    auto start = chrono::system_clock::now();
    std::map<GraphicsInputLayoutDesc, int> test;
    for (int i = 0; i < numTest; i++)
    {
        GraphicsInputLayoutDesc input_layout_desc;
        input_layout_desc.setAttributes(Vertex::getAttributeDescription(i % 10));
        input_layout_desc.setBindings(Vertex::getBindingDescription(i % 5));

        auto it = test.find(input_layout_desc);
        if (it != test.end())
        {
           sum += it->second;
           continue;
        }
        test.emplace_hint(it, input_layout_desc, i);
    }
    auto end = chrono::system_clock::now();
    auto elpased = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << elpased.count() << " " << sum << endl;
}

struct MetalAttribute
{
    uint32_t _binding;
    uint32_t _location;
    GraphicsVertexFormat _format;
    uint32_t _offset;

    bool operator==(const MetalAttribute& other) const {
        return _binding == other._binding
            && _location == other._location
            && _format == other._format
            && _offset == other._offset;
    }

    bool operator!=(const MetalAttribute& other) const {
        return !operator==(other);
    }
};

struct MetalInputDesc
{
    GraphicsInputBinding binding[8];
    MetalAttribute attribute[8];

    bool operator==(const MetalInputDesc& other) const {
        bool result = true;
        
        for (int i = 0; i < 8; i++) {
            result &= attribute[i] == other.attribute[i];
        }
        for (int i = 0; i < 8; i++) {
            result &= binding[i] == other.binding[i];
        }
        return result;
    }
};

void test1()
{
    int64_t sum = 0;
    auto start = chrono::system_clock::now();
    std::unordered_map<MetalInputDesc, int, utils::hash::MurmurHashFn<MetalInputDesc>> test;
    for (int i = 0; i < numTest; i++)
    {
        GraphicsInputLayoutDesc input_layout_desc;
        input_layout_desc.setAttributes(Vertex::getAttributeDescription(i % 10));
        input_layout_desc.setBindings(Vertex::getBindingDescription(i % 5));

        MetalInputDesc desc {};
        const auto& bindings = input_layout_desc.getBindings();
        for (int i = 0; i < bindings.size(); i++)
            desc.binding[i] = bindings[i];
        const auto& attribs = input_layout_desc.getAttributes();
        for (int i = 0; i < attribs.size(); i++) {
            desc.attribute[i]._binding = attribs[i].getBinding();
            desc.attribute[i]._format = attribs[i].getFormat();
            desc.attribute[i]._location = attribs[i].getLocation();
            desc.attribute[i]._offset = attribs[i].getOffset();
        }

        auto it = test.find(desc);
        if (it != test.end())
        {
           sum += it->second;
           continue;
        }
        test.emplace_hint(it, desc, i);
    }
    auto end = chrono::system_clock::now();
    auto elpased = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << elpased.count() << " " << sum << endl;
}

void test2()
{
    int64_t sum = 0;
    auto start = chrono::system_clock::now();
    using HashFn = utils::hash::MurmurHashFn<MetalInputDesc>;
    tsl::robin_map<MetalInputDesc, int, HashFn> test;
    
    for (int i = 0; i < numTest; i++)
    {
        GraphicsInputLayoutDesc input_layout_desc;
        input_layout_desc.setAttributes(Vertex::getAttributeDescription(i % 10));
        input_layout_desc.setBindings(Vertex::getBindingDescription(i % 5));
        
        MetalInputDesc desc {};
        const auto& bindings = input_layout_desc.getBindings();
        for (int i = 0; i < bindings.size(); i++)
            desc.binding[i] = bindings[i];
        const auto& attribs = input_layout_desc.getAttributes();
        for (int i = 0; i < attribs.size(); i++) {
            desc.attribute[i]._binding = attribs[i].getBinding();
            desc.attribute[i]._format = attribs[i].getFormat();
            desc.attribute[i]._location = attribs[i].getLocation();
            desc.attribute[i]._offset = attribs[i].getOffset();
        }
        
        auto it = test.find(desc);
        if (it != test.end())
        {
            sum += it->second;
            continue;
        }
        test.emplace_hint(it, desc, i);
    }
    auto end = chrono::system_clock::now();
    auto elpased = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << elpased.count() << " " << sum << endl;
}
int main()
{
    test0();
    test1();
    test2();

    return 0;
}
