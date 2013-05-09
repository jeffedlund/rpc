#include "JVector.h"
#include "JClass.h"
#include <cstdio>
#include "Collections.h"
#include "JArrayIndexOutOfBoundsException.h"
#include "JNoSuchElementException.h"
#include <sstream>
#include "JCollections.h"
#include "JConcurrentModificationException.h"

namespace jcpp{
    namespace util{
        class JVectorClass : public JClass{

            static JObject* invokeWriteObject(JObject* object,vector<JObject*>* args){
                JVector* arrayList=(JVector*)object;
                arrayList->writeObject((JObjectOutputStream*)args->at(0));
                return NULL;
            }

            static JObject* staticGetElementCount(JObject* object){
                JVector* s=(JVector*)object;
                return s->getElementCount();
            }

            static void staticSetElementCount(JObject* object,JObject* value){
                JVector* s=(JVector*)object;
                s->setElementCount((JPrimitiveInt*)value);
            }

            static JObject* staticGetCapacityIncrement(JObject* object){
                JVector* s=(JVector*)object;
                return s->getCapacityIncrement();
            }

            static void staticSetCapacityIncrement(JObject* object,JObject* value){
                JVector* s=(JVector*)object;
                s->setCapacityIncrement((JPrimitiveInt*)value);
            }

        public:
          JVectorClass(){
              this->canonicalName="java.util.Vector";
              this->name="java.util.Vector";
              this->simpleName="Vector";
              this->serialVersionUID=-2767605614048989439ULL;
              addInterface(JSerializable::getClazz());
              addInterface(JList::getClazz());
              addInterface(JRandomAccess::getClazz());
              addInterface(JCloneable::getClazz());
              vector<JClass*>* paramType=new vector<JClass*>();
              paramType->push_back(JObjectOutputStream::getClazz());
              addMethod(new JMethod("writeObject",this,JVoid::getClazz(),paramType,invokeWriteObject));
              addField(new JField("elementCount",JPrimitiveInt::getClazz(),this,staticGetElementCount,staticSetElementCount));
              addField(new JField("capacityIncrement",JPrimitiveInt::getClazz(),this,staticGetCapacityIncrement,staticSetCapacityIncrement));
          }

          JClass* getSuperclass(){
              return JAbstractList::getClazz();
          }

          JObject* newInstance(){
              return new JVector();
          }

          virtual void fillDeclaredClasses();
        };

        static JClass* clazz;

        JClass* JVector::getClazz(){
            if (clazz==NULL){
                clazz=new JVectorClass();
            }
            return clazz;
        }

        JVector::JVector(int,int c):JAbstractList(getClazz()){
            items=new vector<JObject*>();
            elementCount=new JPrimitiveInt(0);
            capacityIncrement=new JPrimitiveInt(c);
        }

        JVector::JVector(JCollection* c):JAbstractList(getClazz()){
            items=new vector<JObject*>();
            elementCount=new JPrimitiveInt(0);
            capacityIncrement=new JPrimitiveInt(0);
            JIterator* i=c->iterator();
            while (i->hasNext()){
                add(i->next());
            }
            delete i;
        }

        void JVector::setElementCount(JPrimitiveInt* s){
            lock();
            delete elementCount;
            elementCount=s;
            unlock();
        }

        JPrimitiveInt* JVector::getElementCount(){
            return elementCount;
        }

        void JVector::setCapacityIncrement(JPrimitiveInt* s){
            lock();
            delete capacityIncrement;
            capacityIncrement=s;
            unlock();
        }

        JPrimitiveInt* JVector::getCapacityIncrement(){
            return capacityIncrement;
        }

        jint JVector::getModCount(){
            lock();
            jint i=modCount;
            unlock();
            return i;
        }

        void JVector::copyInto(JPrimitiveArray* anArray) {
            lock();
            clear();
            for (int i=0;i<anArray->size();i++){
                modCount++;
                items->push_back(anArray->get(i));
            }
            elementCount->set(items->size());
            unlock();
        }

        void JVector::trimToSize(){
            lock();
            modCount++;
            unlock();
        }

        void JVector::ensureCapacity(jint){
            lock();
            modCount++;
            unlock();
        }

        void JVector::setSize(jint s){
            lock();
            modCount++;
            if (s<elementCount->get()){
                for (int i=s;i<elementCount->get();i++){
                    items->erase(items->begin()+i);
                }
                elementCount->set(items->size());
            }
            unlock();
        }

