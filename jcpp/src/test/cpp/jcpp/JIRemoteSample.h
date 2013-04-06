#ifndef JIREMOTESAMPLE_H
#define JIREMOTESAMPLE_H

#include "JInterface.h"
#include "JClass.h"
#include "JCPP.h"
#include "JSampleObject.h"

namespace jcpp{
    class JIRemoteSample : public JInterface{
    public:
        static JClass* getClazz();
        virtual JSampleObject* getSampleObject()=0;
        virtual JIRemoteSample* getRemoteSample()=0;
        virtual ~JIRemoteSample();
    };
}

#endif // JIREMOTESAMPLE_H
