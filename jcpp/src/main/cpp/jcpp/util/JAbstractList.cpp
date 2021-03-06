#include "JAbstractList.h"
#include "JClass.h"
#include <cstdio>
#include "JInstantiationException.h"
#include "JListIterator.h"
#include "JNoSuchElementException.h"
#include "JConcurrentModificationException.h"
#include "JRandomAccess.h"
#include "JIndexOutOfBoundsException.h"
#include "JIllegalStateException.h"
#include "JUnsupportedOperationException.h"
#include "JIllegalArgumentException.h"
using namespace std;

namespace jcpp{
    namespace util{
        class JAbstractListClass : public JClass{
        public:
          JAbstractListClass(){
              this->canonicalName="java.util.AbstractList";
              this->name="java.util.AbstractList";
              this->simpleName="AbstractList";
              addInterface(JList::getClazz());
          }

          JClass* getSuperclass(){
              return JAbstractCollection::getClazz();
          }

          virtual void fillDeclaredClasses();
        };

        static JClass* clazz;

        JClass* JAbstractList::getClazz(){
            if (clazz==NULL){
                clazz=new JAbstractListClass();
            }
            return clazz;
        }

        static JClass* itrClazz;

        class JItr : public JObject ,public JIterator{
        protected:
            JAbstractList* list;
            jint cursor;
            jint lastRet;
            jint expectedModCount;

            class JAbstractListItrClass : public JClass{
            public:
              JAbstractListItrClass(){
                  this->canonicalName="java.util.AbstractList$Itr";
                  this->name="java.util.AbstractList$Itr";
                  this->simpleName="AbstractList$Itr";
                  addInterface(JIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JAbstractList::getClazz();
              }
            };

        public:

            JItr(JAbstractList* list,JClass* _class):JObject(_class){
                this->list=list;
                cursor = 0;
                lastRet = -1;
                expectedModCount = list->modCount;
            }

            JItr(JAbstractList* list):JObject(getClazz()){
                this->list=list;
                cursor = 0;
                lastRet = -1;
                expectedModCount = list->modCount;
            }

            static JClass* getClazz(){
                if (itrClazz==NULL){
                    itrClazz=new JAbstractListItrClass();
                }
                return itrClazz;
            }

            jbool hasNext() {
                return cursor != list->size();
            }

            JObject* next() {
                checkForComodification();
                try {
                    jint i=cursor;
                    JObject* next = list->get(i);
                    lastRet = i;
                    cursor=i+1;
                    return next;
                } catch (JIndexOutOfBoundsException* e) {
                    delete e;
                    checkForComodification();
                    throw new JNoSuchElementException();
                }
            }

            void remove() {
                if (lastRet <0){
                    throw new JIllegalStateException();
                }
                checkForComodification();
                try {
                    list->remove(lastRet);
                    if (lastRet < cursor){
                        cursor--;
                    }
                    lastRet = -1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* e) {
                    delete e;
                    throw new JConcurrentModificationException();
                }
            }

            void checkForComodification() {
                if (list->modCount != expectedModCount){
                    throw new JConcurrentModificationException();
                }
            }
        };

        static JClass* listItrClazz;

        class JListItr : public JItr, public JListIterator {
        protected:
            class JAbstractListListItrClass : public JClass{
            public:
              JAbstractListListItrClass(){
                  this->canonicalName="java.util.AbstractList$ListItr";
                  this->name="java.util.AbstractList$ListItr";
                  this->simpleName="AbstractList$ListItr";
                  addInterface(JListIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JItr::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JAbstractList::getClazz();
              }
            };

        public:

            JListItr(JAbstractList* list,jint index) : JItr(list,getClazz()){
                cursor = index;
            }

            static JClass* getClazz(){
                if (listItrClazz==NULL){
                    listItrClazz=new JAbstractListListItrClass();
                }
                return listItrClazz;
            }

            jbool hasNext(){
                return JItr::hasNext();
            }

            JObject* next(){
                return JItr::next();
            }

            void remove(){
                JItr::remove();
            }

            jbool hasPrevious() {
                return cursor != 0;
            }

            JObject* previous() {
                checkForComodification();
                try {
                    jint i = cursor - 1;
                    JObject* previous = list->get(i);
                    lastRet = cursor = i;
                    return previous;
                } catch (JIndexOutOfBoundsException* e) {
                    delete e;
                    checkForComodification();
                    throw new JNoSuchElementException();
                }
            }

