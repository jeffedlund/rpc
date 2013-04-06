#ifndef JREMOTESAMPLE_H
#define JREMOTESAMPLE_H

#include "JObject.h"
#include "JClass.h"
#include "JIRemoteSample.h"
using namespace jcpp::io;

namespace jcpp{
    class JRemoteSample : public JObject, public JIRemoteSample{
    private:

    public:
        JRemoteSample();
        static JClass* getClazz();
        virtual JSampleObject* getSampleObject();
        virtual JIRemoteSample* getRemoteSample();
        virtual void checkRemoteSample(JIRemoteSample* rs);
        virtual ~JRemoteSample();
    };
}

#endif // JREMOTESAMPLE_H
