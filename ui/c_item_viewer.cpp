#include "c_item_viewer.h"
#include "ui_c_item_viewer.h"

c_item_viewer::c_item_viewer(const QString item_position, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_item_viewer) {
    ui->setupUi(this);

    _parent = parent;
    this->setAttribute(Qt::WA_Hover);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&c_item_viewer::customContextMenuRequested,this,&c_item_viewer::slot_context_menu);

    int size_widget = 40;

    this->setStyleSheet(QString("QWidget#c_item_viewer{background-color: %1;} img {vertical-align:middle;}").arg(app_color::dark_blue));
    //ui->widget_elements->setStyleSheet(QString("QWidget{background-color: %1;} img {vertical-align:middle;}").arg(app_color::dark_blue));
    image_layout = new QStackedLayout();
    ui->image_widget->setLayout(image_layout);
    background = new QLabel();
    image = new QLabel();
    item = new c_item();
    position = item_position;

    ui->image_widget->setMaximumSize(QSize(size_widget,size_widget));
    ui->image_widget->setMinimumSize(QSize(size_widget,size_widget));
    QPixmap pixmap_background;
    background->setPixmap(pixmap_background);
    background->setBackgroundRole(QPalette::Base);
    background->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    background->setScaledContents(true);

    image_layout->addWidget(image);
    image_layout->addWidget(background);
    image_layout->setStackingMode(QStackedLayout::StackAll);
    image_layout->setContentsMargins(0,0,0,0);

    images_elements["Feu"] = QPixmap(":/images/elements/smallFIRE.png");
    images_elements["Eau"] = QPixmap(":/images/elements/smallWATER.png");
    images_elements["Air"] = QPixmap(":/images/elements/smallAIR.png");
    images_elements["Terre"] = QPixmap(":/images/elements/smallEARTH.png");

    elements_layout = static_cast<QVBoxLayout*>(ui->widget_elements->layout());

    updateView();
    own_item = true;
    disabled = false;

    it_display = nullptr;
    block = false;
}

c_item_viewer::~c_item_viewer() {
    foreach (QLabel* pt, elements) {
        pt->deleteLater();
    }
    if (own_item) {
        delete item;
    }
    delete ui;
}

void c_item_viewer::setItem(c_item *new_item) {
    if (new_item == nullptr) {
        item = new c_item();
    } else {
        item = new_item;
        own_item = false;
    }
    updateView();
}
void c_item_viewer::updateView() {
    QPixmap pixmap_image(QString("images/items/%1.png").arg(item->getGfxId()));
    image->setPixmap(pixmap_image);
    image->setBackgroundRole(QPalette::Base);
    image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    image->setScaledContents(true);
    foreach(QLabel* label,elements) {
        elements_layout->removeWidget(label);
        elements.removeAll(label);
        label->deleteLater();
    }
    foreach(QString elem, item->getElements(item->getNumber_element())) {
        elements.push_back(new QLabel());
        elements.last()->setPixmap(images_elements[elem]);
        elements_layout->insertWidget(elements.size(),elements.last());
    }
    setBackgroundImage();
    this->update();
}

void c_item_viewer::setBackgroundImage() {
    if (!disabled){
        if (item->isEmpty()) {
            background->setPixmap(QPixmap(QString(":/images/divers/%1.png").arg(position)));
        } else {
            background->setPixmap(QPixmap(QString(":/images/rarityborder/%1.png").arg(item->getRarity())));
        }
    } else {
        background->setPixmap(QPixmap());
    }
}

void c_item_viewer::slot_context_menu(const QPoint &pos) {
    if (item->isEmpty()) return;
    QMenu contextMenu(tr("Context menu"), this);
    QAction action1("Déséquiper item", this);
    QAction action2("Réassigner les éléments", this);
    connect(&action1,&QAction::triggered, this,&c_item_viewer::slot_unequip);
    connect(&action2,&QAction::triggered, this,&c_item_viewer::slot_refresh_elements);
    contextMenu.addAction(&action1);
    contextMenu.addAction(&action2);

    contextMenu.exec(mapToGlobal(pos));
}

void c_item_viewer::slot_unequip() {
    emit unequip(position);
}

void c_item_viewer::slot_refresh_elements() {
    int number_elements = item->getNumber_element();
    c_element_dialog diag(number_elements);
    QList<QString> elems;
    elems << "Feu" << "Eau" << "Terre" << "Air";
    QList<QString> item_elem = item->getElements();
    QList<bool> item_chosen_elem;
    for (int i = 0; i < item_elem.size(); ++i) {
        item_chosen_elem.push_back(false);
    }
    for (int i = 0; i < number_elements; ++i) {
        item_chosen_elem.replace(c_elements_display::frToId_elem[item_elem.at(i)],true);
    }
    diag.setElems(item_chosen_elem);
    QList<QString> new_elems_list;
    if (diag.exec()==QDialog::Accepted) {
        item_chosen_elem = diag.getElems();
        for (int i = 0; i < item_chosen_elem.size(); ++i) {
            if (item_chosen_elem.at(i)) {
                new_elems_list.push_front(elems.at(i));
            } else {
                new_elems_list.push_back(elems.at(i));
            }
        }
    } else {
        new_elems_list = item_elem;
    }
    item->setElements(new_elems_list);
    updateView();
    emit elementsChanged();
}

void c_item_viewer::disable(int gfxId) {

    item->setGfxId(gfxId);
    disabled = true;
    updateView();
}

void c_item_viewer::enable() {
    item->setGfxId(0);
    disabled = false;
    updateView();
}

c_item *c_item_viewer::get_item() {
    return item;
}

c_item c_item_viewer::get_item_const() const {
    return *item;
}

QString c_item_viewer::getPosition() const {
    return position;
}

bool c_item_viewer::event(QEvent *event) {
    if ( event->type() == QEvent::HoverEnter ) {
        if (item->isEmpty()) {
            return QWidget::event(event);
        }
        QPoint p = this->pos();
        p.setY(p.y());
        p.setX(p.x()+150);
        QPoint res = _parent->mapToGlobal(p);
        if (it_display == nullptr) {
            it_display = new c_item_display(*item);
            it_display->setWindowFlags(Qt::ToolTip | Qt::Popup);
            it_display->setFocusPolicy(Qt::NoFocus);
        }
        it_display->move(res);
        it_display->show();
        timer = new QTimer(this);
        connect(timer,&QTimer::timeout,this,&c_item_viewer::check_mouse_over);
        timer->start(100);

    } else if ( event->type() == QEvent::HoverLeave ) {
        if (item->isEmpty()) {
            return QWidget::event(event);
        }
        it_display->hide();

    }
    return QWidget::event(event);
}

void c_item_viewer::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)  {
        if (item->isEmpty()) {
            if (!block) {
                emit clicked(position);
            } else {
                block = false;
            }
        }
    } else {
        event->ignore();
    }
}

void c_item_viewer::mouseDoubleClickEvent(QMouseEvent * /*event*/) {
    if (!item->isEmpty()) {
        emit unequip(position);
        block = true;
    }
}

void c_item_viewer::check_mouse_over() {
    if(underMouse()) {
        timer->start(100);
    } else {
        disconnect(timer,&QTimer::timeout,this,&c_item_viewer::check_mouse_over);
        it_display->hide();
        it_display->update();
    }
}

