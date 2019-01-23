// Qwt offers several options to work around a bug of Qt on the X Windows
// System with XFT (X FreeType) enabled.  The bug affects the drawing of the
// cursor label of QwtPicker and classes derived from QwtPicker.
//
// If the command
// ldd bode | grep libXft
// returns something like
//      libXft.so.2 => /usr/X11R6/lib/libXft.so.2 (0x40be2000)
// the bugs affects you and you might want to play with those options.
//
// See the documentation for QwtPainter::setTextXorRopMode().
//
// You can play with those options by uncommenting the following line:
//#define XORROP

#ifdef QWT_QTOPIA
#include <qpe/qpeapplication.h>
#endif
#include <qregexp.h>
#include <qapplication.h>
#include <qhbox.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qlabel.h>
#include <qstatusbar.h>
#include <qprinter.h>
#include <qwt_counter.h>
#include <qwt_plot_zoomer.h>
#include <qwt_math.h>
#include "pixmaps.h"
#include "bode_plot.h"
#include "bode.h"

#ifdef XORROP
#include <qcombobox.h>
#include <qwt_painter.h>
#endif

#ifndef QT_NO_PRINTER
class PrintFilter: public QwtPlotPrintFilter
{
public:
    PrintFilter() {};

    virtual QColor color(const QColor &c, Item item, int) const
    {
        if ( !(options() & PrintCanvasBackground))
        {
            switch(item)
            {
            case MajorGrid:
                return Qt::darkGray;
            case MinorGrid:
                return Qt::gray;
            default:
                ;
            }
        }
        switch(item)
        {
        case Title:
            return Qt::red;
        case AxisScale:
            return Qt::green;
        case AxisTitle:
            return Qt::blue;
        default:
            ;
        }
        return c;
    }

    virtual QFont font(const QFont &f, Item, int) const
    {
        QFont f2 = f;
        f2.setPointSize(int(f.pointSize() * 1.25));
        return f2;
    }
};
#endif

//-----------------------------------------------------------------
//
//      bode.cpp -- A demo program featuring QwtPlot and QwtCounter
//
//      This example demonstrates the mapping of different curves
//      to different axes in a QwtPlot widget. It also shows how to
//      display the cursor position and how to implement zooming.
//
//-----------------------------------------------------------------

MainWin::MainWin(QWidget *p , const char *name): 
    QMainWindow(p, name)
{
    d_plot = new BodePlot(this);
    d_plot->setMargin(5);

    d_zoomer[0] = new QwtPlotZoomer(QwtPlot::xBottom, QwtPlot::yLeft,
        QwtPicker::DragSelection, QwtPicker::AlwaysOff, d_plot->canvas());
    d_zoomer[0]->setRubberBandPen(Qt::green);

    d_zoomer[1] = new QwtPlotZoomer(QwtPlot::xTop, QwtPlot::yRight,
        QwtPicker::DragSelection, QwtPicker::AlwaysOff, d_plot->canvas());
    d_zoomer[1]->setRubberBand(QwtPicker::NoRubberBand);
    
    d_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
        QwtPicker::PointSelection | QwtPicker::DragSelection, 
        QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn, 
        d_plot->canvas());
    d_picker->setRubberBandPen(Qt::green);
    d_picker->setCursorLabelPen(Qt::cyan);

    setCentralWidget(d_plot);

    QToolBar *toolBar = new QToolBar(this);

    QToolButton *btnZoom = new QToolButton(toolBar);
    btnZoom->setTextLabel("Zoom");
    btnZoom->setPixmap(zoom_xpm);
    btnZoom->setToggleButton(TRUE);
    btnZoom->setUsesTextLabel(TRUE);

#ifndef QT_NO_PRINTER
    QToolButton *btnPrint = new QToolButton(toolBar);
    btnPrint->setTextLabel("Print");
    btnPrint->setPixmap(print_xpm);
    btnPrint->setUsesTextLabel(TRUE);
#endif

#ifdef XORROP
    QComboBox *comboXorROP = new QComboBox(FALSE, toolBar);
    int mode = QwtPainter::textXorRopMode();
    comboXorROP->insertItem("XorRopTextNormal");
    if (QwtPainter::XorRopTextKeepFont == 
        QwtPainter::setTextXorRopMode(QwtPainter::XorRopTextKeepFont))
    {
        comboXorROP->insertItem("XorRopTextKeepFont");
        if (QwtPainter::XorRopTextKeepColor ==
            QwtPainter::setTextXorRopMode(QwtPainter::XorRopTextKeepColor))
            comboXorROP->insertItem("XorRopTextKeepColor");
    }
    QwtPainter::setTextXorRopMode(QwtPainter::TextXorRopMode(mode));
    comboXorROP->setCurrentItem(QwtPainter::textXorRopMode());
