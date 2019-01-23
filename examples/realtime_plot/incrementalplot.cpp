#include <qwt_plot.h>
#include <qwt_plot_dict.h>
#include "incrementalplot.h"

CurveData::CurveData():
    d_count(0)
{
}

void CurveData::append(double *x, double *y, int count)
{
    int newSize = ( (d_count + count) / 1000 + 1 ) * 1000;
    if ( newSize > size() )
    {
        d_x.resize(newSize);
        d_y.resize(newSize);
    }

    for ( register int i = 0; i < count; i++ )
    {
        d_x[d_count + i] = x[i];
        d_y[d_count + i] = y[i];
    }
    d_count += count;
}

int CurveData::count() const
{
    return d_count;
}

int CurveData::size() const
{
    return d_x.size();
}

double *CurveData::x() const
{
    return d_x.data();
}

double *CurveData::y() const
{
    return d_y.data();
}

IncrementalPlot::IncrementalPlot(QWidget *parent, const char* name): 
    QwtPlot(parent, name)
{
    d_curveDictionary.setAutoDelete(TRUE);
}

IncrementalPlot::~IncrementalPlot()
{
    removeCurves();
}

void IncrementalPlot::appendCurvePoint(long curveId, double x, double y)
{
    appendCurveData(curveId, &x, &y, 1);
}

void IncrementalPlot::appendCurveData(long curveId, 
    double *x, double *y, int size)
{
    QwtPlotCurve *curve = IncrementalPlot::curve(curveId);
    if ( curve == 0 || size <= 0 )
        return;
    
    CurveData *curveData = d_curveDictionary.find(curveId);
    if ( curveData == 0 )
    {
        curveData = new CurveData();
        d_curveDictionary.insert(curveId, curveData);
    }

    curveData->append(x, y, size);
    curve->setRawData(curveData->x(), curveData->y(), curveData->count());

    drawCurve(curveId, curve->dataSize() - size, curve->dataSize() - 1);
}

void IncrementalPlot::removeCurveData(long curveId)
{
    d_curveDictionary.remove(curveId);
}
