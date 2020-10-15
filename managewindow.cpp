#include "managewindow.h"
#include "ui_managewindow.h"
#include "dbms.h"
#include "defs.h"
#include "enterdlg.h"
#include "addtrafficdialog.h"
#include "deltrafficdialog.h"
#include <QStandardItemModel>
#include <QMessageBox>

ManageWindow::ManageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("疫情交通防控综合管理系统");
    createActions();
}

ManageWindow::~ManageWindow()
{
    delete ui;
}

void ManageWindow::createActions(){
    connect(ui->shwAct,SIGNAL(triggered()),this,SLOT(onShowTraffic()));
    connect(ui->addAct,SIGNAL(triggered()),this,SLOT(onAddTraffic()));
    connect(ui->delAct,SIGNAL(triggered()),this,SLOT(onDelTraffic()));

    connect(ui->shwrskAct,SIGNAL(triggered()),this,SLOT(onShowRisk()));
    connect(ui->addrskAct,SIGNAL(triggered()),this,SLOT(onAddRisk()));
    connect(ui->delrskAct,SIGNAL(triggered()),this,SLOT(onDelRisk()));

    connect(ui->retAct_2,SIGNAL(triggered()),this,SLOT(onReturn()));
    connect(ui->exitAct_2,SIGNAL(triggered()),this,SLOT(onExit()));
    ui->delrskAct->setEnabled(false);
}

void ManageWindow::onExit(){
    exit(0);
}

void ManageWindow::onReturn(){
    EnterDlg *dlg=new EnterDlg;
    dlg->show();
    this->close();
}

void ManageWindow::onShowTraffic(){
    QSqlTableModel* model = showDB("traffic");

    model->setHeaderData(0,Qt::Horizontal,QStringLiteral("班次"));
    model->setHeaderData(1,Qt::Horizontal,QStringLiteral("类型"));
    model->setHeaderData(2,Qt::Horizontal,QStringLiteral("出发日期"));
    model->setHeaderData(3,Qt::Horizontal,QStringLiteral("终到日期"));
    model->setHeaderData(4,Qt::Horizontal,QStringLiteral("途径站点"));

    ui->tableView->setModel(model);
    ui->delrskAct->setEnabled(false);
}

void ManageWindow::onAddTraffic(){
    addTrafficDialog* dlg=new addTrafficDialog;
    dlg->show();
    onShowTraffic();
}

void ManageWindow::onDelTraffic(){
    delTrafficDialog* dlg=new delTrafficDialog;
    dlg->show();
    onShowTraffic();
}

void ManageWindow::onShowRisk(){
    QSqlTableModel* model = showDB("riskroute");

    model->setHeaderData(0,Qt::Horizontal,QStringLiteral("患者识别号"));
    model->setHeaderData(1,Qt::Horizontal,QStringLiteral("班次"));
    model->setHeaderData(2,Qt::Horizontal,QStringLiteral("类型"));
    model->setHeaderData(3,Qt::Horizontal,QStringLiteral("出发日期"));
    model->setHeaderData(4,Qt::Horizontal,QStringLiteral("车厢号"));
    model->setHeaderData(5,Qt::Horizontal,QStringLiteral("座位号"));
    model->setHeaderData(6,Qt::Horizontal,QStringLiteral("途径路段"));

    ui->tableView->setModel(model);
    ui->delrskAct->setEnabled(true);
    ui->ingnoreBtn->setEnabled(false);
}

void ManageWindow::onAddRisk(){
    QSqlTableModel* model = showDB("newrisk");
    model->setHeaderData(0,Qt::Horizontal,"车次日期");
    model->setHeaderData(1,Qt::Horizontal,"车厢号");
    model->setHeaderData(2,Qt::Horizontal,"座位号");
    model->setHeaderData(3,Qt::Horizontal,"出发地");
    model->setHeaderData(4,Qt::Horizontal,"目的地");
    ui->tableView->setModel(model);
    ui->ingnoreBtn->setEnabled(true);
}

void ManageWindow::onDelRisk(){
    int row=ui->tableView->currentIndex().row();
    QModelIndex index=ui->tableView->model()->index(row,0);
    QString id=ui->tableView->model()->data(index).toString();
    bool flag=delRiskDB(id);
    QMessageBox *box=new QMessageBox;
    box->setWindowTitle("操作信息");
    if(flag){
        box->setText("删除成功");
    }
    else{
        box->setText("删除失败，请重试");
    }
    box->exec();
    onShowRisk();
}

void ManageWindow::on_addBtn_clicked()
{
    int row=ui->tableView->currentIndex().row();
    QModelIndex a=ui->tableView->model()->index(row,0);
    QString s=ui->tableView->model()->data(a).toString();

    bool flag=addtoRiskDB(s);
    QMessageBox* box=new QMessageBox;
    box->setWindowTitle("操作结果");
    if(flag){
        box->setText("添加成功");
    }
    else{
        box->setText("添加失败");
    }
    box->exec();
    onShowRisk();
}

void ManageWindow::on_ingnoreBtn_clicked()
{
    QModelIndex s;
    int row=ui->tableView->currentIndex().row();
    s=ui->tableView->model()->index(row,0);
    QString trafficDate=ui->tableView->model()->data(s).toString();

    bool flag=delNewRiskDB(trafficDate);
    QMessageBox *box=new QMessageBox;
    box->setWindowTitle("操作信息");
    if(flag){
        box->setText("删除成功");
    }
    else{
        box->setText("删除失败，请重试");
    }
    box->exec();
    onAddRisk();
}
