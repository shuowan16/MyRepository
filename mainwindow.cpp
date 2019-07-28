#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "public_functions.h"
#include <QPixmap>
#include <QLabel>
#include <QAction>
#include <QUrl>
#include <QDesktopServices>
#include <QObject>
#include <QString>
#include <QFile>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    fileWindow.hide();
    ui->setupUi(this);
    this->setWindowTitle("XX公司人事管理系统");
    //职工信息默认操作
    this->currentShowEmployee_CLASSname ="FALSE";
    this->currentShowEmployee_path="FALSE";
    this->update_avatar_normal();
    this->showUI_Info_mainWindow();


    //menuBar里action的实现


    QObject::connect(ui->action3463877866_qq_com,&QAction::triggered,
                     [=]()
    {
        QDesktopServices::openUrl((QString)"https://mail.qq.com/");
    });

    QObject::connect(ui->actionView_Source_code,&QAction::triggered,
                     [=]()
    {
        QDesktopServices::openUrl((QString)"https://github.com/shuowan16/MyRepository");
    });






    //关于file的action实现




    QObject::connect(ui->actionNew_file,&QAction::triggered,
                     [=]()
    {
        this->close();
        fileWindow.show();
    });
    QObject::connect(&fileWindow,&fileOperationWindow::backMainWindow_signal_file,
                     [=]()
    {
        this->show();
        fileWindow.hide();
    });
    QObject::connect(ui->actionOpen_file,&QAction::triggered,
                     [=]()
    {
        this->hide();
        this->fileWindow.show();
        this->fileWindow.openFile_fromMainWindow();
    });



    //AddInfo的实现

    QObject::connect(ui->actionManager_addInfo,&QAction::triggered,
                     [=]()
    {
       this->transformToAddInfo_port("manager");
    });
    QObject::connect(ui->actionSalesman_addInfo,&QAction::triggered,
                     [=]()
    {
        this->transformToAddInfo_port("salesman");
    });
    QObject::connect(ui->actionTechnician_addInfo,&QAction::triggered,
                     [=]()
    {
        this->transformToAddInfo_port("technician");
    });
    QObject::connect(ui->actionSalesManager_addInfo,&QAction::triggered,
                     [=]()
    {
        this->transformToAddInfo_port("salesmanager");
    });
    QObject::connect(ui->actionOtherTypes_addInfo,&QAction::triggered,
                     [=]()
    {
        this->transformToAddInfo_port("othertypes");
    });

    QObject::connect(&addInformationWindow,&addInfoWindow::backMainWindow_signal_addInfo,
                     [=]()
    {
          this->show();
          addInformationWindow.close();
    });





    //职工个人信息修改
    ui->personalInfoChange_mainWindow->setAlignment(Qt::AlignCenter);

    //sales更改按钮的实现
    QObject::connect(ui->sales_PersonalInfoChange,&QPushButton::clicked,
                     [=]()
    {
        this->changeSales();
        this->showUI_Info_mainWindow();
    });
    //worktime更改按钮实现
    QObject::connect(ui->worktime_PersonalInfoChange,&QPushButton::clicked,
                     [=]()
    {
        this->changeWorktime();
        this->showUI_Info_mainWindow();
    });
    //pay更改按钮的实现
    QObject::connect(ui->pay_PersonalInfoChange_onlyOTHER,&QPushButton::clicked,
                     [=]()
    {
        this->changePay();
        this->showUI_Info_mainWindow();
    });


    //search by number的实现
    QObject::connect(ui->searchBYnumber_button_mainWindow,&QPushButton::clicked,
                     [=]()
    {
       public_fuctions help;
       int number_returnAfterSearch = help.searchNumber_allEmployees(ui->lineEdit_searchBYnum_mainWindow->text().toInt());
       this->setcurrentShowEmployee_path_num(number_returnAfterSearch);
       this->showUI_Info_mainWindow();

    });

    //search by name的实现
    QObject::connect(ui->searchBYname_button_mainWindow,&QPushButton::clicked,
                     [=]()
    {
       public_fuctions help;
       int i= help.searchName_allEmployees(ui->lineEdit_searchBYname_mainWindow->text());
       this->setcurrentShowEmployee_path_name(i);

       this->showUI_Info_mainWindow();
    });

    //salesmanager的view more实现
    QObject::connect(ui->View_More_button_onlySALESMANAGER,&QPushButton::clicked,
                     [=]()
    {
        this->viewMoreWindow.show();
        viewMoreWindow.showUI_viewMoreWindow();
    });
    //接收到信息更新的信号
    QObject::connect(&viewMoreWindow,&viewMore_mainWindow::update_salesmanager_mainWindow,
                     [=]()
    {
        this->updatePay_salesmanager();
        this->showUI_Info_mainWindow();
    });

    //put into backlist按钮的实现
    QObject::connect(ui->put_into_blacklist_button_mainWindow,&QPushButton::clicked,
                     [=]()
    {
        QFile file_put("blacklist/"+ui->numberDisplay->text());

        bool isOk = file_put.open(QIODevice::WriteOnly);
        if(true == isOk)
        {
            QTextStream stream_finish(&file_put);
            stream_finish<<ui->numberDisplay->text()<<"\n";
        }

        file_put.close();
        this->showUI_Info_mainWindow();
    });
    //remove from blacklist的实现
    QObject::connect(ui->remove_from_blacklist_button_mainWindow,&QPushButton::clicked,
                     [=]()
    {
        QFile file_put("blacklist/"+ui->numberDisplay->text());
        file_put.remove();
        this->showUI_Info_mainWindow();
    });

   //delete的实现
   QObject::connect(ui->delete_button_mainWindow,&QPushButton::clicked,
                    [=]()
   {
       QFile file_delete(this->currentShowEmployee_path);
       file_delete.remove();

       //如果被删除的员工在blacklist里，则需要移除
       QFile file_blacklist("blacklist/"+ui->numberDisplay->text());
       file_blacklist.remove();


       //如果被删除的是salesman，则需要对salesmanager做检查并且更新
       if(this->currentShowEmployee_CLASSname == "salesman")
       {
           managed_people_salesmanager help;
           int judge_ornot = help.searchNumber_allEmployees(ui->numberDisplay->text().toInt());
           if(judge_ornot == 10)
           {
               QFile file_sales_managed("managedpeople_salesmanager/"+ui->numberDisplay->text());
               file_sales_managed.remove();
           }

           this->currentShowEmployee_CLASSname = "salesmanager";
           this->updatePay_salesmanager();
       }

       //如果被删除的是salesmanager，则需要将其管理的salesman从managed_people名单移除
       if(this->currentShowEmployee_CLASSname == "salesmanager")
       {
           managed_people_salesmanager help;
           help--;          //应用运算符重载机制
       }
       this->currentShowEmployee_path= "FALSE";
       this->currentShowEmployee_CLASSname="FALSE";
       this->showUI_Info_mainWindow();
   });

   //提升工资的实现
   QObject::connect(ui->actionManager_SP,&QAction::triggered,
                    [=]()
   {
       this->classTOpromote="manager";
       promotePayWindow.setCurrentClassName("manager");
       promotePayWindow.show();
   });
   QObject::connect(ui->actionSalesman_SP,&QAction::triggered,
                    [=]()
   {
       this->classTOpromote="salesman";
       promotePayWindow.setCurrentClassName("salesman");
       promotePayWindow.show();
   });
   QObject::connect(ui->actionTechnician_SP,&QAction::triggered,
                    [=]()
   {
       this->classTOpromote="technician";
       promotePayWindow.setCurrentClassName("technician");
       promotePayWindow.show();
   });
   QObject::connect(ui->actionSalesManager_SP,&QAction::triggered,
                    [=]()
   {
       this->classTOpromote="salesmanager";
       promotePayWindow.setCurrentClassName("salesmanager");
       promotePayWindow.show();
   });
   QObject::connect(ui->actionOthers_SP,&QAction::triggered,
                    [=]()
   {
       this->classTOpromote="othertypes";
       promotePayWindow.setCurrentClassName("othertypes");
       promotePayWindow.show();
   });

   QObject::connect(&promotePayWindow,&pay_promote::_updatePay,
                    [=]()
   {
       this->updatePay_afterPromote();
   });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::transformToAddInfo_port(QString _position)
{
    MainWindow::hide();
    addInformationWindow.show();
    addInformationWindow.setposition_referSELECTED_addInfo(_position);
    addInformationWindow.setUIdisplay_referSELECTED_addInfo(_position);
}

