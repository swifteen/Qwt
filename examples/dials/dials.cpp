#ifdef QWT_QTOPIA
#include <qpe/qpeapplication.h>
#endif
#include <qapplication.h>
#include <qtabwidget.h>
#include "compass_grid.h"
#include "cockpit_grid.h"

//-----------------------------------------------------------------
//
//      dials.cpp -- A demo program featuring QwtDial and friends
//
//-----------------------------------------------------------------

int main (int argc, char **argv)
{
#ifdef QWT_QTOPIA
    QPEApplication a(argc, argv);
#else
    QApplication a(argc, argv);
#endif

    QTabWidget tabWidget;
    tabWidget.addTab(new CompassGrid(&tabWidget), "Compass");
    tabWidget.addTab(new CockpitGrid(&tabWidget), "Cockpit");

    a.setMainWidget(&tabWidget);

    tabWidget.show();

    return a.exec();
}

