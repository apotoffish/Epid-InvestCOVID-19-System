#ifndef ADDTRAFFICDIALOG_H
#define ADDTRAFFICDIALOG_H

#include <QDialog>

namespace Ui {
class addTrafficDialog;
}

class addTrafficDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addTrafficDialog(QWidget *parent = nullptr);
    ~addTrafficDialog();

private slots:
    void on_cancelBtn_clicked();

    void on_addTrafficBtn_clicked();

private:
    Ui::addTrafficDialog *ui;
};

#endif // ADDTRAFFICDIALOG_H
