#ifdef QWT_QTOPIA
#include <qpe/qpeapplication.h>
#endif
#include <qapplication.h>
#include "mainwindow.h"

int main(int argc, char **argv)
{
#ifdef QWT_QTOPIA
    QPEApplication a(argc, argv);
#else
    QApplication a(argc, argv);
#endif

    MainWindow w;
    w.show();
    a.setMainWidget(&w);

    return a.exec();
}
