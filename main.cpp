//#include "mainwindow.h"
#include "enterdlg.h"
#include <QApplication>
#include "dbms.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EnterDlg w;
    if(!initdb())
        QMessageBox::critical(nullptr,"数据库错误","数据库连接失败，请重试",QMessageBox::Yes);

    w.show();

    return a.exec();
}
