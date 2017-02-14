#ifndef TEXTEDITWITHDOCK_H
#define TEXTEDITWITHDOCK_H

#include"textediter.h"

namespace Ui {
class TextEditWithDock;
}

class TextEditWithDock : public QWidget
{
    Q_OBJECT
    friend class TextEditer;
public:
    explicit TextEditWithDock(QWidget *parent = 0);
    ~TextEditWithDock();

private:
    Ui::TextEditWithDock *ui;
};

#endif // TEXTEDITWITHDOCK_H
