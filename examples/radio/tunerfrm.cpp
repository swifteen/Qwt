#include "tunerfrm.h"
#include <qlabel.h>
#include <qwt_wheel.h>
#include <qwt_slider.h>
#include <qwt_thermo.h>
#include <qwt_math.h>

TunerFrame::TunerFrame(QWidget *p, const char *name): 
	QFrame(p, name)
{
    QLabel *lblTune = new QLabel("Tuning",this);
    whlFreq = new QwtWheel(this);
    thmTune = new QwtThermo(this);
    sldFreq = new QwtSlider(this, "", Qt::Horizontal, QwtSlider::Top);

    setFixedSize(720,120);
    sldFreq->setGeometry(30,10,660,60);
    sldFreq->setScaleMaxMinor(5);
    sldFreq->setScaleMaxMajor(12);
    sldFreq->setThumbLength(80);
    sldFreq->setBorderWidth(1);
    thmTune->setGeometry(30,80,90,20);
    lblTune->setGeometry(30,100,90,15);
    lblTune->setAlignment(Qt::AlignCenter);
    whlFreq->setGeometry(540,80,150,30);
    whlFreq->setMass(0.5);
    whlFreq->setRange(87.5, 108, 0.01);
    whlFreq->setTotalAngle(3600.0);
    sldFreq->setRange(87.5, 108, 0.01, 10);
    thmTune->setOrientation(Qt::Horizontal, QwtThermo::None);
    thmTune->setRange(0.0, 1.0);
    thmTune->setFillColor(Qt::green);

    connect(whlFreq, SIGNAL(valueChanged(double)), SLOT(adjustFreq(double)));
    connect(sldFreq, SIGNAL(valueChanged(double)), SLOT(adjustFreq(double)));

}

void TunerFrame::adjustFreq(double frq)
{
    double x, field;
    static double factor = 13.0 / (108 - 87.5);

    x = (frq - 87.5)  * factor;
    field = qwtSqr(sin(x) * cos(4.0 * x));
    
    thmTune->setValue(field);  

    if (sldFreq->value() != frq) sldFreq->setValue(frq);
    if (whlFreq->value() != frq) whlFreq->setValue(frq);
    emit fieldChanged(field);	
}

void TunerFrame::setFreq(double frq)
{
    whlFreq->setValue(frq);
}










