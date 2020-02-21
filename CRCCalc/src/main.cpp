#include "crccalc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CrcCalc w;
    w.show();

    return a.exec();
}
