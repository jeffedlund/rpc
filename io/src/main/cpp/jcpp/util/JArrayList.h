#ifndef JARRAYLIST_H
#define JARRAYLIST_H

#include "JObject.h"
#include "JCollection.h"
#include "JSerializable.h"
#include <QtGlobal>

class JArrayList : public JObject, public JSerializable, public JCollection
{
    std::vector<JObject*>* items;

 //   void writeObject(MObjectOutputStream *s);

 //   void readObject(MObjectInputStream *s);

public:
    JArrayList(int initialCapacity = 10);

    static JClass* clazz;

    //virtual qint64 getSerialVersionUID() const;

    qint32 getSize();

    bool isEmpty();

    JObject* get(int index);

    void add(JObject* item);

    void clear();

    ~JArrayList();
};

#endif // JARRAYLIST_H
