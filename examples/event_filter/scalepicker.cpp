#include <qevent.h>
#include <qwt_plot.h>
#include <qwt_scale.h>
#include "scalepicker.h"

ScalePicker::ScalePicker(QwtPlot *plot):
    QObject(plot)
{
    for ( uint i = 0; i < QwtPlot::axisCnt; i++ )
    {
        QwtScale *scale = (QwtScale *)plot->axis(i);
        if ( scale )
            scale->installEventFilter(this);
    }
}

bool ScalePicker::eventFilter(QObject *object, QEvent *e)
{
    if ( object->inherits("QwtScale") && 
        e->type() == QEvent::MouseButtonPress )
    {
        mouseClicked((const QwtScale *)object,
            ((QMouseEvent *)e)->pos());
        return TRUE;
    }

    return QObject::eventFilter(object, e);
}

void ScalePicker::mouseClicked(const QwtScale *scale, const QPoint &pos) 
{
    QRect rect = scaleRect(scale);

    int margin = 10; // 10 pixels tolerance
    rect.setRect(rect.x() - margin, rect.y() - margin,
        rect.width() + 2 * margin, rect.height() +  2 * margin);

    if ( rect.contains(pos) ) // No click on the title
    {
        // translate the position in a value on the scale 

        double value = 0.0;
        int axis = -1;

        const QwtScaleDraw *sd = scale->scaleDraw();
        switch(scale->position())   
        {
            case QwtScale::Left:
            {
                value = sd->invTransform(pos.y());
                axis = QwtPlot::yLeft;
                break;
            }
            case QwtScale::Right:
            {
                value = sd->invTransform(pos.y());
                axis = QwtPlot::yRight;
                break;
            }
            case QwtScale::Bottom:
            {
                value = sd->invTransform(pos.x());
                axis = QwtPlot::xBottom;
                break;
            }
            case QwtScale::Top:
            {
                value = sd->invTransform(pos.x());
                axis = QwtPlot::xTop;
                break;
            }
        }
        emit clicked(axis, value);
    }
}

// The rect of a scale without the title
QRect ScalePicker::scaleRect(const QwtScale *scale) const
{
    const int bld = scale->baseLineDist();
    const int mjt = scale->scaleDraw()->majTickLength();
    const int sbd = scale->startBorderDist();
    const int ebd = scale->endBorderDist();

    QRect rect;
    switch(scale->position())   
    {
        case QwtScale::Left:
        {
            rect.setRect(scale->width() - bld - mjt, sbd,
                mjt, scale->height() - sbd - ebd);
            break;
        }
        case QwtScale::Right:
        {
            rect.setRect(bld, sbd,
                mjt, scale->height() - sbd - ebd);
            break;
        }
        case QwtScale::Bottom:
        {
            rect.setRect(sbd, bld, 
                scale->width() - sbd - ebd, mjt);
            break;
        }
        case QwtScale::Top:
        {
            rect.setRect(sbd, scale->height() - bld - mjt, 
                scale->width() - sbd - ebd, mjt);
            break;
        }
    }
    return rect;
}
