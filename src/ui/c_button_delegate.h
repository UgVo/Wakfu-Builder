#ifndef C_BUTTON_DELEGATE_H
#define C_BUTTON_DELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>
#include <QTableView>
#include <QToolButton>
#include <QPainter>
#include <QDebug>
#include "utilities/c_save_builder_model.h"

class c_button_delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    c_button_delegate(QObject *parent = nullptr);
    ~c_button_delegate();

    QWidget * createEditor(QWidget *parent,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const;

    void setEditorData(QWidget *editor,
                                    const QModelIndex &index) const;

//    void setModelData(QWidget *editor, QAbstractItemModel *model,
//                                   const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
              const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setModel(c_save_builder_model *value);

public slots:
    void cellEntered(const QModelIndex &index);
    void button_clicked();

    private:
    QTableView *myWidget;
    QToolButton *btn;
    bool isOneCellInEditMode;
    QPersistentModelIndex currentEditedCellIndex;
    int current_row;
    c_save_builder_model *model;
};

#endif // C_BUTTON_DELEGATE_H
