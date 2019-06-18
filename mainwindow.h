#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "asmoperations.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString getSign1() const;
    void setSign1(const QString &value);

    QString getSign2() const;
    void setSign2(const QString &value);

    QString getSignRes() const;
    void setSignRes(const QString &value);

    QString getExp1() const;
    void setExp1(const QString &value);

    QString getExp2() const;
    void setExp2(const QString &value);

    QString getExpRes() const;
    void setExpRes(const QString &value);

    QString getFra1() const;
    void setFra1(const QString &value);

    QString getFra2() const;
    void setFra2(const QString &value);

    QString getFraRes() const;
    void setFraRes(const QString &value);

private slots:
    void on_addButton_clicked();

    void on_subButton_clicked();

    void on_mulButton_clicked();

    void on_divButton_clicked();

    void on_sqrtButton_clicked();

private:
    Ui::MainWindow *ui;

    AsmOperations asmObj;

    QString sign1;
    QString sign2;
    QString signRes;

    QString exp1;
    QString exp2;
    QString expRes;

    QString fra1;
    QString fra2;
    QString fraRes;
};

#endif // MAINWINDOW_H
