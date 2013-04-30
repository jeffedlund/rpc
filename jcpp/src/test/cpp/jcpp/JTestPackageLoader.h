#ifndef JTESTPACKAGELOADER_H
#define JTESTPACKAGELOADER_H

#include <QObject>
#include "JIPackageLoader.h"
#include "QtPlugin"

using namespace jcpp::lang::reflect;

class JTestPackageLoader : public QObject, public JIPackageLoader{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "jtestpackageloader" )
    Q_INTERFACES(jcpp::lang::reflect::JIPackageLoader)

public:
    virtual JPackage* getPackage();
};

#endif // JTESTPACKAGELOADER_H
