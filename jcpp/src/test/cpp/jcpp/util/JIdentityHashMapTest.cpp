#include "JIdentityHashMapTest.h"

namespace jcpp{
    namespace util{
        //TODO test bugged
        JIdentityHashMapTest::JIdentityHashMapTest():JTest(){
        }

        JString JIdentityHashMapTest::getFileName(){
            return "IdentityHashMap.ser";
        }

        JObject* JIdentityHashMapTest::testReflect(){
            JIdentityHashMap* s=new JIdentityHashMap(4);
            assert (s->getClass()->getName()=="java.util.IdentityHashMap");
            JShort* short1=new JShort(1);
            JLong* long1=new JLong(2);
            JInteger* int1=new JInteger(3);
            JFloat* f1=new JFloat(4);
            JString* ss1=new JString("short1");
            JString* ss2=new JString("long1");
            JString* ss3=new JString("int1");
            JString* ss4=new JString("f1");
            s->put(short1,ss1);
            s->put(long1,ss2);
            s->put(int1,ss3);
            s->put(f1,ss4);

            assert (s->get(short1)==ss1);
            assert (s->get(long1)==ss2);
            assert (s->get(int1)==ss3);
            assert (s->get(f1)==ss4);

            JSet* ks=s->keySet();
            assert (ks->contains(short1));
            assert (ks->contains(long1));
            assert (ks->contains(int1));
            assert (ks->contains(f1));

            JIterator* iks=ks->iterator();
            while (iks->hasNext()){
                JObject* o=iks->next();
                assert (o->equals(short1) || o->equals(long1) || o->equals(int1) || o->equals(f1));
            };

            JCollection* cv=s->values();
            assert (cv->contains(ss1));
            assert (cv->contains(ss2));
            assert (cv->contains(ss3));
            assert (cv->contains(ss4));

            JIterator* icv=cv->iterator();
            while (icv->hasNext()){
                JObject* o=icv->next();
                assert (o==ss1 || o==ss2 || o==ss3 || o==ss4);
            };
            return s;
        }

        JIdentityHashMapTest::~JIdentityHashMapTest(){
        }
    }
}



