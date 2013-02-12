#ifndef COLLECTIONS_H
#define COLLECTIONS_H

using namespace std;

namespace jcpp{
    namespace util{
        /*
        TODO :
            -centralize qt dependencies by definiing jbyte,...
            -review all new calls and chek delete is called
        */
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

        template<class K,class V>
        void deleteMapOfValuePointer(map<K,V*>* elements){
            typename map<K,V*>::iterator i;
            for(i = elements->begin(); i != elements->end(); ++i){
                delete (*i).second;
            }
            delete elements;
        }

        template<class K, class V>
        V* getFromMap(map<K,V*>* elements, K k){
            typename map<K,V*>::const_iterator i;
            i= elements->find(k);
            if (i!=elements->end()){
                return (*i).second;
            }else{
                return NULL;
            }
        }

        #define arrayLength(a) ( sizeof ( a ) / sizeof ( *a ) )
    }
}

#endif // COLLECTIONS_H
