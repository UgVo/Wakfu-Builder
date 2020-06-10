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
    ui->lvl->setStyleSheet(QString("background-color: %1; border: 1px solid white; border-radius: 5px; color:white; padding: 2px ").arg(app_color::dark));
    ui->image_widget->setStyleSheet(QString(".QWidget#image_widget{background-color:%1; border-top-left-radius: 3px; border-bottom-left-radius: 3px;}").arg(app_color::green_blue));
    ui->icon->setStyleSheet(QString("background-color: %1;").arg(app_color::dark_blue));
    it_display = nullptr;
    _database_manager = database_manager;

    updateView();
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
            image = QPixmap(":/divers/smalllegs.png");
        } else if (!type.compare("RING")) {
            image = QPixmap(":/divers/smallring.png");
        } else if (!type.compare("NECK")) {
            image = QPixmap(":/divers/smallneck.png");
        } else if (!type.compare("BACK")) {
            image = QPixmap(":/divers/smallback.png");
        } else if (!type.compare("BELT")) {
            image = QPixmap(":/divers/smallbelt.png");
        } else if (!type.compare("HEAD")) {
            image = QPixmap(":/divers/smallhead.png");
        } else if (!type.compare("CHEST")) {
            image = QPixmap(":/divers/smallchest.png");
        } else if (!type.compare("SHOULDERS")) {
            image = QPixmap(":/divers/smallshoulders.png");
        } else if (!type.compare("SECOND_HAND")) {
            image = QPixmap(":/divers/smallsecondhand.png");
        } else if (!type.compare("PET")) {
            image = QPixmap(":/divers/smallpet.png");
        } else if (!type.compare("ACCESSORY")) {
            image = QPixmap(":/divers/smallaccessory.png");
        } else if (!type.compare("ONE_HAND_WEAPON")) {
            image = QPixmap(":/divers/smallfirsthand.png");
        } else if (!type.compare("TWO_HAND_WEAPON")) {
            image = QPixmap(":/divers/smalldoublehand.png");
        } else if (!type.compare("MOUNT")) {
            image = QPixmap(":/divers/smallmount.png");
        }
    ui->icon->setPixmap(image);
    ui->icon->setBackgroundRole(QPalette::Base);
    ui->icon->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->icon->setScaledContents(true);
}

bool c_item_lite::event(QEvent *event) {
    if ( event->type() == QEvent::HoverEnter ) {
        QPoint p = this->pos();
        p.setY(p.y()+60);
        p.setX(p.x()+9);
        if (it_display == nullptr) {
            it_display = new c_item_display(_item);
            it_display->setWindowFlags(Qt::ToolTip | Qt::Popup);
            it_display->setFocusPolicy(Qt::NoFocus);
        }
        if ((p.y() + it_display->size().height()) > (_parent->size().height() + 100)) {
            p.setY(p.y()-it_display->size().height()-70);
        }
        QPoint res = _parent->mapToGlobal(p);
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

void c_item_lite::setDatabase_manager(c_dbmanager *manager) {
    _database_manager = manager;
}

c_item c_item_lite::item() const {
    return _item;
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
        it_display->update();
    }
}

void c_item_lite::setItem(const c_item &item) {
    _item = item;
    if (it_display != nullptr) {
        it_display->deleteLater();
        it_display = nullptr;
    }
    updateView();
}

void c_item_lite::updateView() {
    QFontMetrics metrics(ui->name->font());
    QString elidedText = metrics.elidedText(_item.getName(), Qt::ElideRight, ui->name->width());
    ui->name->setStyleSheet(QString("color : %1").arg(app_color::color_rarity.at(_item.getRarity())));
    ui->name->setText(elidedText);
    ui->lvl->setText(QString("LvL.%1").arg(_item.getLvl()));
    QPixmap image = QPixmap(QString("images/items/%1.png").arg(_item.getGfxId()));
    ui->image->setPixmap(image);
    ui->image->setBackgroundRole(QPalette::Base);
    ui->image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->image->setScaledContents(true);
    set_icon();
}
