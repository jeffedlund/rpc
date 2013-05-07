#include "JFileInputStream.h"
#include "JClass.h"
#include <QString>
#include "QObjectHolder.h"

namespace jcpp{
    namespace io{
        class JFileInputStreamClass : public JClass{
            public:
                JFileInputStreamClass(){
                    this->canonicalName="java.io.FileInputStream";
                    this->name="java.io.FileInputStream";
                    this->simpleName="FileInputStream";
                }

                JClass* getSuperclass(){
                    return JInputStream::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JFileInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JFileInputStreamClass();
            }
            return clazz;
        }

        JFileInputStream::JFileInputStream(string name):JInputStream(getClazz()){
            bIsClosed=false;
            QString fn=QString::fromStdString(name);
            file=new QFile(fn);
            file->open(QIODevice::ReadOnly);
            in=new QDataStream(file);
        }

        JFileInputStream::JFileInputStream(JFile* file):JInputStream(getClazz()){
            bIsClosed=false;
            QString fn=QString::fromStdString(file->getPath());
            this->file=new QFile(fn);
            this->file->open(QIODevice::ReadOnly);
            in=new QDataStream(this->file);
        }

        jint JFileInputStream::available() {
            return (jint)in->device()->bytesAvailable();
        }

        jbool JFileInputStream::waitForReadyRead(jint i) {
            jbool b=false;
            QIODevice* dev=in->device();
            if (dev!=NULL){
                b=dev->waitForReadyRead(i);
            }
            return b;
        }

        jint JFileInputStream::peek() {
            jbyte b;
            while (!isClosed() && available() < 1) {
                waitForReadyRead(100);
            }
            in->device()->peek((char*) &b,1);
            return b & 0xFF;
        }

        jint JFileInputStream::read() {
            jbyte b;
            while (!isClosed() && available() < 1) {
                waitForReadyRead(-1);
            }
            (*in)>>b;
            return (jint)b & 0xFF;
        }

        jbool JFileInputStream::isClosed(){
            lock();
            jbool b=bIsClosed;
            unlock();
            return b;
        }

        void JFileInputStream::close(){
            lock();
            bIsClosed=true;
            this->in->setDevice(0);
            this->file->close();
            unlock();
        }

        void JFileInputStream::takeOwner(){
            QObjectHolder::getQObjectHolder()->takeOwner(file);
        }

        void JFileInputStream::releaseOwner(){
            QObjectHolder::getQObjectHolder()->releaseOwner(file);
        }

        QObject* JFileInputStream::getQObject(){
            return file;
        }

        JFileInputStream::~JFileInputStream() {
            delete file;
            delete in;
        }
    }
}
