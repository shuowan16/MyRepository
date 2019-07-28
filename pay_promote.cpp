#include "pay_promote.h"
#include "ui_pay_promote.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

pay_promote::pay_promote(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pay_promote)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("Salary Promote");
    //OK按钮的操作

    QObject::connect(ui->promoteOk_button,&QPushButton::clicked,
                     [=]()
    {
        QFile file_promote("paypercent_promote/"+this->currentClassName);
        //qDebug()<<"paypercent_promote/"+this->currentClassName;
        file_promote.open(QIODevice::WriteOnly|QIODevice::Truncate);
        QTextStream stream_promote(&file_promote);
        stream_promote<<ui->lineEdit_promote_input->text();
        file_promote.close();

        emit this->_updatePay();

        this->hide();
    });
}

pay_promote::~pay_promote()
{
    delete ui;
}

void pay_promote::setCurrentClassName(QString _position)
{
    this->currentClassName=_position;
}
