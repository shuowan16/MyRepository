#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fileoperationwindow.h>
#include <addinfowindow.h>
#include <viewmore_mainwindow.h>
#include <pay_promote.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    //设置显示员工信息界面的样式和信息
    void showUI_Info_mainWindow();

    //更改sales
    void changeSales();
    //更改worktimes
    void changeWorktime();
    //更改pay
    void changePay();

    //查询并修改currentShowEmployee_path的值，未找到的话设置为FALSE
    //根据_flag的值判断，1代表在manager文件夹找到
    //2代表在salesman文件夹找到
    //3代表在technician文件夹里找到
    //4代表在salesmanager文件夹里找到
    //5代表在othertypes文件夹里找到
    void setcurrentShowEmployee_path_num(const int _flag);
    void setcurrentShowEmployee_path_name(const int _flag);


    //根据添加的职位设置界面的接口
    void transformToAddInfo_port(QString _position);

    //将搜索后的结果显示到界面
    void showInfo_searchedEmployee();

    //更新salesmanager工资函数
    void updatePay_salesmanager();
    //更新manager的工资函数
    void updatePay_afterPromote();

    //更新头像函数
    void update_avatar_blacklist();
    void update_avatar_normal();

    //根据选择的人决定使用哪个头像
    void chooseAvatar();

private:
    Ui::MainWindow *ui;
    QString currentShowEmployee_path;        //当前显示的员工的路径
    QString currentShowEmployee_CLASSname;   //当前显示的员工所属的类别
    QString salesmanager_path;               //salesmanager所在的路径
    QString classTOpromote;

    fileOperationWindow fileWindow;
    addInfoWindow addInformationWindow;
    viewMore_mainWindow viewMoreWindow;
    pay_promote promotePayWindow;
};
#endif // MAINWINDOW_H
