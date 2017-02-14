#include"textediter.h"
#include "ui_textediter.h"
#include"QColorDialog"

void TextEditer::changeColor(){
    QColor color=QColorDialog::getColor(Qt::black,this,tr("选择字体颜色"));
    if(color.isValid()){
        QTextCharFormat colorFormat;
        colorFormat.setForeground(color);
        mergeCurrentTextFormat(&colorFormat);
    }
}

void TextEditer::changeItalic(){
    QTextEdit*text=getCurrentTextEdit();
    QTextCursor cursor=text->textCursor();
    QTextCharFormat italicFormat;
    italicFormat.setFontItalic(ui->italicAction->isChecked());
    cursor.mergeCharFormat(italicFormat);
    text->mergeCurrentCharFormat(italicFormat);
}

void TextEditer::changeBold(){
    QTextEdit*text=getCurrentTextEdit();
    QTextCursor cursor=text->textCursor();
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(ui->boldAction->isChecked()?QFont::Bold:QFont::Normal);
    cursor.mergeCharFormat(boldFormat);
    text->mergeCurrentCharFormat(boldFormat);
}

void TextEditer::changeUnderLine(){
    QTextEdit*text=getCurrentTextEdit();
    QTextCursor cursor=text->textCursor();
    QTextCharFormat underLineFormat;
    underLineFormat.setFontUnderline(ui->underLineAction->isChecked());
    cursor.mergeCharFormat(underLineFormat);
    text->mergeCurrentCharFormat(underLineFormat);
}

void TextEditer::changeFontSize(int size){
    QTextEdit*text=getCurrentTextEdit();
    QTextCursor cursor=text->textCursor();
    QFont font;
    font.setPointSize(size);
    QTextCharFormat fmt;
    fmt.setFont(font);
    cursor.mergeCharFormat(fmt);
    text->mergeCurrentCharFormat(fmt);
}

void TextEditer::changeFont(QFont font){
    QTextEdit*text=getCurrentTextEdit();
    QTextCursor cursor=text->textCursor();
    QFont oldFont = text->currentFont();
    font.setPointSize(oldFont.pointSize());//保持原字体大小
    QTextCharFormat fmt;
    fmt.setFont(font);
    cursor.mergeCharFormat(fmt);
    text->mergeCurrentCharFormat(fmt);
}

void TextEditer::setAlignLeft(){
    ui->rightAction->setChecked(false);
    ui->centerAction->setChecked(false);
    ui->justifyAction->setChecked(false);
    getCurrentTextEdit()->setAlignment(Qt::AlignLeft);
}
void TextEditer::setAlignRight(){
    ui->leftAction->setChecked(false);
    ui->centerAction->setChecked(false);
    ui->justifyAction->setChecked(false);
    getCurrentTextEdit()->setAlignment(Qt::AlignRight);
}
void TextEditer::setAlignCenter(){
    ui->rightAction->setChecked(false);
    ui->justifyAction->setChecked(false);
    ui->leftAction->setChecked(false);
    getCurrentTextEdit()->setAlignment(Qt::AlignCenter);
}
void TextEditer::setAlignJustify(){
    ui->rightAction->setChecked(false);
    ui->centerAction->setChecked(false);
    ui->leftAction->setChecked(false);
    getCurrentTextEdit()->setAlignment(Qt::AlignJustify);
}