        jint JVector::capacity(){
            jint i;
            lock();
            i=capacityIncrement->get();//TODO not extra, can be bugged
            unlock();
            return i;
        }

        jint JVector::size() {
            jint i;
            lock();
            i=elementCount->get();
            unlock();
            return i;
        }

        bool JVector::isEmpty() {
            lock();
            bool b=elementCount->get() == 0;
            unlock();
            return b;
        }

        JListIterator* JVector::listIterator(jint index){
            return JAbstractList::listIterator(index);
        }

        static JClass* enumerationImplClazz;

        class JEnumerationImpl : public JObject ,public JEnumeration{
        protected:
            JVector* v;
            jint count;

            class JEnumerationImplClass : public JClass{
            public:
              JEnumerationImplClass(){
                  this->canonicalName="java.util.Vector$Enumeration";
                  this->name="java.util.Vector$Enumeration";
                  this->simpleName="Vector$Enumeration";
                  addInterface(JEnumeration::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JVector::getClazz();
              }
            };

        public:

            JEnumerationImpl(JVector* v):JObject(getClazz()){
                this->v=v;
                count = 0;
            }

            static JClass* getClazz(){
                if (enumerationImplClazz==NULL){
                    enumerationImplClazz=new JEnumerationImplClass();
                }
                return enumerationImplClazz;
            }

            bool hasMoreElements() {
                return count < v->size();
            }

            JObject* nextElement() {
                JObject* o=NULL;
                v->lock();
                if (count < v->size()) {
                    o=v->get(count);
                    count++;
                }else{
                    v->unlock();
                    throw new JNoSuchElementException("Vector Enumeration");
                }
                v->unlock();
                return o;
            }
        };

        JEnumeration* JVector::elements() {
            return new JEnumerationImpl(this);
        }

        bool JVector::contains(JObject* o){
            return indexOf(o)>=0;
        }

        jint JVector::indexOf(JObject* o){
            return indexOf(o,0);
        }

        jint JVector::indexOf(JObject* o,jint index){
            jint r=-1;
            lock();
            if (o == NULL) {
                for (int i = index; i < elementCount->get(); i++){
                    if (items->at(i)==NULL){
                        r=i;
                        break;
                    }
                }
            } else {
                for (int i = 0; i < elementCount->get(); i++){
                    if (o->equals(items->at(i))){
                        r=i;
                        break;
                    }
                }
            }
            unlock();
            return r;
        }

        jint JVector::lastIndexOf(JObject* o){
            lock();
            jint index=elementCount->get()-1;
            jint i=lastIndexOf(o,index);
            unlock();
            return i;
        }

        jint JVector::lastIndexOf(JObject* o,jint index){
            jint r=-1;
            lock();
            if (o == NULL) {
                for (int i = index; i >= 0; i--){
                    if (items->at(i)==NULL){
                        r=i;
                        break;
                    }
                }
            } else {
                for (int i = index; i >= 0; i--){
                    if (o->equals(items->at(i))){
                        r=i;
                        break;
                    }
                }
            }
            unlock();
            return r;
        }

        JObject* JVector::elementAt(jint index) {
            JObject* r=NULL;
            lock();
            if (index >= elementCount->get()) {
                unlock();
                throw new JArrayIndexOutOfBoundsException();
            }
            r=items->at(index);
            unlock();
            return r;
        }

        JObject* JVector::firstElement() {
            JObject* r=NULL;
            lock();
            if (elementCount->get() == 0) {
                unlock();
                throw new JNoSuchElementException();
            }
            r=items->at(0);
            unlock();
            return r;
        }

        JObject* JVector::lastElement() {
            JObject* r=NULL;
            lock();
            if (elementCount->get() == 0) {
                unlock();
                throw new JNoSuchElementException();
            }
            r=items->at(elementCount->get()-1);
            unlock();
            return r;
        }

        void JVector::setElementAt(JObject* obj, jint index) {
            lock();
            if (index >= elementCount->get()) {
                unlock();
                throw new JArrayIndexOutOfBoundsException();
            }
            (*items)[index]=obj;
            unlock();
        }

        void JVector::removeElementAt(jint index) {
            lock();
            modCount++;
            if (index >= elementCount->get()) {
                unlock();
                throw new JArrayIndexOutOfBoundsException();
            }else if (index < 0) {
                unlock();
                throw new JArrayIndexOutOfBoundsException();
            }
            items->erase(items->begin()+index);
            elementCount->set(items->size());
            unlock();
        }

