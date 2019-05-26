#ifndef __GRAPHICS_INPUT_LAYOUT_H__
#define __GRAPHICS_INPUT_LAYOUT_H__

#include <graphics_types.h>

namespace el {

    class GraphicsInputBinding final
    {
    public:

        GraphicsInputBinding();
        GraphicsInputBinding(uint32_t binding, uint32_t stride, GraphicsInputRate rate = GraphicsInputRateVertex);

        void setBinding(uint32_t binding);
        uint32_t getBinding() const;

        void setStride(uint32_t stride);
        uint32_t getStride() const;

        void setInputRate(GraphicsInputRate rate);
        GraphicsInputRate getInputRate() const;

        bool operator==(const GraphicsInputBinding& other) const;
        bool operator!=(const GraphicsInputBinding& other) const;
        bool operator<(const GraphicsInputBinding& other) const;
        
    private:

        uint32_t _binding;
        uint32_t _stride;
        GraphicsInputRate _inputRate;
    };

    class GraphicsInputAttribute final
    {
    public:

        GraphicsInputAttribute();
        GraphicsInputAttribute(uint32_t binding, std::string name, uint32_t location, GraphicsVertexFormat format, uint32_t offset);

        void setBinding(uint32_t binding);
        uint32_t getBinding() const;

        void setLocation(uint32_t location);
        uint32_t getLocation() const;

        void setName(std::string name);
        const std::string& getName() const;

        void setFormat(GraphicsVertexFormat format);
        GraphicsVertexFormat getFormat() const;

        void setOffset(uint32_t offset);
        uint32_t getOffset() const;
        
        bool operator==(const GraphicsInputAttribute& other) const;
        bool operator<(const GraphicsInputAttribute& other) const;

    private:

        uint32_t _binding;
        std::string _name;
        uint32_t _location;
        GraphicsVertexFormat _format;
        uint32_t _offset;
    };

    class GraphicsInputLayoutDesc final
    {
    public:

        GraphicsInputLayoutDesc();

        void addAttribute(GraphicsInputAttribute attrib);
        void addBinding(GraphicsInputBinding binding);

        void setAttributes(GraphicsInputAttributes attrib);
        const GraphicsInputAttributes& getAttributes() const;

        void setBindings(GraphicsInputBindings bindings);
        const GraphicsInputBindings& getBindings() const;

        bool operator==(const GraphicsInputLayoutDesc& other) const;
        bool operator<(const GraphicsInputLayoutDesc& other) const;
        
    private:

        GraphicsInputAttributes _attributes;
        GraphicsInputBindings _bindings;
    };

    class GraphicsInputLayout
    {
    public:

        GraphicsInputLayout();
        virtual ~GraphicsInputLayout();

        virtual const GraphicsInputLayoutDesc& getDesc() const = 0;

    private:

        GraphicsInputLayout(const GraphicsInputLayout&);
        GraphicsInputLayout& operator=(const GraphicsShader&);

        GraphicsInputLayoutDesc _desc;
    };

} // namespace el {

#endif // __GRAPHICS_INPUT_LAYOUT_H__
