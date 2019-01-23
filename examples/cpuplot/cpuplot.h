#include <qwt_plot.h>
#include "cpustat.h"

#define HISTORY 60 // seconds

class CpuPlot : public QwtPlot 
{
	Q_OBJECT
public:
	enum CpuData
	{
		User,
		System,
		Total,
		Idle,
		Average,

		NCpuData
	};

	CpuPlot(QWidget * = 0);
	const QwtPlotCurve *cpuCurve(int id) const
		{ return curve(data[id].curve); }

protected:
    virtual void drawCanvasItems(QPainter *, const QRect &,
        const QwtArray<QwtDiMap> &, const QwtPlotPrintFilter &) const;

    void timerEvent(QTimerEvent *e);

private slots:
	void toggleCurve(long);

private:
	struct
	{
		long curve;
		double data[HISTORY];
	} data[NCpuData];
	double timeData[HISTORY];

	int dataCount;
	CpuStat cpuStat;
};