        void JVector::insertElementAt(JObject* obj, jint index) {
            lock();
            modCount++;
            if (index > elementCount->get()) {
                unlock();
                throw new JArrayIndexOutOfBoundsException();
            }
            items->insert(items->begin()+index,obj);
            elementCount->set(items->size());
            unlock();
        }

        void JVector::addElement(JObject* obj) {
            lock();
            modCount++;
            items->push_back(obj);
            elementCount->set(items->size());
            unlock();
        }

        bool JVector::removeElement(JObject* obj) {
            lock();
            modCount++;
            jint i = indexOf(obj);
            if (i >= 0) {
                removeElementAt(i);
                unlock();
                return true;
            }
            unlock();
            return false;
        }

        void JVector::removeAllElements() {
            lock();
            modCount++;
            items->clear();
            elementCount->set(items->size());
            unlock();
        }

        JVector* JVector::clone(){
            lock();
            JVector* list=new JVector();
            for (unsigned int i=0;i<items->size();i++){
                JObject* o=items->at(i);
                list->items->push_back(o->clone());
            }
            list->elementCount->set(elementCount->get());
            list->capacityIncrement->set(capacityIncrement->get());
            unlock();
            return list;
        }

        JPrimitiveArray* JVector::toArray(){
            lock();
            JPrimitiveArray* a=JAbstractList::toArray();
            unlock();
            return a;
        }

        JObject* JVector::get(int index){
            lock();
            JObject* o=items->at(index);
            unlock();
            return o;
        }

        JObject* JVector::set(jint index, JObject* element){
            lock();
            JObject* old=items->at(index);
            (*items)[index]=element;
            unlock();
            return old;
        }

        bool JVector::add(JObject* item){
            lock();
            modCount++;
            items->push_back(item);
            elementCount->set(elementCount->get()+1);
            unlock();
            return true;
        }

        bool JVector::remove(JObject* e){
            return removeElement(e);
        }

        void JVector::add(int index,JObject* o){
            insertElementAt(o,index);
        }

        JObject* JVector::remove(int index){
            lock();
            if (index >= elementCount->get()){
                JString ss;
                ss<<"index ="<<index<<" size="<<elementCount->get();
                unlock();
                throw new JArrayIndexOutOfBoundsException(ss);
            }
            JObject* o=items->at(index);
            items->erase(items->begin()+index);
            unlock();
            return o;
        }

        void JVector::clear(){
            removeAllElements();
        }

        bool JVector::containsAll(JCollection *c){
            lock();
            bool b=JAbstractList::containsAll(c);
            unlock();
            return b;
        }

        bool JVector::addAll(JCollection *c){
            JIterator* i=c->iterator();
            lock();
            modCount++;
            while (i->hasNext()){
                items->push_back(i->next());
            }
            elementCount->set(items->size());
            delete i;
            unlock();
            return true;
        }

        bool JVector::removeAll(JCollection *c){
            lock();
            bool b=JAbstractList::removeAll(c);
            unlock();
            return b;
        }

        bool JVector::retainAll(JCollection *c){
            lock();
            bool b=JAbstractList::retainAll(c);
            unlock();
            return b;
        }

        bool JVector::addAll(jint index,JCollection* c){
            lock();
            int i=0;
            JIterator* it=c->iterator();
            while (it->hasNext()){
                JObject* o=it->next();
                if (i>=index){
                    items->push_back(o);
                }
                i++;
            }
            delete it;
            elementCount->set(items->size());
            unlock();
            return true;
        }

        bool JVector::equals(JObject *other){
            lock();
            bool q=JAbstractList::equals(other);
            unlock();
            return q;
        }

        jint JVector::hashCode(){
            lock();
            jint h=JAbstractList::hashCode();
            unlock();
            return h;
        }

        JString JVector::toString(){
            lock();
            JString s=JAbstractList::toString();
            unlock();
            return s;
        }

        JList* JVector::subList(jint fromIndex, jint toIndex){
            return JCollections::synchronizedList(JAbstractList::subList(fromIndex,toIndex));
        }

        void JVector::removeRange(jint fromIndex, jint toIndex){
            lock();
            modCount++;
            JListIterator* it = listIterator(fromIndex);
            for (int i=0, n=toIndex-fromIndex; i<n; i++) {
                it->next();
                it->remove();
            }
            delete it;
            unlock();
        }

