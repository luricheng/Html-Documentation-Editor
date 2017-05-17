#include"textediter.h"
#include "ui_textediter.h"
#include"QFile"
#include"QFileDialog"
#include"QDebug"

void TextEditer::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this,"打开新文件");
    if(fileName.isEmpty()){//未选中文件
        return;
    }
    /*
    //找到第一个为空的textEdit
    for(auto&it:list){
        if(it->document()->isEmpty()){
            loadFile(it,fileName);
            QString title = getTitle(fileName);
            int idx=list.size();
            if(!title.isEmpty()){
                ui->tabWidget->setTabText(idx,title);//设置tab标题
            }
            ui->tabWidget->setCurrentIndex(idx);//设置当前tab
            return;
        }
    }*/
    //没空的，新建一个
    newFile(fileName);
    loadFile(getCurrentTextEdit(),fileName);
}

void TextEditer::newFile(QString title){
    static qint32 counter=0;
    QTextEdit*newTextEdit = new QTextEdit();
    if(title.isEmpty()&&(title = getTitle(title)).isEmpty()){
        title = "文本" + QString::number(++counter);
    }
    ui->tabWidget->addTab(newTextEdit,title);
}

void TextEditer::loadFile(QTextEdit*textEdit,QString fileName){
    textEdit->clear();
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream textStream(&file);
        QString line = textStream.readAll();
        textEdit->setHtml(line);
    }
    else{
        qDebug()<<"open file:"<<fileName<<" error!"<<endl;
    }
    file.close();
}

void TextEditer::saveIn(QTextEdit*textEdit,QString fileName){
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly)){
        qDebug()<<"open file: "<<fileName<<" error!";
        return;
    }
    QTextStream textStream(&file);

    textStream<<(textEdit->toHtml());

    file.close();
}

void TextEditer::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this);
    if(!fileName.isEmpty()){
        saveIn(getCurrentTextEdit(),fileName);
    }
}

void TextEditer::save(){
    QTextEdit*textEdit=getCurrentTextEdit();
    QString fileName = ui->tabWidget->tabText(ui->tabWidget->currentIndex());
    qDebug()<<fileName;
    if(!fileName.endsWith(tr(".html"))){
        fileName.append(tr(".html"));
    }
    saveIn(textEdit,fileName);
}
