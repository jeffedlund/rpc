#ifndef COLLECTIONS_H
#define COLLECTIONS_H

using namespace std;

template <class T>
void deleteVectorOfPointers(T *vector) {
  typename T::iterator i;
  for (i = vector->begin(); i < vector->end(); ++i) {
    delete *i;
  }
  delete vector;
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

#endif // COLLECTIONS_H
