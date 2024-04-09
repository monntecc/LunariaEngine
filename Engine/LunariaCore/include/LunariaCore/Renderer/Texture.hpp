﻿#pragma once

namespace Lunaria {

    class LUNARIA_API Texture
    {
    public:
        virtual ~Texture() = default;
        
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetRendererID() const = 0;

        virtual void SetData(void* data, uint32_t size) = 0;
        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class LUNARIA_API Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string& path);
        static Ref<Texture2D> Create(uint32_t width, uint32_t height);

        virtual bool operator==(const Texture2D& other) const = 0;
    };
    
}