            jint nextIndex() {
                return cursor;
            }

            jint previousIndex() {
                return cursor-1;
            }

            void set(JObject* e) {
                if (lastRet<0){
                    throw new JIllegalStateException();
                }
                checkForComodification();
                try {
                    list->set(lastRet, e);
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    delete ex;
                    throw new JConcurrentModificationException();
                }
            }

            void add(JObject* e) {
                checkForComodification();
                try {
                    jint i=cursor;
                    list->add(i, e);
                    lastRet = -1;
                    cursor=i+1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    delete ex;
                    throw new JConcurrentModificationException();
                }
            }
        };

        static JClass* subListClazz;
        class JSubList : public JAbstractList {
        protected:
            JAbstractList* l;
            jint offset;
            jint isize;
            jint expectedModCount;

            class JSubListClass : public JClass{
            public:
              JSubListClass(){
                  this->canonicalName="java.util.SubList";
                  this->name="java.util.SubList";
                  this->simpleName="SubList";
              }

              JClass* getSuperclass(){
                  return JAbstractList::getClazz();
              }

              virtual void fillDeclaredClasses();
            };

        public:

            static JClass* getClazz(){
                if (subListClazz==NULL){
                    subListClazz=new JSubListClass();
                }
                return subListClazz;
            }

            JSubList(JAbstractList* list, jint fromIndex, jint toIndex) : JAbstractList(getClazz()){
                if (fromIndex < 0){
                    throw new JIndexOutOfBoundsException();
                }
                if (toIndex > list->size()){
                    throw new JIndexOutOfBoundsException();
                }
                if (fromIndex > toIndex){
                    throw new JIllegalArgumentException();
                }
                l = list;
                offset = fromIndex;
                isize = toIndex - fromIndex;
                expectedModCount = l->modCount;
            }

            JSubList(JClass* _class,JAbstractList* list, jint fromIndex, jint toIndex) : JAbstractList(_class){
                if (fromIndex < 0){
                    throw new JIndexOutOfBoundsException();
                }
                if (toIndex > list->size()){
                    throw new JIndexOutOfBoundsException();
                }
                if (fromIndex > toIndex){
                    throw new JIllegalArgumentException();
                }
                l = list;
                offset = fromIndex;
                isize = toIndex - fromIndex;
                expectedModCount = l->modCount;
            }

            JObject* set(jint index, JObject* element) {
                rangeCheck(index);
                checkForComodification();
                return l->set(index+offset, element);
            }

            JObject* get(jint index) {
                rangeCheck(index);
                checkForComodification();
                return l->get(index+offset);
            }

            jint size() {
                checkForComodification();
                return isize;
            }

            void incrementSize(){
                isize++;
            }

            void decrementSize(){
                isize--;
            }

            void setExpectedModCount(jint expectedModCount){
                this->expectedModCount=expectedModCount;
            }

            void add(jint index, JObject* element) {
                if (index<0 || index>isize){
                    throw new JIndexOutOfBoundsException();
                }
                checkForComodification();
                l->add(index+offset, element);
                expectedModCount = l->modCount;
                isize++;
                modCount++;
            }

            JObject* remove(jint index) {
                rangeCheck(index);
                checkForComodification();
                JObject* result = l->remove(index+offset);
                expectedModCount = l->modCount;
                isize--;
                modCount++;
                return result;
            }

            void removeRange(jint fromIndex, jint toIndex) {
                checkForComodification();
                l->removeRange(fromIndex+offset, toIndex+offset);
                expectedModCount = l->modCount;
                isize -= (toIndex-fromIndex);
                modCount++;
            }

            jbool addAll(JCollection* c) {
                return addAll(isize, c);
            }

            jbool addAll(jint index, JCollection* c) {
                if (index<0 || index>isize){
                    throw new JIndexOutOfBoundsException();
                }
                jint cSize = c->size();
                if (cSize==0){
                    return false;
                }
                checkForComodification();
                l->addAll(offset+index, c);
                expectedModCount = l->modCount;
                isize += cSize;
                modCount++;
                return true;
            }

            JIterator* iterator() {
                return JAbstractList::listIterator();
            }

            JListIterator* listIterator(jint index);

            JList* subList(jint fromIndex, jint toIndex) {
                return new JSubList(this, fromIndex, toIndex);
            }

