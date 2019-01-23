#include <qframe.h>
class QwtKnob;
class QwtThermo;

class AmpFrame : public QFrame
{
    Q_OBJECT
public:
    AmpFrame(QWidget *p, const char *name = 0);

public slots:
    void setMaster(double v);

protected:
    void timerEvent(QTimerEvent *t);

private:
    QwtKnob *knbVolume, *knbTreble, *knbBass, *knbBalance;
    QwtThermo *thmLeft, *thmRight;
    double master;
};



