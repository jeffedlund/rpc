#include "JArrayListTest.h"

namespace jcpp{
    namespace util{
        JArrayListTest::JArrayListTest():JTest(){
        }

        string JArrayListTest::getFileName(){
            return "arraylist.ser";
        }

        JObject* JArrayListTest::testReflect(){//TODO reading from Java is failing!!!!!
            JArrayList* s=new JArrayList(4);
            assert (s->getClass()->getName()=="java.util.ArrayList");
            JShort* short1=new JShort(1);
            JLong* long1=new JLong(2);
            JInteger* int1=new JInteger(3);
            JFloat* f1=new JFloat(4);
            s->add(short1);
            s->add(long1);
            s->add(int1);
            s->add(f1);
            return s;
        }
    }
}

