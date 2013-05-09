#include "QtDataInputStream.h"
#include "JBits.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace io{
        class QtDataInputStreamClass : public JClass{
        public:
            QtDataInputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.QtDataInputStream";//not usefull...
                name="java.io.QtDataInputStream";
                simpleName="QtDataInputStream";
            }

            JClass* getSuperclass(){
                return JInputStream::getClazz();
            }

            JObject* newInstance(){
                return new QtDataInputStream();
            }
        };

        static JClass* clazz;

        JClass* QtDataInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new QtDataInputStreamClass();
            }
            return clazz;
        }

        QtDataInputStream::QtDataInputStream():JInputStream(getClazz()){
            bytes=new vector<jbyte>();
            bIsClosed=false;
        }

        QtDataInputStream::QtDataInputStream(QDataStream* in):JInputStream(getClazz()){
            this->in = in;
            bytes=new vector<jbyte>();
            bIsClosed=false;
        }

        QDataStream* QtDataInputStream::getStream(){
            return this->in;
        }

        void QtDataInputStream::setStream(QDataStream* in){
            this->in=in;
        }

        jint QtDataInputStream::available() {
            return (jint)in->device()->bytesAvailable();
        }

        jbool QtDataInputStream::waitForReadyRead(jint i) {
            jbool b=false;
            QIODevice* dev=in->device();
            if (dev!=NULL){
                b=dev->waitForReadyRead(i);
            }
            return b;
        }

        jint QtDataInputStream::peek() {
            jbyte b;
            while (!isClosed() && available() < 1) {
                waitForReadyRead(100);
            }
            in->device()->peek((char*) &b,1);
            return b & 0xFF;
        }

        jint QtDataInputStream::read() {
            jbyte b;
            while (!isClosed() && available() < 1) {
                waitForReadyRead(-1);
            }
            (*in)>>b;
            //bytes->push_back(b); TODO for debugging, remove later
            return (jint)b & 0xFF;
        }

        jbool QtDataInputStream::isClosed(){
            lock();
            jbool b=bIsClosed;
            unlock();
            return b;
        }

        void QtDataInputStream::close(){
            lock();
            bIsClosed=true;
            this->in->setDevice(0);
            unlock();
        }

        QtDataInputStream::~QtDataInputStream() {
            delete in;
            delete bytes;
        }
    }
}
