QT       += core gui

lessThan(QT_MAJOR_VERSION, 5) {
    QT += openglwidgets
} else {
    QT += opengl
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
QMAKE_CXXFLAGS += -Wall -Wextra -std=c++17 -Wno-sign-compare
INCLUDEPATH += ../src


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(./QtGifImage-master/src/gifimage/qtgifimage.pri)

SOURCES += \
    ./main.cc \
    ./View/View.cc \
    ./View/MyGLWidget.cc \
    ./View/TypeSavingModel.cc \
    ./View/SavingBmp.cc \
    ./View/SavingJpeg.cc \
    ./View/Setting.cc \
    ./Controller/Controller.cc \
    ./Model/Facade.cc \
    ./Model/FacadeOperationResult.cc \
    ./Model/FileReader.cc \
    ./Model/Model.cc \
    ./Model/MovedModel.cc \
    ./Model/RotatedModel.cc \
    ./Model/ScaledModel.cc \
    ./Model/OffsetScene.cc

HEADERS += \
    ./View/View.h \
    ./View/MyGLWidget.h \
    ./View/SavingModelStrategy.h \
    ./View/TypeSavingModel.h \
    ./View/SavingBmp.h \
    ./View/SavingJpeg.h \
    ./View/Setting.h \
    ./Controller/Controller.h \
    ./Model/Facade.h \
    ./Model/FacadeOperationResult.h \
    ./Model/FileReader.h \
    ./Model/Model.h \
    ./Model/MovedModel.h \
    ./Model/RotatedModel.h \
    ./Model/ScaledModel.h \
    ./Model/OffsetScene.h

FORMS += \
    ./View/View.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
