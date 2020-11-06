#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <QDialog>
#include<string>
using namespace std;

namespace Ui {
class BruteForce;
}

class BruteForce : public QDialog
{
    Q_OBJECT

public:
    explicit BruteForce(QWidget *parent = 0);
    ~BruteForce();
    QString ciphertext;
    string lower="abcdefghijklmnopqrstuvwxyz";
    string upper="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string number="1234567890";
    string symbol="!@#$%^&*";
signals:
    void updateText(QString msg);

private slots:
    void on_buttonBox_accepted();

    void on_spinBox_editingFinished();

    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void receiveText(QString msg);

private:
    Ui::BruteForce *ui;
};

#endif // BRUTEFORCE_H
