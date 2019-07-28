#ifndef FILEOPERATIONWINDOW_H
#define FILEOPERATIONWINDOW_H

#include <QMainWindow>
namespace Ui {
class fileOperationWindow;
}

class fileOperationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit fileOperationWindow(QWidget *parent = nullptr);
    ~fileOperationWindow();
    void exitDialog_modal();
    void openFile_fromMainWindow();
    void saveFile_newPath();

    //是否打开记录员工信息的文件
    //共有属性
    bool isopenManager;
    bool isopenSalesman;
    bool isopenTechnician;
    bool isopenSalesmanager;
    bool isopenOthers;
private:
    Ui::fileOperationWindow *ui;
    QString currentPath_open;



signals:
    void backMainWindow_signal_file();
};

#endif // FILEOPERATIONWINDOW_H
