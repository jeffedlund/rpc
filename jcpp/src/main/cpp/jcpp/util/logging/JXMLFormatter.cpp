#include "JXMLFormatter.h"
#include "JClass.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JXMLFormatterClass : public JClass{
                public:
                    JXMLFormatterClass(){
                        this->canonicalName="java.util.logging.XMLFormatter";
                        this->name="java.util.logging.XMLFormatter";
                        this->simpleName="XMLFormatter";
                        this->serialVersionUID=0ULL;
                    }

                    JClass* getSuperclass(){
                        return JFormatter::getClazz();
                    }

                    JObject* newInstance(){
                        return new JXMLFormatter();
                    }
            };

            static JClass* clazz;

            JClass* JXMLFormatter::getClazz(){
                if (clazz==NULL){
                    clazz=new JXMLFormatterClass();
                }
                return clazz;
            }

            JXMLFormatter::JXMLFormatter():JFormatter(getClazz()){
                this->manager=JLogManager::getLogManager();
            }

            void JXMLFormatter::a2(JStringBuffer* sb, jint x) {
                if (x < 10) {
                    sb->append('0');
                }
                sb->append(x);
            }

            void JXMLFormatter::appendISO8601(JStringBuffer* sb, jlong millis) {
                /*TODO
                 *JDate* date = new JDate(millis);
                sb->append(date->getYear() + 1900);
                sb->append('-');
                a2(sb, date->getMonth() + 1);
                sb->append('-');
                a2(sb, date->getDate());
                sb->append('T');
                a2(sb, date->getHours());
                sb->append(':');
                a2(sb, date->getMinutes());
                sb->append(':');
                a2(sb, date->getSeconds());*/
                sb->append("Time :");
                sb->append(millis);
            }

            void JXMLFormatter::escape(JStringBuffer* sb, JString text) {
                for (jint i = 0; i < text.length(); i++) {
                    jchar ch = text.charAt(i);
                    if (ch == '<') {
                        sb->append("&lt;");
                    } else if (ch == '>') {
                        sb->append("&gt;");
                    } else if (ch == '&') {
                        sb->append("&amp;");
                    } else {
                        sb->append(ch);
                    }
                }
            }

            JString JXMLFormatter::format(JLogRecord* record) {
                JStringBuffer* sb = new JStringBuffer();
                sb->append("<record>\n");

                sb->append("  <date>");
                appendISO8601(sb, record->getMillis());
                sb->append("</date>\n");

                sb->append("  <millis>");
                sb->append(record->getMillis());
                sb->append("</millis>\n");

                sb->append("  <sequence>");
                sb->append(record->getSequenceNumber());
                sb->append("</sequence>\n");

                JString name = record->getLoggerName();
                if (name != "") {
                    sb->append("  <logger>");
                    escape(sb, name);
                    sb->append("</logger>\n");
                }

                sb->append("  <level>");
                escape(sb, record->getLevel()->toString());
                sb->append("</level>\n");

                if (record->getSourceClassName() != NULL) {
                    sb->append("  <class>");
                    escape(sb, record->getSourceClassName());
                    sb->append("</class>\n");
                }

                if (record->getSourceMethodName() != NULL) {
                    sb->append("  <method>");
                    escape(sb, record->getSourceMethodName());
                    sb->append("</method>\n");
                }

                sb->append("  <thread>");
                sb->append(record->getThreadID());
                sb->append("</thread>\n");

                if (record->getMessage() != NULL) {
                    JString message = formatMessage(record);
                    sb->append("  <message>");
                    escape(sb, message);
                    sb->append("</message>");
                    sb->append("\n");
                }

                JPrimitiveArray* parameters = record->getParameters();
                if ( parameters != NULL && parameters->size() != 0 && record->getMessage()->indexOf("{") == -1 ) {
                    for (int i = 0; i < parameters->size(); i++) {
                        sb->append("  <param>");
                        try {
                            escape(sb, parameters->get(i)->toString());
                        } catch (JException* ex) {
                            delete ex;
                            sb->append("???");
                        }
                        sb->append("</param>\n");
                    }
                }

                if (record->getThrown() != NULL) {
                    JThrowable* th = record->getThrown();
                    sb->append("  <exception>\n");
                    sb->append("    <message>");
                    escape(sb, th->toString());
                    sb->append("</message>\n");
                    JPrimitiveArray* trace = th->getStackTrace();
                    for (int i = 0; i < trace->size(); i++) {
                        JStackTraceElement* frame = (JStackTraceElement*)trace->get(i);
                        sb->append("    <frame>\n");
                        sb->append("      <class>");
                        escape(sb, frame->getDeclaringClass());
                        sb->append("</class>\n");
                        sb->append("      <method>");
                        escape(sb, frame->getMethodName());
                        sb->append("</method>\n");
                        if (frame->getLineNumber() >= 0) {
                            sb->append("      <line>");
                            sb->append(frame->getLineNumber());
                            sb->append("</line>\n");
                        }
                        sb->append("    </frame>\n");
                    }
                    sb->append("  </exception>\n");
                }
                sb->append("</record>\n");
                return sb->toString();
            }

            JString JXMLFormatter::getHead(JHandler* h) {
                JStringBuffer* sb = new JStringBuffer();
                JString encoding;
                sb->append("<?xml version=\"1.0\"");
                if (h != NULL) {
                    encoding = h->getEncoding();
                } else {
                    encoding = "";
                }

                /*
                if (encoding == "") {
                    //TODO encoding = java.nio.charset.Charset.defaultCharset().name();
                }
                try {
                    JCharset* cs = JCharset::forName(encoding);
                    encoding = cs->name();
                } catch (JException* ex) {
                }*/

                sb->append(" encoding=\"");
                sb->append(encoding);
                sb->append("\"");
                sb->append(" standalone=\"no\"?>\n");
                sb->append("<!DOCTYPE log SYSTEM \"logger.dtd\">\n");
                sb->append("<log>\n");
                return sb->toString();
            }

            JString JXMLFormatter::getTail(JHandler*) {
                return "</log>\n";
            }

            JXMLFormatter::~JXMLFormatter(){
            }
       }
    }
}
