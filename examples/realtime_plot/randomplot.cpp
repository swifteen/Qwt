#include <stdlib.h>
#include <qtimer.h>
#include "scrollzoomer.h"
#include "randomplot.h"

const unsigned int c_rangeMax = 1000;

RandomPlot::RandomPlot(QWidget *parent):
    IncrementalPlot(parent),
    d_curveId(0),
    d_timer(0),
    d_timerCount(0)
{
    setFrameStyle(QFrame::NoFrame);
    setLineWidth(0);
    setCanvasLineWidth(2);

    enableGridX(TRUE);
    enableGridY(TRUE);
    setGridMajPen(QPen(Qt::gray, 0, Qt::DotLine));

    setCanvasBackground(QColor(29, 100, 141)); // nice blue

    setAxisScale(xBottom, 0, c_rangeMax);
    setAxisScale(yLeft, 0, c_rangeMax);

    for ( int i = 0; i < QwtPlot::axisCnt; i++ )
        setAxisLabelFormat(i, 'g', 8);

    // enable zooming

    ScrollZoomer *zoomer = new ScrollZoomer(canvas());
    zoomer->setRubberBandPen(QPen(Qt::yellow, 0, Qt::DotLine));
    zoomer->setCursorLabelPen(QPen(Qt::yellow));

    initCurve();
}

QSize RandomPlot::sizeHint() const
{
    return QSize(540,400);
}

void RandomPlot::initCurve()
{
    if ( d_curveId > 0 )
    {
        removeCurveData(d_curveId);
        removeCurve(d_curveId);
    }

    d_curveId = insertCurve("Test Curve");
    setCurveStyle(d_curveId, QwtCurve::NoCurve);

    const QColor &c = Qt::white;
    setCurveSymbol(d_curveId, QwtSymbol(QwtSymbol::XCross,
        QBrush(c), QPen(c), QSize(5, 5)) );
}

void RandomPlot::appendPoint()
{
    double x = rand() % c_rangeMax;
    x += ( rand() % 100 ) / 100;

    double y = rand() % c_rangeMax;
    y += ( rand() % 100 ) / 100;

    appendCurvePoint(d_curveId, x, y);

    if ( --d_timerCount <= 0 )
        stop();
}

void RandomPlot::append(int timeout, int count)
{
    if ( !d_timer )
    {
        d_timer = new QTimer(this);
        connect(d_timer, SIGNAL(timeout()), SLOT(appendPoint()));
    }

    d_timerCount = count;

    emit running(TRUE);
    d_timer->start(timeout);
}

void RandomPlot::stop()
{
    if ( d_timer )
    {
        d_timer->stop();
        emit running(FALSE);
    }
}

void RandomPlot::clear()
{
    initCurve();
    replot();
}
