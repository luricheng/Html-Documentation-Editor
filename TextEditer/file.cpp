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
    //找到第一个为空的textEdit
    for(QLinkedList<std::pair<int,QTextEdit*> >::iterator it = list.begin();it!=list.end();++it){
        if(it->second->document()->isEmpty()){
            loadFile(it->second,fileName);
            QString title = getTitle(fileName);
            if(!title.isEmpty()){
                ui->tabWidget->setTabText(it->first,title);//设置tab标题
            }
            ui->tabWidget->setCurrentIndex(it->first);//设置当前tab
            return;
        }
    }
    //没空的，新建一个
    newFile(fileName);
    loadFile(list.back().second,fileName);
}

void TextEditer::newFile(QString title){
    QTextEdit*newTextEdit = new QTextEdit();
    if(title.isEmpty()||(title = getTitle(title)).isEmpty()){
        title = "文本" + QString::number(tabIndex);
    }
    ui->tabWidget->addTab(newTextEdit,title);
    list<<std::make_pair(tabIndex,newTextEdit);
    ui->tabWidget->setCurrentIndex(tabIndex);
    tabIndex++;
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

void TextEditer::saveIn(int index,QString fileName){
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly)){
        qDebug()<<"open file: "<<fileName<<" error!";
        return;
    }
    QTextStream textStream(&file);
    for(QLinkedList<std::pair<int,QTextEdit*> >::iterator it = list.begin();it!=list.end();++it){
        if(it->first==index){
            QTextEdit* textEdit = it->second;
            textStream<<(textEdit->toHtml());
        }
    }
    file.close();
}

void TextEditer::saveAs(){
    int index = ui->tabWidget->currentIndex();
    QString fileName = QFileDialog::getSaveFileName(this);
    if(!fileName.isEmpty()){
        saveIn(index,fileName);
    }
}

void TextEditer::save(){
    int index = ui->tabWidget->currentIndex();
    QString fileName = ui->tabWidget->tabText(index);
    qDebug()<<fileName;
    if(!fileName.endsWith(tr(".html"))){
        fileName.append(tr(".html"));
    }
    saveIn(index,fileName);
}