void MainWindow::setcurrentShowEmployee_path_num(const int _flag)
{
    if(_flag == 1)
    {
        QFile file_search("manager/"+ui->lineEdit_searchBYnum_mainWindow->text());
        file_search.open(QIODevice::ReadOnly);
        QFileInfo file_info(file_search);
        this->currentShowEmployee_path=file_info.absolutePath()+"/"+ui->lineEdit_searchBYnum_mainWindow->text();
        this->currentShowEmployee_CLASSname = "manager";
    }
    if(_flag == 2)
    {
        QFile file_search("salesman/"+ui->lineEdit_searchBYnum_mainWindow->text());
        file_search.open(QIODevice::ReadOnly);
        QFileInfo file_info(file_search);
        this->currentShowEmployee_path=file_info.absolutePath()+"/"+ui->lineEdit_searchBYnum_mainWindow->text();
        this->currentShowEmployee_CLASSname = "salesman";
    }
    if(_flag == 3)
    {
        QFile file_search("technician/"+ui->lineEdit_searchBYnum_mainWindow->text());
        file_search.open(QIODevice::ReadOnly);
        QFileInfo file_info(file_search);
        this->currentShowEmployee_path=file_info.absolutePath()+"/"+ui->lineEdit_searchBYnum_mainWindow->text();
        this->currentShowEmployee_CLASSname = "technician";
    }
    if(_flag == 4)
    {
        QFile file_search("salesmanager/"+ui->lineEdit_searchBYnum_mainWindow->text());
        file_search.open(QIODevice::ReadOnly);
        QFileInfo file_info(file_search);
        this->currentShowEmployee_path=file_info.absolutePath()+"/"+ui->lineEdit_searchBYnum_mainWindow->text();
        this->salesmanager_path=this->currentShowEmployee_path;
        this->currentShowEmployee_CLASSname = "salesmanager";
    }
    if(_flag == 5)
    {
        QFile file_search("othertypes/"+ui->lineEdit_searchBYnum_mainWindow->text());
        file_search.open(QIODevice::ReadOnly);
        QFileInfo file_info(file_search);
        this->currentShowEmployee_path=file_info.absolutePath()+"/"+ui->lineEdit_searchBYnum_mainWindow->text();
        this->currentShowEmployee_CLASSname = "othertypes";
    }
    else if(_flag == -1)
    {
        this->currentShowEmployee_path = "FALSE";
        this->currentShowEmployee_CLASSname = "FALSE";
    }
}

