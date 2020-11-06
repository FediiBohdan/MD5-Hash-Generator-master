#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QDebug>
#include <QElapsedTimer>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/welcome.png");
    QSplashScreen screen(pixmap);
    screen.show();
    int delayTime = 2;
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < (delayTime * 1000))
    {
         a.processEvents();
    }
    MainWindow w;
    w.setFixedSize(600,400);
    w.setWindowFlags(Qt::WindowCloseButtonHint);
    w.show();
    return a.exec();
}
