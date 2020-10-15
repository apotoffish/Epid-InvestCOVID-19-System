#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defs.h"
#include "dbms.h"
#include "kernel.h"
#include "enterdlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setText(TIPS);
    this->setWindowTitle("疫情交通防控综合管理系统");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//退出响应
void MainWindow::on_exitBtn_clicked()
{
    exit(0);
}

//重置响应，将输入清空
void MainWindow::on_resetBtn_clicked()
{
    ui->trafficNumEdit->clear();
    ui->seatNumEdit->clear();
    ui->departureEdit->clear();
    ui->destinationEdit->clear();
    ui->riskLevelEdit->clear();
    ui->carriageNumEdit->clear();
    ui->calendarWidget->showToday();
    ui->textEdit->setText(TIPS);
}

//搜索响应，输入信息格式化处理，调用搜索和计算功能
void MainWindow::on_searchBtn_clicked()
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

    //检查输入是否合理，对错误的输入显示错误信息，对正确的输入进行查找
    if(finfo.carriageNum.toInt()<=0||finfo.seatNum.toInt()<=0){//车厢号出错
        on_resetBtn_clicked();
        ui->textEdit->setText(SEATWRONG);
    }
    else{
        struct finfo rfinfo=searchDB(finfo,flag);
        int risk=riskCompute(rfinfo,finfo);
        ui->riskLevelEdit->setText(QString::number(risk));

        switch (risk) {//风险等级
        case 0:
            ui->riskLevelEdit->setText("0");
            ui->textEdit->setText(NORISK);
            break;
        case 1:
            ui->riskLevelEdit->setText("1");
            ui->textEdit->setText(LOWRISK);
            break;
        case 2:
            ui->riskLevelEdit->setText("2");
            ui->textEdit->setText(MEDIUMRISK);
            break;
        default:
            ui->riskLevelEdit->setText("3");
            ui->textEdit->setText(HIGHRISK);
            break;
        }

        switch (flag) {//错误码
        case 0://无错误，不修改显示内容，直接进入下一步
            break;
        case NOTRAFFIC:
            on_resetBtn_clicked();
            ui->textEdit->setText(TRAFFICWRONG);
            break;
        case SEATERROR:
            on_resetBtn_clicked();
            ui->textEdit->setText(SEATWRONG);
            break;
        case LOCATIONERROR:
            on_resetBtn_clicked();
            ui->textEdit->setText(LOCATIONWRONG);
            break;
        }
    }
}

void MainWindow::on_returnBtn_clicked()
{
    EnterDlg *w=new EnterDlg;
    w->show();
    this->close();
}
