#include "textediter.h"
#include "ui_textediter.h"
#include"QDir"
#include<QMessageBox>

int TextEditer::getNextTabIdx(){
    return ui->tabWidget->count();
}

void TextEditer::initFindReplaceBox(){//查找替换窗口
    findOrRepalceWidget=new FindOrRepalce(this);
    connect(ui->findAction,SIGNAL(triggered()),this,SLOT(findText()));
    connect(ui->replaceAction,SIGNAL(triggered()),this,SLOT(findText()));
}

void TextEditer::initMenuBar(){//菜单栏
    //文件
    connect(ui->openFileAction,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(ui->newFileAction,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(ui->saveAction,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));
    //编辑
    connect(ui->copyAction,SIGNAL(triggered()),getCurrentTextEdit(),SLOT(copy()));
    connect(ui->cutAction,SIGNAL(triggered()),getCurrentTextEdit(),SLOT(cut()));
    connect(ui->pasteAction,SIGNAL(triggered()),getCurrentTextEdit(),SLOT(paste()));
    connect(ui->undoAction,SIGNAL(triggered()),getCurrentTextEdit(),SLOT(undo()));
    connect(ui->redoAction,SIGNAL(triggered()),getCurrentTextEdit(),SLOT(redo()));
}

void TextEditer::initToolBar(){
    //字号
    fontSizeSpinBox=new QSpinBox();
    fontSizeLabel=new QLabel(tr("字号"));
    fontSizeSpinBox->setRange(6,72);
    QAction*before=ui->colorAction;
    before=ui->mainToolBar->insertWidget(before,fontSizeSpinBox);
    before=ui->mainToolBar->insertWidget(before,fontSizeLabel);

    //字体
    fontComboBox=new QFontComboBox();
    fontLabel=new QLabel(tr("字体"));
    before=ui->mainToolBar->insertWidget(before,fontComboBox);
    before=ui->mainToolBar->insertWidget(before,fontLabel);

    ui->mainToolBar->insertAction(ui->colorAction,ui->mainToolBar->addSeparator());

    //font
    connect(ui->colorAction,SIGNAL(triggered()),this,SLOT(changeColor()));
    connect(ui->italicAction,SIGNAL(triggered()),this,SLOT(changeItalic()));
    connect(ui->boldAction,SIGNAL(triggered()),this,SLOT(changeBold()));
    connect(ui->underLineAction,SIGNAL(triggered()),this,SLOT(changeUnderLine()));
    connect(fontSizeSpinBox,SIGNAL(valueChanged(int)),this,SLOT(changeFontSize(int)));
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),this,SLOT(changeFont(QFont)));
    //alginment
    connect(ui->leftAction,SIGNAL(triggered()),this,SLOT(setAlignLeft()));
    connect(ui->rightAction,SIGNAL(triggered()),this,SLOT(setAlignRight()));
    connect(ui->centerAction,SIGNAL(triggered()),this,SLOT(setAlignCenter()));
    connect(ui->justifyAction,SIGNAL(triggered()),this,SLOT(setAlignJustify()));
}

TextEditer::TextEditer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditer)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);//设置中心部件

    ui->tabWidget->clear();//清空所以浮动标签页
    //tabIndex = 0;//从0开始计数
    newFile();//新建新文件

    initFindReplaceBox();
    initMenuBar();
    initToolBar();

    //关闭标签页
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
    //关闭窗口
    connect(ui->closeAction,SIGNAL(triggered()),this,SLOT(close()));
    //适应对齐
    setAlignJustify();
}

TextEditer::~TextEditer()
{
    delete ui;
}

QTextEdit*TextEditer::getCurrentTextEdit(){//获取当前被选中的QTextEdit
    return (QTextEdit*)ui->tabWidget->currentWidget();
}

void TextEditer::closeTab(int index){
    ui->tabWidget->removeTab(index);
}

QString TextEditer::getTitle(QString fileName){
    std::string str = fileName.toStdString();
    int n = str.size();
    for(int i=n-1;i>=0;--i){
        if(str[i]==QDir::separator()){
            str.assign(str.begin()+i+1,str.end());
            return QString::fromStdString(str);
        }
    }
    return QString();
}


void TextEditer::mergeCurrentTextFormat(QTextCharFormat *fmt){
    QTextEdit*text=getCurrentTextEdit();
    QTextCursor cursor=text->textCursor();
    if(!cursor.hasSelection()){
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(*fmt);
    text->mergeCurrentCharFormat(*fmt);
}

void TextEditer::findText(){
    QTextEdit*textEdit=getCurrentTextEdit();
    if(textEdit!=NULL){
        this->findOrRepalceWidget->setVisible(true);
    }
    else{
        QMessageBox::warning(this,tr("文本文件不存在"),tr("文本文件不存在，请先建立文本"));
    }
}

void TextEditer::on_aboutAction_triggered()//关于
{
    newFile(tr("about"));
    loadFile(getCurrentTextEdit(),tr("about"));
}

void TextEditer::on_actionHelp_triggered()//帮助
{
    newFile(tr("help"));
    loadFile(getCurrentTextEdit(),tr("help"));
}
