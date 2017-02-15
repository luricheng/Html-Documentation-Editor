#ifndef TEXTEDITER_H
#define TEXTEDITER_H

#include <QMainWindow>
#include"QTextEdit"
#include"QLinkedList"
#include"QSpinBox"
#include"QLabel"
#include"QFontComboBox"
namespace Ui {
class TextEditer;
}

class TextEditer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextEditer(QWidget *parent = 0);
    ~TextEditer();

private:
    Ui::TextEditer *ui;
    QSpinBox*fontSizeSpinBox;
    QFontComboBox*fontComboBox;
    QLabel*fontSizeLabel;
    QLabel*fontLabel;
    void loadFile(QTextEdit*textEdit,QString fileName);//加载文件
    QLinkedList<std::pair<int,QTextEdit*> >list;//first:tab的序号，second tabWidget中的QTextEdit的指针
    int tabIndex;//下个tab的序号
    QTextEdit*getCurrentTextEdit();//返回当前的TextEdit
    QString getTitle(QString);//提取出文件名
    void mergeCurrentTextFormat(QTextCharFormat*fmt);
    void saveIn(int index,QString fileName);
protected slots:
    //menu bar
    void openFile();
    void newFile(QString title = QString());
    void closeTab(int);
    void save();
    void saveAs();
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
};

#endif // TEXTEDITER_H