void MainWindow::setcurrentShowEmployee_path_name(const int _flag)
{
    public_fuctions help;
    int allNumber = help.getAllNumber_fromFile();

    if(_flag == 1)
    {
        for(int i = 1; i <= allNumber; i++)
        {
             QFile file_search("manager/"+QString::number(i));
             bool isOk_search = file_search.open(QIODevice::ReadOnly);
             if(isOk_search == true)
             {
                 QTextStream stream_search(&file_search);
                 if(stream_search.readLine() == ui->lineEdit_searchBYname_mainWindow->text())
                 {
                    QFileInfo file_info(file_search);


                    this->currentShowEmployee_path=file_info.absolutePath()+"/"+QString::number(i);


                    this->currentShowEmployee_CLASSname = "manager";

                    file_search.close();
                 }
                 else {
                     file_search.close();
                 }
             }
        }
    }
    if(_flag == 2)
    {
        for(int i = 1; i <= allNumber; i++)
        {
             QFile file_search("salesman/"+QString::number(i));
             bool isOk_search = file_search.open(QIODevice::ReadOnly);
             if(isOk_search == true)
             {
                 QTextStream stream_search(&file_search);
                 if(stream_search.readLine() == ui->lineEdit_searchBYname_mainWindow->text())
                 {
                    QFileInfo file_info(file_search);
                    this->currentShowEmployee_path=file_info.absolutePath()+"/"+QString::number(i);
                    this->currentShowEmployee_CLASSname = "salesman";
                    file_search.close();
                 }
                 else {
                     file_search.close();
                 }
             }
        }
    }
    if(_flag == 3)
    {
        for(int i = 1; i <= allNumber; i++)
        {
             QFile file_search("technician/"+QString::number(i));
             bool isOk_search = file_search.open(QIODevice::ReadOnly);
             if(isOk_search == true)
             {
                 QTextStream stream_search(&file_search);
                 if(stream_search.readLine() == ui->lineEdit_searchBYname_mainWindow->text())
                 {
                    QFileInfo file_info(file_search);
                    this->currentShowEmployee_path=file_info.absolutePath()+"/"+QString::number(i);
                    this->currentShowEmployee_CLASSname = "technician";
                    file_search.close();
                 }
                 else {
                     file_search.close();

                 }
             }
        }
    }
    if(_flag == 4)
    {
        for(int i = 1; i <= allNumber; i++)
        {
             QFile file_search("salesmanager/"+QString::number(i));
             bool isOk_search = file_search.open(QIODevice::ReadOnly);
             if(isOk_search == true)
             {
                 QTextStream stream_search(&file_search);
                 if(stream_search.readLine() == ui->lineEdit_searchBYname_mainWindow->text())
                 {
                    QFileInfo file_info(file_search);
                    this->currentShowEmployee_path=file_info.absolutePath()+"/"+QString::number(i);
                    this->salesmanager_path=this->currentShowEmployee_path;
                    this->currentShowEmployee_CLASSname = "salesmanager";
                    file_search.close();

                 }
                 else {
                     file_search.close();
                 }
             }
        }
    }
    if(_flag == 5)
    {
        for(int i = 1; i <= allNumber; i++)
        {
             QFile file_search("othertypes/"+QString::number(i));
             bool isOk_search = file_search.open(QIODevice::ReadOnly);
             if(isOk_search == true)
             {
                 QTextStream stream_search(&file_search);
                 if(stream_search.readLine() == ui->lineEdit_searchBYname_mainWindow->text())
                 {
                    QFileInfo file_info(file_search);
                    this->currentShowEmployee_path=file_info.absolutePath()+"/"+QString::number(i);
                    this->currentShowEmployee_CLASSname = "othertypes";
                    file_search.close();

                 }
                 else {
                     file_search.close();

                 }
             }
        }
    }
  if(_flag == -1)
  {
      this->currentShowEmployee_path="FALSE";
      this->currentShowEmployee_CLASSname="FALSE";
  }
}

