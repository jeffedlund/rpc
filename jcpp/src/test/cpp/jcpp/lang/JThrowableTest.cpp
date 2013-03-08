#include "JThrowableTest.h"

namespace jcpp{
    namespace lang{
        JThrowableTest::JThrowableTest():JTest(){
        }

        string JThrowableTest::getFileName(){
            return "throwable.ser";
        }

        JThrowable* JThrowableTest::createFirstCause(){
            return new JThrowable();
        }

        JThrowable* JThrowableTest::createSecondCause(){
            return new JThrowable();
        }

        string JThrowableTest::getThrowableClassName(){
            return "java.lang.Throwable";
        }

        JObject* JThrowableTest::testReflect(){
            JPrimitiveArray* causeArray=new JPrimitiveArray(JStackTraceElement::getClazz(),2);
            causeArray->set(0,new JStackTraceElement(new JString("declaringclass"),new JString("methodName"),new JString("filename"),new JPrimitiveInt(0)));
            causeArray->set(1,new JStackTraceElement(new JString("declaringclass1"),new JString("methodName1"),new JString("filename1"),new JPrimitiveInt(1111)));
            JThrowable* cause=createSecondCause();
            cause->setMessage(new JString("cause!!!"));
            cause->setStackTrace(causeArray);

            causeArray=new JPrimitiveArray(JStackTraceElement::getClazz(),2);
            causeArray->set(0,new JStackTraceElement(new JString("declaringclass2"),new JString("methodName2"),new JString("filename2"),new JPrimitiveInt(22)));
            causeArray->set(1,new JStackTraceElement(new JString("declaringclass21"),new JString("methodName21"),new JString("filename21"),new JPrimitiveInt(2221111)));
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
