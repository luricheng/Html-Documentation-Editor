#ifndef DOCKER_H
#define DOCKER_H

#include <QDockWidget>

namespace Ui {
class Docker;
}

class Docker : public QDockWidget
{
    Q_OBJECT
    friend class TextEditer;
public:
    explicit Docker(QWidget *parent = 0);
    ~Docker();

private:
    Ui::Docker *ui;
};

#endif // DOCKER_H
