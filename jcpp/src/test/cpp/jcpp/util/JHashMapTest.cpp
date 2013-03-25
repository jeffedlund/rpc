#include "JHashMapTest.h"

namespace jcpp{
    namespace util{
        JHashMapTest::JHashMapTest():JTest(){
        }

        string JHashMapTest::getFileName(){
            return "HashMap.ser";
        }

        JObject* JHashMapTest::testReflect(){
            JHashMap* s=new JHashMap(4);
            assert (s->getClass()->getName()=="java.util.HashMap");
            JShort* short1=new JShort(1);
            JLong* long1=new JLong(2);
            JInteger* int1=new JInteger(3);
            JFloat* f1=new JFloat(4);
            s->put(short1,new JString("short1"));
            s->put(long1,new JString("long1"));
            s->put(int1,new JString("int1"));
            s->put(f1,new JString("f1"));

            assert (s->get(short1)->equals(new JString("short1")));
            assert (s->get(long1)->equals(new JString("long1")));
            assert (s->get(int1)->equals(new JString("int1")));
            assert (s->get(f1)->equals(new JString("f1")));

            JSet* ks=s->keySet();
            assert (ks->contains(short1));
            assert (ks->contains(long1));
            assert (ks->contains(int1));
            assert (ks->contains(f1));

            JIterator* iks=ks->iterator();
            while (iks->hasNext()){
                JObject* o=iks->next();
                assert (o->equals(short1) || o->equals(long1) ||
                        o->equals(int1) || o->equals(f1));
            };

            JCollection* cv=s->values();
            assert (cv->contains(new JString("short1")));
            assert (cv->contains(new JString("long1")));
            assert (cv->contains(new JString("int1")));
            assert (cv->contains(new JString("f1")));

            JIterator* icv=cv->iterator();
            while (icv->hasNext()){
                JObject* o=icv->next();
                assert (o->equals(new JString("short1")) || o->equals(new JString("long1")) ||
                        o->equals(new JString("int1")) || o->equals(new JString("f1")));
            };



            return s;
        }

        JHashMapTest::~JHashMapTest(){
        }
    }
}


