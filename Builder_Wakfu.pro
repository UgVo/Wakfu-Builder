QT       += core gui \
            sql \
            network \
            concurrent \
            quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += qtquickcompiler

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

RC_ICONS = resources/icon.ico

INCLUDEPATH += \
        $$PWD/src/

VPATH += \
        $$PWD/src/

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/ui/c_button_delegate.cpp \
    src/ui/c_class_selection.cpp \
    src/ui/c_theory_craft_resume.cpp \
    ui/c_aptitude_unite.cpp \
    ui/c_aptitudes_display.cpp \
    ui/c_bdd_password_dialog.cpp \
    ui/c_build_display.cpp \
    ui/c_builder_view.cpp \
    ui/c_dialoggestion.cpp \
    ui/c_element_dialog.cpp \
    ui/c_element_popup_widget.cpp \
    ui/c_elements_display.cpp \
    ui/c_entry_point.cpp \
    ui/c_item_display.cpp \
    ui/c_item_lite.cpp \
    ui/c_item_viewer.cpp \
    ui/c_load_builder_dialog.cpp \
    ui/c_result_display.cpp \
    ui/c_search_widget.cpp \
    ui/c_status_build.cpp \
    utilities/c_action.cpp \
    utilities/c_build.cpp \
    utilities/c_calcul.cpp \
    utilities/c_datamanager.cpp \
    utilities/c_dbmanager.cpp \
    utilities/c_equipmentitemtypes.cpp \
    utilities/c_io_manager.cpp \
    utilities/c_item.cpp \
    utilities/c_effect.cpp \
    utilities/c_itemproperties.cpp \
    utilities/c_networkmanager.cpp \
    utilities/c_save_builder_model.cpp \
    utilities/c_state.cpp \
    utilities/c_tokenizer.cpp \
    utilities/c_item_model.cpp\

HEADERS += \
    mainwindow.h \
    src/ui/c_button_delegate.h \
    src/ui/c_class_selection.h \
    src/ui/c_theory_craft_resume.h \
    ui/c_aptitude_unite.h \
    ui/c_aptitudes_display.h \
    ui/c_bdd_password_dialog.h \
    ui/c_build_display.h \
    ui/c_builder_view.h \
    ui/c_dialoggestion.h \
    ui/c_element_dialog.h \
    ui/c_element_popup_widget.h \
    ui/c_elements_display.h \
    ui/c_entry_point.h \
    ui/c_item_display.h \
    ui/c_item_lite.h \
    ui/c_item_viewer.h \
    ui/c_load_builder_dialog.h \
    ui/c_result_display.h \
    ui/c_search_widget.h \
    ui/c_status_build.h \
    ui/ui.h \
    utilities/c_action.h \
    utilities/c_build.h \
    utilities/c_calcul.h \
    utilities/c_datamanager.h \
    utilities/c_dbmanager.h \
    utilities/c_equipmentitemtypes.h \
    utilities/c_io_manager.h \
    utilities/c_item.h \
    utilities/c_effect.h \
    utilities/c_itemproperties.h \
    utilities/c_networkmanager.h \
    utilities/c_save_builder_model.h \
    utilities/c_state.h \
    utilities/c_tokenizer.h \
    utilities/c_item_model.h \
    utilities/utilities.h

FORMS += \
    mainwindow.ui \
    src/ui/c_class_selection.ui \
    src/ui/c_theory_craft_resume.ui \
    ui/c_aptitude_unite.ui \
    ui/c_aptitudes_display.ui \
    ui/c_bdd_password_dialog.ui \
    ui/c_build_display.ui \
    ui/c_builder_view.ui \
    ui/c_dialoggestion.ui \
    ui/c_element_dialog.ui \
    ui/c_element_popup_widget.ui \
    ui/c_elements_display.ui \
    ui/c_entry_point.ui \
    ui/c_item_display.ui \
    ui/c_item_lite.ui \
    ui/c_item_viewer.ui \
    ui/c_load_builder_dialog.ui \
    ui/c_result_display.ui \
    ui/c_search_widget.ui \
    ui/c_status_build.ui

TRANSLATIONS += \
    Builder_Wakfu_fr_FR.ts

DESTDIR = $$PWD

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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

RESOURCES += \
    resources/resources.qrc \
