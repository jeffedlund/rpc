#ifndef JABSTRACTMAP_H
#define JABSTRACTMAP_H

#include "JObject.h"
#include "JMap.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JCollection.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JAbstractMap: public JObject, public JMap{
        protected:
            JAbstractMap(JClass* _class);

        public:
            static JClass* getClazz();
            virtual jint size();
            virtual jbool isEmpty();
            virtual jbool containsValue(JObject* value);
            virtual jbool containsKey(JObject* key);
            virtual JObject* get(JObject* key);
            virtual JObject* put(JObject*, JObject*);
            virtual JObject* remove(JObject* key);
            virtual void putAll(JMap* m);
            virtual void clear();
            virtual JSet* keySet();
            virtual JCollection* values();
            virtual JSet* entrySet()=0;
            virtual jbool equals(JObject* o);
            virtual jint hashCode();
            virtual string toString();
            virtual JObject* clone()=0;
            virtual ~JAbstractMap();

            class JSimpleEntry : public JEntry, public JObject, public JSerializable{
            protected:
                class JSimpleEntryClass : public JClass{

                public:
                  JSimpleEntryClass(){
                      this->canonicalName="java.util.AbstractMap$SimpleEntry";
                      this->name="java.util.AbstractMap$SimpleEntry";
                      this->simpleName="AbstractMap$SimpleEntry";
                      this->serialVersionUID=-8499721149061103585ULL;
                      addInterface(JEntry::getClazz());
                      addInterface(JSerializable::getClazz());
                  }

                  JClass* getSuperclass(){
                      return JObject::getClazz();
                  }
                };

                static JClass* clazz;
                JObject* key;
                JObject* value;
            public:
                JClass* getClazz(){
                    if (clazz==NULL){
                        clazz=new JSimpleEntryClass();
                    }
                    return clazz;
                }

                JSimpleEntry(JObject* key, JObject* value) {
                    this->key   = key;
                    this->value = value;
                }

                JSimpleEntry(JEntry* entry) {
                    this->key   = entry->getKey();
                    this->value = entry->getValue();
                }

                JObject* getKey() {
                    return key;
                }

                JObject* getValue() {
                    return value;
                }

                JObject* setValue(JObject* value) {
                    JObject* oldValue = this->value;
                    this->value = value;
                    return oldValue;
                }

                jbool equals(JObject* o) {
                    if (!(JEntry::getClazz()->isAssignableFrom(o->getClass()))){
                        return false;
                    }
                    JEntry* e = dynamic_cast<JEntry*>(o);
                    return (key==NULL ? e->getKey()==NULL : key->equals(e->getKey())) &&
                           (value==NULL ? e->getValue()==NULL : value->equals(e->getValue()));
                }

                jint hashCode() {
                    return (key   == NULL ? 0 :   key->hashCode()) ^
                           (value == NULL ? 0 : value->hashCode());
                }

                string toString() {
                    return key->toString() + "=" + value->toString();
                }
            };


            class JSimpleImmutableEntry : public JEntry , public JSerializable{
            protected:
                JObject* key;
                JObject* value;
                class JSimpleImmutableEntryClass : public JClass{

                public:
                  JSimpleImmutableEntryClass(){
                      this->canonicalName="java.util.AbstractMap$SimpleImmutableEntry";
                      this->name="java.util.AbstractMap$SimpleImmutableEntry";
                      this->simpleName="AbstractMap$SimpleImmutableEntry";
                      this->serialVersionUID=7138329143949025153ULL;
                      addInterface(JEntry::getClazz());
                      addInterface(JSerializable::getClazz());
                  }

                  JClass* getSuperclass(){
                      return JObject::getClazz();
                  }

                  JObject* newInstance(){
                      throw new JInstantiationException("cannot instantiate object of class "+getName());
                  }
                };

                static JClass* clazz;

            public:
                JClass* getClazz(){
                    if (clazz==NULL){
                        clazz=new JSimpleImmutableEntryClass();
                    }
                    return clazz;
                }

                JSimpleImmutableEntry(JObject* key, JObject* value) {
                    this->key   = key;
                    this->value = value;
                }

                JSimpleImmutableEntry(JEntry* entry) {
                    this->key   = entry->getKey();
                    this->value = entry->getValue();
                }

                JObject* getKey() {
                    return key;
                }

                JObject* getValue() {
                    return value;
                }

                JObject* setValue(JObject*) {
                    throw new JUnsupportedOperationException();
                }

                jbool equals(JObject* o) {
                    if (!(JEntry::getClazz()->isAssignableFrom(o->getClass()))){
                        return false;
                    }
                    JEntry* e = dynamic_cast<JEntry*>(o);
                    return (key==NULL ? e->getKey()==NULL : key->equals(e->getKey())) &&
                           (value==NULL ? e->getValue()==NULL : value->equals(e->getValue()));
                }

                jint hashCode() {
                    return (key   == NULL ? 0 :   key->hashCode()) ^
                           (value == NULL ? 0 : value->hashCode());
                }

                string toString() {
                    return key->toString() + "=" + value->toString();
                }
            };
        };
    }
}

#endif // JABSTRACTMAP_H
