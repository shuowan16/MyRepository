#include "addinfowindow.h"
#include "ui_addinfowindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDialog>
#include <QDebug>
#include <mainwindow.h>
#include <QMessageBox>
#include <public_functions.h>


addInfoWindow::addInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addInfoWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("Add Information");


    //save按键的实现
    QObject::connect(ui->actionSave_addInfoWindow,&QAction::triggered,
                     [=]()
    {
         this->exitAfterSaved_addInfo();
    });

    //back按键的实现
    QObject::connect(ui->actionBack_addInfoWindow,&QAction::triggered,
                     [=]()
    {
        ui->line_4->show();                           //将隐藏的内容恢复
        ui->line_5->show();
        ui->line_6->show();
        ui->widget_worktime_OnlyTEC->show();
        ui->widget_sales_OnlySALESMAN->show();
        ui->widget_managedPeople_OnlySALESMANAGER->show();
        emit backMainWindow_signal_addInfo();
    });

    //add按键的实现
    QObject::connect(ui->addManagedPeople_button_addInfoWindow,&QPushButton::clicked,
                     [=]()
    {
        ui->lineEdit_addManagedPeople_addInfo->show();
    });

    //finish按键的实现
    QObject::connect(ui->finfish_addManaged_addInfo,&QPushButton::clicked,
                     [=]()
    {
          this->finishButton_addInfo();
    });

}

addInfoWindow::~addInfoWindow()
{
    delete ui;
}

void addInfoWindow::setposition_referSELECTED_addInfo(QString &_position)
{
    if(_position != "othertypes")
    {   this->selectedPosition=_position;
        ui->lineEdit_position_addInfoWindow->setText(_position);
        ui->lineEdit_position_addInfoWindow->setReadOnly(true);
    }
    else
    {
        this->selectedPosition = _position;
    }
}

void addInfoWindow::setUIdisplay_referSELECTED_addInfo(QString &_position)
{
    if(_position == "manager")
    {
        ui->widget_worktime_OnlyTEC->hide();
        ui->widget_sales_OnlySALESMAN->hide();
        ui->widget_managedPeople_OnlySALESMANAGER->hide();
        ui->line_4->hide();
        ui->line_5->hide();
        ui->line_6->hide();
        ui->lineEdit_pay_addInfoWindow->setText("12000");
        ui->lineEdit_pay_addInfoWindow->setReadOnly(true);
        ui->lineEdit_number_addInfoWindow->setText("NAN");
        ui->lineEdit_number_addInfoWindow->setReadOnly(true);
    }
    if(_position == "salesman")
    {
        ui->widget_worktime_OnlyTEC->hide();
        ui->widget_managedPeople_OnlySALESMANAGER->hide();
        ui->line_5->hide();
        ui->lineEdit_pay_addInfoWindow->setText("***");
        ui->lineEdit_pay_addInfoWindow->setReadOnly(true);

        ui->lineEdit_number_addInfoWindow->setText("NAN");
        ui->lineEdit_number_addInfoWindow->setReadOnly(true);
    }
    if(_position == "technician")
    {
        ui->widget_sales_OnlySALESMAN->hide();
        ui->widget_managedPeople_OnlySALESMANAGER->hide();
        ui->line_6->hide();
        ui->lineEdit_pay_addInfoWindow->setText("***");
        ui->lineEdit_pay_addInfoWindow->setReadOnly(true);
        ui->lineEdit_number_addInfoWindow->setText("NAN");
        ui->lineEdit_number_addInfoWindow->setReadOnly(true);
    }
    if(_position == "salesmanager")
    {
        ui->widget_worktime_OnlyTEC->hide();
        ui->widget_sales_OnlySALESMAN->hide();
        ui->line_4->hide();
        ui->line_5->hide();
        ui->lineEdit_addManagedPeople_addInfo->hide();
        ui->lineEdit_pay_addInfoWindow->setText("***");
        ui->lineEdit_pay_addInfoWindow->setReadOnly(true);
        ui->lineEdit_number_addInfoWindow->setText("NAN");
        ui->lineEdit_number_addInfoWindow->setReadOnly(true);

    }
    if(_position == "othertypes")
    {
        ui->widget_managedPeople_OnlySALESMANAGER->hide();
        ui->lineEdit_position_addInfoWindow->setReadOnly(false);
        ui->lineEdit_pay_addInfoWindow->setReadOnly(false);
        ui->line_6->hide();
        ui->lineEdit_number_addInfoWindow->setText("NAN");
        ui->lineEdit_number_addInfoWindow->setReadOnly(true);
    }
    else{
        ;
    }
}

