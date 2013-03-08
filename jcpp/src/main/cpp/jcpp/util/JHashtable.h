#ifndef JHASHTABLE_H
#define JHASHTABLE_H

#include "JObject.h"
#include <map>
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        //TODO implement most of util classes
        template <class Key, class Value>
        class JCPP_LIBRARY_EXPORT JHashtable : public JObject{
            map<Key,Value>* hashtable;

        public:
            JHashtable();

            //static JClass* clazz;

            int size();

            Value get(const Key & key);

            void put(const Key & key, const Value & value);

            Value remove(const Key & key);

            bool containsKey(const Key & key);

        //    QList<Value> values();

        //    QList<Key> keys();

            virtual ~JHashtable();

        };
    }
}

#endif // JHASHTABLE_H