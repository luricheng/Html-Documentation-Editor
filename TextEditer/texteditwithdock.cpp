#include "texteditwithdock.h"
#include "ui_texteditwithdock.h"

TextEditWithDock::TextEditWithDock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextEditWithDock)
{
    ui->setupUi(this);
}

TextEditWithDock::~TextEditWithDock()
{
    delete ui;
}
