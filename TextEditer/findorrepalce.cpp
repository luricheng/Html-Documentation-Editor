#include "findorrepalce.h"
#include "ui_findorrepalce.h"

#include"QPalette"
#include<QMessageBox>

FindOrRepalce::FindOrRepalce(TextEditer *father) :
    QDialog(father),
    ui(new Ui::FindOrRepalce)
{
    ui->setupUi(this);

    this->father=father;
    this->setVisible(false);
    this->ui->previous->setEnabled(false);
    this->ui->next->setEnabled(false);
    this->ui->replaceAll->setEnabled(false);
    this->ui->replace->setEnabled(false);
}

FindOrRepalce::~FindOrRepalce()
{
    delete ui;
}

void FindOrRepalce::close(){//伪删除 关闭时只隐藏窗口
    this->setVisible(false);
}

void FindOrRepalce::on_findLineEdit_textChanged(const QString &arg1)
{
    ui->next->setEnabled(!arg1.isEmpty());
    ui->previous->setEnabled(!arg1.isEmpty());
}

void FindOrRepalce::findNext(bool foreward){
    QTextEdit*textEdit=father->getCurrentTextEdit();
    QString pToFind=ui->findLineEdit->text();
    ui->next->setEnabled(true);
    bool findAns;
    if(foreward){
        findAns=textEdit->find(pToFind);
    }
    else{
        findAns=textEdit->find(pToFind,QTextDocument::FindBackward);
    }
    if(findAns==false){
        textEdit->moveCursor(foreward?QTextCursor::Start:QTextCursor::End);
        ui->replace->setEnabled(false);
    }
    else{
        ui->replace->setEnabled(!ui->replaceLineEdit->text().isEmpty());
        QPalette palette=textEdit->palette();
        palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
        textEdit->setPalette(palette);
    }
}

void FindOrRepalce::on_previous_clicked()
{
    findNext(false);
}

void FindOrRepalce::on_next_clicked()
{
    findNext(true);
}

void FindOrRepalce::on_replace_clicked()
{
    QTextEdit*textEdit=father->getCurrentTextEdit();
    QString str=ui->replaceLineEdit->text();
    textEdit->textCursor().insertText(str);
}

void FindOrRepalce::on_replaceLineEdit_textChanged(const QString &arg1)
{
    ui->replaceAll->setEnabled(!arg1.isEmpty()&&
                               !ui->findLineEdit->text().isEmpty());
}

void FindOrRepalce::on_replaceAll_clicked()
{
    QTextEdit*textEdit=father->getCurrentTextEdit();
    QString p=ui->findLineEdit->text();
    textEdit->moveCursor(QTextCursor::Start);
    while(textEdit->find(p)){
        textEdit->textCursor().insertText(ui->replaceLineEdit->text());
    }
}
