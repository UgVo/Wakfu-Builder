#include "c_item_viewer.h"
#include "ui_c_item_viewer.h"

c_item_viewer::c_item_viewer(const QString item_position, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_item_viewer) {
    ui->setupUi(this);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&c_item_viewer::customContextMenuRequested,this,&c_item_viewer::slot_context_menu);

    int size_widget = 40;

    this->setStyleSheet(QString("QWidget#c_item_viewer{background-color: #6A8BA8;} img {vertical-align:middle;}"));
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

    images_elements["Feu"] = QPixmap(":/elements/smallFIRE.png");
    images_elements["Eau"] = QPixmap(":/elements/smallWATER.png");
    images_elements["Air"] = QPixmap(":/elements/smallAIR.png");
    images_elements["Terre"] = QPixmap(":/elements/smallEARTH.png");

    elements_layout = static_cast<QVBoxLayout*>(ui->widget_elements->layout());

    updateView();
    own_item = true;
    disabled = false;

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
            background->setPixmap(QPixmap(QString(":/divers/%1.png").arg(position)));
        } else {
            background->setPixmap(QPixmap(QString(":/divers/NONE_ts.png")));
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
    qDebug() << item;
    emit unequip(position);
}

void c_item_viewer::slot_refresh_elements() {
    //TODO
}

void c_item_viewer::disable(int gfxId) {

    item->setGfxId(gfxId);
    disabled = true;
    updateView();
}

void c_item_viewer::enable() {
    disabled = false;
    updateView();
}

c_item *c_item_viewer::get_item() {
    return item;
}
