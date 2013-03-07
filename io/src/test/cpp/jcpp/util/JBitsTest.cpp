#include "JBitsTest.h"

namespace jcpp{
    namespace util{
        JBitsTest::JBitsTest():JTest(){
        }

        void JBitsTest::test(){
            jint i=2147483646;
            jbyte* bi=new jbyte[4];
            JBits::putInt(bi,0,i);
            jint newi=JBits::getInt(bi,0);
            assert(newi==i);

            jshort s=32766;
            jbyte* bs=new jbyte[2];
            JBits::putShort(bs,0,s);
            jshort news=JBits::getShort(bs,0);
            assert(news==s);

            jlong l=9223372036854775806;
            jbyte* bl=new jbyte[8];
            JBits::putLong(bl,0,l);
            jlong newl=JBits::getLong(bl,0);
            assert(newl==l);

            jfloat f=21474836476.343434;
            jbyte* bf=new jbyte[4];
            JBits::putFloat(bf,0,f);
            jfloat newf=JBits::getFloat(bf,0);
            assert(newf==f);

            jdouble d=922337203685477580.343434;
            jbyte* bd=new jbyte[8];
            JBits::putDouble(bd,0,d);
            jdouble newd=JBits::getDouble(bd,0);
            assert(newd==d);

            string str="abcdefghijklmnopqrstuvwxyz";
            const char* c=str.c_str();
            jchar* jc=new jchar[str.length()];
            JBits::fromCharToJChar(c,jc,0,str.length());
            char* newc=new char[str.length()+1];
            newc[str.length()]='\0';
            JBits::fromJChartoChar(jc,newc,0,str.length());
            string newstr(newc);
            assert(str==newstr);

            jbyte* jcb=new jbyte[str.length()];
            JBits::fromCharToJByte((char*)c,jcb,0,str.length());
            char* newcb=new char[str.length()+1];
            newcb[str.length()]='\0';
            JBits::fromJBytetoChar(jcb,newcb,0,str.length());
            string newstrb(newcb);
            assert(str==newstrb);
        }

        JBitsTest::~JBitsTest(){
        }
    }
}


