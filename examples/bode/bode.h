#include <qmainwindow.h>

class BodePlot;
class QPointArray;
class QwtPlotZoomer;
class QwtPlotPicker;

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *p = 0, const char *name = 0);

private slots:
    void moved(const QPoint &);
    void selected(const QPointArray &);
    
    void print();
    void zoom(bool);
    void setXorRop(int);

private:
    void showInfo(QString text = QString::null);

    BodePlot *d_plot;

    QwtPlotZoomer *d_zoomer[2];
    QwtPlotPicker *d_picker;
};
