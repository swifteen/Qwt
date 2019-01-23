#include "plot.h"
#include "colorbar.h"
#include <qevent.h>
#include <qslider.h>
#include <qwhatsthis.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale.h>
#include <stdlib.h>

Plot::Plot(QWidget *parent):
    QwtPlot(parent)
{
    setTitle("Interactive Plot");

    setCanvasColor(Qt::darkCyan);
    setGridMajPen(QPen(Qt::white, 0, Qt::DotLine));

    // axes

    setAxisScale(xBottom, 0.0, 100.0);
    setAxisScale(yLeft, 0.0, 100.0);

    plotLayout()->setAlignCanvasToScales(TRUE);

    insertCurve(Qt::Vertical, Qt::blue, 30.0);
    insertCurve(Qt::Vertical, Qt::magenta, 70.0);
    insertCurve(Qt::Horizontal, Qt::yellow, 30.0);
    insertCurve(Qt::Horizontal, Qt::white, 70.0);

    replot();

    // ------------------------------------
    // We add a color bar to the left axis
    // ------------------------------------

    QwtScale *scale = (QwtScale *)axis(yLeft);
    scale->setBaselineDist(10); // area for the color bar
    QWhatsThis::add(scale, 
        "Selecting a value at the scale will insert a new curve.");

    d_colorBar = new ColorBar(Qt::Vertical, scale);
    d_colorBar->setRange(Qt::red, Qt::darkBlue);
    d_colorBar->setFocusPolicy( TabFocus  );
    QWhatsThis::add(d_colorBar, 
        "Selecting a color will change the background of the plot.");

    connect(d_colorBar, SIGNAL(selected(const QColor &)),
        SLOT(setCanvasColor(const QColor &)));

    // we need the resize events, to lay out the color bar
    scale->installEventFilter(this); 

    // ------------------------------------
    // We add a slider to the bottom axis
    // ------------------------------------

    scale = (QwtScale *)axis(xBottom);
    scale->setBaselineDist(12); // area for the slider
    QWhatsThis::add(scale, 
        "Selecting a value at the scale will insert a new curve.");

    d_slider = new QSlider(0, 100, 10, 50, Qt::Horizontal, scale);
    d_slider->setTracking(TRUE);
    QWhatsThis::add(d_slider, 
        "With this slider you can move the visible area.");
    connect(d_slider, SIGNAL(valueChanged(int)),
        SLOT(sliderMoved(int)));

    // we need the resize events, to lay out the slider
    scale->installEventFilter(this);
}

void Plot::setCanvasColor(const QColor &c)
{
    setCanvasBackground(c);
    replot();
}

void Plot::sliderMoved(int)
{
    // sync slider and axis
    double pos = d_slider->sliderRect().center().x();
    double range = d_slider->width();

    double base = 50.0 - 100.0 * pos / range;
    setAxisScale(xBottom, base, base + 100);

    replot();
}

bool Plot::eventFilter(QObject *object, QEvent *e)
{
    if ( e->type() == QEvent::Resize )
    {
        const QSize &size = ((QResizeEvent *)e)->size();
        if ( object == (QObject *)axis(yLeft) )
        {
            const QwtScale *scale = axis(yLeft);

            const int margin = 2;

            // adjust the color bar to the scale backbone
            const int x = size.width() - scale->baseLineDist() + margin;
            const int w = scale->baseLineDist() - 2 * margin;
            const int y = scale->startBorderDist();
            const int h = size.height() -
                scale->startBorderDist() - scale->endBorderDist();

            d_colorBar->setGeometry(x, y, w, h);
        }
        if ( object == (QObject *)axis(xBottom) )
        {
            const QwtScale *scale = axis(xBottom);

            // adjust the slider to the scale backbone
            const int x = scale->startBorderDist();
            const int w = size.width() - 
                scale->startBorderDist() - scale->endBorderDist();
            const int y = 0;
            const int h = scale->baseLineDist();

            d_slider->setGeometry(x, y, w, h);
        }
    }

    return QwtPlot::eventFilter(object, e);
}

void Plot::insertCurve(int axis, double base)
{
    Qt::Orientation o;
    if ( axis == yLeft || axis == yRight )
        o = Qt::Horizontal;
    else
        o = Qt::Vertical;
    
    QRgb rgb = (uint)rand();
    insertCurve(o, QColor(rgb), base);
    replot();
}

void Plot::insertCurve(Qt::Orientation o,
    const QColor &c, double base)
{
    QwtPlotCurve *curve = new QwtPlotCurve(this);

    curve->setPen(c);
    curve->setSymbol(QwtSymbol(QwtSymbol::Ellipse,
        Qt::gray, c, QSize(8, 8)));

    double x[10];
    double y[sizeof(x) / sizeof(x[0])];

    for ( uint i = 0; i < sizeof(x) / sizeof(x[0]); i++ )
    {
        double v = 5.0 + i * 10.0;
        if ( o == Qt::Horizontal )
        {
            x[i] = v;
            y[i] = base;
        }
        else
        {
            x[i] = base;
            y[i] = v;
        }
    }
        
    curve->setData(x, y, sizeof(x) / sizeof(x[0]));
    (void)QwtPlot::insertCurve(curve);
}
