#include "logindialog.h"
#include "ui_logindialog.h"
#include "defs.h"
#include "managewindow.h"
#include "enterdlg.h"
#include "dbms.h"
#include "QMessageBox"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("疫情交通防控综合管理系统");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_exitBtn_clicked()
{
    exit(0);
}

void LoginDialog::on_returnBtn_clicked()
{
    EnterDlg *w=new EnterDlg;
    w->show();
    this->close();
}

void LoginDialog::on_loginBtn_clicked()
{
    QString id=ui->idEdit->text();
    QString key=ui->keyEdit->text();
    bool flag=loginDB(id,key);
    if(flag){
        ManageWindow *w=new ManageWindow;
        w->show();
        this->close();
    }
    else{
        QMessageBox* box=new QMessageBox;
        box->setText("账号密码错误，请重新再试");
        box->setWindowTitle("登录错误");
        box->exec();
        ui->keyEdit->clear();
    }
}
