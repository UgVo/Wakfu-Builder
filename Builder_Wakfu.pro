QT       += core gui \
            sql \
            network \
            concurrent \
            testlib \
            quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

#DEFINES  += QT_NO_SSL

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ui/c_build_display.cpp \
    ui/c_dialoggestion.cpp \
    ui/c_item_display.cpp \
    ui/c_item_lite.cpp \
    ui/c_item_viewer.cpp \
    ui/c_result_display.cpp \
    ui/c_search_widget.cpp \
    utilities/c_action.cpp \
    utilities/c_build.cpp \
    utilities/c_calcul.cpp \
    utilities/c_datamanager.cpp \
    utilities/c_dbmanager.cpp \
    utilities/c_equipmentitemtypes.cpp \
    utilities/c_item.cpp \
    utilities/c_effect.cpp \
    utilities/c_itemproperties.cpp \
    utilities/c_networkmanager.cpp \
    utilities/c_state.cpp \
    utilities/c_tokenizer.cpp \
    utilities/c_item_model.cpp\
    utilities/c_item_model.cpp

HEADERS += \
    mainwindow.h \
    ui/c_build_display.h \
    ui/c_dialoggestion.h \
    ui/c_item_display.h \
    ui/c_item_lite.h \
    ui/c_item_viewer.h \
    ui/c_result_display.h \
    ui/c_search_widget.h \
    ui/ui.h \
    utilities/c_action.h \
    utilities/c_build.h \
    utilities/c_calcul.h \
    utilities/c_datamanager.h \
    utilities/c_dbmanager.h \
    utilities/c_equipmentitemtypes.h \
    utilities/c_item.h \
    utilities/c_effect.h \
    utilities/c_itemproperties.h \
    utilities/c_networkmanager.h \
    utilities/c_state.h \
    utilities/c_tokenizer.h \
    utilities/c_item_model.h \
    utilities/utilities.h

FORMS += \
    mainwindow.ui \
    ui/c_build_display.ui \
    ui/c_dialoggestion.ui \
    ui/c_item_display.ui \
    ui/c_item_lite.ui \
    ui/c_item_viewer.ui \
    ui/c_result_display.ui \
    ui/c_search_widget.ui

TRANSLATIONS += \
    Builder_Wakfu_fr_FR.ts

DESTDIR = $$PWD

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#INCLUDEPATH += $$PWD\openssl\include
#LIBS += $$PWD\openssl\lib\libcrypto.lib
#LIBS += $$PWD\openssl\lib\libssl.lib

#OPENSSL_LIBS='-L$$PWD/openssl/lib -lssl -lcrypto' ./configure -openssl-linked

DISTFILES += \
    bdd/setup_database.sql \
    json/actions.json \
    json/config.json \
    json/equipmentItemTypes.json \
    json/itemProperties.json \
    json/items.json \
    json/rarity.json \
    ressources/loading.gif \
    ressources/update32.png \
    test.qmodel \
    ui/qck_double_slider.qml

RESOURCES += images/images.qrc
