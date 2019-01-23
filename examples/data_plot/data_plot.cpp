#include <stdlib.h>

#ifdef QWT_QTOPIA
#include <qpe/qpeapplication.h>
#endif

#include <qapplication.h>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale.h>
#include <qwt_scldraw.h>
#include <qwt_math.h>


const int PLOT_SIZE = 201;      // 0 to 200

//-----------------------------------------------------------------
//      data_plot.cpp
//
//  This example shows how to display time-varying data
//  using QwtPlot.
//
//-----------------------------------------------------------------

class DataPlot : public QwtPlot
{
public:
    DataPlot();

protected:
    virtual void timerEvent(QTimerEvent *e);

private:
    void alignScales();

    double x[PLOT_SIZE], y[PLOT_SIZE], z[PLOT_SIZE];
};


//
//  Initialize main window
//
DataPlot::DataPlot() 
{
    alignScales();
    
    //  Initialize data
    for (int i = 0; i< PLOT_SIZE; i++)
    {
        x[i] = 0.5 * double(i);     // time axis
        y[i] = 0;
        z[i] = 0;
    }

    // Assign a title
    setTitle("Another Simple QwtPlot Demonstration");
    setAutoLegend(TRUE);

    // Insert new curves
    long cRight = insertCurve("Data Moving Right");
    long cLeft = insertCurve("Data Moving Left");

    // Set curve styles
    setCurvePen(cRight, QPen(Qt::red));
    setCurvePen(cLeft, QPen(Qt::blue));

    // Attach (don't copy) data. Both curves use the same x array.
    setCurveRawData(cRight, x, y, PLOT_SIZE);
    setCurveRawData(cLeft, x, z, PLOT_SIZE);

    //  Insert zero line at y = 0
    long mY = insertLineMarker("", QwtPlot::yLeft);     
    setMarkerYPos(mY, 0.0);

    // Set axis titles
    setAxisTitle(QwtPlot::xBottom, "Time/seconds");
    setAxisTitle(QwtPlot::yLeft, "Values");
    
    // Generate timer event every 50ms
    (void)startTimer(50);
}

//
//  Set a plain canvas frame and align the scales to it
//
void DataPlot::alignScales()
{
    // The code below shows how to align the scales to
    // the canvas frame, but is also a good example demonstrating
    // why the spreaded API needs polishing.

    canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
    canvas()->setLineWidth(1);

    for ( int i = 0; i < QwtPlot::axisCnt; i++ )
    {
        QwtScale *scale = (QwtScale *)axis(i);
        if ( scale )
            scale->setBaselineDist(0);

        QwtScaleDraw *scaleDraw = (QwtScaleDraw *)axisScaleDraw(i);
        if ( scaleDraw )
        {
            scaleDraw->setOptions(
                scaleDraw->options() & ~QwtScaleDraw::Backbone);
        }
    }
}

//
//  Generate new values every 500ms. 
//
void DataPlot::timerEvent(QTimerEvent *)
{
    static double phase = 0.0;

    if (phase > (M_PI - 0.0001)) phase = 0;

    // y moves from left to right:
    // Shift y array right and assign new value to y[0].
    qwtShiftArray(y, PLOT_SIZE, 1);
    y[0] = sin(phase) * (-1.0 + 2.0 * double(rand()) / double(RAND_MAX));

    // z moves from right to left:
    // Shift z array left and assign new value to z[n-1].
    qwtShiftArray(z, PLOT_SIZE, -1);
    z[PLOT_SIZE - 1] = 0.8 - (2.0 * phase/M_PI) + 0.4 * 
        double(rand()) / double(RAND_MAX);

    // update the display
    replot();

    phase += M_PI * 0.02;
}

int main(int argc, char **argv)
{
#ifdef QWT_QTOPIA
    QPEApplication a(argc, argv);
#else
    QApplication a(argc, argv);
#endif

    DataPlot plot;
    a.setMainWidget(&plot);

    plot.resize(500,300);
    plot.show();

    return a.exec(); 
}