void addInfoWindow::saved_action_addInfo()
{
    if(this->selectedPosition == "manager")
    {
        this->selectedManager_save_addInfo();
    }

    if(this->selectedPosition == "salesman")
    {
        this->selectedSalesman_save_addInfo();
    }

    if(this->selectedPosition == "technician")
    {
        this->selectedTechnician_save_addInfo();
    }
    if(this->selectedPosition == "salesmanager")
    {
        this->selectedSalesmanager_save_addInfo();
    }
    if(this->selectedPosition == "othertypes")
    {
        this->selectedOtherType_save_addInfo();
    }
}
    void addInfoWindow::selectedManager_save_addInfo()
{
    public_fuctions help;
    help.changeAllNumber_toFile(help.getAllNumber_fromFile()+1);
    //qDebug()<<"save succeed";
    int _allnumber_fromFile = help.getAllNumber_fromFile();
    QString path_manager = "manager/"+QString::number(_allnumber_fromFile);

    QFile file_manager(path_manager);
    bool isOk = file_manager.open(QIODevice::WriteOnly);
    if(true == isOk)
    {
        QTextStream stream_manager(&file_manager);
        stream_manager<<ui->lineEdit_name_addInfoWindow->text()<<"\n";
        stream_manager<<QString::number(_allnumber_fromFile)<<"\n";
        stream_manager<<ui->lineEdit_position_addInfoWindow->text()<<"\n";
        this->setPay_referPOSITION_and_PERCENT_addInfo();
        stream_manager<<ui->lineEdit_pay_addInfoWindow->text()<<"\n";
    }
    file_manager.close();
}
    void addInfoWindow::selectedSalesman_save_addInfo()
{
    public_fuctions help;
    help.changeAllNumber_toFile(help.getAllNumber_fromFile()+1);
    //qDebug()<<"save succeed";
    int _allnumber_fromFile = help.getAllNumber_fromFile();
    QString path_salesman = "salesman/"+QString::number(_allnumber_fromFile);

    QFile file_salesman(path_salesman);
    bool isOk = file_salesman.open(QIODevice::WriteOnly);
    if(true == isOk)
    {
        QTextStream stream_salesman(&file_salesman);
        stream_salesman<<ui->lineEdit_name_addInfoWindow->text()<<"\n";
        stream_salesman<<QString::number(_allnumber_fromFile)<<"\n";
        stream_salesman<<ui->lineEdit_position_addInfoWindow->text()<<"\n";
        this->setPay_referPOSITION_and_PERCENT_addInfo();
        stream_salesman<<ui->lineEdit_pay_addInfoWindow->text()<<"\n";
        stream_salesman<<ui->lineEdit_sales_addInfoWindow->text()<<"\n";
    }
    file_salesman.close();
}
    void addInfoWindow::selectedTechnician_save_addInfo()
{
    public_fuctions help;
    help.changeAllNumber_toFile(help.getAllNumber_fromFile()+1);
    //qDebug()<<"save succeed";
    int _allnumber_fromFile = help.getAllNumber_fromFile();
    QString path_tec = "technician/"+QString::number(_allnumber_fromFile);

    QFile file_tec(path_tec);
    bool isOk = file_tec.open(QIODevice::WriteOnly);
    if(true == isOk)
    {
        QTextStream stream_tec(&file_tec);
        stream_tec<<ui->lineEdit_name_addInfoWindow->text()<<"\n";
        stream_tec<<QString::number(_allnumber_fromFile)<<"\n";
        stream_tec<<ui->lineEdit_position_addInfoWindow->text()<<"\n";
        this->setPay_referPOSITION_and_PERCENT_addInfo();
        stream_tec<<ui->lineEdit_pay_addInfoWindow->text()<<"\n";
        stream_tec<<ui->lineEdit_worktime_addInfoWindow->text()<<"\n";
    }
    file_tec.close();
}
    void addInfoWindow::selectedSalesmanager_save_addInfo()
{
    public_fuctions help;
    help.changeAllNumber_toFile(help.getAllNumber_fromFile()+1);
    qDebug()<<"save succeed";
    int _allnumber_fromFile = help.getAllNumber_fromFile();
    QString path_salesmanager = "salesmanager/"+QString::number(_allnumber_fromFile);

    QFile file_salesmanager(path_salesmanager);
    bool isOk = file_salesmanager.open(QIODevice::WriteOnly);
    if(true == isOk)
    {
        QTextStream stream_salesmanager(&file_salesmanager);
        stream_salesmanager<<ui->lineEdit_name_addInfoWindow->text()<<"\n";
        stream_salesmanager<<QString::number(_allnumber_fromFile)<<"\n";
        stream_salesmanager<<ui->lineEdit_position_addInfoWindow->text()<<"\n";
        this->setPay_referPOSITION_and_PERCENT_addInfo();
        stream_salesmanager<<ui->lineEdit_pay_addInfoWindow->text()<<"\n";
    }


    file_salesmanager.close();
}
    void addInfoWindow::selectedOtherType_save_addInfo()
{
    public_fuctions help;
    help.changeAllNumber_toFile(help.getAllNumber_fromFile()+1);
    qDebug()<<"save succeed";
    int _allnumber_fromFile = help.getAllNumber_fromFile();
    QString path_othertype = "othertypes/"+QString::number(_allnumber_fromFile);

    QFile file_othertype(path_othertype);
    bool isOk = file_othertype.open(QIODevice::WriteOnly);
    if(true == isOk)
    {
        QTextStream stream_othertype(&file_othertype);
        stream_othertype<<ui->lineEdit_name_addInfoWindow->text()<<"\n";
        stream_othertype<<QString::number(_allnumber_fromFile)<<"\n";
        stream_othertype<<ui->lineEdit_position_addInfoWindow->text()<<"\n";
        stream_othertype<<ui->lineEdit_pay_addInfoWindow->text()<<"\n";
        stream_othertype<<ui->lineEdit_worktime_addInfoWindow->text()<<"\n";
        stream_othertype<<ui->lineEdit_sales_addInfoWindow->text()<<"\n";
    }
    file_othertype.close();
}



