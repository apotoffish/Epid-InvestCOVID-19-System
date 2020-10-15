#ifndef DELTRAFFICDIALOG_H
#define DELTRAFFICDIALOG_H

#include <QDialog>

namespace Ui {
class delTrafficDialog;
}

class delTrafficDialog : public QDialog
{
    Q_OBJECT

public:
    explicit delTrafficDialog(QWidget *parent = nullptr);
    ~delTrafficDialog();

private slots:
    void on_cancelBtn_clicked();

    void on_addTrafficBtn_clicked();

private:
    Ui::delTrafficDialog *ui;
};

#endif // DELTRAFFICDIALOG_H
