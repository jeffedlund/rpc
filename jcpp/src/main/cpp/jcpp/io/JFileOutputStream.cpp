#include "JFileOutputStream.h"
#include "JClass.h"
#include <QThread>
#include "QObjectHolder.h"

namespace jcpp{
    namespace io{
        class JFileOutputStreamClass : public JClass{
            public:
                JFileOutputStreamClass(){
                    this->canonicalName="java.io.FileOutputStream";
                    this->name="java.io.FileOutputStream";
                    this->simpleName="FileOutputStream";
                }

                JClass* getSuperclass(){
                    return JOutputStream::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JFileOutputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JFileOutputStreamClass();
            }
            return clazz;
        }

        JFileOutputStream::JFileOutputStream(JString name,jbool append):JOutputStream(getClazz()){
            this->bIsClosed=false;
            QString fname=QString::fromStdString(name.getString());//TODO
            file=new QFile(fname);
            file->open(QIODevice::WriteOnly | (append ? QIODevice::Append : QIODevice::Truncate));
            this->out=new QDataStream(file);
        }

        JFileOutputStream::JFileOutputStream(JFile* file,jbool append):JOutputStream(getClazz()){
            this->bIsClosed=false;
            QString fname=QString::fromStdString(file->getPath().getString());//TODO
            this->file=new QFile(fname);
            this->file->open(QIODevice::WriteOnly | (append ? QIODevice::Append : QIODevice::Truncate));
            this->out=new QDataStream(this->file);        }

        void JFileOutputStream::write(jint b){
            (*out)<<((jbyte)b);
        }

        void JFileOutputStream::flush(){
            file->flush();
        }

        jbool JFileOutputStream::isClosed(){
            lock();
            jbool b=bIsClosed;
            unlock();
            return b;
        }

        void JFileOutputStream::close(){
            lock();
            this->bIsClosed=true;
            file->close();
            if (out->device()->thread()==QThread::currentThread()){
                if (out->device()!=NULL && out->device()->isOpen()){
                    out->device()->close();
                }
            }
            unlock();
        }

        void JFileOutputStream::takeOwner(){
            QObjectHolder::getQObjectHolder()->takeOwner(file);
        }

        void JFileOutputStream::releaseOwner(){
            QObjectHolder::getQObjectHolder()->releaseOwner(file);
        }

        QObject* JFileOutputStream::getQObject(){
            return file;
        }

        JFileOutputStream::~JFileOutputStream(){
            delete file;
            delete out;
        }
    }
}

