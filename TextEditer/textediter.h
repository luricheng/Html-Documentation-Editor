#ifndef TEXTEDITER_H
#define TEXTEDITER_H

#include <QMainWindow>
#include"QTextEdit"
#include"QLinkedList"
#include"QSpinBox"
#include"QLabel"
#include"QFontComboBox"
#include<findorrepalce.h>

class FindOrRepalce;

namespace Ui {
class TextEditer;
}

class TextEditer : public QMainWindow
{
    Q_OBJECT
    friend class FindOrRepalce;
public:
    explicit TextEditer(QWidget *parent = 0);
    ~TextEditer();

private:
    Ui::TextEditer *ui;
    QSpinBox*fontSizeSpinBox;//字体大小调整框
    QFontComboBox*fontComboBox;//字体选择框
    QLabel*fontSizeLabel;//字体大小标签
    QLabel*fontLabel;//字体选择标签
    void loadFile(QTextEdit*textEdit,QString fileName);//载入文件到textEdit,文件名为fileName
    QVector<QTextEdit*>list;
    //int tabIndex;//下个tab的序号
    QString getTitle(QString);//提取出文件名
    void mergeCurrentTextFormat(QTextCharFormat*fmt);//合并fmt到当前的文本格式
    void saveIn(int index,QString fileName);//保存标号为index的QTextEdit的文本，文件名为fileName

    int getIdxInTextEdits(int idx);//idx在当前tab中的标号

    FindOrRepalce*findOrRepalceWidget;//查找替换窗口

    //初始化函数
    void initMenuBar();//初始化菜单栏
    void initToolBar();//工具栏
    void initFindReplaceBox();//查找替换窗口
    int getNextTabIdx();

protected:
    QTextEdit*getCurrentTextEdit();//返回当前的TextEdit

protected slots:
    //menu bar
    void openFile();
    void newFile(QString title = QString());
    void closeTab(int);
    void save();
    void saveAs();

    void findText();
    //void replaceText();

    //tool bar
    void changeColor();
    void changeItalic();
    void changeBold();
    void changeFontSize(int);
    void changeFont(QFont);
    void changeUnderLine();
    void setAlignLeft();
    void setAlignRight();
    void setAlignCenter();
    void setAlignJustify();
private slots:
    void on_aboutAction_triggered();
    void on_actionHelp_triggered();
};

#endif // TEXTEDITER_H
