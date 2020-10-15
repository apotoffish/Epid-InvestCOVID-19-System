#include "deltrafficdialog.h"
#include "ui_deltrafficdialog.h"
#include "dbms.h"
#include <QMessageBox>

delTrafficDialog::delTrafficDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delTrafficDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("删除火车/飞机/客车/轮船");
}

delTrafficDialog::~delTrafficDialog()
{
    delete ui;
}

void delTrafficDialog::on_cancelBtn_clicked()
{
    this->destroy();
}

void delTrafficDialog::on_addTrafficBtn_clicked()
{
    bool flag;
    QStringList list;
    list<<ui->trafficEdit->text();
    list<<ui->dateEdit->text();
    list<<ui->typeEdit->text();
    QMessageBox* box=new QMessageBox;
    box->setWindowTitle("删除结果");
    flag=delTrafficDB(list);

    if(flag){
        box->setText("删除成功");
    }
    else{
        box->setText("删除失败，请检查是否存在此班次");

    }
    box->exec();
    this->destroy();
}
