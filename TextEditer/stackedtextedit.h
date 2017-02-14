#ifndef STACKEDTEXTEDIT_H
#define STACKEDTEXTEDIT_H

#include <QStackedWidget>

namespace Ui {
class StackedTextEdit;
}

class StackedTextEdit : public QStackedWidget
{
    Q_OBJECT

public:
    explicit StackedTextEdit(QWidget *parent = 0);
    ~StackedTextEdit();

private:
    Ui::StackedTextEdit *ui;
};

#endif // STACKEDTEXTEDIT_H
