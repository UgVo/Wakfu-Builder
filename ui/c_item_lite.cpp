#include "c_item_lite.h"
#include "ui_c_item_lite.h"

c_item_lite::c_item_lite(c_dbmanager * database_manager, c_item item, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_item_lite) {
    ui->setupUi(this);
    this->setAttribute(Qt::WA_Hover);
    _parent = parent;
    _item = item;
    setStyleSheet(QString(".c_item_lite {background-color: %1; border: 1px solid %2; border-radius: 4px;}").arg(app_color::dark_blue).arg(app_color::color_rarity.at(_item.getRarity())));
    ui->widget_background->setStyleSheet(QString(".QWidget#widget_background{background-color: %1; border : 1px solid %1; border-radius: 4px;}").arg(app_color::dark_blue));
    QFontMetrics metrics(ui->name->font());
    QString elidedText = metrics.elidedText(item.getName(), Qt::ElideRight, ui->name->width());
    ui->name->setText(elidedText);
    ui->name->setStyleSheet(QString("color : %1").arg(app_color::color_rarity.at(_item.getRarity())));
    ui->lvl->setText(QString("LvL.%1").arg(item.getLvl()));
    ui->lvl->setStyleSheet(QString("background-color: %1; border: 1px solid white; border-radius: 5px; color:white; padding: 2px ").arg(app_color::dark));
    ui->image_widget->setStyleSheet(QString(".QWidget#image_widget{background-color:%1; border-top-left-radius: 3px; border-bottom-left-radius: 3px;}").arg(app_color::green_blue));
    QPixmap image = QPixmap(QString("images/items/%1.png").arg(item.getGfxId()));
    ui->image->setPixmap(image);
    ui->image->setBackgroundRole(QPalette::Base);
    ui->image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->image->setScaledContents(true);

    image = QPixmap("images/divers/smallneck.png");
    ui->icon->setStyleSheet(QString("background-color: %1;").arg(app_color::dark_blue));
    ui->icon->setPixmap(image);
    ui->icon->setBackgroundRole(QPalette::Base);
    ui->icon->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->icon->setScaledContents(true);
    set_icon();
    it_display = new c_item_display(_item);
    it_display->setWindowFlags(Qt::ToolTip | Qt::Popup);
    it_display->setFocusPolicy(Qt::NoFocus);
    _database_manager = database_manager;
}

c_item_lite::~c_item_lite() {
    delete ui;
}

void c_item_lite::set_icon() {
    QPixmap image;
    QString type = "NONE";
    if (!_item.isEmpty()) {
        type = mapItemToType[_item.getType().getTitle()];
    }
        if(!type.compare("LEGS")) {
            image = QPixmap("images/divers/smalllegs.png");
        } else if (!type.compare("RING")) {
            image = QPixmap("images/divers/smallring.png");
        } else if (!type.compare("NECK")) {
            image = QPixmap("images/divers/smallneck.png");
        } else if (!type.compare("BACK")) {
            image = QPixmap("images/divers/smallback.png");
        } else if (!type.compare("BELT")) {
            image = QPixmap("images/divers/smallbelt.png");
        } else if (!type.compare("HEAD")) {
            image = QPixmap("images/divers/smallhead.png");
        } else if (!type.compare("CHEST")) {
            image = QPixmap("images/divers/smallchest.png");
        } else if (!type.compare("SHOULDERS")) {
            image = QPixmap("images/divers/smallshoulders.png");
        } else if (!type.compare("SECOND_HAND")) {
            image = QPixmap("images/divers/smallsecondhand.png");
        } else if (!type.compare("PET")) {
            image = QPixmap("images/divers/smallpet.png");
        } else if (!type.compare("ACCESSORY")) {
            image = QPixmap("images/divers/smallaccessory.png");
        } else if (!type.compare("ONE_HAND_WEAPON")) {
            image = QPixmap("images/divers/smallfirsthand.png");
        } else if (!type.compare("TWO_HAND_WEAPON")) {
            image = QPixmap("images/divers/smalldoublehand.png");
        }
    ui->icon->setPixmap(image);
    ui->icon->setBackgroundRole(QPalette::Base);
    ui->icon->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->icon->setScaledContents(true);
}

bool c_item_lite::event(QEvent *event) {
    if ( event->type() == QEvent::HoverEnter ) {
        QPoint p = this->pos();
        QPoint p_parent = _parent->pos();
        QSize size = this->size();
        p.setY(p.y()+size.height()*2);
        QPoint res = p + p_parent;
        it_display->completeData(_database_manager);
        it_display->move(res);
        it_display->show();
        timer = new QTimer(this);
        connect(timer,&QTimer::timeout,this,&c_item_lite::check_mouse_over);
        timer->start(100);

    } else if ( event->type() == QEvent::HoverLeave ) {
        it_display->hide();

    }
    return QWidget::event(event);
}

void c_item_lite::mouseDoubleClickEvent(QMouseEvent* /*event*/) {
    it_display->completeData(_database_manager);
    _item = it_display->getItem();
    emit item_doubleCliked(_item);
}

void c_item_lite::check_mouse_over() {
    if(underMouse()) {
        timer->start(100);
    } else {
        disconnect(timer,&QTimer::timeout,this,&c_item_lite::check_mouse_over);
        it_display->hide();
    }
}
