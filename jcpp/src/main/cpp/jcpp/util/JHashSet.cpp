#include "JHashSet.h"
#include "JClass.h"
#include <cstdio>
#include "Collections.h"

namespace jcpp{
    namespace util{
        class JHashSetClass : public JClass{

            static JObject* invokeWriteObject(JObject* object,vector<JObject*>* args){
                JHashSet* HashSet=(JHashSet*)object;
                HashSet->writeObject((JObjectOutputStream*)args->at(0));
                return NULL;
            }

            static JObject* invokeReadObject(JObject* object,vector<JObject*>* args){
                JHashSet* HashSet=(JHashSet*)object;
                HashSet->readObject((JObjectInputStream*)args->at(0));
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

        JHashSet::JHashSet(jint initialCapacity, jfloat loadFactor):JAbstractSet(getClazz()){
        }

        JHashSet::JHashSet(JCollection* c):JAbstractSet(getClazz()){

        }

        JIterator* JHashSet::iterator(){
            return NULL;
        }

        jint JHashSet::size(){
            return 0;
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
            return false;
        }

        jbool JHashSet::contains(JObject* o){
            return 0;
        }

        jbool JHashSet::add(JObject* item){
            return false;
        }

        jbool JHashSet::remove(JObject* e){
            return false;
        }

        void JHashSet::clear(){
        }

        JHashSet* JHashSet::clone(){
            return NULL;
        }

        void JHashSet::writeObject(JObjectOutputStream* out){

        }

        void JHashSet::readObject(JObjectInputStream* in){

        }

        JHashSet::~JHashSet(){

        }
    }
}
