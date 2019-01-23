#ifdef QWT_QTOPIA
#include <qpe/qpeapplication.h>
#endif
#include <qapplication.h>
#include <qvbox.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include "cpupiemarker.h"
#include "cpuaveragecurve.h"
#include "cpuplot.h"

class TimeScaleDraw: public QwtScaleDraw
{
public:
    TimeScaleDraw(const QTime &base):
        baseTime(base)
    {
    }
    virtual QString label(double v) const
    {
        QTime upTime = baseTime.addSecs((int)v);
        return upTime.toString();
    }
private:
    QTime baseTime;
};

CpuPlot::CpuPlot(QWidget *parent):
    QwtPlot(parent),
    dataCount(0)
{
    plotLayout()->setAlignCanvasToScales(TRUE);
    setCanvasBackground(Qt::darkGray);

    setAutoLegend(TRUE);
    setLegendPosition(QwtPlot::Right);

    setAxisTitle(QwtPlot::xBottom, " System Uptime [h:m:s]");
    setAxisScaleDraw(QwtPlot::xBottom, 
        new TimeScaleDraw(cpuStat.upTime()));
    setAxisScale(QwtPlot::xBottom, 0, HISTORY);
    setAxisLabelRotation(QwtPlot::xBottom, -50.0);
    setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);


    setAxisTitle(QwtPlot::yLeft, "Cpu Usage [%]");
    setAxisScale(QwtPlot::yLeft, 0, 100);

    data[Total].curve = insertCurve("Total");
    setCurvePen(data[Total].curve, QPen(Qt::black));
    setCurveBrush(data[Total].curve, 
        QBrush(QColor(), Qt::SolidPattern));

    data[Idle].curve = insertCurve("Idle");
    setCurvePen(data[Idle].curve, QPen(Qt::lightGray));
    setCurveBrush(data[Idle].curve, 
        QBrush(QColor(), Qt::Dense4Pattern));

    data[User].curve = insertCurve("User");
    setCurvePen(data[User].curve, QPen(Qt::blue));
    setCurveBrush(data[User].curve, 
        QBrush(QColor(), Qt::Dense2Pattern));

    data[System].curve = insertCurve("System");
    setCurvePen(data[System].curve, QPen(Qt::red));
    setCurveBrush(data[System].curve, 
        QBrush(QColor(), Qt::Dense2Pattern));

    CpuAverageCurve *curve = new CpuAverageCurve(this);
    data[Average].curve = insertCurve(curve);
    setCurveTitle(data[Average].curve, "Average");
    setCurvePen(data[Average].curve, QPen(Qt::NoPen));
    setCurveBrush(data[Average].curve, 
        QBrush(QColor(Qt::black), Qt::BDiagPattern));

    CpuPieMarker *pie = new CpuPieMarker(this);
    (void)insertMarker(pie);
    
    toggleCurve(data[Total].curve);
    toggleCurve(data[Idle].curve);
    toggleCurve(data[Average].curve);

    for ( int i = 0; i < HISTORY; i++ )
        timeData[HISTORY - 1 - i] = i;

    (void)startTimer(1000); // 1 second
    replot();

    connect(this, SIGNAL(legendClicked(long)),
        SLOT(toggleCurve(long)));
}

void CpuPlot::drawCanvasItems(QPainter *painter, const QRect &rect,
        const QwtArray<QwtDiMap> &map, const QwtPlotPrintFilter &pfilter) const
{
    const QwtDiMap &yMap = map[QwtPlot::yLeft];

    QRect r = canvas()->rect();
    r.setHeight(yMap.transform(80.0) - r.top());
    painter->fillRect(r, QColor(Qt::white));

    r.setTop(yMap.transform(80.0));
    r.setHeight(yMap.transform(40.0) - yMap.transform(80.0));
    painter->fillRect(r, QColor(Qt::gray));

    QwtPlot::drawCanvasItems(painter, rect, map, pfilter);
}

void CpuPlot::timerEvent(QTimerEvent *)
{
    for ( int i = dataCount; i > 0; i-- )
    {
        for ( int c = 0; c < NCpuData; c++ )
        {
            if ( i < HISTORY )
                data[c].data[i] = data[c].data[i-1];
        }
    }

    cpuStat.statistic(data[User].data[0], data[System].data[0]);

    data[Total].data[0] = data[User].data[0] + 
        data[System].data[0];
    data[Idle].data[0] = 100.0 - data[Total].data[0];
    data[Average].data[0] = cpuStat.average();

    if ( dataCount < HISTORY )
        dataCount++;

    for ( int j = 0; j < HISTORY; j++ )
        timeData[j]++;

    setAxisScale(QwtPlot::xBottom, 
        timeData[HISTORY - 1], timeData[0]);

    for ( int c = 0; c < NCpuData; c++ )
    {
        setCurveRawData(data[c].curve, 
            timeData, data[c].data, dataCount);
    }

    replot();
}

void CpuPlot::toggleCurve(long curveId)
{
    QwtPlotCurve *c = curve(curveId);
    if ( c )
    {
        c->setEnabled(!c->enabled());
        replot();
    }
}

int main(int argc, char **argv)
{
#ifdef QWT_QTOPIA
    QPEApplication a(argc, argv);
#else
    QApplication a(argc, argv); 
#endif
    
    QVBox vBox;
    vBox.setCaption("Cpu Plot");

    CpuPlot *plot = new CpuPlot(&vBox);
    plot->setTitle("History");
    plot->setMargin(5);

    QString info("Press the legend to en/disable a curve");

    (void)new QLabel(info, &vBox);
    a.setMainWidget(&vBox);

    vBox.resize(500,300);
    vBox.show();

    return a.exec();  
}   

