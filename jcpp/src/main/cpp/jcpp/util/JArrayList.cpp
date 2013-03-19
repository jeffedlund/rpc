#include "JArrayList.h"
#include "JClass.h"
#include <cstdio>
#include "Collections.h"

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

        JArrayList::JArrayList(int):JAbstractList(getClazz()){
            items=new vector<JObject*>();
            isize=new JPrimitiveInt(0);
        }

        JArrayList::JArrayList(JCollection* c):JAbstractList(getClazz()){
            items=new vector<JObject*>();
            isize=new JPrimitiveInt(0);
            JIterator* i=c->iterator();
            while (i->hasNext()){
                add(i->next());
            }
            delete i;
        }

        jint JArrayList::size(){
            return items->size();
        }

        void JArrayList::setPSize(JPrimitiveInt* s){
            delete isize;
            isize=s;
        }

        JPrimitiveInt* JArrayList::getPSize(){
            return isize;
        }

        void JArrayList::trimToSize(){
            modCount++;
        }

        void JArrayList::ensureCapacity(jint){
            modCount++;
        }

        bool JArrayList::contains(JObject* o){
            return indexOf(o)>=0;
        }

        jint JArrayList::indexOf(JObject* o){
            if (o == NULL) {
                for (int i = 0; i < isize->get(); i++){
                    if (items->at(i)==NULL){
                        return i;
                    }
                }
            } else {
                for (int i = 0; i < isize->get(); i++){
                    if (o->equals(items->at(i))){
                        return i;
                    }
                }
            }
            return -1;
        }

        jint JArrayList::lastIndexOf(JObject* o){
            if (o == NULL) {
                for (int i = isize->get()-1; i >= 0; i--){
                    if (items->at(i)==NULL){
                        return i;
                    }
                }
            } else {
                for (int i = isize->get()-1; i >= 0; i--){
                    if (o->equals(items->at(i))){
                        return i;
                    }
                }
            }
            return -1;
        }

        JObject* JArrayList::set(jint index, JObject* element){
            JObject* old=items->at(index);
            (*items)[index]=element;
            return old;
        }

        bool JArrayList::isEmpty(){
            return items->empty();
        }

        JObject* JArrayList::get(int index){
            return items->at(index);
        }

        bool JArrayList::add(JObject* item){
            items->push_back(item);
            isize->set(isize->get()+1);
            return true;
        }

        void JArrayList::add(int index,JObject* o){
            vector<JObject*>::iterator iterator1=items->begin();
            items->insert(iterator1+index , o);
            isize->set(isize->get()+1);
        }

        JObject* JArrayList::remove(int index){
            JObject* o=items->at(index);
            remove(o);
            return o;
        }

        bool JArrayList::remove(JObject* e){
            bool b=deleteFromVector(items,e);
            isize->set(items->size());
            return b;
        }

        void JArrayList::clear(){
            items->clear();
            isize->set(0);
        }

        JArrayList* JArrayList::clone(){
            JArrayList* list=new JArrayList();
            for (unsigned int i=0;i<items->size();i++){
                JObject* o=items->at(i);
                list->items->push_back(o->clone());
            }
            list->isize->set(isize->get());
            return list;
        }

        bool JArrayList::addAll(JCollection* c){
            JIterator* i=c->iterator();
            while (i->hasNext()){
                add(i->next());
            }
            delete i;
            return true;
        }

        bool JArrayList::addAll(jint index, JCollection* c){
            int i=0;
            JIterator* it=c->iterator();
            while (it->hasNext()){
                JObject* o=it->next();
                if (i>=index){
                    add(o);
                }
                i++;
            }
            delete it;
            return true;
        }

        void JArrayList::writeObject(JObjectOutputStream* out){
            out->defaultWriteObject();
            out->writeInt(isize);
            for (unsigned int i=0;i<items->size();i++){
                out->writeObject(items->at(i));
            }
        }

        void JArrayList::readObject(JObjectInputStream* in){
            in->defaultReadObject();
            JPrimitiveInt* arrayLength = in->readPrimitiveInt();
            delete isize;
            delete items;
            isize=arrayLength;
            items=new vector<JObject*>();
            for (int i=0;i<isize->get();i++){
                items->push_back(in->readObject());
            }
        }

        JArrayList::~JArrayList(){
            delete items;
            delete isize;
        }
    }
}
