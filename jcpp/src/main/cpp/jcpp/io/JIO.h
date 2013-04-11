#ifndef JIO_H
#define JIO_H

#include "JBlockDataInputStream.h"
#include "JBlockDataOutputStream.h"
#include "JBits.h"
#include "JBufferedInputStream.h"
#include "JBufferedOutputStream.h"
#include "JDataInput.h"
#include "JDataInputStream.h"
#include "JDataOutput.h"
#include "JDataOutputStream.h"
#include "JEOFException.h"
#include "JExternalizable.h"
#include "JFilterInputStream.h"
#include "JFilterOutputStream.h"
#include "JInputStream.h"
#include "JInvalidClassException.h"
#include "JInvalidObjectException.h"
#include "JIOException.h"
#include "JNotActiveException.h"
#include "JNotSerializableException.h"
#include "JObjectInput.h"
#include "JObjectInputStream.h"
#include "JObjectOutput.h"
#include "JObjectOutputStream.h"
#include "JObjectStreamClass.h"
#include "JObjectStreamException.h"
#include "JObjectStreamConstants.h"
#include "JObjectStreamField.h"
#include "JOptionalDataException.h"
#include "JOutputStream.h"
#include "JSerializable.h"
#include "JStreamCorruptedException.h"
#include "JUTFDataFormatException.h"
#include "QtDataInputStream.h"
#include "QtDataOutputStream.h"
#include "JPackage.h"
#include "JCPP_PACKAGE.h"
#include "JCPP.h"
using namespace std;
using namespace std;
using namespace jcpp::lang::reflect;
using namespace jcpp;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JIO : public JPackage{
        protected:
            JIO();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JIO* getPackage();

            virtual ~JIO();
        };
    }
}

#endif // JIO_H
