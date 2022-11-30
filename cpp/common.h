#pragma once

#undef IMGUI_ENABLE_FREETYPE
#include <functional>
#include <cassert>
#include <map>

#include <mutils/logger/logger.h>
#include <mutils/algorithm/ringiterator.h>
#include <mutils/file/file.h>
#include <mutils/algorithm/container_utils.h>
#include <mutils/string/string_utils.h>

#include "config_app.h"

class ObjectFactory;
class Object
{
private:
public:
    Object()
    {}

    static std::map<std::string, ObjectFactory*>& GetFactories()  
    {
        static std::map<std::string, ObjectFactory*> factories;
        return factories;
    }

    static void registerType(const std::string& name, ObjectFactory *factory)
    {
        Object::GetFactories()[name] = factory;
    }
    virtual void RunOnce() {};
    virtual void Run() {};
    virtual void DrawGUI() {};
    virtual void SetName(const std::string& name) { m_name = name; }
    virtual const std::string& GetName() const { return m_name; }

    std::string m_name;
};

class ObjectFactory
{
public:
    virtual Object *create() = 0;
};

#define REGISTER_PROBLEM(klass) \
    class klass##Factory : public ObjectFactory { \
    public: \
        klass##Factory() \
        { \
            Object::registerType(#klass, this); \
        } \
        virtual Object *create() { \
            auto pObj = new klass(); \
            pObj->SetName(#klass); \
            return pObj; \
        } \
    }; \
    static klass##Factory global_##klass##Factory;