void MainWindow::showUI_Info_mainWindow()
{

    if(this->currentShowEmployee_CLASSname == "FALSE")
    {
        ui->nameDisplay->setText("name");
        ui->positionDisplay->setText("position");
        ui->payDisplay->setText("pay");
        ui->salesDisplay->setText("sales");
        ui->numberDisplay->setText("number");
        ui->worktimeDisplay->setText("worktime");
        ui->View_More_button_onlySALESMANAGER->hide();
    }
    if(this->currentShowEmployee_CLASSname == "manager")
    {
        QFile file_show(this->currentShowEmployee_path);
        bool isOk = file_show.open(QIODevice::ReadOnly);
        if(true == isOk)
        {
            QTextStream stream_show(&file_show);
            QString _name = stream_show.readLine();
            QString _number = stream_show.readLine();
            QString _position = stream_show.readLine();
            QString _pay = stream_show.readLine();

            ui->nameDisplay->setText(_name);
            ui->numberDisplay->setText(_number);
            ui->positionDisplay->setText(_position);
            ui->payDisplay->setText(_pay);

            file_show.close();
        }

        ui->widget_worktimeDisplay_only_TEC->hide();
        ui->widget_salesDisplay_only_SALESMAN->hide();
        ui->View_More_button_onlySALESMANAGER->hide();
        ui->widget_change->hide();
        ui->personalInfoChange_mainWindow->hide();
    }
    if(this->currentShowEmployee_CLASSname == "salesman")
    {
        QFile file_show(this->currentShowEmployee_path);
        bool isOk = file_show.open(QIODevice::ReadOnly);
        if(true == isOk)
        {
            QTextStream stream_show(&file_show);
            QString _name = stream_show.readLine();
            QString _number = stream_show.readLine();
            QString _position = stream_show.readLine();
            QString _pay = stream_show.readLine();
            QString _sales = stream_show.readLine();

            ui->nameDisplay->setText(_name);
            ui->numberDisplay->setText(_number);
            ui->positionDisplay->setText(_position);
            ui->payDisplay->setText(_pay);
            ui->salesDisplay->setText(_sales);
            file_show.close();
        }
        ui->widget_salesDisplay_only_SALESMAN->show();
        ui->widget_worktimeDisplay_only_TEC->hide();
        ui->View_More_button_onlySALESMANAGER->hide();


        ui->personalInfoChange_mainWindow->show();
        ui->widget_change->show();

        ui->sales_PersonalInfoChange->show();
        ui->lineEdit_changeSales->show();

        ui->worktime_PersonalInfoChange->hide();
        ui->lineEdit_changeWorktime->hide();

        ui->pay_PersonalInfoChange_onlyOTHER->hide();
        ui->lineEdit_changePay->hide();
    }
    if(this->currentShowEmployee_CLASSname == "technician")
    {
        QFile file_show(this->currentShowEmployee_path);
        bool isOk = file_show.open(QIODevice::ReadOnly);
        if(true == isOk)
        {
            QTextStream stream_show(&file_show);
            QString _name = stream_show.readLine();
            QString _number = stream_show.readLine();
            QString _position = stream_show.readLine();
            QString _pay = stream_show.readLine();
            QString _worktime=stream_show.readLine();

            ui->nameDisplay->setText(_name);
            ui->numberDisplay->setText(_number);
            ui->positionDisplay->setText(_position);
            ui->payDisplay->setText(_pay);
            ui->worktimeDisplay->setText(_worktime);

            file_show.close();
        }
        ui->widget_worktimeDisplay_only_TEC->show();
        ui->widget_salesDisplay_only_SALESMAN->hide();
        ui->View_More_button_onlySALESMANAGER->hide();


        ui->personalInfoChange_mainWindow->show();
        ui->widget_change->show();

        ui->worktime_PersonalInfoChange->show();
        ui->lineEdit_changeWorktime->show();

        ui->sales_PersonalInfoChange->hide();
        ui->lineEdit_changeSales->hide();

        ui->pay_PersonalInfoChange_onlyOTHER->hide();
        ui->lineEdit_changePay->hide();
    }
    if(this->currentShowEmployee_CLASSname == "salesmanager")
    {
        QFile file_show(this->currentShowEmployee_path);
       // qDebug()<<this->currentShowEmployee_CLASSname;

        bool isOk = file_show.open(QIODevice::ReadOnly);
        if(true == isOk)
        {
            QTextStream stream_show(&file_show);
            QString _name = stream_show.readLine();
            QString _number = stream_show.readLine();
            QString _position = stream_show.readLine();
            QString _pay = stream_show.readLine();

            ui->nameDisplay->setText(_name);
            ui->numberDisplay->setText(_number);
            ui->positionDisplay->setText(_position);
            ui->payDisplay->setText(_pay);

            file_show.close();
        }
        ui->widget_salesDisplay_only_SALESMAN->hide();
        ui->widget_worktimeDisplay_only_TEC->hide();

        ui->widget_change->hide();
        ui->personalInfoChange_mainWindow->hide();
        ui->View_More_button_onlySALESMANAGER->show();
    }

    if(this->currentShowEmployee_CLASSname == "othertypes")
    {
        QFile file_show(this->currentShowEmployee_path);
        bool isOk = file_show.open(QIODevice::ReadOnly);
        if(true == isOk)
        {
            QTextStream stream_show(&file_show);
            QString _name = stream_show.readLine();
            QString _number = stream_show.readLine();
            QString _position = stream_show.readLine();
            QString _pay = stream_show.readLine();
            QString _worktime=stream_show.readLine();
            QString _sales=stream_show.readLine();


            ui->nameDisplay->setText(_name);
            ui->numberDisplay->setText(_number);
            ui->positionDisplay->setText(_position);
            ui->payDisplay->setText(_pay);
            ui->worktimeDisplay->setText(_worktime);
            ui->salesDisplay->setText(_sales);

            file_show.close();
        }
        ui->View_More_button_onlySALESMANAGER->hide();
        ui->widget_salesDisplay_only_SALESMAN->show();
        ui->widget_worktimeDisplay_only_TEC->show();

        ui->personalInfoChange_mainWindow->show();
        ui->widget_change->show();

        ui->sales_PersonalInfoChange->show();
        ui->lineEdit_changeSales->show();
        ui->worktime_PersonalInfoChange->show();
        ui->lineEdit_changeWorktime->show();
        ui->pay_PersonalInfoChange_onlyOTHER->show();
        ui->lineEdit_changePay->show();
    }
    this->chooseAvatar();
}

