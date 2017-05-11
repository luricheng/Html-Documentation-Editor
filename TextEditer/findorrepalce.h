#ifndef FINDORREPALCE_H
#define FINDORREPALCE_H

#include <QWidget>
#include<QTextEdit>
#include<QLinkedList>
#include<textediter.h>

class TextEditer;

namespace Ui {
class FindOrRepalce;
}

class FindOrRepalce : public QWidget
{

    Q_OBJECT
    friend class TextEditer;
public:
    explicit FindOrRepalce(QWidget *parent = 0);
    explicit FindOrRepalce(TextEditer *father);
    ~FindOrRepalce();

private:
    Ui::FindOrRepalce *ui;
    //QTextEdit*textEdit;//包含匹配串
    TextEditer*father;
    void findNext(bool);
protected:
    void setTextEdit(QTextEdit*);
protected slots:
    void close();
private slots:
    void on_findLineEdit_textChanged(const QString &arg1);
    void on_previous_clicked();
    void on_next_clicked();
    void on_replace_clicked();
    void on_replaceLineEdit_textChanged(const QString &arg1);
    void on_replaceAll_clicked();
};

#endif // FINDORREPALCE_H
