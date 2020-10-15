#include "enterdlg.h"
#include "ui_enterdlg.h"
#include "mainwindow.h"
#include "repowindow.h"
#include "logindialog.h"


EnterDlg::EnterDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("疫情交通防控综合管理系统");
}

EnterDlg::~EnterDlg()
{
    delete ui;
}

void EnterDlg::on_extBtn_clicked()
{
    exit(0);
}

void EnterDlg::on_srchBtn_clicked()
{
    MainWindow *w= new MainWindow;
    w->show();
    this->close();
}

void EnterDlg::on_repoBtn_clicked()
{
    repoWindow *w=new repoWindow;
    w->show();
    this->close();
}

void EnterDlg::on_adminBtn_clicked()
{
    LoginDialog *w=new LoginDialog;
    w->show();
    this->close();
}
