#include "aracnewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    unsigned short port = argc > 1 ? (unsigned short) atoi(argv[argc - 1]) : 8228;
    QApplication a(argc, argv);
    AracneWindow w(port);
    w.show();

    return a.exec();
}
