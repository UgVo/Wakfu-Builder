#include "c_tool_button.h"

c_tool_button::c_tool_button(QWidget *parent) : QToolButton(parent) {

}

void c_tool_button::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::RightButton) {
        emit rightClicked();
    }
    QToolButton::mouseReleaseEvent(event);
}
