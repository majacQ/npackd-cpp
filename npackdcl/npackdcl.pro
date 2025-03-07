# -------------------------------------------------
# Project created by QtCreator 2010-11-21T18:29:49
# -------------------------------------------------
QT += xml
QT -= gui
TARGET = npackdcl
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
RC_FILE = npackdcl.rc
INCLUDEPATH += ..\\quazip\\quazip ..\\zlib
LIBS += ..\\quazip\\quazip\\release\\libquazip.a \
    ..\\zlib\\libz.a \
    -lole32 -luuid -lwininet -lpsapi -lversion \
    ..\\wpmcpp\\libmsi.a
SOURCES += main.cpp \
    ../wpmcpp/repository.cpp \
    ../wpmcpp/version.cpp \
    ../wpmcpp/packageversionfile.cpp \
    ../wpmcpp/package.cpp \
    ../wpmcpp/packageversion.cpp \
    ../wpmcpp/job.cpp \
    ../wpmcpp/installoperation.cpp \
    ../wpmcpp/dependency.cpp \
    ../wpmcpp/wpmutils.cpp \
    ../wpmcpp/downloader.cpp \
    ../wpmcpp/license.cpp \
    ../wpmcpp/windowsregistry.cpp \
    ../wpmcpp/detectfile.cpp \
    app.cpp \
    ../wpmcpp/commandline.cpp \
    ../wpmcpp/xmlutils.cpp
HEADERS += ../wpmcpp/repository.h \
    ../wpmcpp/version.h \
    ../wpmcpp/packageversionfile.h \
    ../wpmcpp/package.h \
    ../wpmcpp/packageversion.h \
    ../wpmcpp/job.h \
    ../wpmcpp/installoperation.h \
    ../wpmcpp/dependency.h \
    ../wpmcpp/wpmutils.h \
    ../wpmcpp/msi.h \
    ../wpmcpp/downloader.h \
    ../wpmcpp/license.h \
    ../wpmcpp/windowsregistry.h \
    ../wpmcpp/detectfile.h \
    app.h \
    ../wpmcpp/commandline.h \
    ../wpmcpp/xmlutils.h
FORMS += 
