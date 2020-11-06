#include "bruteforce.h"
#include "ui_bruteforce.h"

#include "cmath"
#include "qmessagebox.h"
#include "MD5.h"
#include "qdebug.h"

#include<string>
#include<iostream>

using namespace std;

void exhaust_plaintext(string options, unsigned opt_length, unsigned digits, char **plaintext)
{
    // the traversal depth
    static unsigned depth = 1;
    // count the total number of valid plaintext combinations.
    static unsigned count = 0;

    for (int i = 1; i <= opt_length; i++) {
        // is it the last digit of the plaintext
        if (depth == digits) {
            // copy and store the plaintext combination to plaintext
            // only the last digit is different, that is, the last digit needs to be set separately
            for (int k=1; k < digits; k++) {
                plaintext[count][k-1] = plaintext[0][k-1];
            }
            plaintext[count][depth-1] = options[i-1];

            // the total number of valid plaintext stored in plaintext plus 1.
            count++;

            continue;

        }else{
            // since the first plaintext combination of plaintext is established, plaintext[0] is temporarily used as a temporary character array to store each plaintext combination
            plaintext[0][depth-1] = options[i-1];
            // the traversal depth increases by 1
            depth++;
            exhaust_plaintext(options, opt_length, digits, plaintext);
        }

    }
    // determine whether to exhaust all valid combinations.
    if (count == pow(opt_length, digits)) {
        // set plaintext[0] correctly;
        for (int i = 1; i <= digits; i++) {
            plaintext[0][i-1] = options[0];
        }
        count=0;
    }else{
        // if there is huge amount of all valid plaintext combinations, return to the upper level and continue execution
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
    qDebug()<<QObject::connect(this, SIGNAL(updateText(QString)), this, SLOT(receiveText(QString)));
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
    string current = ui->lineEdit->text().toUpper().toStdString();
    bool flag = false;
    int i, j, k;
    ui->progressBar->setValue(0);
    // input check
    if (current.length() == 16 || current.length() == 32)
    {
        for (i = 0; i<current.length(); i++)
        {
            if ((current[i]> = 'A' && current[i] <= 'Z') || (current[i] >= '0' && current[i] <= '9'));
            else break;
        }
        if (i == current.size())
            flag = true;
    }
    if (!flag){
        QMessageBox::warning(NULL, "Error","Input string should be 16 or 32 length and alphanumeric！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if (!ui->checkBox->isChecked() && !ui->checkBox_2->isChecked()
            && !ui->checkBox_3->isChecked() && !ui->checkBox_4->isChecked())
    {
        QMessageBox::warning(NULL, "Error","Select possible key space！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if (!ui->spinBox->value())
    {
        QMessageBox::warning(NULL,"Error","Input size can not be 0！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    // start
    string keyspace="";
    if (ui->checkBox->isChecked()) keyspace.append(lower);
    if (ui->checkBox_2->isChecked()) keyspace.append(upper);
    if (ui->checkBox_3->isChecked()) keyspace.append(number);
    if (ui->checkBox_4->isChecked()) keyspace.append(symbol);
    int opt_length = keyspace.length();// number of options
    int total_length = 0;// maximum number of attempts
    int cnt = 0;// count the number of attempts
    for (i=ui->spinBox->value(); i<=ui->spinBox_2->value(); i++)
    {
        total_length += pow(opt_length, i);
    }
    ui->progressBar->setRange(1, total_length);
    ui->progressBar->setVisible(true);
    for (i=ui->spinBox->value(); i<=ui->spinBox_2->value(); i++)
    {
        int digits = i;//Digits
        // dynamic memory allocation: define a dynamic two-dimensional array of rows and columns to store all password combinations
        char **plaintxt = (char**)malloc(sizeof(char*)*pow(opt_length, digits));
        for (j = 1; j <= pow(opt_length, digits); j++)
            plaintxt[j-1] = (char*)malloc(sizeof(char)*digits);

        // function call, get all plaintext
        exhaust_plaintext(keyspace, opt_length, digits, plaintxt);
        //匹配
        for (k = 1; k <= pow(opt_length, digits); k++){
            // extract a plaintext
            string s = plaintxt[k-1];
            cnt++;
            ui->progressBar->setValue(cnt);
            MD5 temp(s);
            //cout<<s<<endl;
            if (current == temp.Hexcipher32()||
                    current == temp.Hexcipher16())
            {
                // find matching plaintext
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
    ui->spinBox_2->setRange(arg1, 500);
}
