#include "SerialCallbackContext.h"
#include "JObjectStreamClass.h"
#include "JObject.h"

namespace jcpp{
    namespace io{
        //missing thread handling
        SerialCallbackContext::SerialCallbackContext() {
            curObj = NULL;
            curDesc = NULL;
            upcall = false;
        }

        jbool SerialCallbackContext::setUpcall(jbool v) {
            if (upcall == v) {
                return upcall;
            }
            upcall = v;
            return (!upcall);
        }

        jbool SerialCallbackContext::isUpcall(){
            return upcall;
        }

        JObject* SerialCallbackContext::getObj(){
            return curObj;
        }

        JObjectStreamClass* SerialCallbackContext::getDesc(){
            return curDesc;
        }

        void SerialCallbackContext::setContext(JObject* obj, JObjectStreamClass* desc) {
            curObj = obj;
            curDesc = desc;
            upcall = true;
        }

        void SerialCallbackContext::clear() {
            curObj = NULL;
            curDesc = NULL;
            upcall = false;
        }
    }
}