void MainWindow::updatePay_salesmanager()
{
    public_fuctions help;
    if(this->currentShowEmployee_CLASSname == "salesmanager")
    {
        public_fuctions help1;
        managed_people_salesmanager help2;
        int _allNumber = help1.getAllNumber_fromFile();
        double _pay_salesmanager = 8000*help.getPayPromoteRadio(currentShowEmployee_CLASSname)+help2.getAllSales(_allNumber)*0.04;

        QFile file_salesmanager(this->salesmanager_path);
        file_salesmanager.open(QIODevice::ReadOnly);
        QTextStream stream_salesmanager(&file_salesmanager);
        QString _name=stream_salesmanager.readLine();
        QString _number=stream_salesmanager.readLine();
        QString _position = stream_salesmanager.readLine();
        file_salesmanager.close();

        file_salesmanager.open(QIODevice::WriteOnly|QIODevice::Truncate);
        stream_salesmanager<<_name<<"\n";
        stream_salesmanager<<_number<<"\n";
        stream_salesmanager<<_position<<"\n";
        stream_salesmanager<<_pay_salesmanager<<"\n";

        file_salesmanager.close();
    }

    else{
        ;
    }
}

void MainWindow::changeSales()
{
    addInformationWindow.setposition_referSELECTED_addInfo(this->currentShowEmployee_CLASSname);
    if(this->currentShowEmployee_CLASSname == "salesman")
    {
        double _pay_salesman = ui->lineEdit_changeSales->text().toDouble()*addInformationWindow.getPayPercent_referSELECTED_addInfo()*0.05;

        QFile file_salesman(this->currentShowEmployee_path);
        file_salesman.open(QIODevice::ReadOnly);
        QTextStream stream_salesman(&file_salesman);
        QString _name=stream_salesman.readLine();
        QString _number=stream_salesman.readLine();
        QString _position = stream_salesman.readLine();
        file_salesman.close();

        file_salesman.open(QIODevice::WriteOnly|QIODevice::Truncate);
        stream_salesman<<_name<<"\n";
        stream_salesman<<_number<<"\n";
        stream_salesman<<_position<<"\n";
        stream_salesman<<_pay_salesman<<"\n";
        stream_salesman<<ui->lineEdit_changeSales->text()<<"\n";
        file_salesman.close();
    }
    if(this->currentShowEmployee_CLASSname == "othertypes")
    {
        QFile file_other(this->currentShowEmployee_path);
        file_other.open(QIODevice::ReadOnly);
        QTextStream stream_other(&file_other);
        QString _name=stream_other.readLine();
        QString _number=stream_other.readLine();
        QString _position = stream_other.readLine();
        QString _pay=stream_other.readLine();
        QString _worktime=stream_other.readLine();
        QString _sales_old=stream_other.readLine();
        file_other.close();

        file_other.open(QIODevice::WriteOnly|QIODevice::Truncate);
        stream_other<<_name<<"\n";
        stream_other<<_number<<"\n";
        stream_other<<_position<<"\n";
        stream_other<<_pay<<"\n";
        stream_other<<_worktime<<"\n";
        stream_other<<ui->lineEdit_changeSales->text()<<"\n";
        file_other.close();
    }
}

