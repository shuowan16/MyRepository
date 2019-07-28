#ifndef VIEWMORE_MAINWINDOW_H
#define VIEWMORE_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class viewMore_mainWindow;
}

class viewMore_mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewMore_mainWindow(QWidget *parent = nullptr);
    ~viewMore_mainWindow();


    //view more窗口的界面设置
    void showUI_viewMoreWindow();
signals:
    void update_salesmanager_mainWindow();

private:
    Ui::viewMore_mainWindow *ui;
};

#endif // VIEWMORE_MAINWINDOW_H
