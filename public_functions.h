#ifndef PUBLIC_FUNCTIONS_H
#define PUBLIC_FUNCTIONS_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>
#include <QString>
#include <mainwindow.h>

class public_fuctions         //获取公有文件内容的函数集合类
{
public:
    //根据输入的编号或者姓名获取所查询的员工所在的文件夹

    virtual int searchNumber_allEmployees(const int _number)
{
    QFile file_manager("manager/"+QString::number(_number));
    QFile file_salesman("salesman/"+QString::number(_number));
    QFile file_tec("technician/"+QString::number(_number));
    QFile file_salesmanager("salesmanager/"+QString::number(_number));
    QFile file_other("othertypes/"+QString::number(_number));

    bool isOk_manager = file_manager.open(QIODevice::ReadOnly);
    bool isOk_salesman = file_salesman.open(QIODevice::ReadOnly);
    bool isOk_tec = file_tec.open(QIODevice::ReadOnly);
    bool isOk_salesmanager = file_salesmanager.open(QIODevice::ReadOnly);
    bool isOk_other = file_other.open(QIODevice::ReadOnly);

    if(isOk_manager == true)
    {
        QFileInfo file_info(file_manager);
        //qDebug()<<file_info.absolutePath();
        return  1;
    }
    if(isOk_salesman == true)
    {
        QFileInfo file_info(file_salesman);
        //qDebug()<<file_info.absolutePath();
        return 2;
    }
    if(isOk_tec == true)
    {
        QFileInfo file_info(file_tec);
        //qDebug()<<file_info.absolutePath();
        return  3;
    }
    if(isOk_salesmanager == true)
    {
        QFileInfo file_info(file_salesmanager);
        qDebug()<<file_info.absolutePath();
        return  4;
    }
    if(isOk_other == true)
    {
        QFileInfo file_info(file_other);
        //qDebug()<<file_info.absolutePath();
        return  5;
    }
    else {
          //qDebug()<<"no such employee";
        return -1;
    }
}


    int searchName_allEmployees(const QString &_name)
{
   int allNumber = this->getAllNumber_fromFile();

   for(int i = 0; i <= allNumber; i++)
   {
        QFile file_manager("manager/"+QString::number(i));
        bool isOk_manager = file_manager.open(QIODevice::ReadOnly);
        if(isOk_manager == true)
        {
            QTextStream stream_manager(&file_manager);
            if(stream_manager.readLine() == _name)
            {
               file_manager.close();
               return 1;
            }
            else {
                file_manager.close();
            }
        }
   }
   for(int i = 0; i <= allNumber; i++)
   {
        QFile file_salesman("salesman/"+QString::number(i));
        bool isOk_salesman = file_salesman.open(QIODevice::ReadOnly);
        if(isOk_salesman == true)
        {
            QTextStream stream_salesman(&file_salesman);
            if(stream_salesman.readLine() == _name)
            {
               file_salesman.close();
               return 2;
            }
            else {
                file_salesman.close();
            }
        }
   }
   for(int i = 0; i <= allNumber; i++)
   {
        QFile file_tec("technician/"+QString::number(i));
        bool isOk_tec = file_tec.open(QIODevice::ReadOnly);
        if(isOk_tec == true)
        {
            QTextStream stream_tec(&file_tec);
            if(stream_tec.readLine() == _name)
            {
               file_tec.close();
               return 3;
            }
            else {
               file_tec.close() ;
            }
        }
   }
   for(int i = 0; i <= allNumber; i++)
   {
        QFile file_salesmanager("salesmanager/"+QString::number(i));
        bool isOk_salesmanager = file_salesmanager.open(QIODevice::ReadOnly);
        if(isOk_salesmanager == true)
        {
            QTextStream stream_salesmanagerr(&file_salesmanager);
            if(stream_salesmanagerr.readLine() == _name)
            {
               file_salesmanager.close();
               return 4;
            }
            else {
                file_salesmanager.close();
            }
        }
   }
   for(int i = 0; i <= allNumber; i++)
   {
        QFile file_othertypes("othertypes/"+QString::number(i));
        bool isOk_othertypes = file_othertypes.open(QIODevice::ReadOnly);
        if(isOk_othertypes == true)
        {
            QTextStream stream_other(&file_othertypes);
            if(stream_other.readLine() == _name)
            {
               file_othertypes.close();
               return 5;
            }
            else {
                file_othertypes.close();
            }
        }
   }
   return -1;
}


    //得到公司员工总数
    int getAllNumber_fromFile()
{
    QFile file_allnumber("allnumber/allNumber");
    int _number_fromFile;
    bool isOk = file_allnumber.open(QIODevice::ReadOnly);
    if(true == isOk)
    {
        QTextStream stream_allnumber(&file_allnumber);
        _number_fromFile = stream_allnumber.readLine().toInt();
    }
    else
    {
        _number_fromFile = -1;
    }
    file_allnumber.close();
    return _number_fromFile;
}

    //修改公司员工总数
    void changeAllNumber_toFile(int _num)
{
    QFile file_allnumber("allnumber/allNumber");
    bool isOk = file_allnumber.open(QIODevice::WriteOnly);
    if(true == isOk)
    {
        QTextStream stream_allnumber(&file_allnumber);
        stream_allnumber<<_num;
    }
    file_allnumber.close();
}

    //得到薪资提升比例

    double getPayPromoteRadio(QString _position)
{
    QString _pay_percent_double;
    QFile file_percent("paypercent_promote/"+_position);
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


};
class managed_people_salesmanager:public public_fuctions
{

public:

    //获取销售经理管辖的总人数
    int getAllNumber_managedPeople(int _allNumber)
    {
       int allNUmber_managedPeople = 0;
       for(int i=1;i<=_allNumber;i++)
       {
           QFile file_people("managedpeople_salesmanager/"+QString::number(i));
           bool isOk = file_people.open(QIODevice::ReadOnly);
           if(true == isOk)
           {
               allNUmber_managedPeople++;
               file_people.close();
           }
       }
       return allNUmber_managedPeople;
    }

    //获取销售经理管辖人员的总销售额
    double getAllSales(int _allNumber)
    {
        double allSales=0;
        for(int i =1;i<=_allNumber;i++)
        {
            QFile file_managed("managedpeople_salesmanager/"+QString::number(i));
            bool isOk = file_managed.open(QIODevice::ReadOnly);
            if(true == isOk)
            {
                QFile file_sales("salesman/"+QString::number(i));
                file_sales.open(QIODevice::ReadOnly);
                QTextStream stream_readSale(&file_sales);
                QString _name = stream_readSale.readLine();
                QString _number = stream_readSale.readLine();
                QString _position = stream_readSale.readLine();
                QString _pay = stream_readSale.readLine();
                QString _sales = stream_readSale.readLine();

                allSales += _sales.toDouble();

                file_sales.close();
            }
           file_managed.close();
        }
        return allSales;
    }

    //根据输入的编号查询此员工是否在managed people文件夹
     int searchNumber_allEmployees(const int _number)
    {
       QFile file_found("managedpeople_salesmanager"+QString::number(_number));
       bool isOk = file_found.open(QIODevice::ReadOnly);
       if(isOk == true)
       {
           return 10;
       }
       else {
           return -10;
       }

    }

    //重载后置--  将managed_people文件夹里的内容清除
    managed_people_salesmanager operator -- (int)
    {
        for(int i=0;i<INT_MAX;i++)
        {
            QFile file_delete("managedpeople_salesmanager"+QString::number(i));
            file_delete.remove();
        }
    }

};

#endif // PUBLIC_FUNCTIONS_H
