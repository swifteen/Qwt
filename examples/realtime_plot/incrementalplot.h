#ifndef _INCREMENTALPLOT_H_
#define _INCREMENTALPLOT_H_ 1

#include <qintdict.h>
#include <qwt_array.h>
#include <qwt_plot.h>

class CurveData
{
    // A container class for growing data
public:

    CurveData();

    void append(double *x, double *y, int count);

    int count() const;
    int size() const;
    double *x() const;
    double *y() const;

private:
    int d_count;
    QwtArray<double> d_x;
    QwtArray<double> d_y;
};

class IncrementalPlot : public QwtPlot
{
    Q_OBJECT
public:
    IncrementalPlot(QWidget *parent = 0, const char *name = 0);
    virtual ~IncrementalPlot();

    void appendCurvePoint(long curveId, double x, double y);
    void appendCurveData(long curveId,
        double *x, double *y, int size);

    void removeCurveData(long curveId);
private:

    QIntDict<CurveData> d_curveDictionary;
};

#endif // _INCREMENTALPLOT_H_