#endif

    toolBar->setStretchableWidget(new QWidget(toolBar));

    QHBox *dampBox = new QHBox(toolBar);
    dampBox->setSpacing(10);
    (void)new QLabel("Damping Factor", dampBox);
    QwtCounter *cntDamp = new QwtCounter(dampBox);
    cntDamp->setRange(0.0, 5.0, 0.01);
    cntDamp->setValue(0.0);
    
    addToolBar(toolBar);
    (void)statusBar();

    zoom(FALSE);
    showInfo();

    connect(cntDamp, SIGNAL(valueChanged(double)), 
        d_plot, SLOT(setDamp(double))); 

#ifndef QT_NO_PRINTER
    connect(btnPrint, SIGNAL(clicked()), SLOT(print()));
#endif
    connect(btnZoom, SIGNAL(toggled(bool)), SLOT(zoom(bool)));

#ifdef XORROP
    connect(comboXorROP, SIGNAL(activated(int)), SLOT(setXorRop(int)));
#endif

    connect(d_picker, SIGNAL(moved(const QPoint &)),
            SLOT(moved(const QPoint &)));
    connect(d_picker, SIGNAL(selected(const QPointArray &)),
            SLOT(selected(const QPointArray &)));
}

#ifdef XORROP
void MainWin::setXorRop(int mode)
{
    QwtPainter::setTextXorRopMode(QwtPainter::TextXorRopMode(mode));
}
#else
void MainWin::setXorRop(int)
{
}
#endif

void MainWin::print()
{
#ifndef QT_NO_PRINTER
#if 1
    QPrinter printer;
#else
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputToFile(TRUE);
    printer.setOutputFileName("/tmp/bode.ps");
#endif

    QString docName = d_plot->title();
    if ( docName.isEmpty() )
    {
        docName.replace (QRegExp (QString::fromLatin1 ("\n")), tr (" -- "));
        printer.setDocName (docName);
    }

    printer.setCreator("Bode example");
    printer.setOrientation(QPrinter::Landscape);

    if (printer.setup())
    {
#if 0
        PrintFilter filter;
#else
		QwtPlotPrintFilter filter;
#endif
        if ( printer.colorMode() == QPrinter::GrayScale )
        {
            filter.setOptions(QwtPlotPrintFilter::PrintAll 
                & ~QwtPlotPrintFilter::PrintCanvasBackground);
        }
        d_plot->print(printer, filter);
    }
#endif
}

void MainWin::zoom(bool on)
{
    d_zoomer[0]->setEnabled(on);
    d_zoomer[0]->zoom(0);

    d_zoomer[1]->setEnabled(on);
    d_zoomer[1]->zoom(0);

    d_picker->setRubberBand(
        on ? QwtPicker::NoRubberBand: QwtPicker::CrossRubberBand);

    showInfo();
}

void MainWin::showInfo(QString text)
{
    if ( text == QString::null )
    {
        if ( d_picker->rubberBand() )
            text = "Cursor Pos: Press left mouse button in plot region";
        else
            text = "Zoom: Press mouse button and drag";
    }

    statusBar()->message(text);
}

void MainWin::moved(const QPoint &pos)
{
    QString info;
    info.sprintf("Freq=%g, Ampl=%g, Phase=%g",
        d_plot->invTransform(QwtPlot::xBottom, pos.x()),
        d_plot->invTransform(QwtPlot::yLeft, pos.y()),
        d_plot->invTransform(QwtPlot::yRight, pos.y())
    );
    showInfo(info);
}

void MainWin::selected(const QPointArray &)
{
    showInfo();
}

int main (int argc, char **argv)
{
#ifdef QWT_QTOPIA
    QPEApplication a(argc, argv);
#else
    QApplication a(argc, argv);
#endif

    MainWin w;
    a.setMainWidget(&w);
    w.resize(540,400);
    w.show();

    int rv = a.exec();
    return rv;
}

// Local Variables:
// mode: C++
// c-file-style: "stroustrup"
// indent-tabs-mode: nil
// End:
