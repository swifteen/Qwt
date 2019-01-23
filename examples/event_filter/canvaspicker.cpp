#include <qevent.h>
#include <qwhatsthis.h>
#include <qpainter.h>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include "canvaspicker.h"

CanvasPicker::CanvasPicker(QwtPlot *plot):
    QObject(plot),
    d_selectedCurve(-1),
    d_selectedPoint(-1)
{
    QwtPlotCanvas *canvas = plot->canvas();

    canvas->installEventFilter(this);

    // We want the focus, but no focus rect. The
    // selected point will be highlighted instead.

    canvas->setFocusPolicy(QWidget::StrongFocus);
    canvas->setFocusIndicator(QwtPlotCanvas::ItemFocusIndicator);
    canvas->setFocus();
    canvas->setCursor(Qt::pointingHandCursor);

    QWhatsThis::add(canvas,
        "All points can be moved using the left mouse button "
        "or with these keys:\n\n"
        "- Up:\t\tSelect next curve\n"
        "- Down:\t\tSelect previous curve\n"
        "- Left, ´-´:\tSelect next point\n"
        "- Right, ´+´:\tSelect previous point\n"
        "- 7, 8, 9, 4, 6, 1, 2, 3:\tMove selected point"
    );

    shiftCurveCursor(TRUE);
}

bool CanvasPicker::eventFilter(QObject *object, QEvent *e)
{
    if ( object != (QObject *)plot()->canvas() )
        return FALSE;

    switch(e->type())
    {
        case QEvent::FocusIn:
            showCursor(TRUE);
        case QEvent::FocusOut:
            showCursor(FALSE);

        case QEvent::Paint:
        {   
            // The inPaint guard protecs from producing endless
            // paint events.

            static bool inPaint = FALSE;
            if ( plot()->canvas()->hasFocus() && !inPaint )
            {
                const QPaintEvent *pe = (const QPaintEvent *)e;

                inPaint = TRUE;

                // we have to paint the canvas first, before
                // we can highlight the selected point.

                plot()->canvas()->repaint(pe->rect().x(), pe->rect().y(),
                    pe->rect().width(), pe->rect().height(), FALSE);
                inPaint = FALSE;

                showCursor(TRUE);
                return TRUE; 
            }
            break;
        }
        case QEvent::MouseButtonPress:
        {
            select(((QMouseEvent *)e)->pos());
            return TRUE; 
        }
        case QEvent::MouseMove:
        {
            move(((QMouseEvent *)e)->pos());
            return TRUE; 
        }
        case QEvent::KeyPress:
        {
            const int delta = 5;
            switch(((const QKeyEvent *)e)->key())
            {
                case Qt::Key_Up:
                    shiftCurveCursor(TRUE);
                    return TRUE;
                    
                case Qt::Key_Down:
                    shiftCurveCursor(FALSE);
                    return TRUE;

                case Qt::Key_Right:
                case Qt::Key_Plus:
                    if ( d_selectedCurve < 0 )
                        shiftCurveCursor(TRUE);
                    else
                        shiftPointCursor(TRUE);
                    return TRUE;

                case Qt::Key_Left:
                case Qt::Key_Minus:
                    if ( d_selectedCurve < 0 )
                        shiftCurveCursor(TRUE);
                    else
                        shiftPointCursor(FALSE);
                    return TRUE;

                // The following keys represent a direction, they are
                // organized on the keyboard.
 
                case Qt::Key_1: 
                    moveBy(-delta, delta);
                    break;
                case Qt::Key_2:
                    moveBy(0, delta);
                    break;
                case Qt::Key_3: 
                    moveBy(delta, delta);
                    break;
                case Qt::Key_4:
                    moveBy(-delta, 0);
                    break;
                case Qt::Key_6: 
                    moveBy(delta, 0);
                    break;
                case Qt::Key_7:
                    moveBy(-delta, -delta);
                    break;
                case Qt::Key_8:
                    moveBy(0, -delta);
                    break;
                case Qt::Key_9:
                    moveBy(delta, -delta);
                    break;
                default:
                    break;
            }
        }
        default:
            break;
    }
    return QObject::eventFilter(object, e);
}

