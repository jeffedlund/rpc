#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <vector>
#include "JObject.h"
using namespace std;
using namespace jcpp::lang;

//TODO maybe put in JCollections?
namespace jcpp{
    namespace util{
        template <class T>
        void deleteVectorOfPointers(T *vector) {
            if (vector!=NULL){
              typename T::iterator i;
              for (i = vector->begin(); i < vector->end(); ++i) {
                  if ((*i)!=NULL){
                    delete *i;
                  }
              }
              delete vector;
            }
        }

        template <class E>
        jbool deleteFromVector(vector<E*>* v, E* e) {
            if (v!=NULL){
              JObject* oe=dynamic_cast<JObject*>(e);
              typename vector<E*>::iterator i;
              for (i = v->begin(); i < v->end(); ++i) {
                  E* el=(*i);
                  JObject* o=dynamic_cast<JObject*>(el);
                  if ((*o)==(*oe)){
                      v->erase(i);
                      return true;
                  }
              }
            }
            return false;
        }

        template<class K,class V>
        void deleteMapOfValuePointer(map<K,V*>* elements){
            typename map<K,V*>::iterator i;
            for(i = elements->begin(); i != elements->end(); ++i){
                delete (*i).second;
            }
            delete elements;
        }

        template<class K,class V,class Z>
        void deleteMapOfValuePointer(map<K,V*,Z>* elements){
            typename map<K,V*,Z>::iterator i;
            for(i = elements->begin(); i != elements->end(); ++i){
                delete (*i).second;
            }
            delete elements;
        }

        template<class K, class V>
        V* getFromMap(map<K,V*>* elements, K k){
            typename map<K,V*>::iterator i;
            i= elements->find(k);
            if (i!=elements->end()){
                return (*i).second;
            }else{
                return NULL;
            }
        }

        template<class K, class V>
        V getFromMap(map<K,V>* elements, K k, V defaultNull){
            typename map<K,V>::iterator i;
            i= elements->find(k);
            if (i!=elements->end()){
                return (*i).second;
            }else{
                return defaultNull;
            }
        }

        template<class K, class V>
        V* getFromMap(map<K*,V*>* elements, K* k){
            typename map<K*,V*>::iterator i;
            i= elements->find(k);
            if (i!=elements->end()){
                return (*i).second;
            }else{
                return NULL;
            }
        }

        template<class K, class V, class Z>
        V* getFromMap(map<K,V*,Z>* elements, K k){
            typename map<K,V*,Z>::iterator i;
            i= elements->find(k);
            if (i!=elements->end()){
                return (*i).second;
            }else{
                return NULL;
            }
        }

        template<class K, class V, class Z>
        V* getFromMap(map<K,V*,Z>* elements, K* k){
            typename map<K,V*,Z>::iterator i;
            i= elements->find(k);
            if (i!=elements->end()){
                return (*i).second;
            }else{
                return NULL;
            }
        }

        template<class K, class V, class Z>
        V* getAndDeleteFromMap(map<K*,V*,Z>* elements, K* k){
            typename map<K*,V*,Z>::iterator i;
            i= elements->find(k);
            if (i!=elements->end()){
                V* v=(*i).second;
                elements->erase(k);
                return v;
            }else{
                return NULL;
            }
        }

        template<class K, class V, class Z>
        jbool hasValueFromMap(map<K*,V*,Z>* elements, V* v){
            typename map<K*,V*,Z>::iterator i;
            for(i = elements->begin(); i != elements->end(); ++i){
                if (v==NULL){
                    if ((*i).second==NULL){
                        return true;
                    }
                }else if ((*v)==(*(*i).second)){
                    return true;
                }
            }
            return false;
        }

        template<class K, class V>
        vector<V*>* getValues(map<K,V*>* elements){
            vector<V*>* vec=new vector<V*>();
            typename map<K,V*>::iterator i;
            for(i = elements->begin(); i != elements->end(); ++i){
                vec->push_back((*i).second);
            }
            return vec;
        }

        template<class K, class V,class Z>
        vector<V*>* getValues(map<K,V*,Z>* elements){
            vector<V*>* vec=new vector<V*>();
            typename map<K,V*,Z>::iterator i;
            for(i = elements->begin(); i != elements->end(); ++i){
                vec->push_back((*i).second);
            }
            return vec;
        }

        template<class K, class V>
        vector<K>* getKeys(map<K,V*>* elements){
            vector<K>* vec=new vector<K>();
            typename map<K,V*>::iterator i;
            for(i = elements->begin(); i != elements->end(); ++i){
                vec->push_back((*i).first);
            }
            return vec;
        }

        template<class K, class V, class Z>
        vector<K>* getKeys(map<K,V*,Z>* elements){
            vector<K>* vec=new vector<K>();
            typename map<K,V*,Z>::iterator i;
            for(i = elements->begin(); i != elements->end(); ++i){
                vec->push_back((*i).first);
            }
            return vec;
        }

        template<class K>
        void arraycopy(vector<K>* src,jint ofsrc, vector<K>* dest,jint ofdes, jint nb){
            for (jint i=0;i<nb;i++){
                dest->at(i+ofdes)=src->at(i+ofsrc);
            }
        }

        template<class K>
        void arraycopy(vector<K>* src,jint ofsrc, K dest[],jint ofdes, jint nb){
            for (jint i=0;i<nb;i++){
                dest[i+ofdes]=src->at(i+ofsrc);
            }
        }

        template<class K>
        void arraycopy(K src[],jint ofsrc, vector<K>* dest,jint ofdes, jint nb){
            for (jint i=0;i<nb;i++){
                dest->at(i+ofdes)=src[i+ofsrc];
            }
        }
    }
}

#endif // COLLECTIONS_H