            void rangeCheck(jint index) {
                if (index<0 || index>=isize){
                    throw new JIndexOutOfBoundsException();
                }
            }

            void checkForComodification() {
                if (l->modCount != expectedModCount){
                    throw new JConcurrentModificationException();
                }
            }
        };

        static JClass* randomAccessSubListClazz;
        class JRandomAccessSubList: public JSubList, public JRandomAccess {
        protected:
            class JRandomAccessSubListClass : public JClass{

            public:
              JRandomAccessSubListClass(){
                  this->canonicalName="java.util.RandomAccessSubList";
                  this->name="java.util.RandomAccessSubList";
                  this->simpleName="RandomAccessSubList";
                  addInterface(JRandomAccess::getClazz());
              }

              JClass* getSuperclass(){
                  return JSubList::getClazz();
              }
            };

        public:
            JRandomAccessSubList(JAbstractList* list, jint fromIndex, jint toIndex) : JSubList(getClazz(),list,fromIndex,toIndex){
            }

            static JClass* getClazz(){
                if (randomAccessSubListClazz==NULL){
                    randomAccessSubListClazz=new JRandomAccessSubListClass();
                }
                return randomAccessSubListClazz;
            }

            JList* subList(jint fromIndex, jint toIndex) {
                return new JRandomAccessSubList(this, fromIndex, toIndex);
            }
        };

        static JClass* listIteratorClazzImpl;

        class JListIteratorImpl : public JListIterator, public JObject {
            protected:
                class JListIteratorImplClass : public JClass{

                public:
                  JListIteratorImplClass(){
                      this->canonicalName="java.util.SubList$ListIterator";
                      this->name="java.util.SubList$ListIterator";
                      this->simpleName="SubList$ListIterator";
                  }

                  JClass* getSuperclass(){
                      return JObject::getClazz();
                  }

                  virtual JClass* getDeclaringClass(){
                      return JSubList::getClazz();
                  }
                };

                JSubList* l;
                JListIterator* i;
                jint index;
                jint offset;

            public:
                static JClass* getClazz(){
                    if (listIteratorClazzImpl==NULL){
                        listIteratorClazzImpl=new JListIteratorImplClass();
                    }
                    return listIteratorClazzImpl;
                }

                JListIteratorImpl(JSubList* l,jint index,jint offset):JObject(getClazz()){
                    this->l=l;
                    this->index=index;
                    this->offset=offset;
                    i= l->listIterator(index+offset);
                }

                bool hasNext() {
                    return nextIndex() < l->size();
                }

                JObject* next() {
                    if (hasNext()){
                        return i->next();
                    }else{
                        throw new JNoSuchElementException();
                    }
                }

                bool hasPrevious() {
                    return previousIndex() >= 0;
                }

                JObject* previous() {
                    if (hasPrevious()){
                        return i->previous();
                    }else{
                        throw new JNoSuchElementException();
                    }
                }

                jint nextIndex() {
                    return i->nextIndex() - offset;
                }

                jint previousIndex() {
                    return i->previousIndex() - offset;
                }

                void remove() {
                    i->remove();
                    l->setExpectedModCount(l->modCount);
                    l->decrementSize();
                }

                void set(JObject* e) {
                    i->set(e);
                }

                void add(JObject* e) {
                    i->add(e);
                    l->setExpectedModCount(l->modCount);
                    l->incrementSize();
                }

                ~JListIteratorImpl(){
                    delete i;
                }
        };

        void JSubList::JSubListClass::fillDeclaredClasses(){
            addDeclaredClass(JListIteratorImpl::getClazz());
        }

        JListIterator* JSubList::listIterator(jint index) {
            checkForComodification();
            if (index<0 || index>isize){
                throw new JIndexOutOfBoundsException();
            }
            return new JListIteratorImpl(this,index,offset);
        }

        JAbstractList::JAbstractList(JClass* _class):JAbstractCollection(_class){
            this->modCount=0;
        }

        jbool JAbstractList::isEmpty(){
            return JAbstractCollection::isEmpty();
        }

        jbool JAbstractList::add(JObject* e){
            add(size(), e);
            return true;
        }

        JObject* JAbstractList::set(jint, JObject*){
            throw new JUnsupportedOperationException();
        }

        void JAbstractList::add(jint, JObject*){
            throw new JUnsupportedOperationException();
        }

