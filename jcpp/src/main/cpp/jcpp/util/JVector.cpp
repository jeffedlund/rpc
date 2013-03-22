#include "JVector.h"
#include "JClass.h"
#include <cstdio>
#include "Collections.h"
#include "JArrayIndexOutOfBoundsException.h"
#include "JNoSuchElementException.h"
#include <sstream>
#include "JCollections.h"

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
              addField(new JField("elementCount",JPrimitiveInt::getClazz(),staticGetElementCount,staticSetElementCount));
              addField(new JField("capacityIncrement",JPrimitiveInt::getClazz(),staticGetCapacityIncrement,staticSetCapacityIncrement));
          }

          JClass* getSuperclass(){
              return JAbstractList::getClazz();
          }

          JObject* newInstance(){
              return new JVector();
          }
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

        JIterator* JVector::iterator(){
            return JAbstractList::iterator();
        }

        JListIterator* JVector::listIterator(){
            return JAbstractList::listIterator();
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

              JObject* newInstance(){
                  throw new JInstantiationException("cannot instantiate object of class "+getName());
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
            jint index=elementCount->get()-1;//mayeb bugged ...
            unlock();
            return lastIndexOf(o,index);
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
                throw new JNoSuchElementException();
            }
            r=items->at(elementCount->get()-1);
            unlock();
            return r;
        }

        void JVector::setElementAt(JObject* obj, jint index) {
            lock();
            if (index >= elementCount->get()) {
                throw new JArrayIndexOutOfBoundsException();
            }
            (*items)[index]=obj;
            unlock();
        }

        void JVector::removeElementAt(jint index) {
            lock();
            modCount++;
            if (index >= elementCount->get()) {
                throw new JArrayIndexOutOfBoundsException();
            }else if (index < 0) {
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
                removeElementAt(i);//TODO bug because of the lock
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
                stringstream ss;
                ss<<"index ="<<index<<" size="<<elementCount->get();
                throw new JArrayIndexOutOfBoundsException(ss.str());
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

        string JVector::toString(){
            lock();
            string s=JAbstractList::toString();
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

        JVector::~JVector(){
            delete items;
            delete this->elementCount;
            delete this->capacityIncrement;
        }
    }
}

