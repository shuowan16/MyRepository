#include "viewmore_mainwindow.h"
#include "ui_viewmore_mainwindow.h"
#include <QDebug>
#include <public_functions.h>
viewMore_mainWindow::viewMore_mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::viewMore_mainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("Managed People");

    //remove按键的实现
    QObject::connect(ui->removeManagedPeople_button,&QPushButton::clicked,
                     [=]()
    {
       QString numberTOremove_managed = ui->comboBox_managedPeople->currentText();
       ui->comboBox_managedPeople->removeItem(ui->comboBox_managedPeople->currentIndex());

       QFile file_managed("managedpeople_salesmanager/"+numberTOremove_managed);
       file_managed.remove();
       this->showUI_viewMoreWindow();

       emit this->update_salesmanager_mainWindow();
    });

    //add按键的实现
    QObject::connect(ui->addManagedPeople_button,&QPushButton::clicked,
                     [=]()
    {
        QString numberTOadd_managed = ui->lineEdit_addManagedPeople->text();

        QFile file_managed("managedpeople_salesmanager/"+numberTOadd_managed);
        bool isOk = file_managed.open(QIODevice::WriteOnly);
        if(isOk == true)
        {
            QTextStream stream_managed(&file_managed);
            stream_managed<<ui->lineEdit_addManagedPeople->text();
        }
        file_managed.close();
        this->showUI_viewMoreWindow();

        emit this->update_salesmanager_mainWindow();
    });

}

viewMore_mainWindow::~viewMore_mainWindow()
{
    delete ui;
}
void viewMore_mainWindow::showUI_viewMoreWindow()
{

    //先清空缓存
    ui->comboBox_managedPeople->clear();

    public_fuctions help1;
    managed_people_salesmanager help2;
    int _allManagedNumber = help2.getAllNumber_managedPeople(help1.getAllNumber_fromFile());
    double allSales=help2.getAllSales(help1.getAllNumber_fromFile());

    ui->label_allNumberOFmanagedPeople->setText(QString::number(_allManagedNumber));
    ui->label_allSales->setText(QString::number(allSales));

   for(int i=1;i<=help1.getAllNumber_fromFile();i++)
   {
      QFile file_people("managedpeople_salesmanager/"+QString::number(i));
      bool isOk=file_people.open(QIODevice::ReadOnly);
      if(true == isOk)
      {
          ui->comboBox_managedPeople->addItem(QString::number(i));
      }
      file_people.close();
   }
}
