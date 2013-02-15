#include "JArrayList.h"
#include "JClass.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JArrayListClass : public JClass{

            static JObject* invokeWriteObject(JObject* object,vector<JObject*>* args){
                JArrayList* arrayList=(JArrayList*)object;
                arrayList->writeObject((JObjectOutputStream*)args->at(0));
                return NULL;
            }

            static JObject* invokeReadObject(JObject* object,vector<JObject*>* args){
                JArrayList* arrayList=(JArrayList*)object;
                arrayList->readObject((JObjectInputStream*)args->at(0));
                return NULL;
            }

            static JObject* staticGetSize(JObject* object){
                JArrayList* s=(JArrayList*)object;
                return s->getPSize();
            }

            static void staticSetSize(JObject* object,JObject* value){
                JArrayList* s=(JArrayList*)object;
                s->setPSize((JPrimitiveInt*)value);
            }

        public:
          JArrayListClass(){
              this->canonicalName="java.util.ArrayList";
              this->name="java.util.ArrayList";
              this->simpleName="ArrayList";
              this->serialVersionUID=8683452581122892189ULL;
              addInterface(JSerializable::getClazz());
              vector<JClass*>* paramType=new vector<JClass*>();
              paramType->push_back(JObjectInputStream::getClazz());
              addMethod(new JMethod("readObject",this,JVoid::getClazz(),paramType,invokeReadObject));
              paramType=new vector<JClass*>;
              paramType->push_back(JObjectOutputStream::getClazz());
              addMethod(new JMethod("writeObject",this,JVoid::getClazz(),paramType,invokeWriteObject));
              addField(new JField("size",JPrimitiveInt::getClazz(),staticGetSize,staticSetSize));
          }

          JClass* getSuperclass(){
              return JAbstractList::getClazz();
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

        JArrayList::JArrayList(int initialCapacity):JAbstractList(getClazz()){
            items=new vector<JObject*>();
            size=new JPrimitiveInt(0);
        }

        bool JArrayList::operator==(JObject &other){
            if (other.getClass()!=getClass()){
                return false;
            }
            JArrayList* s=dynamic_cast<JArrayList*>(&other);
            if (s->getSize()!=getSize()){
                return false;
            }
            for (int i=0;i<getSize();i++){
                if (!((*get(i))==(*s->get(i)))){
                    return false;
                }
            }
            return true;
        }

        jint JArrayList::getSize(){
            return items->size();
        }

        void JArrayList::setPSize(JPrimitiveInt* s){//TODO do something on the vector, clean it
            delete size;
            size=s;
        }

        JPrimitiveInt* JArrayList::getPSize(){
            return size;
        }

        bool JArrayList::isEmpty(){
            return items->empty();
        }

        JObject* JArrayList::get(int index){
            return items->at(index);
        }

        void JArrayList::add(JObject* item){
            items->push_back(item);
            size->set(size->get()+1);
        }

        void JArrayList::add(int index,JObject* item){
            //TODO
        }

        JObject* JArrayList::remove(int index){
            return NULL;//TODO
        }

        bool JArrayList::remove(JObject* e){
            return false;//TODO
        }

        void JArrayList::clear(){
            items->clear();
            size->set(0);
        }

        void JArrayList::writeObject(JObjectOutputStream* out){
            out->defaultWriteObject();
            out->flush();
            out->writeInt(size);
            out->flush();
            for (unsigned int i=0;i<items->size();i++){
                out->flush();
                out->writeObject(items->at(i));
                out->flush();
            }
            out->flush();
        }

        void JArrayList::readObject(JObjectInputStream* in){
            in->defaultReadObject();
            JPrimitiveInt* arrayLength = in->readPrimitiveInt();
            delete size;
            delete items;
            size=arrayLength;
            items=new vector<JObject*>();
            for (int i=0;i<size->get();i++){
                items->push_back(in->readObject());
            }
        }

        JArrayList::~JArrayList(){
            delete items;
            delete size;
        }
    }
}
