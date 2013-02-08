#ifndef JTHROWABLETEST_H
#define JTHROWABLETEST_H

#include "JThrowable.h"
#include "assert.h"
#include "JIO.h"
#include "JLang.h"
#include "JUtil.h"

static JThrowable* testReflectThrowable(){
    JPrimitiveArray* causeArray=new JPrimitiveArray(JStackTraceElement::getClazz(),2);
    causeArray->set(0,new JStackTraceElement(new JString("declaringclass"),new JString("methodName"),new JString("filename"),new JPrimitiveInt(0)));
    causeArray->set(1,new JStackTraceElement(new JString("declaringclass1"),new JString("methodName1"),new JString("filename1"),new JPrimitiveInt(1111)));
    JThrowable* cause=new JThrowable();
    cause->setMessage(new JString("cause!!!"));
    cause->setStackTrace(causeArray);

    causeArray=new JPrimitiveArray(JStackTraceElement::getClazz(),2);
    causeArray->set(0,new JStackTraceElement(new JString("declaringclass2"),new JString("methodName2"),new JString("filename2"),new JPrimitiveInt(22)));
    causeArray->set(1,new JStackTraceElement(new JString("declaringclass21"),new JString("methodName21"),new JString("filename21"),new JPrimitiveInt(2221111)));
    JThrowable* th=new JThrowable();
    th->setMessage(new JString("Hello world"));
    th->setCause(cause);
    th->setStackTrace(causeArray);

    assert (th->getClass()->getName()=="java.lang.Throwable");

    JField* fMessage=th->getClass()->getField("detailMessage");
    JField* fCause=th->getClass()->getField("cause");
    JField* fStackTrace=th->getClass()->getField("stackTrace");

    assert (((JString*)fMessage->get(th))->getString()=="Hello world");
    assert (((JThrowable*)fCause->get(th))->getMessage()->getString()=="cause!!!");
    assert (((JPrimitiveArray*)fStackTrace->get(th))->size()==2);

    th->printStackTrace(&cout);
    return th;
}

static void testWriteThrowable(JThrowable* throwable){
    try{
        QString name("throwable.ser");
        QFile* file=new QFile(name);
        file->open(QIODevice::WriteOnly);
        QDataStream* qs=new QDataStream(file);
        QtDataOutputStream* qos=new QtDataOutputStream(qs);
        JObjectOutputStream* oos=new JObjectOutputStream(qos);
        oos->writeObject(throwable);
        file->close();
    }catch(JThrowable* th){
        th->printStackTrace(&cout);
        throw th;
    }
}

static JThrowable* testReadThrowable(){
    QString name("throwable.ser");
    QFile* file=new QFile(name);
    file->open(QIODevice::ReadOnly);
    QDataStream* qs=new QDataStream(file);
    QtDataInputStream* qis=new QtDataInputStream(qs);
    JObjectInputStream* ois=new JObjectInputStream(qis);
    JThrowable* throwable=(JThrowable*)ois->readObject();
    return throwable;
}

static void testThrowable(){
    JThrowable* throwable=testReflectThrowable();
    testWriteThrowable(throwable);
    JThrowable* readThrowable=testReadThrowable();
    assert (*readThrowable==*throwable);
}

#endif
