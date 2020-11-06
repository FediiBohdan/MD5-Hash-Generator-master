#ifndef FILEMD5_H
#define FILEMD5_H

#include <QDialog>

namespace Ui {
class filemd5;
}

class filemd5 : public QDialog
{
    Q_OBJECT

public:
    explicit filemd5(QWidget *parent = 0);
    ~filemd5();
    QString openfilepath;
    QString savefilepath;

private slots:
    void on_buttonBox_accepted();

    void on_toolButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::filemd5 *ui;
};

#endif // FILEMD5_H
