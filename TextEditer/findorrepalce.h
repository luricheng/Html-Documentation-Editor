#ifndef FINDORREPALCE_H
#define FINDORREPALCE_H

#include <QWidget>
#include<QTextEdit>
#include<QLinkedList>
#include<textediter.h>
#include<QDialog>
class TextEditer;

namespace Ui {
class FindOrRepalce;
}

class FindOrRepalce : public QDialog
{

    Q_OBJECT
    friend class TextEditer;
public:
    explicit FindOrRepalce(QWidget *parent = 0);
    explicit FindOrRepalce(TextEditer *father);
    ~FindOrRepalce();

private:
    Ui::FindOrRepalce *ui;
    TextEditer*father;//父亲部件
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