void MainWindow::changeWorktime()
{
    addInformationWindow.setposition_referSELECTED_addInfo(this->currentShowEmployee_CLASSname);
    if(this->currentShowEmployee_CLASSname == "technician")
    {
        double _pay_tec=260*addInformationWindow.getPayPercent_referSELECTED_addInfo()*ui->lineEdit_changeWorktime->text().toDouble();
        QFile file_tec(this->currentShowEmployee_path);

        file_tec.open(QIODevice::ReadOnly);
        QTextStream stream_tec(&file_tec);
        QString _name=stream_tec.readLine();
        QString _number=stream_tec.readLine();
        QString _position = stream_tec.readLine();
        file_tec.close();

        file_tec.open(QIODevice::WriteOnly|QIODevice::Truncate);
        stream_tec<<_name<<"\n";
        stream_tec<<_number<<"\n";
        stream_tec<<_position<<"\n";
        stream_tec<<_pay_tec<<"\n";
        stream_tec<<ui->lineEdit_changeWorktime->text()<<"\n";
        file_tec.close();
    }
    if(this->currentShowEmployee_CLASSname == "othertypes")
    {
        QFile file_other(this->currentShowEmployee_path);
        file_other.open(QIODevice::ReadOnly);
        QTextStream stream_other(&file_other);
        QString _name=stream_other.readLine();
        QString _number=stream_other.readLine();
        QString _position = stream_other.readLine();
        QString _pay=stream_other.readLine();
        QString _worktime_old=stream_other.readLine();
        QString _sales=stream_other.readLine();
        file_other.close();

        file_other.open(QIODevice::WriteOnly|QIODevice::Truncate);
        stream_other<<_name<<"\n";
        stream_other<<_number<<"\n";
        stream_other<<_position<<"\n";
        stream_other<<_pay<<"\n";
        stream_other<<ui->lineEdit_changeWorktime->text()<<"\n";
        stream_other<<_sales<<"\n";
        file_other.close();
    }
}

