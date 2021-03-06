#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>
#include <graphics_input_layout.h>
#include "cityhash/city.h"
#include "tsl/robin_map.h"
#include "utils/hash.h"

using namespace std;
using namespace el;

#if defined(__GNUC__)
#define EXPECT_LIKELY(x)    (__builtin_expect(!!(x), 1))
#define EXPECT_UNLIKELY(x)  (__builtin_expect(!!(x), 0))
#else
#define EXPECT_LIKELY(x)    (x)
#define EXPECT_UNLIKELY(x)  (x)
#endif

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

// just for cpu warmming up
// unlike other hash-based tests, it's not fair
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
        if (EXPECT_UNLIKELY(it != test.end()))
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
        input_layout_desc.setAttributes(Vertex::getAttributeDescription(i % 101));
        input_layout_desc.setBindings(Vertex::getBindingDescription(i % 53));

        MetalInputDesc desc {};
        const auto& bindings = input_layout_desc.getBindings();
        for (size_t i = 0; i < bindings.size(); i++)
            desc.binding[i] = bindings[i];
        const auto& attribs = input_layout_desc.getAttributes();
        for (size_t i = 0; i < attribs.size(); i++) {
            desc.attribute[i]._binding = attribs[i].getBinding();
            desc.attribute[i]._format = attribs[i].getFormat();
            desc.attribute[i]._location = attribs[i].getLocation();
            desc.attribute[i]._offset = attribs[i].getOffset();
        }

        auto it = test.find(desc);
        if (EXPECT_UNLIKELY(it != test.end()))
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
        input_layout_desc.setAttributes(Vertex::getAttributeDescription(i % 101));
        input_layout_desc.setBindings(Vertex::getBindingDescription(i % 53));
        
        MetalInputDesc desc {};
        const auto& bindings = input_layout_desc.getBindings();
        for (size_t i = 0; i < bindings.size(); i++)
            desc.binding[i] = bindings[i];
        const auto& attribs = input_layout_desc.getAttributes();
        for (size_t i = 0; i < attribs.size(); i++) {
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

template <typename T>
struct CityHashFn {
    uint32_t operator()(const T& key) const {
        return CityHash32((const char*)&key, sizeof(key));
    }
};

void test3()
{
    int64_t sum = 0;
    auto start = chrono::system_clock::now();
    using HashFn = CityHashFn<MetalInputDesc>;
    tsl::robin_map<MetalInputDesc, int, HashFn> test;
    
    for (size_t i = 0; i < numTest; i++)
    {
        GraphicsInputLayoutDesc input_layout_desc;
        input_layout_desc.setAttributes(Vertex::getAttributeDescription(i % 101));
        input_layout_desc.setBindings(Vertex::getBindingDescription(i % 53));
        
        MetalInputDesc desc {};
        const auto& bindings = input_layout_desc.getBindings();
        for (size_t i = 0; i < bindings.size(); i++)
            desc.binding[i] = bindings[i];
        const auto& attribs = input_layout_desc.getAttributes();
        for (size_t i = 0; i < attribs.size(); i++) {
            desc.attribute[i]._binding = attribs[i].getBinding();
            desc.attribute[i]._format = attribs[i].getFormat();
            desc.attribute[i]._location = attribs[i].getLocation();
            desc.attribute[i]._offset = attribs[i].getOffset();
        }
        
        auto it = test.find(desc);
        if (EXPECT_UNLIKELY(it != test.end()))
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
    test3();

    return 0;
}
