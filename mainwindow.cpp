#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stringmd5.h"
#include"filemd5.h"
#include"bruteforce.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap title(":/title.png");
    title=title.scaled(521,191,Qt::KeepAspectRatio);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setPixmap(title);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    stringMD5 *dialog=new stringMD5(this);
    dialog->setWindowModality(Qt::ApplicationModal);
    dialog->exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    filemd5 *dialog=new filemd5(this);
    dialog->setWindowModality(Qt::ApplicationModal);
    dialog->exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    BruteForce *dialog=new BruteForce(this);
    dialog->setWindowModality(Qt::ApplicationModal);
    dialog->exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->close();
}
