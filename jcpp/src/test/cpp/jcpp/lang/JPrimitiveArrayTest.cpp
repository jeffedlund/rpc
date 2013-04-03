#include "JPrimitiveArrayTest.h"
#include "JPrimitiveArray.h"
#include "JSampleObject.h"

namespace jcpp{
    namespace lang{
        JPrimitiveArrayTest::JPrimitiveArrayTest():JTest(){
        }

        string JPrimitiveArrayTest::getFileName(){
            return "PrimitiveArray.ser";
        }

        JObject* JPrimitiveArrayTest::testReflect(){
            JPrimitiveArray* global=new JPrimitiveArray(JObject::getClazz(),9);

            JPrimitiveArray* s=new JPrimitiveArray(JShort::getClazz(),4);
            JShort* short1=new JShort(1);
            JShort* short2=new JShort(2);
            JShort* short3=new JShort(3);
            JShort* short4=new JShort(4);
            s->set(0,short1);
            s->set(1,short2);
            s->set(2,short3);
            s->set(3,short4);

            JPrimitiveArray* ps=new JPrimitiveArray(JPrimitiveShort::getClazz(),4);
            JPrimitiveShort* pshort1=new JPrimitiveShort(1);
            JPrimitiveShort* pshort2=new JPrimitiveShort(2);
            JPrimitiveShort* pshort3=new JPrimitiveShort(3);
            JPrimitiveShort* pshort4=new JPrimitiveShort(4);
            ps->set(0,pshort1);
            ps->set(1,pshort2);
            ps->set(2,pshort3);
            ps->set(3,pshort4);

            JPrimitiveArray* l=new JPrimitiveArray(JLong::getClazz(),4);
            JLong* long1=new JLong(1);
            JLong* long2=new JLong(2);
            JLong* long3=new JLong(3);
            JLong* long4=new JLong(4);
            l->set(0,long1);
            l->set(1,long2);
            l->set(2,long3);
            l->set(3,long4);

            JPrimitiveArray* pl=new JPrimitiveArray(JPrimitiveLong::getClazz(),4);
            JPrimitiveLong* plong1=new JPrimitiveLong(1);
            JPrimitiveLong* plong2=new JPrimitiveLong(2);
            JPrimitiveLong* plong3=new JPrimitiveLong(3);
            JPrimitiveLong* plong4=new JPrimitiveLong(4);
            pl->set(0,plong1);
            pl->set(1,plong2);
            pl->set(2,plong3);
            pl->set(3,plong4);

            JPrimitiveArray* i=new JPrimitiveArray(JInteger::getClazz(),4);
            JInteger* int1=new JInteger(1);
            JInteger* int2=new JInteger(2);
            JInteger* int3=new JInteger(3);
            JInteger* int4=new JInteger(4);
            i->set(0,int1);
            i->set(1,int2);
            i->set(2,int3);
            i->set(3,int4);

            JPrimitiveArray* pi=new JPrimitiveArray(JPrimitiveInt::getClazz(),4);
            JPrimitiveInt* pint1=new JPrimitiveInt(1);
            JPrimitiveInt* pint2=new JPrimitiveInt(2);
            JPrimitiveInt* pint3=new JPrimitiveInt(3);
            JPrimitiveInt* pint4=new JPrimitiveInt(4);
            pi->set(0,pint1);
            pi->set(1,pint2);
            pi->set(2,pint3);
            pi->set(3,pint4);

            JPrimitiveArray* f=new JPrimitiveArray(JFloat::getClazz(),4);
            JFloat* float1=new JFloat(1);
            JFloat* float2=new JFloat(2);
            JFloat* float3=new JFloat(3);
            JFloat* float4=new JFloat(4);
            f->set(0,float1);
            f->set(1,float2);
            f->set(2,float3);
            f->set(3,float4);

            JPrimitiveArray* pf=new JPrimitiveArray(JPrimitiveFloat::getClazz(),4);
            JPrimitiveFloat* pfloat1=new JPrimitiveFloat(1);
            JPrimitiveFloat* pfloat2=new JPrimitiveFloat(2);
            JPrimitiveFloat* pfloat3=new JPrimitiveFloat(3);
            JPrimitiveFloat* pfloat4=new JPrimitiveFloat(4);
            pf->set(0,pfloat1);
            pf->set(1,pfloat2);
            pf->set(2,pfloat3);
            pf->set(3,pfloat4);

            JPrimitiveArray* po=new JPrimitiveArray(JSampleObject::getClazz(),4);
            JSampleObject* o1=new JSampleObject();
            o1->setBool1(new JPrimitiveBoolean(false));
            o1->setByte1(new JPrimitiveByte(123));
            o1->setC1(new JPrimitiveChar('c'));
            o1->setD1(new JPrimitiveDouble(456));
            o1->setF1(new JPrimitiveFloat(789));
            o1->setL1(new JPrimitiveLong(124));
            o1->setS1(new JPrimitiveShort(235));
            o1->setI1(new JPrimitiveInt(345));
            po->set(0,o1);

            JSampleObject* o2=new JSampleObject();
            o2->setBool1(new JPrimitiveBoolean(false));
            o2->setByte1(new JPrimitiveByte(123));
            o2->setC1(new JPrimitiveChar('c'));
            o2->setD1(new JPrimitiveDouble(456));
            o2->setF1(new JPrimitiveFloat(789));
            o2->setL1(new JPrimitiveLong(124));
            o2->setS1(new JPrimitiveShort(235));
            o2->setI1(new JPrimitiveInt(345));
            po->set(1,o2);

            JSampleObject* o3=new JSampleObject();
            o3->setBool1(new JPrimitiveBoolean(false));
            o3->setByte1(new JPrimitiveByte(123));
            o3->setC1(new JPrimitiveChar('c'));
            o3->setD1(new JPrimitiveDouble(456));
            o3->setF1(new JPrimitiveFloat(789));
            o3->setL1(new JPrimitiveLong(124));
            o3->setS1(new JPrimitiveShort(235));
            o3->setI1(new JPrimitiveInt(345));
            po->set(2,o3);

            JSampleObject* o4=new JSampleObject();
            o4->setBool1(new JPrimitiveBoolean(false));
            o4->setByte1(new JPrimitiveByte(123));
            o4->setC1(new JPrimitiveChar('c'));
            o4->setD1(new JPrimitiveDouble(456));
            o4->setF1(new JPrimitiveFloat(789));
            o4->setL1(new JPrimitiveLong(124));
            o4->setS1(new JPrimitiveShort(235));
            o4->setI1(new JPrimitiveInt(345));
            po->set(3,o4);

            global->set(0,s);
            global->set(1,l);
            global->set(2,i);
            global->set(3,f);
            global->set(4,ps);
            global->set(5,pl);
            global->set(6,pi);
            global->set(7,pf);
            global->set(8,po);

            return global;
        }

        JPrimitiveArrayTest::~JPrimitiveArrayTest(){
        }
    }
}



