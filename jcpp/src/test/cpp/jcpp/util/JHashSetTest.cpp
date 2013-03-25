#include "JHashSetTest.h"

namespace jcpp{
    namespace util{
        JHashSetTest::JHashSetTest():JTest(){
        }

        string JHashSetTest::getFileName(){
            return "HashSet.ser";
        }

        JObject* JHashSetTest::testReflect(){
            JHashSet* s=new JHashSet();
            assert (s->getClass()->getName()=="java.util.HashSet");
            JShort* short1=new JShort(1);
            JLong* long1=new JLong(2);
            JInteger* int1=new JInteger(3);
            JFloat* f1=new JFloat(4);
            s->add(short1);
            s->add(long1);
            s->add(int1);
            s->add(f1);

            assert (s->contains(short1));
            assert (s->contains(long1));
            assert (s->contains(int1));
            assert (s->contains(f1));

            JIterator* iks=s->iterator();
            while (iks->hasNext()){
                JObject* o=iks->next();
                assert (o->equals(short1) || o->equals(long1) ||
                        o->equals(int1) || o->equals(f1));
            };

            return s;
        }

        JHashSetTest::~JHashSetTest(){
        }
    }
}



