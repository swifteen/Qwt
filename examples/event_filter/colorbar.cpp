#include <qevent.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qpainter.h>
#include "colorbar.h"

ColorBar::ColorBar(Qt::Orientation o, QWidget *parent, const char *name):
    QWidget(parent, name),
    d_orientation(o),
    d_light(Qt::white),
    d_dark(Qt::black)
{
    setCursor(Qt::pointingHandCursor);
}

void ColorBar::setOrientation(Qt::Orientation o)
{
    d_orientation = o;
    update();
}

void ColorBar::setLight(const QColor &light)
{
    d_light = light;
    update();
}

void ColorBar::setDark(const QColor &dark)
{
    d_dark = dark;
    update();
}

void ColorBar::setRange(const QColor &light, const QColor &dark)
{
    d_light = light;
    d_dark = dark;
    update();
}

void ColorBar::mousePressEvent(QMouseEvent *e)
{
    if( e->button() ==  Qt::LeftButton )
    {
        // emit the color of the position where the mouse click
        // happened

        const QPixmap pm = QPixmap::grabWidget(this);
        const QRgb rgb = pm.convertToImage().pixel(e->x(), e->y());
    
        emit selected(QColor(rgb));
#if QT_VERSION >= 300
        e->accept();
#endif
    }
}

void ColorBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawColorBar(&painter, rect());
}

void ColorBar::drawColorBar(QPainter *painter, const QRect &rect) const
{
    int h1, s1, v1;
    int h2, s2, v2;

    d_light.hsv(&h1, &s1, &v1);
    d_dark.hsv(&h2, &s2, &v2);

    painter->save();
    painter->setClipRect(rect);
    painter->setClipping(TRUE);

    painter->fillRect(rect, d_dark);

    const int sectionSize = 2;
    
    int numIntervalls;
    if ( d_orientation == Qt::Horizontal )
        numIntervalls = rect.width() / sectionSize;
    else
        numIntervalls = rect.height() / sectionSize;

    for ( int i = 0; i < numIntervalls; i++ )
    {
        QRect section;
        if ( d_orientation == Qt::Horizontal )
        {
            section.setRect(rect.x() + i * sectionSize, rect.y(),
                sectionSize, rect.height());
        }
        else
        {
            section.setRect(rect.x(), rect.y() + i * sectionSize,
                rect.width(), sectionSize);
        }

        const double ratio = i / (double)numIntervalls;
        const QColor c(h1 + qRound(ratio * (h2 - h1)),
            s1 + qRound(ratio * (s2 - s1)),
            v1 + qRound(ratio * (v2 - v1)),
            QColor::Hsv);

        painter->fillRect(section, c);
    }

    painter->restore();
}
