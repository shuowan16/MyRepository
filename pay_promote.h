#ifndef PAY_PROMOTE_H
#define PAY_PROMOTE_H

#include <QMainWindow>

namespace Ui {
class pay_promote;
}

class pay_promote : public QMainWindow
{
    Q_OBJECT

public:
    explicit pay_promote(QWidget *parent = nullptr);
    ~pay_promote();



    //公有属性
    QString currentClassName;
    QString currentOpenPath;
    double oldPayRate;
    double newPayRate;


    void setcurrentClassName(QString _classname);
    void setCurrentClassName(QString _position);
signals:
    void _updatePay();

private:
    Ui::pay_promote *ui;
};

#endif // PAY_PROMOTE_H
