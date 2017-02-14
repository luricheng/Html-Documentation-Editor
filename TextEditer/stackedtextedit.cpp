#include "stackedtextedit.h"
#include "ui_stackedtextedit.h"

StackedTextEdit::StackedTextEdit(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::StackedTextEdit)
{
    ui->setupUi(this);
}

StackedTextEdit::~StackedTextEdit()
{
    delete ui;
}
