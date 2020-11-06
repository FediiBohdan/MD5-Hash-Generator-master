#include "stringmd5.h"
#include "ui_stringmd5.h"
#include"qmessagebox.h"
#include"qtextstream.h"
#include <string>
#include <QFile>
#include"qfiledialog.h"
#include"MD5.h"
#include"iostream"
using namespace std;

stringMD5::stringMD5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stringMD5)
{
    ui->setupUi(this);
    ui->lineEdit_2->setReadOnly(1);
    ui->lineEdit_3->setReadOnly(1);
    ui->lineEdit_4->setReadOnly(1);
    ui->lineEdit_5->setReadOnly(1);
    ui->pushButton_2->setEnabled(false);
}

stringMD5::~stringMD5()
{
    delete ui;
}


void stringMD5::on_buttonBox_accepted()
{
    this->close();
}

void stringMD5::on_pushButton_clicked()
{
    plaintext=ui->lineEdit->text().toStdString();
    //cout<<plaintext;
    MD5 temp(plaintext);
    ui->lineEdit_2->setText(QString::fromStdString(temp.hexcipher16()));
    ui->lineEdit_3->setText(QString::fromStdString(temp.Hexcipher16()));
    ui->lineEdit_4->setText(QString::fromStdString(temp.hexcipher32()));
    ui->lineEdit_5->setText(QString::fromStdString(temp.Hexcipher32()));
    ui->pushButton_2->setEnabled(true);
}

void stringMD5::on_pushButton_2_clicked()
{
    savefilepath = QFileDialog::getSaveFileName(this,tr("Save file"),"~",tr("Text File (*.txt)"));
    QFile file(savefilepath);
    file.open( QIODevice::ReadWrite|QIODevice::Append);
    QTextStream out(&file);
    if(!ui->lineEdit_2->text().isEmpty()){
        out << "String Encrypted: "<<QString::fromStdString(plaintext) <<"\n";
        out << "16-MD5(lowercase): "<<ui->lineEdit_2->text()<<"\n";
        out << "16-MD5(uppercase): "<<ui->lineEdit_3->text()<<"\n";
        out << "32-MD5(lowercase): "<<ui->lineEdit_4->text()<<"\n";
        out << "32-MD5(uppercase): "<<ui->lineEdit_5->text()<<"\n";
        out << "\n";
     }
    else
    {
        QMessageBox::warning(NULL,"Error","文件保存失败！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    file.close();
}
