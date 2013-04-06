#ifndef JIREMOTESAMPLEPROXY_H
#define JIREMOTESAMPLEPROXY_H

#include "JProxy.h"
#include "JClass.h"
#include "JIRemoteSample.h"
using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{
    class JIRemoteSampleProxy : public JProxy, public JIRemoteSample{
    protected:
        class JIRemoteSampleProxyClass : public JProxyClass {
        public:
            JIRemoteSampleProxyClass();
            virtual JClass* getSuperclass();
            virtual JObject* newInstance();
        };
    public:
        JIRemoteSampleProxy();
        static JClass* getClazz();
        virtual JSampleObject* getSampleObject();
        virtual JIRemoteSample* getRemoteSample();
        virtual ~JIRemoteSampleProxy();
    };
}


#endif // JIREMOTESAMPLEPROXY_H
