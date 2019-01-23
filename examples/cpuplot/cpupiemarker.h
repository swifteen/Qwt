//-----------------------------------------------------------------
// This class shows how to extend QwtPlotItems. It displays a
// pie chart of user/total/idle cpu usage in percent.
//-----------------------------------------------------------------

#include <qwt_plot_classes.h>

class CpuPlot;

class CpuPieMarker: public QwtPlotMarker
{
public:
	CpuPieMarker(CpuPlot *);
    virtual void draw(QPainter *p, int x, int y, const QRect &);
};
