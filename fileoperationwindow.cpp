#include "fileoperationwindow.h"
#include "ui_fileoperationwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QDebug>


fileOperationWindow::fileOperationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fileOperationWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("File Operation");
    this->setFixedSize(this->width(),this->height());//固定窗口大小
    ui->textedit_fileWindow->setGeometry(0,0,1000,600);//设置编辑区大小

    //设置menuBar的action
    QObject::connect(ui->actionBack_fileWindow,&QAction::triggered,
                     [=]()
    {
        emit this->backMainWindow_signal_file();                 //返回主窗口
    });

    QObject::connect(ui->actionExit_fileWindow,&QAction::triggered,
                     [=]()
    {
        this->exitDialog_modal();  //显示是否退出的模态对话框
    });

    QObject::connect(ui->actionNewPath_fileWindow_2,&QAction::triggered,   //保存文件在一个新的路径
                     [=]()
    {
         this->saveFile_newPath();
    });


}

fileOperationWindow::~fileOperationWindow()
{
    delete ui;
}
void fileOperationWindow::exitDialog_modal()
{
    QMessageBox IsExit_modal;
    IsExit_modal.setWindowTitle("Exit");
    IsExit_modal.setText("Really to exit?\nconfirm you have saved");
    IsExit_modal.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    int return_value=IsExit_modal.exec();
    switch(return_value)
    {
       case QMessageBox::Yes:
           this->close();
           break;
       case QMessageBox::No:
           IsExit_modal.close();
           break;
    }
}

void fileOperationWindow::openFile_fromMainWindow()
{
    QString path = QFileDialog::getOpenFileName(this,"open","../");
    QFile file_open(path);
    bool isOk=file_open.open(QIODevice::ReadOnly);
    if(true == isOk)
    {
        QTextStream stream_open(&file_open);
        QString text_on_open;
        while(false == stream_open.atEnd())
        {
            text_on_open = text_on_open+stream_open.readLine()+"\n";
        }
        ui->textedit_fileWindow->setText(text_on_open);
    }
    file_open.close();
}

void fileOperationWindow::saveFile_newPath()
{
    QString path= QFileDialog::getSaveFileName(this,"save","../");
    QFile file_save(path);
    bool isOk = file_save.open(QIODevice::WriteOnly|QIODevice::Text);
    if(true == isOk)
    {
        QTextStream stream_save_newPath(&file_save);
        QString text_save=ui->textedit_fileWindow->toPlainText();
        stream_save_newPath<<text_save;
    }
    file_save.close();
}




