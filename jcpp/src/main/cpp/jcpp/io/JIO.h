#ifndef JIO_H
#define JIO_H

#include "JBlockDataInputStream.h"
#include "JBlockDataOutputStream.h"
#include "JBits.h"
#include "JBufferedInputStream.h"
#include "JBufferedOutputStream.h"
#include "JBufferedWriter.h"
#include "JBufferedReader.h"
#include "JByteArrayInputStream.h"
#include "JByteArrayOutputStream.h"
#include "JCharArrayReader.h"
#include "JCharArrayWriter.h"
#include "JCharConversionException.h"
#include "JCloseable.h"
#include "JDataInput.h"
#include "JDataInputStream.h"
#include "JDataOutput.h"
#include "JDataOutputStream.h"
#include "JDefaultFileSystem.h"
#include "JEOFException.h"
#include "JExternalizable.h"
#include "JFile.h"
#include "JFileFilter.h"
#include "JFileInputStream.h"
#include "JFilenameFilter.h"
#include "JFileNotFoundException.h"
#include "JFileOutputStream.h"
#include "JFileReader.h"
#include "JFileWriter.h"
#include "JFilterInputStream.h"
#include "JFilterOutputStream.h"
#include "JFilterReader.h"
#include "JFilterWriter.h"
#include "JFlushable.h"
#include "JInputStream.h"
#include "JInputStreamReader.h"
#include "JInterruptedIOException.h"
#include "JInvalidClassException.h"
#include "JInvalidObjectException.h"
#include "JIOError.h"
#include "JIOException.h"
#include "JIOFileSystem.h"
#include "JLineNumberReader.h"
#include "JNotActiveException.h"
#include "JNotSerializableException.h"
#include "JObjectInput.h"
#include "JObjectInputStream.h"
#include "JObjectInputValidation.h"
#include "JObjectOutput.h"
#include "JObjectOutputStream.h"
#include "JObjectStreamClass.h"
#include "JObjectStreamException.h"
#include "JObjectStreamConstants.h"
#include "JObjectStreamField.h"
#include "JOptionalDataException.h"
#include "JOutputStream.h"
#include "JOutputStreamWriter.h"
#include "JPipedInputStream.h"
#include "JPipedOutputStream.h"
#include "JPipedReader.h"
#include "JPipedWriter.h"
#include "JPushbackInputStream.h"
#include "JPushbackReader.h"
#include "JReader.h"
#include "JSequenceInputStream.h"
#include "JSerializable.h"
#include "JSerializablePermission.h"
#include "JStreamCorruptedException.h"
#include "JStringBufferInputStream.h"
#include "JStringReader.h"
#include "JStringWriter.h"
#include "JSyncFailedException.h"
#include "JUnsupportedEncodingException.h"
#include "JUTFDataFormatException.h"
#include "JWinNTFileSystem.h"
#include "JWriteAbortedException.h"
#include "JWriter.h"
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
