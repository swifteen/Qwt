#include <qgrid.h>
#include <qlayout.h>
#include <qwt_compass.h>
#include <qwt_compass_rose.h>
#include <qwt_dial_needle.h>
#include "compass_grid.h"

CompassGrid::CompassGrid(QWidget *parent):
    QGrid(3, parent)
{
    setBackgroundColor(Qt::gray);

    int i;

    for ( i = 0; i < 6; i++ )
        createCompass(i);

    QGridLayout *l = (QGridLayout *)layout();
    for ( i = 0; i < l->numCols(); i++ )
        l->setColStretch(i, 1);
}

void CompassGrid::createCompass(int pos)
{
    int c;

    QColorGroup colorGroup;
    for ( c = 0; c < QColorGroup::NColorRoles; c++ )
        colorGroup.setColor((QColorGroup::ColorRole)c, QColor());

    colorGroup.setColor(QColorGroup::Base,
        backgroundColor().light(120));
    colorGroup.setColor(QColorGroup::Foreground, 
        colorGroup.color(QColorGroup::Base));

    QwtCompass *compass = new QwtCompass(this);
    compass->setLineWidth(4);
    compass->setFrameShadow(
        pos <= 2 ? QwtCompass::Sunken : QwtCompass::Raised);

    switch(pos)
    {
        case 0:
        {
            /*
              A compass with a rose and no needle. Scale and rose are
              rotating.
             */
            compass->setMode(QwtCompass::RotateScale);

            QwtSimpleCompassRose *rose = new QwtSimpleCompassRose(16, 2);
            rose->setWidth(0.15);

            compass->setRose(rose);
            break;
        }
        case 1:
        {
            /*
              A windrose, with a scale indicating the main directions only
             */
            QMap<double, QString> map;
            map.insert(0.0, "N");
            map.insert(90.0, "E");
            map.insert(180.0, "S");
            map.insert(270.0, "W");

            compass->setLabelMap(map);

            QwtSimpleCompassRose *rose = new QwtSimpleCompassRose(4, 1);
            compass->setRose(rose);

            compass->setNeedle(
                new QwtCompassWindArrow(QwtCompassWindArrow::Style2));
            compass->setValue(60.0);
            break;
        }
        case 2:
        {
            /*
              A compass with a rotating needle in darkBlue. Shows
              a ticks for each degree.
             */

            colorGroup.setColor(QColorGroup::Base, Qt::darkBlue);
            colorGroup.setColor(QColorGroup::Foreground, 
                QColor(Qt::darkBlue).dark(120));
            colorGroup.setColor(QColorGroup::Text, Qt::white);

            compass->setScaleTicks(1, 1, 3);
            compass->setScale(36, 5, 0);

            compass->setNeedle(
                new QwtCompassMagnetNeedle(QwtCompassMagnetNeedle::ThinStyle));
            compass->setValue(220.0);

            break;
        }
        case 3:
        {
            /*
              A compass without a frame, showing numbers as tick labels.
              The origin is at 220.0
             */
            colorGroup.setColor(QColorGroup::Base, backgroundColor());
            colorGroup.setColor(QColorGroup::Foreground, Qt::blue);
                
            compass->setLineWidth(0);

            compass->scaleDraw()->setOptions(compass->scaleDraw()->options() 
                | QwtScaleDraw::Backbone);
            compass->setScaleOptions(QwtDial::ScaleBackbone | 
                QwtDial::ScaleTicks | QwtDial::ScaleLabel);
            compass->setScaleTicks(0, 0, 3);

            QMap<double, QString> map;
            for ( double d = 0.0; d < 360.0; d += 60.0 )
            {
                QString label;
                label.sprintf("%.0f", d);
                map.insert(d, label);
            }
            compass->setLabelMap(map);
            compass->setScale(36, 5, 0);

            compass->setNeedle(new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Ray,
                FALSE, Qt::white));
            compass->setOrigin(220.0);
            compass->setValue(20.0);
            break;
        }
        case 4:
        {
            /*
             A compass showing another needle
             */
            compass->setScaleTicks(0, 0, 3);

            compass->setNeedle(new QwtCompassMagnetNeedle(
                QwtCompassMagnetNeedle::TriangleStyle, Qt::white, Qt::red));
            compass->setValue(220.0);
            break;
        }
        case 5:
        {
            /*
             A compass with a yellow on black ray
             */
            colorGroup.setColor(QColorGroup::Foreground, Qt::black);

            compass->setNeedle(new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Ray,
                FALSE, Qt::yellow));
            compass->setValue(315.0);
            break;
        }
    }

    QPalette palette = compass->palette();
    for ( c = 0; c < QColorGroup::NColorRoles; c++ )
    {
        if ( colorGroup.color((QColorGroup::ColorRole)c).isValid() )
        {
            for ( int cg = 0; cg < QPalette::NColorGroups; cg++ )
            {   
                palette.setColor(
                    (QPalette::ColorGroup)cg, 
                    (QColorGroup::ColorRole)c, 
                    colorGroup.color((QColorGroup::ColorRole)c));
            }
        }
    }

    QColor c1 = backgroundColor();
    for ( int i = 0; i < QPalette::NColorGroups; i++ )
    {
        QPalette::ColorGroup cg = (QPalette::ColorGroup)i;
        QColor c2 = palette.color(cg, QColorGroup::Base);

        const QColor light = 
            palette.color(cg, QColorGroup::Base).light(170);
        const QColor dark = palette.color(cg, QColorGroup::Base).dark(170);
        const QColor mid = compass->frameShadow() == QwtDial::Raised
            ? palette.color(cg, QColorGroup::Base).dark(110)
            : palette.color(cg, QColorGroup::Base).light(110);
    
        palette.setColor(cg, QColorGroup::Dark, dark);
        palette.setColor(cg, QColorGroup::Mid, mid);
        palette.setColor(cg, QColorGroup::Light, light);
    }
    compass->setPalette(palette);
}
