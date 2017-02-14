#include "textediter.h"
#include "ui_textediter.h"


#ifdef Q_OS_WIN32//地址分隔符
#define ADDRESS_SEPARATOR '\\'
#else
#define ADDRESS_SEPARATOR '/'
#endif


TextEditer::TextEditer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditer)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);

    //-------
    ui->saveAsAction->setVisible(false);
    //-------

    ui->tabWidget->clear();
    tabIndex = 0;
    newFile();

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

    //menu bar

    //file
    connect(ui->openFileAction,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(ui->newFileAction,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(ui->saveAction,SIGNAL(triggered()),this,SLOT(save()));
    //edit
    connect(ui->copyAction,SIGNAL(triggered()),getCurrentTextEdit(),SLOT(copy()));
    connect(ui->cutAction,SIGNAL(triggered()),getCurrentTextEdit(),SLOT(cut()));
    connect(ui->pasteAction,SIGNAL(triggered()),getCurrentTextEdit(),SLOT(paste()));
    connect(ui->undoAction,SIGNAL(triggered()),getCurrentTextEdit(),SLOT(undo()));
    connect(ui->redoAction,SIGNAL(triggered()),getCurrentTextEdit(),SLOT(redo()));
    //other
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
    connect(ui->closeAction,SIGNAL(triggered()),this,SLOT(close()));


    //tool bar

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

TextEditer::~TextEditer()
{
    delete ui;
}

QTextEdit*TextEditer::getCurrentTextEdit(){
    int index=ui->tabWidget->currentIndex();
    for(QLinkedList<std::pair<int,QTextEdit*> >::iterator it=list.begin();it!=list.end();++it){
        if(it->first==index){
            return it->second;
        }
    }
    return NULL;
}

void TextEditer::closeTab(int index){
    ui->tabWidget->removeTab(index);
    for(QLinkedList<std::pair<int,QTextEdit*> >::iterator it = list.begin();it!=list.end();++it){
        if(it->first==index){
            list.erase(it);
            return;
        }
    }
}

QString TextEditer::getTitle(QString fileName){
    std::string str = fileName.toStdString();
    int n = str.size();
    for(int i=n-1;i>=0;--i){
        if(str[i]==ADDRESS_SEPARATOR){
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
