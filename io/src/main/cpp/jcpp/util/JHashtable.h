#ifndef JHASHTABLE_H
#define JHASHTABLE_H

#include "JObject.h"
#include <map>

template <class Key, class Value> class JHashtable : public JObject
{
    std::map<Key,Value>* hashtable;

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

    ~JHashtable();

};

#endif // JHASHTABLE_H
