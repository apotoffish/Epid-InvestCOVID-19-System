#ifndef MANAGEWINDOW_H
#define MANAGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ManageWindow;
}

class ManageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManageWindow(QWidget *parent = nullptr);
    ~ManageWindow();
    void createActions();//初始化，连接菜单项和槽信号

private:
    Ui::ManageWindow *ui;

private slots:
    void onExit();//退出
    void onReturn();//返回
    void onShowTraffic();//显示交通工具
    void onAddTraffic();//添加交通工具
    void onDelTraffic();//删除交通工具
    void onShowRisk();//显示已有的病患信息
    void onAddRisk();//显示申报的病患信息
    void onDelRisk();//删除病患
    void on_addBtn_clicked();//添加申报信息到病患列表
    void on_ingnoreBtn_clicked();//删除申报信息
};

#endif // MANAGEWINDOW_H
