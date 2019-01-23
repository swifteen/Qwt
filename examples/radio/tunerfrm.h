#include <qframe.h>

class QwtWheel;
class QLabel;
class QwtSlider;
class QwtThermo;


class TunerFrame : public QFrame
{
    Q_OBJECT
public:
    TunerFrame(QWidget *p, const char *namei = 0);

signals:
    void fieldChanged(double f);

public slots:
    void setFreq(double frq);

private slots:
    void adjustFreq(double frq);

private:
    QwtWheel *whlFreq;
    QwtThermo *thmTune;
    QwtSlider *sldFreq;
};




