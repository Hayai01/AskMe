QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apunte.cpp \
    apunteform.cpp \
    asignatura.cpp \
    cuestionario.cpp \
    cuestionarioform.cpp \
    main.cpp \
    askme.cpp \
    pregunta.cpp \
    preguntaform.cpp \
    resultadosform.cpp \
    tema.cpp

HEADERS += \
    apunte.h \
    apunteform.h \
    asignatura.h \
    askme.h \
    cuestionario.h \
    cuestionarioform.h \
    pregunta.h \
    preguntaform.h \
    resultadosform.h \
    tema.h

FORMS += \
    apunteform.ui \
    askme.ui \
    cuestionarioform.ui \
    preguntaform.ui \
    resultadosform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    diagrama.qmodel
