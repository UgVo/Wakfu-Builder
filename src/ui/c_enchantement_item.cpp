#include "c_enchantement_item.h"
#include "ui_c_enchantement_item.h"
#include "c_enchantement_display.h"

c_enchantement_item::c_enchantement_item(QWidget *parent,  QString emplacement) :
    QWidget(parent),
    ui(new Ui::c_enchantement_item)
{
    ui->setupUi(this);
    _level = 0;
    _block = false;
    _emplacement = emplacement;
    _parent = parent;
    setButtonStyle(ui->toolButton);
    ui->widget_4->setStyleSheet(QString("#widget_4 {background-color : %1; border : 1px solid %2; border-radius : 3px;}").arg(app_color::dark_blue).arg(app_color::grey_blue_3));
    QObject::connect(ui->toolButton,&QToolButton::clicked,this,&c_enchantement_item::slot_positionClicked);
    _chasse_list.push_back(c_enchantement_chasse());
    _chasse_list.push_back(c_enchantement_chasse());
    _chasse_list.push_back(c_enchantement_chasse());
    _chasse_list.push_back(c_enchantement_chasse());

    _tool_buttons.push_back(new c_tool_button(this));
    ui->horizontalLayout->insertWidget(1,_tool_buttons.last());
    _tool_buttons.push_back(new c_tool_button(this));
    ui->horizontalLayout->insertWidget(2,_tool_buttons.last());
    _tool_buttons.push_back(new c_tool_button(this));
    ui->horizontalLayout->insertWidget(3,_tool_buttons.last());
    _tool_buttons.push_back(new c_tool_button(this));
    ui->horizontalLayout->insertWidget(4,_tool_buttons.last());



    foreach (c_tool_button* button, _tool_buttons) {
        QObject::connect(button,&QToolButton::clicked,this,&c_enchantement_item::slot_slotClicked);
        QObject::connect(button,&c_tool_button::rightClicked,this,&c_enchantement_item::slot_slotRightClicked);
        button->setMinimumSize(QSize(30,30));
        button->setMaximumSize(QSize(30,30));
        button->setStyleSheet(  "background-color : #6A8BA8; "
                                "color : white;"
                                "border: 1px solid white;"
                                "border-radius : 3px;");
    }

    updateView();
}

c_enchantement_item::~c_enchantement_item()
{
    delete ui;
}

void c_enchantement_item::updateView() {
    if (_emplacement.contains("HAND")) {
        ui->toolButton->setIcon(QIcon(QString(":/images/divers/smallring.png")));
    } else {
        ui->toolButton->setIcon(QIcon(QString(":/images/divers/small%1.png").arg(_emplacement.toLower())));
    }

    for (int i = 0; i < _chasse_list.size(); ++i) {
        if(_chasse_list[i].color()) {
            QMap<QString, int> val = _chasse_list[i].computeBonus(_emplacement);
            QString key = _chasse_list[i].effect().effect();
            if (_chasse_list[i].white()) {
                _tool_buttons[i]->setIcon(QIcon(QString(":/images/shard/shard4.png")));
            } else {
                _tool_buttons[i]->setIcon(QIcon(QString(":/images/shard/shard%1.png").arg(_chasse_list[i].color())));
            }
            _tool_buttons[i]->setIconSize(QSize(30,30));
            _tool_buttons[i]->setToolTip(QString("%1 %2").arg(val[key]).arg(key));
        } else {
            _tool_buttons[i]->setIcon(QIcon());
        }
    }
    qDebug() << computeBonus();
}

void c_enchantement_item::setButtonStyle(QToolButton *bt) {
    bt->setAutoFillBackground(true);
    bt->setIconSize(QSize(30,30));
    bt->setAutoRaise(true);
    bt->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
}

void c_enchantement_item::slot_highlightPosition(bool flag) {
    if (flag) {
        ui->widget_4->setStyleSheet(QString("#widget_4 {background-color : %1; border : 2px solid white; border-radius : 3px;}").arg(app_color::dark_blue));
    } else {
        ui->widget_4->setStyleSheet(QString("#widget_4 {background-color : %1; border : 1px solid %2; border-radius : 3px;}").arg(app_color::dark_blue).arg(app_color::grey_blue_3));
    }
}

void c_enchantement_item::slot_positionClicked() {
    emit positionSelected(_emplacement);
}

void c_enchantement_item::slot_slotClicked() {
    c_tool_button * sender = static_cast<c_tool_button*>(this->sender());
    c_enchantement_effect effect = static_cast<c_enchantement_display*>(_parent)->selected_effect();

    for (int i = 0; i < _tool_buttons.size(); ++i) {
        if (sender == _tool_buttons[i]) {
            if (_chasse_list[i].color()) {
                _chasse_list[i].setWhite(!_chasse_list[i].white());
            } else {
                _chasse_list[i] = c_enchantement_chasse(0,effect);
                _chasse_list[i].setLevel(_level);
            }
        }
    }
    updateView();
    emit enchantSetUpdated();
}

void c_enchantement_item::slot_slotRightClicked() {
    c_tool_button * sender = static_cast<c_tool_button*>(this->sender());
    for (int i = 0; i < _tool_buttons.size(); ++i) {
        if (sender == _tool_buttons[i]) {
            _chasse_list[i] = c_enchantement_chasse();
        }
    }
    updateView();
    emit enchantSetUpdated();
}

void c_enchantement_item::setLevel(int level) {
    _level = level;
    foreach (c_enchantement_chasse chasse, _chasse_list) {
        chasse.setLevel(_level);
    }
}

QMap<QString, int> c_enchantement_item::computeBonus() {
    QMap<QString, int> res;
    foreach (c_enchantement_chasse chasse, _chasse_list) {
        QMap<QString, int> val = chasse.computeBonus(_emplacement);
        if (!val.isEmpty()) {
            foreach (QString key, val.keys()) {
                res[key] += val[key];
            }
        }
    }
    return res;
}

void c_enchantement_item::setChasse_list(const QList<c_enchantement_chasse> &chasse_list) {
    _chasse_list = chasse_list;
    updateView();
}

int c_enchantement_item::level() const
{
    return _level;
}

QList<c_enchantement_chasse> c_enchantement_item::chasse_list() const
{
    return _chasse_list;
}

QString c_enchantement_item::emplacement() const {
    return _emplacement;
}
