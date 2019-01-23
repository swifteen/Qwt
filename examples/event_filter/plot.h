#include <qwt_plot.h>

class ColorBar;
class QSlider;

class Plot: public QwtPlot
{
    Q_OBJECT
public:
    Plot(QWidget *parent = NULL);
    virtual bool eventFilter(QObject *, QEvent *);

public slots:
    void setCanvasColor(const QColor &);
    void insertCurve(int axis, double base);

private slots:
    void sliderMoved(int);

private:
    void insertCurve(Qt::Orientation, const QColor &, double base);

    ColorBar *d_colorBar;
    QSlider *d_slider;
};