void MainWindow::changePay()
{
   addInformationWindow.setposition_referSELECTED_addInfo(this->currentShowEmployee_CLASSname);
   QFile file_other(this->currentShowEmployee_path);
   file_other.open(QIODevice::ReadOnly);
   QTextStream stream_other(&file_other);
   QString _name=stream_other.readLine();
   QString _number=stream_other.readLine();
   QString _position = stream_other.readLine();
   QString _pay_old=stream_other.readLine();
   QString _worktime=stream_other.readLine();
   QString _sales=stream_other.readLine();
   file_other.close();


   file_other.open(QIODevice::WriteOnly|QIODevice::Truncate);
   stream_other<<_name<<"\n";
   stream_other<<_number<<"\n";
   stream_other<<_position<<"\n";
   stream_other<<ui->lineEdit_changePay->text()<<"\n";
   stream_other<<_worktime<<"\n";
   stream_other<<_sales<<"\n";
   file_other.close();

}

void MainWindow::update_avatar_blacklist()
{
    QPixmap Avatar_user_blacklist("image/emoij02.png");
    ui->Avatar_mainWindow->setPixmap(Avatar_user_blacklist);
    ui->Avatar_mainWindow->setFixedSize(200,200);
    ui->Avatar_mainWindow->setScaledContents(true);
}

void MainWindow::update_avatar_normal()
{
    QPixmap Avatar_user_default("image/emoij01.jpg");
    ui->Avatar_mainWindow->setPixmap(Avatar_user_default);
    ui->Avatar_mainWindow->resize(200,200);
    ui->Avatar_mainWindow->setScaledContents(true);
}

void MainWindow::chooseAvatar()
{
    QFile file_blacklist("blacklist/"+ui->numberDisplay->text());
    bool isOk = file_blacklist.open(QIODevice::ReadOnly);
    if(isOk == true)
    {
        this->update_avatar_blacklist();
    }
    else {
        this->update_avatar_normal();
    }
}

