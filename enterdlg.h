#ifndef ENTERDLG_H
#define ENTERDLG_H

#include <QDialog>

namespace Ui {
class EnterDlg;
}

class EnterDlg : public QDialog
{
    Q_OBJECT

public:
    explicit EnterDlg(QWidget *parent = nullptr);
    ~EnterDlg();

private slots:
    void on_extBtn_clicked();

    void on_srchBtn_clicked();

    void on_repoBtn_clicked();

    void on_adminBtn_clicked();

private:
    Ui::EnterDlg *ui;
};

#endif // ENTERDLG_H
