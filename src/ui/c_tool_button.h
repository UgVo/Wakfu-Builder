#ifndef C_TOOL_BUTTON_H
#define C_TOOL_BUTTON_H

#include <QMouseEvent>
#include <QToolButton>
#include <QWidget>

class c_tool_button : public QToolButton {
    Q_OBJECT
   public:
    c_tool_button(QWidget* parent = nullptr);

    void mouseReleaseEvent(QMouseEvent*) override;

   signals:
    void rightClicked();
};

#endif  // C_TOOL_BUTTON_H
