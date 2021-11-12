QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addform.cpp \
    editform.cpp \
    main.cpp \
    mainwindow.cpp \
    mylist.cpp \
    mylistitem.cpp \
    onewarningform.cpp \
    prefform.cpp \
    warningform.cpp

HEADERS += \
    addform.h \
    editform.h \
    mainwindow.h \
    mylist.h \
    mylistitem.h \
    onewarningform.h \
    prefform.h \
    warningform.h

FORMS += \
    addform.ui \
    editform.ui \
    mainwindow.ui \
    onewarningform.ui \
    prefform.ui \
    warningform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    AddButton.png \
    Avatar.png \
    BookIco.png \
    DeleteButton.png \
    EditButton.png \
    Error.png \
    ExitButton.png \
    ExitButtonPressed.png \
    FindError.png \
    FindLoading.png \
    HomeButton.png \
    LoadingIcon.png \
    OpenButton.png \
    PlayIco.png \
    PreferencesButton.png \
    SaveButton.png \
    Warning.png
