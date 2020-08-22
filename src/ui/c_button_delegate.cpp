#include "c_button_delegate.h"

const int column_delete = 3;

c_button_delegate::c_button_delegate(QObject *parent) : QStyledItemDelegate(parent) {
    if(QTableView *tableView = qobject_cast<QTableView *>(parent))
    {
        qDebug() << "creation button delegate";
        myWidget = tableView;
        //btn = new QToolButton("...", myWidget);
        btn = new QToolButton(myWidget);
        btn->setAutoFillBackground(true);
        btn->setIconSize(QSize(30,30));
        btn->setAutoRaise(true);
        btn->setStyleSheet("border-top:1px solid #BBBBBB; border-bottom:1px solid #BBBBBB; background-color: rgba(255, 255, 255, 0);");
        btn->setIcon(QIcon(":/images/divers/delete_icon.png"));
        btn->hide();
        myWidget->setMouseTracking(true);
        connect(myWidget, SIGNAL(entered(QModelIndex)),
                              this, SLOT(cellEntered(QModelIndex)));
        isOneCellInEditMode = false;
    }
}

c_button_delegate::~c_button_delegate()
{

}
QWidget * c_button_delegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    if (index.column() == column_delete) {
        QToolButton * btn = new QToolButton(parent);
        btn->setAutoFillBackground(true);
        btn->setIconSize(QSize(30,30));
        btn->setAutoRaise(true);
        btn->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
        return btn;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

//setEditorData
void c_button_delegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
   if (index.column() == column_delete) {
        QToolButton * btn = qobject_cast<QToolButton *>(editor);
        btn->setAutoFillBackground(true);
        btn->setIconSize(QSize(30,30));
        btn->setAutoRaise(true);
        btn->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
        btn->setIcon(QIcon(":/images/divers/delete_icon.png"));
        QObject::connect(btn,&QToolButton::clicked,this,&c_button_delegate::button_clicked);
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

//paint
void c_button_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == column_delete)
    {
        QStyleOptionViewItem option2 = option;
        QRect rect = option.rect;
        option2.rect = rect;
        btn->setGeometry(rect);
        btn->setText(index.data().toString());
        if (option.state == QStyle::State_Selected)
                     painter->fillRect(rect, option.palette.highlight());
        QPixmap map = btn->grab();
        painter->drawPixmap(option2.rect.x(),option2.rect.y(),map);
    } else {
        QStyledItemDelegate::paint(painter,option, index);
    }
}
//updateGeometry
void c_button_delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect = option.rect;
    editor->setGeometry(rect);
}

//cellEntered
void c_button_delegate::cellEntered(const QModelIndex &index)
{
    qDebug() << "Cell entered  : " << index;
    if (index.column() == column_delete)
    {
        qDebug() << "coucou";
        if(isOneCellInEditMode)
        {
            myWidget->closePersistentEditor(currentEditedCellIndex);
        }
        myWidget->openPersistentEditor(index);
        isOneCellInEditMode = true;
        currentEditedCellIndex = index;
    } else {
        if(isOneCellInEditMode)
        {
            isOneCellInEditMode = false;
            myWidget->closePersistentEditor(currentEditedCellIndex);
        }
    }
}

void c_button_delegate::button_clicked() {
    qDebug() << "button clicked " << currentEditedCellIndex.row();
    model->removeRow(currentEditedCellIndex);
}

void c_button_delegate::setModel(c_save_builder_model *value)
{
    model = value;
}
