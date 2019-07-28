#ifndef ADDINFOWINDOW_H
#define ADDINFOWINDOW_H

#include <QMainWindow>

namespace Ui {
class addInfoWindow;
}

class addInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit addInfoWindow(QWidget *parent = nullptr);
    ~addInfoWindow();



    //记录保存是否成功
    //公有属性
    bool managerSave_isok;
    bool salesmanSave_isok;
    bool technicianSave_isok;
    bool salesmanagerSave_isok;
    bool otherSave_isok;


    //设置当前操作员工的职位
    void setposition_referSELECTED_addInfo(QString &_position);
    //根据员工职位设置界面
    void setUIdisplay_referSELECTED_addInfo(QString &_position);

    //保存员工信息的操作
    void saved_action_addInfo();
         void selectedManager_save_addInfo();
         void selectedSalesman_save_addInfo();
         void selectedSalesmanager_save_addInfo();
         void selectedTechnician_save_addInfo();
         void selectedOtherType_save_addInfo();
         void setPay_referPOSITION_and_PERCENT_addInfo();
         void exitAfterSaved_addInfo();             //保存后关闭窗口
    //获取薪资提升比例
    double getPayPercent_referSELECTED_addInfo();

    void finishButton_addInfo();
private:
    Ui::addInfoWindow *ui;
    QString selectedPosition;      //记录用户在MainWindow里选择要添加的职位



signals:
    void backMainWindow_signal_addInfo();
};

#endif // ADDINFOWINDOW_H
