#include <qframe.h>
#include <qwt_curve.h>
#include <qwt_dimap.h>

class MainWin : public QFrame 
{
public:
    enum { curveCount = 4 };

	QwtDiMap xMap[curveCount];
	QwtDiMap yMap[curveCount];
    QwtCurve curve[curveCount];

public:
    MainWin();
    
protected:
	virtual void drawContents(QPainter *);
    virtual void timerEvent(QTimerEvent *t);

private:
    void newValues();
};
