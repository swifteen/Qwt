#include <qstring.h>
#include <qwt_dial.h>

class SpeedoMeter: public QwtDial
{
public:
    SpeedoMeter(QWidget *parent = 0, const char *name = 0);

	void setLabel(const QString &);
	QString label() const;

protected:
    virtual void drawScaleContents(QPainter *painter,
        const QPoint &center, int radius) const;

private:
	QString d_label;
};