void addInfoWindow::setPay_referPOSITION_and_PERCENT_addInfo()
{
    if(this->selectedPosition == "manager")
    {
        double _pay_manager_double = 12000*this->getPayPercent_referSELECTED_addInfo();
        ui->lineEdit_pay_addInfoWindow->setReadOnly(false);
        ui->lineEdit_pay_addInfoWindow->setText(QString::number(_pay_manager_double,10,4));
        ui->lineEdit_pay_addInfoWindow->setReadOnly(true);
    }
    if(this->selectedPosition == "salesman")
    {
        double _pass = ui->lineEdit_sales_addInfoWindow->text().toDouble();
        double _pay_salesman_double = _pass*0.05*getPayPercent_referSELECTED_addInfo();
        ui->lineEdit_pay_addInfoWindow->setReadOnly(false);
        ui->lineEdit_pay_addInfoWindow->setText(QString::number(_pay_salesman_double,10,4));
        ui->lineEdit_pay_addInfoWindow->setReadOnly(true);
    }
    if(this->selectedPosition == "technician")
    {
        double _pass = ui->lineEdit_worktime_addInfoWindow->text().toDouble();
        double _pay_tec_double = _pass*260*getPayPercent_referSELECTED_addInfo();
        ui->lineEdit_pay_addInfoWindow->setReadOnly(false);
        ui->lineEdit_pay_addInfoWindow->setText(QString::number(_pay_tec_double,10,4));
        ui->lineEdit_pay_addInfoWindow->setReadOnly(true);
    }
    if(this->selectedPosition == "salesmanager")
    {

        public_fuctions help1;
        managed_people_salesmanager help2;
        int _allNumber = help1.getAllNumber_fromFile();
        double _pay_salesmanager = 8000*this->getPayPercent_referSELECTED_addInfo()+help2.getAllSales(_allNumber)*0.04;
        ui->lineEdit_pay_addInfoWindow->setReadOnly(false);
        ui->lineEdit_pay_addInfoWindow->setText(QString::number(_pay_salesmanager,10,4));
        ui->lineEdit_pay_addInfoWindow->setReadOnly(true);
    }

    else{
        ;
    }
}

double addInfoWindow::getPayPercent_referSELECTED_addInfo()
{
    QString _pay_percent_double;
    QFile file_percent("paypercent_promote/"+this->selectedPosition);
    bool isOk = file_percent.open(QIODevice::ReadOnly);
    if(isOk == true)
    {
        QTextStream stream_payPercent(&file_percent);
        _pay_percent_double=stream_payPercent.readLine();
        file_percent.close();
    }
    else{
        _pay_percent_double="1";
    }
    return _pay_percent_double.toDouble();
}

void addInfoWindow::exitAfterSaved_addInfo()
{
    QMessageBox IsExit_modal;
    IsExit_modal.setWindowTitle("Exit");
    IsExit_modal.setText("Do you want to saved?");
    IsExit_modal.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    int return_value=IsExit_modal.exec();
    switch(return_value)
    {
       case QMessageBox::Yes:
           this->saved_action_addInfo();
           ui->line_4->show();                           //将隐藏的内容恢复
           ui->line_5->show();
           ui->line_6->show();
           ui->widget_worktime_OnlyTEC->show();
           ui->widget_sales_OnlySALESMAN->show();
           ui->widget_managedPeople_OnlySALESMANAGER->show();
           emit backMainWindow_signal_addInfo();
           break;
       case QMessageBox::No:
           IsExit_modal.close();
           break;
    }
}

void addInfoWindow::finishButton_addInfo()
{
    QFile file_finish("managedpeople_salesmanager/"+ui->lineEdit_addManagedPeople_addInfo->text());

    bool isOk = file_finish.open(QIODevice::WriteOnly|QIODevice::Append);
    if(true == isOk)
    {
        QTextStream stream_finish(&file_finish);
        stream_finish<<ui->lineEdit_addManagedPeople_addInfo->text()<<"\n";
    }

    file_finish.close();
    ui->lineEdit_addManagedPeople_addInfo->hide();
}







