#include "JArrayList.h"
#include "JClass.h"
#include <cstdio>
#include <QtGlobal>

class JArrayListClass : public JClass{
public:
  JArrayListClass(){
      this->canonicalName="java.util.ArrayList";
      this->name="java.util.ArrayList";
      this->simpleName="ArrayList";
      this->serialVersionUID=8683452581122892189L;
  }

  JClass* getSuperclass(){
      return JObject::getClazz();//TODO java.util.AbstractList
  }

  JObject* newInstance(){
      return new JArrayList();
  }
};

static JClass* clazz;

JClass* JArrayList::getClazz(){
    if (clazz==NULL){
        clazz=new JArrayListClass();
    }
    return clazz;
}

JArrayList::JArrayList(int initialCapacity):JObject(getClazz())
{
    items=new std::vector<JObject*>();
}

qint32 JArrayList::getSize(){
    return items->size();
}

bool JArrayList::isEmpty(){
    return items->empty();
}

JObject* JArrayList::get(int index){
    return items->at(index);
}

void JArrayList::add(JObject* item){
    items->push_back(item);
}

void JArrayList::clear(){
    items->clear();
}

JArrayList::~JArrayList(){
    delete items;
}

//qint64 JArrayList::getSerialVersionUID() const {
//    return serialVersionUID;
//}

//void ArrayList::writeObject(MObjectOutputStream *s) {
//    // Write out element count, and any hidden stuff
//    s->defaultWriteObject();

//    // Write out array length
//    s->writeInt(length);

//    // Write out all elements in the proper order
//    for (int i = 0; i < size; i++) {
//        s->writeObject(elementData[i]);
//    }
//}

//void ArrayList::readObject(MObjectInputStream *s) {
//    // Read in size, and any hidden stuff
//    s->defaultReadObject();

//    // Read in array length and allocate array
//    qint32 arrayLength = s->readInt();
//    delete[] elementData;
//    MObject* *a = elementData = new MObject*[arrayLength];

//    // Read in all elements in the proper order
//    for (qint32 i = 0; i < size; ++i) {
//        a[i] = s->readObject();
//    }
//}