        jbool JAbstractList::remove(JObject* o){
            return JAbstractCollection::remove(o);
        }

        JObject* JAbstractList::remove(jint){
            throw new JUnsupportedOperationException();
        }

        jbool JAbstractList::contains(JObject* o){
            return JAbstractCollection::contains(o);
        }

        jbool JAbstractList::containsAll(JCollection* c){
            return JAbstractCollection::containsAll(c);
        }

        jbool JAbstractList::removeAll(JCollection* c){
            return JAbstractCollection::removeAll(c);
        }

        jbool JAbstractList::retainAll(JCollection* c){
            return JAbstractCollection::retainAll(c);
        }

        jint JAbstractList::indexOf(JObject* o){
            JListIterator* e = listIterator();
            if (o==NULL) {
                while (e->hasNext()){
                    if (e->next()==NULL){
                        jint index=e->previousIndex();
                        delete e;
                        return index;
                    }
                }
            } else {
                while (e->hasNext()){
                    if (o->equals(e->next())){
                        jint index=e->previousIndex();
                        delete e;
                        return index;
                    }
                }
            }
            delete e;
            return -1;
        }

        jint JAbstractList::lastIndexOf(JObject* o){
            JListIterator* e = listIterator(size());
            if (o==NULL) {
                while (e->hasPrevious()){
                    if (e->previous()==NULL){
                        jint index=e->nextIndex();
                        delete e;
                        return index;
                    }
                }
            } else {
                while (e->hasPrevious()){
                    if (o->equals(e->previous())){
                        jint index=e->nextIndex();
                        delete e;
                        return index;
                    }
                }
            }
            delete e;
            return -1;
        }

        void JAbstractList::clear(){
            removeRange(0, size());
        }

        jbool JAbstractList::addAll(jint index, JCollection* c){
            jbool modified = false;
            JIterator* e = c->iterator();
            while (e->hasNext()) {
                add(index++, e->next());
                modified = true;
            }
            delete e;
            return modified;
        }

        JPrimitiveArray* JAbstractList::toArray(){
            return JAbstractCollection::toArray();
        }

        JIterator* JAbstractList::iterator() {
            return new JItr(this);
        }

        JListIterator* JAbstractList::listIterator() {
            return listIterator(0);
        }

        JListIterator* JAbstractList::listIterator(jint index){
            if (index<0 || index>size()){
              throw new JIndexOutOfBoundsException("Index: "+index);
            }
            return new JListItr(this,index);
        }

        JList* JAbstractList::subList(jint fromIndex, jint toIndex){
            if (JRandomAccess::getClazz()->isAssignableFrom(getClass())){
                return new JRandomAccessSubList(this,fromIndex,toIndex);
            }
            return new JSubList(this,fromIndex,toIndex);
        }

        jbool JAbstractList::equals(JObject* o){
            if (o == this){
                return true;
            }
            if (!JList::getClazz()->isAssignableFrom(o->getClass())){
                return false;
            }
            JListIterator* e1 = listIterator();
            JList* l2=dynamic_cast<JList*>(o);
            JListIterator* e2 = l2->listIterator();
            while (e1->hasNext() && e2->hasNext()) {
                JObject* o1 = e1->next();
                JObject* o2 = e2->next();
                if (!(o1==NULL ? o2==NULL : o1->equals(o2))){
                    delete e1;
                    delete e2;
                    return false;
                }
            }
            jbool eq=!(e1->hasNext() || e2->hasNext());
            delete e1;
            delete e2;
            return eq;
        }

        jint JAbstractList::hashCode(){
            jint h = 1;
            JIterator* i = iterator();
            while (i->hasNext()) {
                JObject* obj = i->next();
                h = 31*h + (obj==NULL ? 0 : obj->hashCode());
            }
            delete i;
            return h;
        }

        void JAbstractList::removeRange(jint fromIndex, jint toIndex){
            JListIterator* it = listIterator(fromIndex);
            for (jint i=0, n=toIndex-fromIndex; i<n; i++) {
                it->next();
                it->remove();
            }
            delete it;
        }

        void JAbstractListClass::fillDeclaredClasses(){
            addDeclaredClass(JItr::getClazz());
            addDeclaredClass(JListItr::getClazz());
        }

        JAbstractList::~JAbstractList(){
        }
    }
}
