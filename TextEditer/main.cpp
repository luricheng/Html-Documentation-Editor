#include "textediter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TextEditer w;
    w.show();

    return a.exec();
}
