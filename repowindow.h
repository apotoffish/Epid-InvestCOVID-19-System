#ifndef REPOWINDOW_H
#define REPOWINDOW_H

#include <QMainWindow>

namespace Ui {
class repoWindow;
}

class repoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit repoWindow(QWidget *parent = nullptr);
    ~repoWindow();

private slots:
    void on_exitBtn_clicked();//退出键按下

    void on_returnBtn_clicked();//返回键，返回系统入口选项

    void on_resetBtn_clicked();//重置键，将输入清空

    void on_promiseBtn_clicked();//承诺选项，按选后将激活申报登记键

    void on_repoBtn_clicked();//登记申报

private:
    Ui::repoWindow *ui;
};

#endif // REPOWINDOW_H
