#include "bruteforce.h"
#include "ui_bruteforce.h"
#include<string>
#include<iostream>
#include"cmath"
//#include"malloc/malloc.h"
#include"qmessagebox.h"
#include"MD5.h"
#include"qdebug.h"
using namespace std;

void exhaust_plaintext(string options, unsigned opt_length, unsigned digits, char **plaintext)
{
    //调用深度
    static unsigned depth = 1;
    //计数,统计有效明文组合的总个数.
    static unsigned count = 0;

    for (int i = 1; i <= opt_length; i++) {
        //是否是明文的最后一位
        if (depth == digits) {
            //把明文组合复制存储到plaintext
            //仅最后一位不同,即最后一位需要单独设定
            for (int k=1; k < digits; k++) {
                plaintext[count][k-1] = plaintext[0][k-1];
            }
            plaintext[count][depth-1] = options[i-1];

            //plaintext存储的有效明文总个数加1.
            count++;

            continue;

        }else{
            //由于plaintext的第一个明文组合是既定的,故暂时使用plaintext[0]作为临时字符数组存储各个明文组合
            plaintext[0][depth-1] = options[i-1];
            //遍历深度自增1
            depth++;
            exhaust_plaintext(options, opt_length, digits, plaintext);
        }

    }
    //判断是否穷举所有有效组合.
    if (count == pow(opt_length, digits)) {
        //正确设定plaintext[0];
        for (int i = 1; i <= digits; i++) {
            plaintext[0][i-1] = options[0];
        }
        count=0;
    }else{
        // 未穷巨额所有有效明文组合,则返回上层,继续执行
        depth--;
    }
    return;
}

BruteForce::BruteForce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BruteForce)
{
    ui->setupUi(this);
    ui->textBrowser->setReadOnly(true);
    qDebug()<<QObject::connect(this,SIGNAL(updateText(QString)),this,SLOT(receiveText(QString)));
    ui->progressBar->setVisible(false);
}

BruteForce::~BruteForce()
{
    delete ui;
}

void BruteForce::on_buttonBox_accepted()
{
    this->close();
}

void BruteForce::on_spinBox_editingFinished()
{
    //ui->spinBox_2->setRange(ui->spinBox->value(),500);
}

void BruteForce::receiveText(QString msg)
{
    ui->textBrowser->append(msg);
}

void BruteForce::on_pushButton_clicked()
{
    string current=ui->lineEdit->text().toUpper().toStdString();
    bool flag=false;
    int i,j,k;
    ui->progressBar->setValue(0);
    //输入检查
    if (current.length()==16 || current.length()==32)
    {
        for(i=0;i<current.length();i++)
        {
            if((current[i]>='A' && current[i]<='Z') || (current[i]>='0' && current[i]<='9'));
            else break;
        }
        if (i==current.size())
            flag=true;
    }
    if (!flag){
        QMessageBox::warning(NULL,"Error","Input string should be 16 or 32 length and alphanumeric！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if (!ui->checkBox->isChecked() && !ui->checkBox_2->isChecked()
            && !ui->checkBox_3->isChecked() && !ui->checkBox_4->isChecked())
    {
        QMessageBox::warning(NULL,"Error","Select possible key space！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if (!ui->spinBox->value())
    {
        QMessageBox::warning(NULL,"Error","Input size can not be 0！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    //start
    string keyspace="";
    if (ui->checkBox->isChecked()) keyspace.append(lower);
    if (ui->checkBox_2->isChecked()) keyspace.append(upper);
    if (ui->checkBox_3->isChecked()) keyspace.append(number);
    if (ui->checkBox_4->isChecked()) keyspace.append(symbol);
    int opt_length = keyspace.length();//可选项数目
    int total_length = 0;//最多需要尝试的次数
    int cnt = 0;//统计已经尝试的次数
    for (i=ui->spinBox->value();i<=ui->spinBox_2->value();i++)
    {
        total_length += pow(opt_length,i);
    }
    ui->progressBar->setRange(1,total_length);
    ui->progressBar->setVisible(true);
    for (i=ui->spinBox->value();i<=ui->spinBox_2->value();i++)
    {
        int digits = i;//位数
        //动态内存分配:定义一个行列都是动态的二维数组,用于存储所有的密码组合
        char **plaintxt = (char**)malloc(sizeof(char*)*pow(opt_length, digits));
        for (j = 1; j <= pow(opt_length, digits); j++)
            plaintxt[j-1] = (char*)malloc(sizeof(char)*digits);

        //函数调用，获取全部明文
        exhaust_plaintext(keyspace, opt_length, digits, plaintxt);
        //匹配
        for (k = 1; k <= pow(opt_length, digits); k++){
            //提取一个明文
            string s=plaintxt[k-1];
            cnt++;
            ui->progressBar->setValue(cnt);
            MD5 temp(s);
            //cout<<s<<endl;
            if (current==temp.Hexcipher32()||
                    current==temp.Hexcipher16())
            {
                //找到匹配明文
                ui->progressBar->setValue(total_length);
                ui->textBrowser->append(QString("Trying:"+ QString::fromStdString(s) + ".................Successed！"));
                ui->textBrowser->append(QString("Cracking Successed！Key: ") + QString::fromStdString(s));
              return;
            }
            //emit updateText(QString("Trying:"+ QString::fromStdString(s) + ".................failed"));
            ui->textBrowser->append(QString("Trying:"+ QString::fromStdString(s) + ".................failed"));
            QApplication::processEvents();
            qDebug()<<QString::fromStdString(s);

        }
        for (k = 1; k <= pow(opt_length, digits); k++){
               free(plaintxt[k-1]);
        }
        free(plaintxt);
    }
    ui->textBrowser->append(QString("Cracking Failed！"));
}


void BruteForce::on_spinBox_valueChanged(int arg1)
{
    ui->spinBox_2->setRange(arg1,500);
}
