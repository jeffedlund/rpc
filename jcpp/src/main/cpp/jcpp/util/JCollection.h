#ifndef JCOLLECTION_H
#define JCOLLECTION_H

#include "JInterface.h"
#include "JIterable.h"
#include "JCPP.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JCollection : public JIterable{
        public:
            static JClass* getClazz();
            virtual jint size()=0;
            virtual bool isEmpty()=0;
            virtual bool contains(JObject*)=0;
            virtual JIterator* iterator()=0;
            //TODO virtual JObject* toArray()=0; //TODO better JObject array
            //virtual JObject* toArray(JObject*)=0;//TODO
            virtual bool add(JObject* e)=0;
            virtual bool remove(JObject* o)=0;
            virtual bool containsAll(JCollection* c)=0;
            virtual bool addAll(JCollection* c)=0;
            virtual bool removeAll(JCollection* c)=0;
            virtual bool retainAll(JCollection* c)=0;
            virtual void clear()=0;
            virtual bool equals(JObject* o)=0;
            virtual jint hashCode()=0;
            virtual ~JCollection();
        };
    }
}

#endif // JCOLLECTION_H
