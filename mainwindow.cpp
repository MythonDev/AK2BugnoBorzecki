#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    QString sign1;
    QString sign2;
    QString signRes;

    QString exp1;
    QString exp2;
    QString expRes;

    QString fra1;
    QString fra2;
    QString fraRes;

    sign1 = ui->sign1Edit->toPlainText();
    sign2 = ui->sign2Edit->toPlainText();
    exp1 = ui->exp1Edit->toPlainText();
    exp2 = ui->exp2Edit->toPlainText();
    fra1 = ui->fra1Edit->toPlainText();
    fra2 = ui->fra2Edit->toPlainText();
    if(sign1.toInt() == sign2.toInt())
    asmObj.addASM(sign1, exp1, fra1,
                  sign2, exp2, fra2,
                  signRes, expRes, fraRes);
    else {
        asmObj.subASM(sign1, exp1, fra1,
                      sign2, exp2, fra2,
                      signRes, expRes, fraRes);
    }

    ui->signResLabel->setText(signRes);
    ui->expResLabel->setText(expRes);
    ui->fraResLabel->setText(fraRes);

    /*Nie jestem pewny czy funkcje asmoperations
            maja zasieg (prawa dostepu) do dzialania
            i zmiany atrybutow klasy mainwindow*/
    /*Update
     * Obecnie AsmOperations dziala na oryginalach*/
}

void MainWindow::on_subButton_clicked()
{
    sign1 = ui->sign1Edit->toPlainText();
    sign2 = ui->sign2Edit->toPlainText();
    exp1 = ui->exp1Edit->toPlainText();
    exp2 = ui->exp2Edit->toPlainText();
    fra1 = ui->fra1Edit->toPlainText();
    fra2 = ui->fra2Edit->toPlainText();

    if(sign1.toInt() == sign2.toInt())
    asmObj.subASM(sign1, exp1, fra1,
                  sign2, exp2, fra2,
                  signRes, expRes, fraRes);
    else
        asmObj.subASM(sign1, exp1, fra1,
                      sign2, exp2, fra2,
                      signRes, expRes, fraRes);

    ui->signResLabel->setText(signRes);
    ui->expResLabel->setText(expRes);
    ui->fraResLabel->setText(fraRes);
}

void MainWindow::on_mulButton_clicked()
{
    sign1 = ui->sign1Edit->toPlainText();
    sign2 = ui->sign2Edit->toPlainText();
    exp1 = ui->exp1Edit->toPlainText();
    exp2 = ui->exp2Edit->toPlainText();
    fra1 = ui->fra1Edit->toPlainText();
    fra2 = ui->fra2Edit->toPlainText();

    asmObj.mulASM(sign1, exp1, fra1,
                  sign2, exp2, fra2,
                  signRes, expRes, fraRes);

    ui->signResLabel->setText(signRes);
    ui->expResLabel->setText(expRes);
    ui->fraResLabel->setText(fraRes);
}

void MainWindow::on_divButton_clicked()
{
    sign1 = ui->sign1Edit->toPlainText();
    sign2 = ui->sign2Edit->toPlainText();
    exp1 = ui->exp1Edit->toPlainText();
    exp2 = ui->exp2Edit->toPlainText();
    fra1 = ui->fra1Edit->toPlainText();
    fra2 = ui->fra2Edit->toPlainText();

    asmObj.divASM(sign1, exp1, fra1,
                  sign2, exp2, fra2,
                  signRes, expRes, fraRes);

    ui->signResLabel->setText(signRes);
    ui->expResLabel->setText(expRes);
    ui->fraResLabel->setText(fraRes);
}

void MainWindow::on_sqrtButton_clicked()
{
    sign1 = ui->sign1Edit->toPlainText();
    sign2 = ui->sign2Edit->toPlainText();
    exp1 = ui->exp1Edit->toPlainText();
    exp2 = ui->exp2Edit->toPlainText();
    fra1 = ui->fra1Edit->toPlainText();
    fra2 = ui->fra2Edit->toPlainText();

    asmObj.sqrtASM(sign1, exp1, fra1,
                   sign2, exp2, fra2,
                   signRes, expRes, fraRes);

    ui->signResLabel->setText(signRes);
    ui->expResLabel->setText(expRes);
    ui->fraResLabel->setText(fraRes);
}

QString MainWindow::getFraRes() const
{
    return fraRes;
}

void MainWindow::setFraRes(const QString &value)
{
    fraRes = value;
}

QString MainWindow::getFra2() const
{
    return fra2;
}

void MainWindow::setFra2(const QString &value)
{
    fra2 = value;
}

QString MainWindow::getFra1() const
{
    return fra1;
}

void MainWindow::setFra1(const QString &value)
{
    fra1 = value;
}

QString MainWindow::getExpRes() const
{
    return expRes;
}

void MainWindow::setExpRes(const QString &value)
{
    expRes = value;
}

QString MainWindow::getExp2() const
{
    return exp2;
}

void MainWindow::setExp2(const QString &value)
{
    exp2 = value;
}

QString MainWindow::getExp1() const
{
    return exp1;
}

void MainWindow::setExp1(const QString &value)
{
    exp1 = value;
}

QString MainWindow::getSignRes() const
{
    return signRes;
}

void MainWindow::setSignRes(const QString &value)
{
    signRes = value;
}

QString MainWindow::getSign2() const
{
    return sign2;
}

void MainWindow::setSign2(const QString &value)
{
    sign2 = value;
}

QString MainWindow::getSign1() const
{
    return sign1;
}

void MainWindow::setSign1(const QString &value)
{
    sign1 = value;
}
