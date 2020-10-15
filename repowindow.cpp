#include "repowindow.h"
#include "ui_repowindow.h"
#include "defs.h"
#include "enterdlg.h"
#include "dbms.h"
#include "QMessageBox"

repoWindow::repoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::repoWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("疫情交通防控综合管理系统");
    ui->repoBtn->setDisabled(true);
    ui->textBrowser->setText(PROMISE);
}

repoWindow::~repoWindow()
{
    delete ui;
}

void repoWindow::on_exitBtn_clicked()
{
    exit(0);
}

void repoWindow::on_returnBtn_clicked()
{
    EnterDlg *w=new EnterDlg;
    w->show();
    this->close();
}

void repoWindow::on_resetBtn_clicked()
{
    ui->trafficNumEdit->clear();
    ui->seatNumEdit->clear();
    ui->departureEdit->clear();
    ui->destinationEdit->clear();
    ui->carriageNumEdit->clear();
    ui->calendarWidget->showToday();
    ui->promiseBtn->setChecked(false);
    ui->repoBtn->setDisabled(true);
}

void repoWindow::on_promiseBtn_clicked()
{
    ui->repoBtn->setEnabled(true);
}

void repoWindow::on_repoBtn_clicked()
{
    struct finfo finfo;
    int flag=0;
    QString metatext = ui->trafficNumEdit->text();
    QDate metadate=ui->calendarWidget->selectedDate();

    //格式化处理，将输入赋值给finfo各分量
    finfo.trafficNum=metatext;
    finfo.seatNum=ui->seatNumEdit->text();
    finfo.date=metadate.toString("yyyy-MM-dd");
    finfo.departure=ui->departureEdit->text();
    finfo.destination=ui->destinationEdit->text();

    //处理交通工具类型，前两位是字母的是航班，A开头客车，B开头客船，其他开头为火车
    if(metatext[0].isLetter()&&metatext[1].isLetter()){
        finfo.type=FLIGHT;
        finfo.carriageNum='1';
    }
    else{
        QChar a=metatext[0];
        switch (a.unicode()-'A') {
        case 0://bus Axxxx
            finfo.type=BUS;
            finfo.carriageNum='1';
            break;

        case 1://ship Bxxxx
            finfo.type=SHIP;
            finfo.carriageNum='1';
            break;

        default://train
            finfo.type=TRAIN;
            finfo.carriageNum=ui->carriageNumEdit->text();
            break;
        }
    }

    //检查输入是否合理，对错误的输入显示错误信息，对正确的输入进行插入
    if(finfo.carriageNum.toInt()<=0||finfo.seatNum.toInt()<=0){//车厢号出错
        on_resetBtn_clicked();
        QMessageBox* box=new QMessageBox;
        box->setWindowTitle("输入错误");
        box->setText(SEATWRONG);
        box->exec();
    }
    else{
        flag=insertDB(finfo);
        QMessageBox* box=new QMessageBox;
        switch (flag) {
        case 0://无错误，不修改显示内容，直接进入下一步
            box->setWindowTitle("成功");
            box->setText("录入成功，请等待审核");
            break;
        case NOTRAFFIC:
            box->setWindowTitle(INPUTWRONG);
            box->setText(TRAFFICWRONG);
            break;
        case SEATERROR:
            box->setWindowTitle(INPUTWRONG);
            box->setText(SEATWRONG);
            break;
        case LOCATIONERROR:
            box->setWindowTitle(INPUTWRONG);
            box->setText(LOCATIONWRONG);
            break;
        }
        box->exec();
    }
}
