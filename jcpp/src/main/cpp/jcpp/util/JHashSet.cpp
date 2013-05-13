#include "JHashSet.h"
#include "JClass.h"
#include <cstdio>
#include "Collections.h"
#include "JVoid.h"

namespace jcpp{
    namespace util{
        class JHashSetClass : public JClass{

            static JObject* invokeWriteObject(JObject* object,vector<JObject*>* args){
                JHashSet* hashSet=(JHashSet*)object;
                hashSet->writeObject((JObjectOutputStream*)args->at(0));
                return NULL;
            }

            static JObject* invokeReadObject(JObject* object,vector<JObject*>* args){
                JHashSet* hashSet=(JHashSet*)object;
                hashSet->readObject((JObjectInputStream*)args->at(0));
                return NULL;
            }

        public:
          JHashSetClass(){
              this->canonicalName="java.util.HashSet";
              this->name="java.util.HashSet";
              this->simpleName="HashSet";
              this->serialVersionUID=-5024744406713321676ULL;
              addInterface(JSet::getClazz());
              addInterface(JSerializable::getClazz());
              addInterface(JCloneable::getClazz());

              vector<JClass*>* paramType=new vector<JClass*>();
              paramType->push_back(JObjectInputStream::getClazz());
              addMethod(new JMethod("readObject",this,JVoid::getClazz(),paramType,invokeReadObject));
              paramType=new vector<JClass*>;
              paramType->push_back(JObjectOutputStream::getClazz());
              addMethod(new JMethod("writeObject",this,JVoid::getClazz(),paramType,invokeWriteObject));
          }

          JClass* getSuperclass(){
              return JAbstractSet::getClazz();
          }

          JObject* newInstance(){
              return new JHashSet();
          }
        };

        static JClass* clazz;

        JClass* JHashSet::getClazz(){
            if (clazz==NULL){
                clazz=new JHashSetClass();
            }
            return clazz;
        }

        static JObject* PRESENT = new JObject();

        JHashSet::JHashSet(jint, jfloat):JAbstractSet(getClazz()){
            this->map=new JHashMap();
        }

        JHashSet::JHashSet(JCollection* c):JAbstractSet(getClazz()){
            this->map=new JHashMap();
            addAll(c);
        }

        JIterator* JHashSet::iterator(){
            return map->keySet()->iterator();
        }

        jint JHashSet::size(){
            return map->size();
        }

        JPrimitiveArray* JHashSet::toArray(){
            return JAbstractSet::toArray();
        }

        jbool JHashSet::containsAll(JCollection* c){
            return JAbstractSet::containsAll(c);
        }

        jbool JHashSet::addAll(JCollection* c){
            return JAbstractSet::addAll(c);
        }

        jbool JHashSet::removeAll(JCollection* c){
            return JAbstractSet::removeAll(c);
        }

        jbool JHashSet::retainAll(JCollection* c){
            return JAbstractSet::retainAll(c);
        }

        jbool JHashSet::equals(JObject* c){
            return JAbstractSet::equals(c);
        }

        jint JHashSet::hashCode(){
            return JAbstractSet::hashCode();
        }

        jbool JHashSet::isEmpty(){
            return map->isEmpty();
        }

        jbool JHashSet::contains(JObject* o){
            return map->containsKey(o);
        }

        jbool JHashSet::add(JObject* item){
            return map->put(item,PRESENT)==NULL;
        }

        jbool JHashSet::remove(JObject* e){
            return map->remove(e)==PRESENT;
        }

        void JHashSet::clear(){
            map->clear();
        }

        JHashSet* JHashSet::clone(){
            return new JHashSet(dynamic_cast<JAbstractCollection*>(this));
        }

        void JHashSet::writeObject(JObjectOutputStream* out){
            out->defaultWriteObject();
            out->writeInt(map->size());//capacity
            out->writeFloat(map->loadFactor);//loadFactor
            out->writeInt(map->size());
            JIterator* iterator=map->keySet()->iterator();
            while (iterator->hasNext()){
                JObject* e=iterator->next();
                out->writeObject(e);
            }
            delete iterator;
        }

        void JHashSet::readObject(JObjectInputStream* in){
            in->defaultReadObject();
            in->readInt();
            in->readFloat();
            jint size = in->readInt();
            for (int i=0; i<size; i++) {
                JObject* e= in->readObject();
                map->put(e, PRESENT);
            }
        }

        JHashSet::~JHashSet(){
            delete map;
        }
    }
}
