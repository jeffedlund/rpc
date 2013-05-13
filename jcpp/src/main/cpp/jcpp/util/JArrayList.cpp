#include "JArrayList.h"
#include "JClass.h"
#include <cstdio>
#include "Collections.h"
#include "JNoSuchElementException.h"
#include "JConcurrentModificationException.h"
#include "Object.h"
#include "JVoid.h"
#include "JIllegalStateException.h"
#include "JIndexOutOfBoundsException.h"
#include "JIllegalArgumentException.h"

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
                return s->isize;
            }

            static void staticSetSize(JObject* object,JObject* value){
                JArrayList* s=(JArrayList*)object;
                delete s->isize;
                s->isize=(JPrimitiveInt*)value;
            }

        public:
          JArrayListClass(){
              this->canonicalName="java.util.ArrayList";
              this->name="java.util.ArrayList";
              this->simpleName="ArrayList";
              this->serialVersionUID=8683452581122892189ULL;
              addInterface(JList::getClazz());
              addInterface(JSerializable::getClazz());
              addInterface(JRandomAccess::getClazz());
              addInterface(JCloneable::getClazz());
              vector<JClass*>* paramType=new vector<JClass*>();
              paramType->push_back(JObjectInputStream::getClazz());
              addMethod(new JMethod("readObject",this,JVoid::getClazz(),paramType,invokeReadObject));
              paramType=new vector<JClass*>;
              paramType->push_back(JObjectOutputStream::getClazz());
              addMethod(new JMethod("writeObject",this,JVoid::getClazz(),paramType,invokeWriteObject));
              addField(new JField("size",JPrimitiveInt::getClazz(),this,staticGetSize,staticSetSize));
          }

          JClass* getSuperclass(){
              return JAbstractList::getClazz();
          }

          JObject* newInstance(){
              return new JArrayList();
          }

          virtual void fillDeclaredClasses();
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
            modCount++;
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
            modCount++;
            return true;
        }

        void JArrayList::add(int index,JObject* o){
            vector<JObject*>::iterator iterator1=items->begin();
            items->insert(iterator1+index , o);
            isize->set(isize->get()+1);
            modCount++;
        }

        JObject* JArrayList::remove(int index){
            JObject* o=items->at(index);
            remove(o);
            return o;
        }

        bool JArrayList::remove(JObject* e){
            modCount++;
            bool b=deleteFromVector(items,e);
            isize->set(items->size());
            return b;
        }

        void JArrayList::clear(){
            modCount++;
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

        JPrimitiveArray* JArrayList::toArray(){
            return JAbstractList::toArray();
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
            in->readPrimitiveInt();
            delete items;
            items=new vector<JObject*>();
            for (int i=0;i<isize->get();i++){
                items->push_back(in->readObject());
            }
        }

        static JClass* arrayListItrClazz;
        class JArrayListItr : public JIterator, public JObject {
        protected:
            class JArrayListItrClass : public JClass{
            public:
              JArrayListItrClass(){
                  this->canonicalName="java.util.ArrayList$Itr";
                  this->name="java.util.ArrayList$Itr";
                  this->simpleName="ArrayList$Itr";
                  addInterface(JIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JArrayList::getClazz();
              }
            };

            JArrayList* list;
            jint cursor;
            jint lastRet;
            jint expectedModCount;

            JArrayListItr(JArrayList* list,JClass* _class):JObject(_class){
                this->list=list;
                this->cursor=0;
                this->lastRet=-1;
                this->expectedModCount=list->modCount;
            }

        public:
            JArrayListItr(JArrayList* list):JObject(getClazz()){
                this->list=list;
                this->cursor=0;
                this->lastRet=-1;
                this->expectedModCount=list->modCount;
            }

            static JClass* getClazz(){
                if (arrayListItrClazz==NULL){
                    arrayListItrClazz=new JArrayListItrClass();
                }
                return arrayListItrClazz;
            }

            jbool hasNext() {
                return cursor != list->size();
            }

            JObject* next() {
                checkForComodification();
                jint i = cursor;
                if (i >= list->size()){
                    throw new JNoSuchElementException();
                }
                cursor = i + 1;
                return list->get(lastRet = i);
            }

            void remove() {
                if (lastRet < 0){
                    throw new JIllegalStateException();
                }
                checkForComodification();
                try {
                    list->remove(lastRet);
                    cursor = lastRet;
                    lastRet = -1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            void checkForComodification() {
                if (list->modCount != expectedModCount){
                    throw new JConcurrentModificationException();
                }
            }
        };

        static JClass* arrayListListItrClazz;
        class JArrayListListItr : public JArrayListItr , public JListIterator {
        protected:
            class JArrayListListItrClass : public JClass{
            public:
              JArrayListListItrClass(){
                  this->canonicalName="java.util.ArrayList$ListItr";
                  this->name="java.util.ArrayList$ListItr";
                  this->simpleName="ArrayList$ListItr";
                  addInterface(JListIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JArrayListItr::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JArrayList::getClazz();
              }
            };

        public:
            static JClass* getClazz(){
                if (arrayListListItrClazz==NULL){
                    arrayListListItrClazz=new JArrayListListItrClass();
                }
                return arrayListListItrClazz;
            }

            JArrayListListItr(JArrayList* list,jint index):JArrayListItr(list,getClazz()){
                cursor = index;
            }

            jbool hasNext(){
                return JArrayListItr::hasNext();
            }

            JObject* next(){
                return JArrayListItr::next();
            }

            jbool hasPrevious() {
                return cursor != 0;
            }

            jint nextIndex() {
                return cursor;
            }

            jint previousIndex() {
                return cursor - 1;
            }

            JObject* previous() {
                checkForComodification();
                jint i = cursor - 1;
                if (i < 0){
                    throw new JNoSuchElementException();
                }
                cursor = i;
                return list->get(lastRet = i);
            }

            void set(JObject* e) {
                if (lastRet < 0){
                    throw new JIllegalStateException();
                }
                try {
                    list->set(lastRet, e);
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            void add(JObject* e) {
                checkForComodification();
                try {
                    jint i = cursor;
                    list->add(i, e);
                    cursor = i + 1;
                    lastRet = -1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            void remove(){
                JArrayListItr::remove();
            }
        };

        static JClass* arrayListSubListClazz;
        class JArrayListSubList : public JAbstractList, public JRandomAccess {
        protected:
            class JArrayListSubListClass : public JClass{
            public:
              JArrayListSubListClass(){
                  this->canonicalName="java.util.ArrayList$SubList";
                  this->name="java.util.ArrayList$SubList";
                  this->simpleName="ArrayList$SubList";
                  addInterface(JRandomAccess::getClazz());
              }

              JClass* getSuperclass(){
                  return JAbstractList::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JArrayList::getClazz();
              }

              virtual void fillDeclaredClasses();
            };

            JArrayList* list;
            JAbstractList* parent;
            jint parentOffset;
            jint offset;
            jint isize;
            friend class JArrayListSubListIterator;
        public:
            static JClass* getClazz(){
                if (arrayListSubListClazz==NULL){
                    arrayListSubListClazz=new JArrayListSubListClass();
                }
                return arrayListSubListClazz;
            }

            JArrayListSubList(JArrayList* list,JAbstractList* parent, jint offset, jint fromIndex, jint toIndex) : JAbstractList(getClazz()){
                this->list=list;
                this->parent = parent;
                this->parentOffset = fromIndex;
                this->offset = offset + fromIndex;
                this->isize = toIndex - fromIndex;
                this->modCount = list->modCount;
            }

            JObject* set(jint index, JObject* e) {
                rangeCheck(index);
                checkForComodification();
                JObject* oldValue = list->get(offset + index);
                list->set(offset + index,e);
                return oldValue;
            }

            JObject* get(jint index) {
                rangeCheck(index);
                checkForComodification();
                return list->get(offset + index);
            }

            jint size() {
                checkForComodification();
                return isize;
            }

            void add(jint index, JObject* e) {
                rangeCheckForAdd(index);
                checkForComodification();
                parent->add(parentOffset + index, e);
                modCount = parent->modCount;
                isize++;
            }

            JObject* remove(jint index) {
                rangeCheck(index);
                checkForComodification();
                JObject* result = parent->remove(parentOffset + index);
                this->modCount = parent->modCount;
                isize--;
                return result;
            }

            void removeRange(jint fromIndex, jint toIndex) {
                checkForComodification();
                parent->removeRange(parentOffset + fromIndex,parentOffset + toIndex);
                this->modCount = parent->modCount;
                this->isize -= toIndex - fromIndex;
            }

            jbool addAll(JCollection* c) {
                return addAll(isize, c);
            }

            jbool addAll(jint index, JCollection* c) {
                rangeCheckForAdd(index);
                jint cSize = c->size();
                if (cSize==0){
                    return false;
                }
                checkForComodification();
                parent->addAll(parentOffset + index, c);
                modCount = parent->modCount;
                isize += cSize;
                return true;
            }

            JIterator* iterator() {
                return listIterator();
            }

            JListIterator* listIterator() {
                return JAbstractList::listIterator();
            }

            JListIterator* listIterator(jint index);

            JList* subList(jint fromIndex, jint toIndex) {
                return new JArrayListSubList(list,this, offset, fromIndex, toIndex);
            }

            void rangeCheck(jint index) {
                if (index < 0 || index >= isize){
                    throw new JIndexOutOfBoundsException(outOfBoundsMsg(index));
                }
            }

            void rangeCheckForAdd(jint index) {
                if (index < 0 || index > isize){
                    throw new JIndexOutOfBoundsException(outOfBoundsMsg(index));
                }
            }

            JString outOfBoundsMsg(jint index) {
                JString s="Index: ";
                s<<index<<", Size: "<<isize;
                return s;
            }

            void checkForComodification() {
                if (list->modCount != this->modCount)
                    throw new JConcurrentModificationException();
            }
        };


        static JClass* arrayListSubListListIteratorClazz;
        class JArrayListSubListIterator : public JObject, public JListIterator {
        protected:
            JArrayList* list;
            JArrayListSubList* sublist;
            jint cursor;
            jint lastRet;
            jint expectedModCount;
            jint offset;

            class JArrayListSubListListIteratorClass : public JClass{
            public:
              JArrayListSubListListIteratorClass(){
                  this->canonicalName="java.util.ArrayList$SubList$ListIterator";
                  this->name="java.util.ArrayList$SubList$ListIterator";
                  this->simpleName="ArrayList$SubList$ListIterator";
                  addInterface(JListIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JArrayListSubList::getClazz();
              }
            };

        public:
            static JClass* getClazz(){
                if (arrayListSubListListIteratorClazz==NULL){
                    arrayListSubListListIteratorClazz=new JArrayListSubListListIteratorClass();
                }
                return arrayListSubListListIteratorClazz;
            }

            JArrayListSubListIterator(JArrayList* list,JArrayListSubList* sublist,jint index,jint offset):JObject(getClazz()){
                this->list=list;
                this->sublist=sublist;
                cursor = index;
                this->offset=offset;
                lastRet = -1;
                expectedModCount = list->modCount;
            }

            jbool hasNext() {
                return cursor != sublist->size();
            }

            JObject* next() {
                checkForComodification();
                jint i = cursor;
                if (i >= sublist->size()){
                    throw new JNoSuchElementException();
                }
                cursor = i + 1;
                return list->get(offset + (lastRet = i));
            }

            jbool hasPrevious() {
                return cursor != 0;
            }

            JObject* previous() {
                checkForComodification();
                jint i = cursor - 1;
                if (i < 0){
                    throw new JNoSuchElementException();
                }
                cursor = i;
                return list->get(offset + (lastRet = i));
            }

            jint nextIndex() {
                return cursor;
            }

            jint previousIndex() {
                return cursor - 1;
            }

            void remove() {
                if (lastRet < 0){
                    throw new JIllegalStateException();
                }
                checkForComodification();
                try {
                    sublist->remove(lastRet);
                    cursor = lastRet;
                    lastRet = -1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            void set(JObject* e) {
                if (lastRet < 0){
                    throw new JIllegalStateException();
                }
                checkForComodification();
                try {
                    list->set(offset + lastRet, e);
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            void add(JObject* e) {
                checkForComodification();

                try {
                    jint i = cursor;
                    sublist->add(i, e);
                    cursor = i + 1;
                    lastRet = -1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            void checkForComodification() {
                if (expectedModCount != list->modCount){
                    throw new JConcurrentModificationException();
                }
            }
        };

        void JArrayListSubList::JArrayListSubListClass::fillDeclaredClasses(){
            addDeclaredClass(JArrayListSubListIterator::getClazz());
        }

        JListIterator* JArrayListSubList::listIterator(jint index) {
            checkForComodification();
            rangeCheckForAdd(index);
            return new JArrayListSubListIterator(list,this,index,this->offset);
        }

        JListIterator* JArrayList::listIterator(){
            return new JArrayListListItr(this,0);
        }

        JIterator* JArrayList::iterator(){
            return new JArrayListItr(this);
        }

        JList* JArrayList::subList(jint fromIndex, jint toIndex){
            if (fromIndex < 0){
                throw new JIndexOutOfBoundsException(JString("fromIndex = ")+fromIndex);
            }
            if (toIndex > size()){
                throw new JIndexOutOfBoundsException(JString("toIndex = ")+ toIndex);
            }
            if (fromIndex > toIndex){
                throw new JIllegalArgumentException(JString("fromIndex(")+ fromIndex +") > toIndex("+ toIndex + ")");
            }
            return new JArrayListSubList(this,this, 0, fromIndex, toIndex);
        }

        void JArrayListClass::fillDeclaredClasses(){
            addDeclaredClass(JArrayListItr::getClazz());
            addDeclaredClass(JArrayListListItr::getClazz());
            addDeclaredClass(JArrayListSubList::getClazz());
        }

        JArrayList::~JArrayList(){
            delete items;
            delete isize;
        }
    }
}
