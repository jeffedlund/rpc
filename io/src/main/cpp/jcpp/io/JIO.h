#ifndef JIO_H
#define JIO_H

#include "JDataInputStream.h"
#include "JDataOutputStream.h"
#include "JEOFException.h"
#include "JExternalizable.h"
#include "JInputStream.h"
#include "JInvalidClassException.h"
#include "JIOException.h"
#include "JNotActiveException.h"
#include "JNotSerializableException.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JObjectStreamClass.h"
#include "JObjectStreamException.h"
#include "JOptionalDataException.h"
#include "JOutputStream.h"
#include "JSerializable.h"
#include "JStreamCorruptedException.h"
#include "JUTFDataFormatException.h"
#include "QtDataInputStream.h"
#include "QtDataOutputStream.h"
#include "JPackage.h"
#include "JCPP.h"
using namespace std;
using namespace std;
using namespace jcpp::lang::reflect;
using namespace jcpp;

namespace jcpp{
    namespace io{
        class JIO : public JPackage{
        protected:
            JIO();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JIO* getPackage();
        };
    }
}

#endif // JIO_H
