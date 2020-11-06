#include "filemd5.h"
#include "ui_filemd5.h"
#include"qfiledialog.h"
#include"qtextstream.h"
#include"MD5.h"
#include <qmessagebox.h>
#include"iostream"
using namespace std;

filemd5::filemd5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filemd5)
{
    ui->setupUi(this);
    ui->lineEdit_2->setReadOnly(1);
    ui->lineEdit_3->setReadOnly(1);
    ui->lineEdit_4->setReadOnly(1);
    ui->lineEdit_5->setReadOnly(1);
    ui->pushButton_2->setEnabled(false);
}

filemd5::~filemd5()
{
    delete ui;
}

void filemd5::on_buttonBox_accepted()
{
    this->close();
}

void filemd5::on_toolButton_clicked()
{
    openfilepath = QFileDialog::getOpenFileName(this,tr("Open file"),"~",tr("All file (*.*)"));
    ui->textEdit->setText(openfilepath);
}

void filemd5::on_pushButton_clicked()
{
    QFile file(openfilepath);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray fileData = file.readAll();
        MD5 temp(fileData.toStdString());
        ui->lineEdit_2->setText(QString::fromStdString(temp.hexcipher16()));
        ui->lineEdit_3->setText(QString::fromStdString(temp.Hexcipher16()));
        ui->lineEdit_4->setText(QString::fromStdString(temp.hexcipher32()));
        ui->lineEdit_5->setText(QString::fromStdString(temp.Hexcipher32()));
        ui->pushButton_2->setEnabled(true);
    }
    else
    {
        QMessageBox::warning(NULL,"Error","File does not exist",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        ui->textEdit->clear();
    }
}

void filemd5::on_pushButton_2_clicked()
{
    savefilepath = QFileDialog::getSaveFileName(this,tr("Save file"),"~",tr("Text File (*.txt)"));
    QFile file(savefilepath);
    file.open( QIODevice::ReadWrite| QIODevice::Append);
    QTextStream out(&file);
    if(!ui->lineEdit_2->text().isEmpty()){
        out << "File Directory: "<<openfilepath <<"\n";
        out << "16-MD5(lowercase): "<<ui->lineEdit_2->text()<<"\n";
        out << "16-MD5(uppercase): "<<ui->lineEdit_3->text()<<"\n";
        out << "32-MD5(lowercase): "<<ui->lineEdit_4->text()<<"\n";
        out << "32-MD5(uppercase): "<<ui->lineEdit_5->text()<<"\n";
        out << "\n";
     }
    else
    {
        QMessageBox::warning(NULL,"Error","Failed saving text!",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    file.close();
}
