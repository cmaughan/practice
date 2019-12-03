#pragma once

#include <functional>
#include <cassert>
#include <map>

#define NOMINMAX
#include <mutils/logger/logger.h>

#include "config_app.h"

class ObjectFactory;
class Object
{
private:
public:
    static std::map<std::string, ObjectFactory*>& GetFactories()  
    {
        static std::map<std::string, ObjectFactory*> factories;
        return factories;
    }

    static void registerType(const std::string& name, ObjectFactory *factory)
    {
        Object::GetFactories()[name] = factory;
    }
    virtual void Run() = 0;
};

class ObjectFactory
{
public:
    virtual Object *create() = 0;
};

#define REGISTER_PROBLEM(klass) \
    class klass : public Object { virtual void Run() override; }; \
    class klass##Factory : public ObjectFactory { \
    public: \
        klass##Factory() \
        { \
            Object::registerType(#klass, this); \
        } \
        virtual Object *create() { \
            return new klass(); \
        } \
    }; \
    static klass##Factory global_##klass##Factory; \
void klass::Run()

