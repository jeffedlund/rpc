#include "OutputHandleTable.h"

namespace jcpp{
    namespace io{
        OutputHandleTable::OutputHandleTable(){
            this->handleByObject=new map<JObject*, jint>();
            handle = 0;
            clear();
        }

        jint OutputHandleTable::assign(JObject *obj){
            handleByObject->insert(pair<JObject*,jint>(obj,handle));
            return handle++;
        }

        void OutputHandleTable::clear(){
            handleByObject->clear();
        }

        jint OutputHandleTable::size(){
            return handleByObject->size();
        }

        jint OutputHandleTable::lookup(JObject* obj){
            if (handleByObject->count(obj)==1){
                return handleByObject->at(obj);
            }else{
                return -1;
            }
        }

        OutputHandleTable::~OutputHandleTable(){
            delete handleByObject;
        }
    }
}