        void JVector::writeObject(JObjectOutputStream* out){
            lock();
            out->defaultWriteObject();
            unlock();
        }

        static JClass* vectorJItrClazz;
        class JVectorItr : public JObject, public JIterator {
        protected:
            class JVectorItrClass : public JClass{
            public:
              JVectorItrClass(){
                  this->canonicalName="java.util.Vector$Itr";
                  this->name="java.util.Vector$Itr";
                  this->simpleName="Vector$Itr";
                  addInterface(JIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JVector::getClazz();
              }
            };
            JVector* v;
            jint cursor;
            jint lastRet;
            jint expectedModCount;

            JVectorItr(JClass* _class, JVector* v):JObject(_class){
                this->v=v;
                cursor=0;
                lastRet=-1;
                this->expectedModCount=v->getModCount();
            }

        public:
            static JClass* getClazz(){
                if (vectorJItrClazz==NULL){
                    vectorJItrClazz=new JVectorItrClass();
                }
                return vectorJItrClazz;
            }

            JVectorItr(JVector* v):JObject(getClazz()){
                this->v=v;
                cursor=0;
                lastRet=-1;
                this->expectedModCount=v->modCount;
            }

            jbool hasNext() {
                return cursor != v->size();
            }

            JObject* next() {
                v->lock();
                checkForComodification();
                jint i = cursor;
                if (i >= v->size()){
                    v->unlock();
                    throw new JNoSuchElementException();
                }
                cursor = i + 1;
                JObject* o=v->get(lastRet = i);
                v->unlock();
                return o;

            }

            void remove() {
                if (lastRet == -1){
                    throw new JIllegalStateException();
                }
                v->lock();
                checkForComodification();
                v->remove(lastRet);
                expectedModCount = v->getModCount();
                cursor = lastRet;
                lastRet = -1;
                v->unlock();
            }

            void checkForComodification() {
                if (v->getModCount() != expectedModCount){
                    throw new JConcurrentModificationException();
                }
            }
        };

        static JClass* vectorListItrClazz;
        class JVectorListItr : public JVectorItr , public JListIterator {
        protected:
            class JVectorListItrClass : public JClass{
            public:
              JVectorListItrClass(){
                  this->canonicalName="java.util.Vector$ListItr";
                  this->name="java.util.Vector$ListItr";
                  this->simpleName="Vector$ListItr";
                  addInterface(JListIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JVectorItr::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JVector::getClazz();
              }
            };

        public:
            static JClass* getClazz(){
                if (vectorListItrClazz==NULL){
                    vectorListItrClazz=new JVectorListItrClass();
                }
                return vectorListItrClazz;
            }

            JVectorListItr(JVector* v, jint index):JVectorItr(getClazz(),v) {
                cursor = index;
            }

            jbool hasNext(){
                return JVectorItr::hasNext();
            }

            JObject* next(){
                return JVectorItr::next();
            }

            void remove(){
                return JVectorItr::remove();
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
                v->lock();
                checkForComodification();
                jint i = cursor - 1;
                if (i < 0){
                    v->unlock();
                    throw new JNoSuchElementException();
                }
                cursor = i;
                JObject* o=v->get(lastRet = i);
                v->unlock();
                return o;
            }

            void set(JObject* e) {
                if (lastRet == -1){
                    throw new JIllegalStateException();
                }
                v->lock();
                checkForComodification();
                v->set(lastRet, e);
                v->unlock();
            }

            void add(JObject* e) {
                jint i = cursor;
                v->lock();
                checkForComodification();
                v->add(i, e);
                expectedModCount = v->getModCount();
                cursor = i + 1;
                lastRet = -1;
                v->unlock();
            }
        };

        JListIterator* JVector::listIterator() {
            lock();
            JListIterator* l=new JVectorListItr(this,0);
            unlock();
            return l;
        }

        JIterator* JVector::iterator() {
            lock();
            JVectorItr* i=new JVectorItr(this);
            unlock();
            return i;
        }

        void JVectorClass::fillDeclaredClasses(){
            addDeclaredClass(JEnumerationImpl::getClazz());
            addDeclaredClass(JVectorItr::getClazz());
            addDeclaredClass(JVectorListItr::getClazz());
        }

        JVector::~JVector(){
            delete items;
            delete this->elementCount;
            delete this->capacityIncrement;
        }
    }
}

