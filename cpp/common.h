#include <functional>
#include <stringutils.h>
#include <fileutils.h>
#include <memory>
#include <assert.h>
#include <cstdio>
#include <map>
#include <string>

#include <easylogging/src/easylogging++.h>

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

