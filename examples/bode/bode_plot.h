#include <qwt_plot.h>

class BodePlot: public QwtPlot
{
    Q_OBJECT
public:
    BodePlot(QWidget *parent);

public slots:
    void setDamp(double damping);

private:
    void showData(double *frequency, double *amplitude, 
        double *phase, int count);
    void showPeak(double freq, double amplitude);
    void show3dB(double freq);

    long crv1, crv2;
    long mrk1, mrk2;
};
