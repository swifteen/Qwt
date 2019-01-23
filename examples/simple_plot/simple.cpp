#ifdef QWT_QTOPIA
#include <qpe/qpeapplication.h>
#endif
#include <qapplication.h>
#include <qwt_plot.h>
#include <qwt_data.h>
#include <math.h>

//-----------------------------------------------------------------
//              simple.cpp
//
//      A simple example which shows how to use QwtPlot and QwtData
//-----------------------------------------------------------------

class SimpleData: public QwtData
{
    // The x values depend on its index and the y values
    // can be calculated from the corresponding x value. 
    // So we don´t need to store the values.
    // Such an implementation is slower because every point 
    // has to be recalculated for every replot, but it demonstrates how
    // QwtData can be used.

public:
    SimpleData(double(*y)(double), size_t size):
        d_size(size),
        d_y(y)
    {
    }

    virtual QwtData *copy() const
    {
        return new SimpleData(d_y, d_size);
    }

    virtual size_t size() const
    {
        return d_size;
    }

    virtual double x(size_t i) const
    {
        return 0.1 * i;
    }

    virtual double y(size_t i) const
    {
        return d_y(x(i));
    }
private:
    size_t d_size;
    double(*d_y)(double);
};

class Plot : public QwtPlot
{
public:
    Plot();
};


Plot::Plot()
{
    setTitle("A Simple QwtPlot Demonstration");
    setAutoLegend(TRUE); // We want a legend
    setLegendPosition(QwtPlot::Right);

    // Set axis titles
    setAxisTitle(xBottom, "x -->");
    setAxisTitle(yLeft, "y -->");
    
    // Insert new curves
    long cSin = insertCurve("y = sin(x)");
    long cCos = insertCurve("y = cos(x)");

    // Set curve styles
    setCurvePen(cSin, QPen(Qt::red));
    setCurvePen(cCos, QPen(Qt::blue));

    // Create sin and cos data
    const int nPoints = 100;
    setCurveData(cSin, SimpleData(::sin, nPoints));
    setCurveData(cCos, SimpleData(::cos, nPoints));

    // Insert markers
    
    //  ...a horizontal line at y = 0...
    long mY = insertLineMarker("y = 0", QwtPlot::yLeft);     
    setMarkerYPos(mY, 0.0);

    //  ...a vertical line at x = 2 * pi
    long mX = insertLineMarker("x = 2 pi", QwtPlot::xBottom);
    setMarkerXPos(mX, 6.284);

    replot();
}

int main(int argc, char **argv)
{
#ifdef QWT_QTOPIA
    QPEApplication a(argc, argv);
#else
    QApplication a(argc, argv);
#endif

    Plot plot;
    a.setMainWidget(&plot);
    plot.resize(500,300);
    plot.show();
    return a.exec(); 
}
