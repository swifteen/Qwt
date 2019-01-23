#include <qpainter.h>
#include "cpuplot.h"
#include "cpupiemarker.h"

CpuPieMarker::CpuPieMarker(CpuPlot *plot):
	QwtPlotMarker(plot)
{
}

void CpuPieMarker::draw(QPainter *p, int, int, const QRect &rect)
{
	const CpuPlot *plot = (CpuPlot *)parentPlot();

	const QwtDiMap yMap = plot->canvasMap(QwtPlot::yLeft);

	const int margin = 5;
	
	QRect pieRect;
	pieRect.setX(rect.x() + margin);
	pieRect.setY(rect.y() + margin);
	pieRect.setHeight(yMap.transform(80.0));
	pieRect.setWidth(pieRect.height());
	
	const int dataType[] = { CpuPlot::User, CpuPlot::System, CpuPlot::Idle };

	int angle = (int)(5760 * 0.75);
	for ( unsigned int i = 0; 
		i < sizeof(dataType) / sizeof(dataType[0]); i++ )
	{
		const QwtPlotCurve *curve = plot->cpuCurve(dataType[i]);
		if ( curve->dataSize() > 0 )
		{
			const int value = (int)(5760 * curve->y(0) / 100.0);

			p->save();
			p->setBrush(QBrush(curve->pen().color(), Qt::SolidPattern));
			p->drawPie(pieRect, -angle, -value);
			p->restore();

			angle += value;
		}
	}
}

