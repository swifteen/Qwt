//-----------------------------------------------------------------
//      A demo program showing how to use event filtering
//-----------------------------------------------------------------

#ifdef QWT_QTOPIA
#include <qpe/qpeapplication.h>
#endif
#include <qapplication.h>
#include <qmainwindow.h>
#include <qwhatsthis.h>
#include <qtoolbar.h>
#include "plot.h"
#include "canvaspicker.h"
#include "scalepicker.h"

int main (int argc, char **argv)
{
#ifdef QWT_QTOPIA
    QPEApplication a(argc, argv);
#else
    QApplication a(argc, argv);
#endif

    QMainWindow mainWindow;
    QToolBar *toolBar = new QToolBar(&mainWindow);
    (void)QWhatsThis::whatsThisButton(toolBar);
    
    Plot *plot = new Plot(&mainWindow);

    // The canvas picker handles all mouse and key
    // events on the plot canvas

    (void) new CanvasPicker(plot);

    // The scale picker translates mouse clicks
    // int o clicked() signals

    ScalePicker *scalePicker = new ScalePicker(plot);
    a.connect(scalePicker, SIGNAL(clicked(int, double)),
        plot, SLOT(insertCurve(int, double)));

    mainWindow.setCentralWidget(plot);
    a.setMainWidget(&mainWindow);

    mainWindow.resize(540, 400);
    mainWindow.show();

    QWhatsThis::add(plot,
        "An useless plot to demonstrate how to use event filtering.\n\n"
        "You can click on the color bar, the scales or move the slider.\n"
        "All points can be moved using the mouse or the keyboard.");

    int rv = a.exec();
    return rv;
}
