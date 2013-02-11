#include "JOutputStream.h"
#include "JIndexOutOfBoundsException.h"
#include "JNullPointerException.h"

namespace jcpp{
    namespace io{
        class JOutputStreamClass : public JClass{
        public:
            JOutputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.OutputStream";
                name="java.io.OutputStream";
                simpleName="OutputStream";
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JOutputStream();
            }
        };

        static JClass* clazz;

        JClass* JOutputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JOutputStreamClass();
            }
            return clazz;
        }

        JOutputStream::JOutputStream():JObject(getClazz()){
        }

        JOutputStream::JOutputStream(JClass* _class):JObject(_class){
        }

        void JOutputStream::write(qint32 b){
        }

        void JOutputStream::write(qint8 b[]){
            qint32 length = sizeof(b);
            write(b, 0, length);
        }

        void JOutputStream::write(qint8 b[], int off, int len){
            if (b == 0) {
                throw new JNullPointerException();
            } else {
                qint32 length = len;
                if ((off < 0) || (off > length) || (len < 0) || ((off + len) > length) || ((off + len) < 0)) {
                    throw new JIndexOutOfBoundsException();
                } else if (len == 0) {
                    return;
                }
                for (int i = 0 ; i < len ; i++) {
                    write(b[off + i]);
                }
            }
        }


        void JOutputStream::close(){
        }

        void JOutputStream::flush(){
        }

        void JOutputStream::writeBoolean(bool v){
        }

        void JOutputStream::writeByte(qint8 v){
        }

        void JOutputStream::writeChar(quint16 v){
        }

        void JOutputStream::writeDouble(double v){
        }

        void JOutputStream::writeFloat(float v){
        }

        void JOutputStream::writeInt(qint32 v){
        }

        void JOutputStream::writeLong(qint64 v){
        }

        void JOutputStream::writeShort(qint16 v){
        }
    }
}
