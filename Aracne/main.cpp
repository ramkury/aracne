#include "aracnewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AracneWindow w(8228);
    w.show();
    w.StartProxy();

    return a.exec();
}
