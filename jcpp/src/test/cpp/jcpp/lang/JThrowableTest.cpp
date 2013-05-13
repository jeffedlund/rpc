#include "JThrowableTest.h"

namespace jcpp{
    namespace lang{
        JThrowableTest::JThrowableTest():JTest(){
        }

        JString JThrowableTest::getFileName(){
            return "throwable.ser";
        }

        JThrowable* JThrowableTest::createFirstCause(){
            return new JThrowable();
        }

        JThrowable* JThrowableTest::createSecondCause(){
            return new JThrowable();
        }

        JString JThrowableTest::getThrowableClassName(){
            return "java.lang.Throwable";
        }

        JObject* JThrowableTest::testReflect(){
            JPrimitiveArray* causeArray=new JPrimitiveArray(JStackTraceElement::getClazz(),2);
            causeArray->set(0,new JStackTraceElement("declaringclass","methodName","filename",0));
            causeArray->set(1,new JStackTraceElement("declaringclass1","methodName1","filename1",1111));
            JThrowable* cause=createSecondCause();
            cause->setMessage(new JString("cause!!!"));
            cause->setStackTrace(causeArray);

            causeArray=new JPrimitiveArray(JStackTraceElement::getClazz(),2);
            causeArray->set(0,new JStackTraceElement("declaringclass2","methodName2","filename2",22));
            causeArray->set(1,new JStackTraceElement("declaringclass21","methodName21","filename21",2221111));
            JThrowable* th=createFirstCause();
            th->setMessage(new JString("Hello world"));
            th->setCause(cause);
            th->setStackTrace(causeArray);

            assert (th->getClass()->getName()==getThrowableClassName());

            JField* fMessage=th->getClass()->getField("detailMessage");
            JField* fCause=th->getClass()->getField("cause");
            JField* fStackTrace=th->getClass()->getField("stackTrace");

            assert (((JString*)fMessage->get(th))->getString()=="Hello world");
            assert (((JThrowable*)fCause->get(th))->getMessage()->getString()=="cause!!!");
            assert (((JPrimitiveArray*)fStackTrace->get(th))->size()==2);

            th->printStackTrace(&cout);
            return th;
        }

        JThrowableTest::~JThrowableTest(){
        }
    }
}
