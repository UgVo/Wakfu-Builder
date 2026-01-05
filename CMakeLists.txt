cmake_minimum_required(VERSION 3.16)

set(target builder_Wakfu)
project(${target} VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS 
    Widgets 
    Sql 
    Concurrent 
    Core 
    Gui 
    Network 
    Quick 
    QuickWidgets 
    QuickControls2 
    Qml
)

qt_standard_project_setup()

set(ui_dir ${PROJECT_SOURCE_DIR}/src/ui)
set(utils_dir ${PROJECT_SOURCE_DIR}/src/utilities)

set(ui_sources
    ${ui_dir}/c_aptitude_unite.cpp 
    ${ui_dir}/c_aptitudes_display.cpp 
    ${ui_dir}/c_bdd_password_dialog.cpp 
    ${ui_dir}/c_build_display.cpp 
    ${ui_dir}/c_builder_view.cpp 
    ${ui_dir}/c_button_delegate.cpp 
    ${ui_dir}/c_class_selection.cpp 
    ${ui_dir}/c_dialoggestion.cpp 
    ${ui_dir}/c_element_dialog.cpp 
    ${ui_dir}/c_element_popup_widget.cpp 
    ${ui_dir}/c_elements_display.cpp 
    ${ui_dir}/c_enchantement_display.cpp 
    ${ui_dir}/c_enchantement_item.cpp 
    ${ui_dir}/c_enchantement_lite.cpp 
    ${ui_dir}/c_entry_point.cpp 
    ${ui_dir}/c_item_display.cpp 
    ${ui_dir}/c_item_lite.cpp
    ${ui_dir}/c_item_viewer.cpp
    ${ui_dir}/c_load_builder_dialog.cpp 
    ${ui_dir}/c_result_display.cpp 
    ${ui_dir}/c_search_widget.cpp 
    ${ui_dir}/c_status_build.cpp 
    ${ui_dir}/c_theory_craft_resume.cpp 
    ${ui_dir}/c_tool_button.cpp   
)

set(ui_forms
    ${ui_dir}/c_aptitude_unite.ui
    ${ui_dir}/c_aptitudes_display.ui
    ${ui_dir}/c_bdd_password_dialog.ui
    ${ui_dir}/c_build_display.ui
    ${ui_dir}/c_builder_view.ui
    ${ui_dir}/c_class_selection.ui
    ${ui_dir}/c_dialoggestion.ui
    ${ui_dir}/c_element_dialog.ui
    ${ui_dir}/c_element_popup_widget.ui
    ${ui_dir}/c_elements_display.ui
    ${ui_dir}/c_enchantement_display.ui
    ${ui_dir}/c_enchantement_item.ui
    ${ui_dir}/c_enchantement_lite.ui
    ${ui_dir}/c_entry_point.ui
    ${ui_dir}/c_item_display.ui 
    ${ui_dir}/c_item_lite.ui 
    ${ui_dir}/c_item_viewer.ui
    ${ui_dir}/c_load_builder_dialog.ui
    ${ui_dir}/c_result_display.ui
    ${ui_dir}/c_search_widget.ui
    ${ui_dir}/c_status_build.ui
    ${ui_dir}/c_theory_craft_resume.ui
)

set(utils_sources
    ${utils_dir}/c_action.cpp
    ${utils_dir}/c_build.cpp
    ${utils_dir}/c_calcul.cpp
    ${utils_dir}/c_datamanager.cpp
    ${utils_dir}/c_dbmanager.cpp
    ${utils_dir}/c_effect.cpp
    ${utils_dir}/c_enchantement_chasse.cpp
    ${utils_dir}/c_enchantement_effect.cpp
    ${utils_dir}/c_equipmentitemtypes.cpp
    ${utils_dir}/c_io_manager.cpp
    ${utils_dir}/c_item_model.cpp
    ${utils_dir}/c_item.cpp
    ${utils_dir}/c_itemproperties.cpp
    ${utils_dir}/c_networkmanager.cpp
    ${utils_dir}/c_save_builder_model.cpp
    ${utils_dir}/c_state.cpp
    ${utils_dir}/tokenizer.cpp
)

qt_add_executable(${target}
    resources/resources.qrc
    src/main.cpp
    src/mainwindow.cpp 
    src/mainwindow.h
    src/mainwindow.ui
    ${ui_sources}
    ${ui_forms}
    ${utils_sources}
)
target_include_directories(${target} PRIVATE
    #${ui_dir}
    #${utils_dir}
    ${PROJECT_SOURCE_DIR}/src
)

target_compile_definitions(${target} PRIVATE
    QT_DEPRECATED_WARNINGS
)

target_link_libraries(${target} PRIVATE
    Qt::Widgets
    Qt::Concurrent
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Quick
    Qt::QuickWidgets
    Qt::QuickControls2
    Qt::Sql
    Qt::Qml
)

set(fonts_resource_files
    "resources/wci.ttf"
)

qt_add_resources(${target} "font"
    PREFIX
        "/font"
    BASE
        "resources"
    FILES
        ${fonts_resource_files}
)

set(qml_resource_files
    "resources/qck_double_slider.qml"
)

qt_add_resources(${target} "qml"
    PREFIX
        "/qml"
    BASE
        "resources"
    FILES
        ${qml_resource_files}
)

install(TARGETS ${target}
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET ${target}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
