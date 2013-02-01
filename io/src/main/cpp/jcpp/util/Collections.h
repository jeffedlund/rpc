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

#endif // COLLECTIONS_H
