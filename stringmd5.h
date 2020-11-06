#ifndef STRINGMD5_H
#define STRINGMD5_H

#include <QDialog>
#include<string>
using namespace std;

namespace Ui {
class stringMD5;
}

class stringMD5 : public QDialog
{
    Q_OBJECT

public:
    explicit stringMD5(QWidget *parent = 0);
    ~stringMD5();
    QString savefilepath;
    string plaintext;
private slots:

    void on_buttonBox_accepted();

    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();

private:
    Ui::stringMD5 *ui;
};

#endif // STRINGMD5_H
