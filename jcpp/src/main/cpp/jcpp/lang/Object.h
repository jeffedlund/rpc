#ifndef OBJECT_H
#define OBJECT_H

#include "stdint.h"
#include "cassert"
#include <sstream>
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        //TODO is it correct values cross OS?
        #define jint int32_t
        #define jbool bool
        #define jbyte int8_t
        #define jchar uint16_t
        #define jdouble double //64
        #define jfloat float //32
        #define jlong int64_t
        #define jshort int16_t
        class JCPP_LIBRARY_EXPORT Object{
        public:
            static void init(){
                assert(sizeof(char)==1);
                assert(sizeof(jchar)==2);
                assert(sizeof(jbyte)==1);
                assert(sizeof(jshort)==2);
                assert(sizeof(jint)==4);
                assert(sizeof(jlong)==8);
                assert(sizeof(jfloat)==4);
                assert(sizeof(jdouble)==8);
            }

            //TODO do we keep it here or in JString?
            static string concat(string s, jint i){
                stringstream ss;
                ss<<s<<i;
                return ss.str();
            }
        };
    }
}

#endif // OBJECT_H