// Select the point at a position. If there is no point
// deselect the selected point

void CanvasPicker::select(const QPoint &pos)
{
    int dist, point;
    double xVal, yVal;

    const int curve = plot()->closestCurve(
        pos.x(), pos.y(), dist, xVal, yVal, point);

    if ( curve >= 0 && dist < 10 ) // 10 pixels tolerance
    {
        d_selectedCurve = curve;
        d_selectedPoint = point;
        showCursor(TRUE);
    }
    else // deselect
    {
        showCursor(FALSE);
        d_selectedCurve = -1;
        d_selectedPoint = -1;
    }
}

// Move the selected point
void CanvasPicker::moveBy(int dx, int dy)
{
    if ( dx == 0 && dy == 0 )
        return;

    const QwtPlotCurve *curve = plot()->curve(d_selectedCurve);
    if ( !curve )
        return;

    const int x = plot()->transform(curve->xAxis(),
        curve->x(d_selectedPoint)) + dx;
    const int y = plot()->transform(curve->yAxis(),
        curve->y(d_selectedPoint)) + dy;

    move(QPoint(x, y));
}

// Move the selected point
void CanvasPicker::move(const QPoint &pos)
{
    QwtPlotCurve *curve = plot()->curve(d_selectedCurve);
    if ( !curve )
        return;

    QwtArray<double> xData(curve->dataSize());
    QwtArray<double> yData(curve->dataSize());

    for ( int i = 0; i < curve->dataSize(); i++ )
    {
        if ( i == d_selectedPoint )
        {
            xData[i] = plot()->invTransform(curve->xAxis(), pos.x());;
            yData[i] = plot()->invTransform(curve->yAxis(), pos.y());;
        }
        else
        {
            xData[i] = curve->x(i);
            yData[i] = curve->y(i);
        }
    }
    curve->setData(xData, yData);

    plot()->replot();
    showCursor(TRUE);
}

// Hightlight the selected point
void CanvasPicker::showCursor(bool showIt)
{
    QwtPlotCurve *curve = plot()->curve(d_selectedCurve);
    if ( !curve )
        return;

    QPainter painter(plot()->canvas());
    
    painter.setClipping(TRUE);
    painter.setClipRect(plot()->canvas()->contentsRect());

    if ( showIt )
        painter.setRasterOp(Qt::NotROP);

    curve->draw(&painter,
        plot()->canvasMap(curve->xAxis()), plot()->canvasMap(curve->yAxis()),
        d_selectedPoint, d_selectedPoint);
}

// Select the next/previous curve 
void CanvasPicker::shiftCurveCursor(bool up)
{
    const QwtArray<long> keys = plot()->curveKeys();

    int index = 0;
    if ( d_selectedCurve >= 0 )
    {
        for ( uint i = 0; i < keys.count() - 1; i++ )
        {
            if ( d_selectedCurve == keys[(int)i] )
            {
                index = i + (up ? 1 : -1);
                break;
            }
        }
    }
    index = (keys.count() + index) % keys.count();

    if ( d_selectedCurve != keys[index] )
    {
        showCursor(FALSE);
        d_selectedPoint = 0;
        d_selectedCurve = keys[index];
        showCursor(TRUE);
    }

}

// Select the next/previous neighbour of the selected point
void CanvasPicker::shiftPointCursor(bool up)
{
    const QwtPlotCurve *curve = plot()->curve(d_selectedCurve);
    if ( !curve )
        return;

    int index = d_selectedPoint + (up ? 1 : -1);
    index = (index + curve->dataSize()) % curve->dataSize();

    if ( index != d_selectedPoint )
    {
        showCursor(FALSE);
        d_selectedPoint = index;
        showCursor(TRUE);
    }
}
