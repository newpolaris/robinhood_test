#include <graphics_input_layout.h>
#include <tuple>

using namespace el;

GraphicsInputBinding::GraphicsInputBinding() :
    _binding(0u),
    _stride(0u),
    _inputRate(GraphicsInputRateVertex)
{
}

GraphicsInputBinding::GraphicsInputBinding(uint32_t binding, uint32_t stride, GraphicsInputRate rate) :
    _binding(binding),
    _stride(stride),
    _inputRate(rate)
{
}

void GraphicsInputBinding::setBinding(uint32_t binding)
{
    _binding = binding;
}

uint32_t GraphicsInputBinding::getBinding() const
{
    return _binding;
}

void GraphicsInputBinding::setStride(uint32_t stride)
{
    _stride = stride;
}

uint32_t GraphicsInputBinding::getStride() const
{
    return _stride;
}

void GraphicsInputBinding::setInputRate(GraphicsInputRate rate)
{
    _inputRate = rate;
}

GraphicsInputRate GraphicsInputBinding::getInputRate() const
{
    return _inputRate;
}

bool GraphicsInputBinding::operator==(const GraphicsInputBinding& other) const
{
    const auto& a = std::tie(_binding, _stride, _inputRate);
    const auto& b = std::tie(other._binding, other._stride, other._inputRate);
    return a == b;
}

bool GraphicsInputBinding::operator!=(const GraphicsInputBinding& other) const
{
    return !operator==(other);
}

bool GraphicsInputBinding::operator<(const GraphicsInputBinding& other) const
{
    const auto& a = std::tie(_binding, _stride, _inputRate);
    const auto& b = std::tie(other._binding, other._stride, other._inputRate);
    return a < b;
}

GraphicsInputAttribute::GraphicsInputAttribute() :
    _binding(0u),
    _location(0u),
    _format(GraphicsVertexFormat::Invalid),
    _offset(0u)
{
}

GraphicsInputAttribute::GraphicsInputAttribute(uint32_t binding, std::string name, uint32_t location, GraphicsVertexFormat format, uint32_t offset) :
    _binding(binding),
    _name(std::move(name)),
    _location(location),
    _format(format),
    _offset(offset)
{
}

void GraphicsInputAttribute::setBinding(uint32_t binding)
{
    _binding = binding;
}

uint32_t GraphicsInputAttribute::getBinding() const
{
    return _binding;
}

void GraphicsInputAttribute::setLocation(uint32_t location)
{
    _location = location;
}

uint32_t GraphicsInputAttribute::getLocation() const
{
    return _location;
}

void GraphicsInputAttribute::setName(std::string name)
{
    _name = std::move(name);
}

const std::string& GraphicsInputAttribute::getName() const
{
    return _name;
}

void GraphicsInputAttribute::setFormat(GraphicsVertexFormat format)
{
    _format = format;
}

GraphicsVertexFormat el::GraphicsInputAttribute::getFormat() const
{
    return _format;
}

void GraphicsInputAttribute::setOffset(uint32_t offset)
{
    _offset = offset;
}

uint32_t GraphicsInputAttribute::getOffset() const
{
    return _offset;
}

bool GraphicsInputAttribute::operator==(const GraphicsInputAttribute& other) const
{
    const auto& a = std::tie(_binding, _name, _location, _format, _offset);
    const auto& b = std::tie(other._binding, other._name, other._location, other._format, other._offset);
    return a == b;
}

bool GraphicsInputAttribute::operator<(const GraphicsInputAttribute& other) const
{
    const auto& a = std::tie(_binding, _name, _location, _format, _offset);
    const auto& b = std::tie(other._binding, other._name, other._location, other._format, other._offset);
    return a < b;
}

GraphicsInputLayoutDesc::GraphicsInputLayoutDesc()
{
}

void GraphicsInputLayoutDesc::addAttribute(GraphicsInputAttribute attrib)
{
    _attributes.push_back(std::move(attrib));
}

void GraphicsInputLayoutDesc::addBinding(GraphicsInputBinding binding)
{
    _bindings.push_back(std::move(binding));
}

void GraphicsInputLayoutDesc::setAttributes(GraphicsInputAttributes attrib)
{
    _attributes = std::move(attrib);
}

const GraphicsInputAttributes& GraphicsInputLayoutDesc::getAttributes() const
{
    return _attributes;
}

void GraphicsInputLayoutDesc::setBindings(GraphicsInputBindings bindings)
{
    _bindings = std::move(bindings);
}

const GraphicsInputBindings& GraphicsInputLayoutDesc::getBindings() const
{
    return _bindings;
}

bool GraphicsInputLayoutDesc::operator==(const GraphicsInputLayoutDesc& other) const
{
    const auto& a = std::tie(_attributes, _bindings);
    const auto& b = std::tie(other._attributes, other._bindings);
    return a == b;
}

bool GraphicsInputLayoutDesc::operator<(const GraphicsInputLayoutDesc& other) const
{
    const auto& a = std::tie(_attributes, _bindings);
    const auto& b = std::tie(other._attributes, other._bindings);
    return a < b;
}

el::GraphicsInputLayout::GraphicsInputLayout()
{
}

el::GraphicsInputLayout::~GraphicsInputLayout()
{
}
