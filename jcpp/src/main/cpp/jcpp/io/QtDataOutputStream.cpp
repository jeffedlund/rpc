#include "QtDataOutputStream.h"
#include "JIndexOutOfBoundsException.h"
#include "JNullPointerException.h"
#include "Collections.h"
#include "JBits.h"
using namespace jcpp::util;

namespace jcpp{
    namespace io{
        class QtDataOutputStreamClass : public JClass{
        public:
            QtDataOutputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.QtDataOutputStream";//not usefull...
                name="java.io.QtDataOutputStream";
                simpleName="QtDataOutputStream";
            }

            JClass* getSuperclass(){
                return JOutputStream::getClazz();
            }

            JObject* newInstance(){
                return new QtDataOutputStream();
            }
        };

        static JClass* clazz;

        JClass* QtDataOutputStream::getClazz(){
            if (clazz==NULL){
                clazz=new QtDataOutputStreamClass();
            }
            return clazz;
        }

        QtDataOutputStream::QtDataOutputStream():JOutputStream(getClazz()){
            bytes=new vector<jbyte>();
        }

        QtDataOutputStream::QtDataOutputStream(QDataStream* out,QFile* file):JOutputStream(getClazz()){
            this->out=out;
            this->file=file;
            this->socket=NULL;
            bytes=new vector<jbyte>();
        }

        QtDataOutputStream::QtDataOutputStream(QDataStream* out,QAbstractSocket* socket):JOutputStream(getClazz()){
            this->out=out;
            this->file=NULL;
            this->socket=socket;
            bytes=new vector<jbyte>();
        }

        QDataStream* QtDataOutputStream::getStream(){
            return out;
        }

        void QtDataOutputStream::setStream(QDataStream* out){
            this->out=out;
        }

        void QtDataOutputStream::write(jint b){
            (*out)<<((jbyte)b);
            //TODO for debugging remove later// bytes->push_back(b);
        }

        void QtDataOutputStream::flush(){
            if (file!=NULL){
                file->flush();
            }
            if (socket!=NULL){
                while (socket->bytesToWrite()>0){
                    socket->waitForBytesWritten();
                }
            }
        }

        void QtDataOutputStream::close(){
            out->device()->close();
        }

        QtDataOutputStream::~QtDataOutputStream(){
            delete out;
            delete bytes;
        }
    }
}
