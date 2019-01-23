#include <qwt_math.h>
#include "cplx.h"
#include "bode_plot.h"

BodePlot::BodePlot(QWidget *parent):
    QwtPlot(parent)
{
    setTitle("Frequency Response of a Second-Order System");

    setCanvasBackground(darkBlue);

    // legend
    setAutoLegend(TRUE);
    enableLegend(TRUE);
    setLegendPosition(QwtPlot::Bottom);
    setLegendFrameStyle(QFrame::Box|QFrame::Sunken);

    // grid 
    enableGridXMin();
    setGridMajPen(QPen(white, 0, DotLine));
    setGridMinPen(QPen(gray, 0 , DotLine));

    // axes
    enableAxis(QwtPlot::yRight);
    setAxisTitle(QwtPlot::xBottom, "Normalized Frequency");
    setAxisTitle(QwtPlot::yLeft, "Amplitude [dB]");
    setAxisTitle(QwtPlot::yRight, "Phase [deg]");

    setAxisOptions(QwtPlot::xBottom, QwtAutoScale::Logarithmic);
    setAxisMaxMajor(QwtPlot::xBottom, 6);
    setAxisMaxMinor(QwtPlot::xBottom, 10);
  
    // curves
    crv1 = insertCurve("Amplitude");
    setCurvePen(crv1, QPen(yellow));
    setCurveYAxis(crv1, QwtPlot::yLeft);

    crv2 = insertCurve( "Phase");
    setCurvePen(crv2, QPen(cyan));
    setCurveYAxis(crv2, QwtPlot::yRight);
    
    // marker
    mrk1 = insertMarker();
    setMarkerLineStyle(mrk1, QwtMarker::VLine);
    setMarkerPos(mrk1, 0.0,0.0);
    setMarkerLabelAlign(mrk1, AlignRight|AlignBottom);
    setMarkerPen(mrk1, QPen(green, 0, DashDotLine));
    setMarkerFont(mrk1, QFont("Helvetica", 10, QFont::Bold));

    mrk2 = insertLineMarker("", QwtPlot::yLeft);
    setMarkerLabelAlign(mrk2, AlignRight|AlignBottom);
    setMarkerPen(mrk2, QPen(QColor(200,150,0), 0, DashDotLine));
    setMarkerFont(mrk2, QFont("Helvetica", 10, QFont::Bold));
    setMarkerSymbol(mrk2, 
        QwtSymbol(QwtSymbol::Diamond, yellow, green, QSize(7,7)));

    setDamp(0.0);
}

void BodePlot::showData(double *frequency, double *amplitude,
    double *phase, int count)
{
    setCurveData(crv1, frequency, amplitude, count);
    setCurveData(crv2, frequency, phase, count);
}

void BodePlot::showPeak(double freq, double amplitude)
{
    QString label;
    label.sprintf("Peak: %.3g dB", amplitude);

    setMarkerPos(mrk2, freq, amplitude);
    setMarkerLabelText(mrk2, label);
}

void BodePlot::show3dB(double freq)
{
    QString label;
    label.sprintf("-3 dB at f = %.3g", freq);

    setMarkerPos(mrk1, freq, 0.0);
    setMarkerLabelText(mrk1, label);
}

//
// re-calculate frequency response
//
void BodePlot::setDamp(double damping)
{
    const int ArraySize = 200;

    double frequency[ArraySize];
    double amplitude[ArraySize];
    double phase[ArraySize];

    // build frequency vector with logarithmic division
    qwtLogSpace(frequency, ArraySize, 0.01, 100);

    int i3 = 1;
    double fmax = 1;
    double amax = -1000.0;
    
    for (int i = 0; i < ArraySize; i++)
    {
        double f = frequency[i];
        cplx g = cplx(1.0) / cplx(1.0 - f * f, 2.0 * damping * f);
        amplitude[i] = 20.0 * log10(sqrt( g.real()*g.real() + g.imag()*g.imag()));
        phase[i] = atan2(g.imag(), g.real()) * (180.0 / M_PI);

        if ((i3 <= 1) && (amplitude[i] < -3.0)) 
           i3 = i;
        if (amplitude[i] > amax)
        {
            amax = amplitude[i];
            fmax = frequency[i];
        }
        
    }
    
    double f3 = frequency[i3] - 
       (frequency[i3] - frequency[i3 - 1]) 
          / (amplitude[i3] - amplitude[i3 -1]) * (amplitude[i3] + 3);
    
    showPeak(fmax, amax);
    show3dB(f3);
    showData(frequency, amplitude, phase, ArraySize);

    replot();
}
