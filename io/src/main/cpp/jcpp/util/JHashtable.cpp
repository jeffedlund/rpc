#include "JHashtable.h"

//JClass* JHashtable::clazz=new JClass(NULL);

namespace jcpp{
    namespace util{
        template<typename Key, typename Value>
        JHashtable<Key,Value>::JHashtable():JObject(NULL){
            hashtable=new std::map<Key,Value>();
        }

        template<typename Key, typename Value>
        int JHashtable<Key,Value>::size(){
            return hashtable->size();
        }

        template<typename Key, typename Value>
        Value JHashtable<Key,Value>::get(const Key & key){
            return hashtable->at(key);//TODO bugged
        }

        template<typename Key, typename Value>
        void JHashtable<Key,Value>::put(const Key & key, const Value & value){
            hashtable[key]=value;
        }

        template<typename Key, typename Value>
        Value JHashtable<Key,Value>::remove(const Key & key){
            //TODO
            return NULL;
        }

        template<typename Key, typename Value>
        bool JHashtable<Key,Value>::containsKey(const Key & key){
            return hashtable->at(key)!=NULL;
        }

        //QList<Value> JHashtable::values(){
        //    hashtable->
        //}

        //QList<Key> keys();

        template<typename Key, typename Value>
        JHashtable<Key,Value>::~JHashtable(){
            delete hashtable;
        }
    }
}
