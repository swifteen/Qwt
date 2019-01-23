#include <qlabel.h>
#include <qhbox.h>
#include <qstatusbar.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qspinbox.h>
#include <qwhatsthis.h>
#include <qpixmap.h>
#include "randomplot.h"
#include "mainwindow.h"
#include "start.xpm"
#include "clear.xpm"

class MyToolBar: public QToolBar
{
public:
    MyToolBar(MainWindow *);
    void addSpacing(int);
    void addStretch();
};

MyToolBar::MyToolBar(MainWindow *parent):
    QToolBar(parent)
{
}

void MyToolBar::addSpacing(int spacing)
{
    QLabel *label = new QLabel(this);
    label->setFixedWidth(spacing);
}

void MyToolBar::addStretch()
{
    QLabel *label = new QLabel(this);
    setStretchableWidget(label);
}

MainWindow::MainWindow()
{
    setDockEnabled(TornOff, TRUE);
    setRightJustification(TRUE);

    (void)toolBar();
    (void)statusBar();

    d_plot = new RandomPlot(this);
    d_plot->setMargin(4);

    setCentralWidget(d_plot);

    connect(d_startBtn, SIGNAL(toggled(bool)), this, SLOT(appendPoints(bool)));
    connect(d_clearBtn, SIGNAL(clicked()), d_plot, SLOT(clear()));
    connect(d_plot, SIGNAL(running(bool)), this, SLOT(showRunning(bool)));

    initWhatsThis();
}

QToolBar *MainWindow::toolBar()
{
    MyToolBar *toolBar = new MyToolBar(this);

    d_startBtn = new QToolButton(toolBar);
    d_startBtn->setUsesTextLabel(TRUE);
    d_startBtn->setPixmap(QPixmap(start_xpm));
    d_startBtn->setToggleButton(TRUE);

    d_clearBtn = new QToolButton(toolBar);
    d_clearBtn->setUsesTextLabel(TRUE);
    d_clearBtn->setPixmap(QPixmap(clear_xpm));
    d_clearBtn->setTextLabel("Clear", FALSE);


    QToolButton *helpBtn = QWhatsThis::whatsThisButton(toolBar);
    helpBtn->setUsesTextLabel(TRUE);
    helpBtn->setTextLabel("Help", FALSE);

    toolBar->addSpacing(20);
    toolBar->addStretch();

    QHBox *hBox = new QHBox(toolBar);

    QLabel *label = new QLabel("Points ", hBox);
    d_randomCount = new QSpinBox(1, 100000, 100, hBox);
    d_randomCount->setValue(1000);

    toolBar->addSpacing(20);

    hBox = new QHBox(toolBar);

    label = new QLabel("Delay ", hBox);
    d_timerCount = new QSpinBox(0, 100000, 100, hBox);
    d_timerCount->setValue(0);
    label = new QLabel(" ms", hBox);

    toolBar->addSpacing(10);

    showRunning(FALSE);

    d_startBtn->setMinimumWidth(helpBtn->sizeHint().width() + 20);
    d_clearBtn->setMinimumWidth(helpBtn->sizeHint().width() + 20);
    helpBtn->setMinimumWidth(helpBtn->sizeHint().width() + 20);

    return toolBar;
}

void MainWindow::appendPoints(bool on)
{
    if ( on )
        d_plot->append(d_timerCount->text().toInt(),
            d_randomCount->text().toInt());
    else
        d_plot->stop();
}

void MainWindow::showRunning(bool running)
{
    d_randomCount->setEnabled(!running);
    d_timerCount->setEnabled(!running);
    d_startBtn->setOn(running);
    d_startBtn->setTextLabel(running ? "Stop" : "Start", FALSE);
}

void MainWindow::initWhatsThis()
{
    QWhatsThis::add(d_plot,
        "Zooming is enabled until the selected area gets "
        "too small for the significance on the axes.\n\n"
        "You can zoom in using the left mouse button.\n"
        "The middle mouse button is used to go back to the "
        "previous zoomed area.\n"
        "The right mouse button is used to unzoom completely."
    );
    QWhatsThis::add(d_randomCount,
        "Number of random points that will be generated." 
    );
    QWhatsThis::add(d_timerCount,
        "Delay between the generation of two random points."
    );
    QWhatsThis::add(d_startBtn,
        "Start generation of random points.\n\n"
        "The intention of this example is to show how to implement "
        "growing curves. The points will be generated and displayed "
        "one after the other.\n"
        "To check the performance, a small delay and a large number "
        "of points are useful. To watch the curve growing, a delay "
        " > 300 ms and less points are better.\n"
        "To inspect the curve, stacked zooming is implemented using the "
        "mouse buttons on the plot."
    );
    QWhatsThis::add(d_clearBtn,
        "Remove all points."
    );
}

