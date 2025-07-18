#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Core/Log.h"

class GPUObject
{
public:
    GPUObject() : m_ID(0)
    {
    }

    GPUObject(const GPUObject &other)
    {
        LOG_WARN("GPUObject copy constructor called - cloning GPU handles is not safe!");
        m_ID = 0;
    }

    GPUObject &operator=(const GPUObject &other)
    {
        LOG_WARN("GPUObject copy assignment called - cloning GPU handles is not safe!");
        if (this != &other)
        {
            Unload();
            m_ID = 0;
        }
        return *this;
    }

    virtual ~GPUObject()
    {
        Unload();
    }

    virtual void Load()
    {
        LOG_WARN("Base GPUObject::Load() called - should be overridden!\n");
    }

    virtual void Unload()
    {
        if (m_ID != 0)
        {
            LOG_WARN("Base GPUObject::Unload() called - should be overridden!\n");
            m_ID = 0;
        }
    }

    GLuint GetID() const { return m_ID; }
    virtual const char *GetClassName() const { return "GPUObject"; }

    operator GLuint() const { return m_ID; }

protected:
    GLuint m_ID;
};