void MainWindow::updatePay_afterPromote()
{
    public_fuctions help;
    int allnumber=help.getAllNumber_fromFile();

    for(int i=1;i<=allnumber;i++)
    {

      if(classTOpromote == "manager")
      {
         double pay_new=help.getPayPromoteRadio(this->classTOpromote)*12000;

         QFile file_update(classTOpromote+"/"+QString::number(i));
         bool isOk=file_update.open(QIODevice::ReadOnly);
         if(isOk == true)
         {
            QTextStream stream_update(&file_update);
            QString _name=stream_update.readLine();
            QString _number=stream_update.readLine();
            QString _position = stream_update.readLine();
            QString _pay_old=stream_update.readLine();

            file_update.close();

            file_update.open(QIODevice::WriteOnly|QIODevice::Truncate);
            stream_update<<_name<<"\n";
            stream_update<<_number<<"\n";
            stream_update<<_position<<"\n";
            stream_update<<QString::number(pay_new)<<"\n";
            file_update.close();
         }
      }
      if(classTOpromote == "salesman")
      {


          QFile file_update(classTOpromote+"/"+QString::number(i));
          bool isOk=file_update.open(QIODevice::ReadOnly);
          if(isOk == true)
          {
             QTextStream stream_update(&file_update);
             QString _name=stream_update.readLine();
             QString _number=stream_update.readLine();
             QString _position = stream_update.readLine();
             QString _pay_old=stream_update.readLine();
             QString _sales=stream_update.readLine();

             file_update.close();

             double pay_new=_pay_old.toDouble()*help.getPayPromoteRadio(this->classTOpromote);

             file_update.open(QIODevice::WriteOnly|QIODevice::Truncate);
             stream_update<<_name<<"\n";
             stream_update<<_number<<"\n";
             stream_update<<_position<<"\n";
             stream_update<<QString::number(pay_new)<<"\n";
             stream_update<<_sales<<"\n";
             file_update.close();
          }
      }
      if(classTOpromote == "technician")
      {
          QFile file_update(classTOpromote+"/"+QString::number(i));
          bool isOk=file_update.open(QIODevice::ReadOnly);
          if(isOk == true)
          {
             QTextStream stream_update(&file_update);
             QString _name=stream_update.readLine();
             QString _number=stream_update.readLine();
             QString _position = stream_update.readLine();
             QString _pay_old=stream_update.readLine();
             QString _worktime=stream_update.readLine();


             file_update.close();

             double pay_new=_pay_old.toDouble()*help.getPayPromoteRadio(this->classTOpromote);

             file_update.open(QIODevice::WriteOnly|QIODevice::Truncate);
             stream_update<<_name<<"\n";
             stream_update<<_number<<"\n";
             stream_update<<_position<<"\n";
             stream_update<<QString::number(pay_new)<<"\n";
             stream_update<<_worktime<<"\n";
             file_update.close();
          }
      }
      if(classTOpromote == "othertypes")
      {
          QFile file_update(classTOpromote+"/"+QString::number(i));
          bool isOk=file_update.open(QIODevice::ReadOnly);
          if(isOk == true)
          {
             QTextStream stream_update(&file_update);
             QString _name=stream_update.readLine();
             QString _number=stream_update.readLine();
             QString _position = stream_update.readLine();
             QString _pay_old=stream_update.readLine();
             QString _worktime = stream_update.readLine();
             QString _sales=stream_update.readLine();

             file_update.close();

             double pay_new=_pay_old.toDouble()*help.getPayPromoteRadio(this->classTOpromote);

             file_update.open(QIODevice::WriteOnly|QIODevice::Truncate);
             stream_update<<_name<<"\n";
             stream_update<<_number<<"\n";
             stream_update<<_position<<"\n";
             stream_update<<QString::number(pay_new)<<"\n";
             stream_update<<_worktime<<"\n";
             stream_update<<_sales<<"\n";
             file_update.close();
          }
      }
      if(classTOpromote == "salesmanager")
      {


          QFile file_update(classTOpromote+"/"+QString::number(i));
          bool isOk=file_update.open(QIODevice::ReadOnly);
          if(isOk == true)
          {
             QTextStream stream_update(&file_update);
             QString _name=stream_update.readLine();
             QString _number=stream_update.readLine();
             QString _position = stream_update.readLine();
             QString _pay_old=stream_update.readLine();

             file_update.close();

             double pay_new=help.getPayPromoteRadio(this->classTOpromote)*_pay_old.toDouble();

             file_update.open(QIODevice::WriteOnly|QIODevice::Truncate);
             stream_update<<_name<<"\n";
             stream_update<<_number<<"\n";
             stream_update<<_position<<"\n";
             stream_update<<QString::number(pay_new)<<"\n";
             file_update.close();
          }
      }
    }
}



