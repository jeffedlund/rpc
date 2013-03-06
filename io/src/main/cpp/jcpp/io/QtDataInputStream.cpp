#include "QtDataInputStream.h"
#include "JBits.h"
using namespace jcpp::util;

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
        }

        QtDataInputStream::QtDataInputStream(QDataStream* in):JInputStream(getClazz()){
            this->in = in;
            bytes=new vector<jbyte>();
        }

        QDataStream* QtDataInputStream::getStream(){
            return this->in;
        }

        void QtDataInputStream::setStream(QDataStream* in){
            this->in=in;
        }

        jlong QtDataInputStream::available() {
            return in->device()->bytesAvailable();
        }

        bool QtDataInputStream::waitForReadyRead(int i) {
            return in->device()->waitForReadyRead(i);
        }

        jbyte QtDataInputStream::peekByte() {
            jbyte b;
            while (available() < 1) {
                waitForReadyRead(-1);
            }
            in->device()->peek((char*) &b,1);
            return b;
        }

        jbyte QtDataInputStream::read() {
            return readByte();
        }

        jbyte QtDataInputStream::readByte() {
            jbyte b;
            while (available() < 1) {
                waitForReadyRead(-1);
            }
            (*in)>>b;
            //bytes->push_back(b); TODO for debugging, remove later
            return b;
        }

        void QtDataInputStream::close(){
            this->in->setDevice(0);
        }

        QtDataInputStream::~QtDataInputStream() {
            delete in;
            delete bytes;
        }
    }
}
