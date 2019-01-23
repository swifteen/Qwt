#include <qobject.h>

class QwtPlot;
class QwtScale;

class ScalePicker: public QObject
{
    Q_OBJECT
public:
    ScalePicker(QwtPlot *plot);
    virtual bool eventFilter(QObject *, QEvent *);

signals:
    void clicked(int axis, double value);

private:
    void mouseClicked(const QwtScale *, const QPoint &);
    QRect scaleRect(const QwtScale *) const;
};
