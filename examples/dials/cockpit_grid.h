#include <qgrid.h>
#include <qpalette.h>

class QwtAnalogClock;
class SpeedoMeter;
class AttitudeIndicator;

class CockpitGrid: public QGrid
{
	Q_OBJECT

public:
    CockpitGrid(QWidget *parent);

private slots:
	void changeSpeed();
	void changeGradient();
	void changeAngle();

private:
	QPalette colorTheme(const QColor &) const;
	void createDial(int pos);

	QwtAnalogClock *d_clock;
	SpeedoMeter *d_speedo;
	AttitudeIndicator *d_ai;
};
