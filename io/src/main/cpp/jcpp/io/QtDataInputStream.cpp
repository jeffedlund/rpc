#include "QtDataInputStream.h"

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
        }

        QtDataInputStream::QtDataInputStream(QDataStream* in):JInputStream(getClazz()){
            this->in = in;
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

        jint QtDataInputStream::read() {
            return readByte();
        }

        jint QtDataInputStream::read(jbyte b[], int off, int len) {
            if (available() < len) {
                waitForReadyRead(-1);
            }
            return in->readRawData((char*)b+off,len);
        }

        jbyte QtDataInputStream::peekByte() {
            jbyte b;
            while (available() < 1) {
                waitForReadyRead(-1);
            }
            in->device()->peek((char*) &b,1);
            return b;
        }

        jbyte QtDataInputStream::readByte() {
            jbyte b;
            while (available() < 1) {
                waitForReadyRead(-1);
            }
            (*in)>>b;
            return b;
        }

        jshort QtDataInputStream::readShort() {
            jshort s;
            while (available() < 2) {
                waitForReadyRead(-1);
            }
            (*in)>>s;
            return s;
        }

        jushort QtDataInputStream::readUnsignedShort() {
            jushort us;
            while (available() < 2) {
                waitForReadyRead(-1);
            }
            (*in)>>us;
            return us;
        }

        jint QtDataInputStream::readInt() {
            jint i;
            while (available() < 4) {
                waitForReadyRead(-1);
            }
            (*in) >> i;
            return i;
        }

        jlong QtDataInputStream::readLong() {
            jlong l;
            while (available() < 8) {
                waitForReadyRead(-1);
            }
            (*in) >> l;
            return l;
        }

        // In versions Qt 4.5 and before, the floating point precision
        // is implicitly dealt with by the corresponding operator<<()
        // and operator>>().
        // In versions Qt 4.6 and after, the floating point precision
        // has to be set explicitly. It is double by default.
        float QtDataInputStream::readFloat() {
            int ver = in->version();
            in->setVersion(QDataStream::Qt_4_5);
            float f;
            while (available() < 4) {
                waitForReadyRead(-1);
            }
            (*in) >> f;
            in->setVersion(ver);
            return f;
        }

        double QtDataInputStream::readDouble() {
            double d;
            while (available() < 8) {
                waitForReadyRead(-1);
            }
            (*in)>>d;
            return d;
        }

        char QtDataInputStream::readChar() {
            jbyte c;
            while (available() < 2) {
                waitForReadyRead(-1);
            }
            (*in) >> c;
            (*in) >> c;
            return c;
        }

        bool QtDataInputStream::readBool() {
            bool b;
            while (available() < 1) {
                waitForReadyRead(-1);
            }
            (*in)>>b;
            return b;
        }

        void QtDataInputStream::close(){
            this->in->setDevice(0);
        }

        QtDataInputStream::~QtDataInputStream() {
        }
    }
}
