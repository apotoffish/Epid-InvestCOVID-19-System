#include "addtrafficdialog.h"
#include "ui_addtrafficdialog.h"
#include "dbms.h"
#include <QMessageBox>

addTrafficDialog::addTrafficDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTrafficDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("添加列车/航班/大巴/客船");
}

addTrafficDialog::~addTrafficDialog()
{
    delete ui;
}

void addTrafficDialog::on_cancelBtn_clicked()
{
    this->destroy();
}

void addTrafficDialog::on_addTrafficBtn_clicked()
{
    bool flag;
    QStringList list;
    list<<ui->trafficEdit->text();
    list<<ui->typeEdit->text();
    list<<ui->dateEdit->text();
    list<<ui->enddateEdit->text();
    list<<ui->carriageEdit->text();
    list<<ui->passesEdit->text();
    QMessageBox* box=new QMessageBox;
    box->setWindowTitle("添加结果");
    flag=addTrafficDB(list);

    if(flag){
        box->setText("添加成功!");
    }
    else{
        box->setText("添加失败，系统已存在此班次");
    }
    box->exec();
    this->destroy();
}
