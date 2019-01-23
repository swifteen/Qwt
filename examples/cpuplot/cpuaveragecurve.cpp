#include <qpainter.h>
#include <qwt_painter.h>
#include "cpuplot.h"
#include "cpuaveragecurve.h"

CpuAverageCurve::CpuAverageCurve(CpuPlot *plot):
	QwtPlotCurve(plot)
{
}

void CpuAverageCurve::drawCurve(QPainter *painter, int,
    const QwtDiMap &xMap, const QwtDiMap &yMap, int from, int to)
{
	QPointArray polyline( 2 * (to - from + 1));

	int idx = 0;
	for (register int i = from; i <= to; i++, idx++)
	{
		int xi = xMap.transform(x(i));
		int yi = yMap.transform(y(i));

		polyline.setPoint(idx, xi, yi);
	}

	const CpuPlot *plot = (const CpuPlot *)parentPlot();
	const QwtPlotCurve *totalCurve = plot->cpuCurve(CpuPlot::Total);

	for (register int j = to; j >= from; j--, idx++)
	{
		int xj = xMap.transform(totalCurve->x(j));
		int yj = yMap.transform(totalCurve->y(j));

		polyline.setPoint(idx, xj, yj);
	}

	QwtPainter::drawPolygon(painter, polyline);
}
