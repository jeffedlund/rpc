#include "JIO.h"

namespace jcpp{
    namespace io{
        JIO::JIO():JPackage("jcpp.io",JPackage::getClazz()){//better class
            classes->push_back(JDataInputStream::getClazz());
            classes->push_back(JDataOutputStream::getClazz());
            classes->push_back(JEOFException::getClazz());
            classes->push_back(JExternalizable::getClazz());
            classes->push_back(JInputStream::getClazz());
            classes->push_back(JInvalidClassException::getClazz());
            classes->push_back(JIOException::getClazz());
            classes->push_back(JNotActiveException::getClazz());
            classes->push_back(JNotSerializableException::getClazz());
            classes->push_back(JObjectInputStream::getClazz());
            classes->push_back(JObjectOutputStream::getClazz());
            classes->push_back(JObjectStreamClass::getClazz());
            classes->push_back(JObjectStreamException::getClazz());
            classes->push_back(JOptionalDataException::getClazz());
            classes->push_back(JOutputStream::getClazz());
            classes->push_back(JSerializable::getClazz());
            classes->push_back(JStreamCorruptedException::getClazz());
            classes->push_back(JUTFDataFormatException::getClazz());
            classes->push_back(QtDataInputStream::getClazz());
            classes->push_back(QtDataOutputStream::getClazz());
        }

        JPackage* JIO::getSuperPackage(){
            return JCPP::getPackage();
        }

        vector<JPackage*>* JIO::getPackages(){
            if (packages->size()==0){
            }
            return packages;
        }

        static JIO* jio=NULL;

        JIO* JIO::getPackage(){
            if (jio==NULL){
                jio=new JIO();
            }
            return jio;
        }
    }
}

