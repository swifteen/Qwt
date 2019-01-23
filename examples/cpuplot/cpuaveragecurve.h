#include <qwt_plot_classes.h>

//-----------------------------------------------------------------
// This class shows how to extend QwtPlotCurves. It fills the
// area between total and average usage curves.
//-----------------------------------------------------------------

class CpuPlot;

class CpuAverageCurve: public QwtPlotCurve
{
public:
	CpuAverageCurve(CpuPlot *);

protected:
	virtual void drawCurve(QPainter *painter, int,
    	const QwtDiMap &xMap, const QwtDiMap &yMap, int from, int to);
};
