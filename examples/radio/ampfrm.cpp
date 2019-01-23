#include "ampfrm.h"
#include <qwt_knob.h>
#include <qlabel.h>
#include <qfont.h>
#include <qwt_thermo.h>
#include <qwt_math.h>

AmpFrame::AmpFrame(QWidget *p, const char *name): 
    QFrame(p, name)
{
    setFont(QFont("Helvetica", 10, QFont::Bold));

    knbVolume = new QwtKnob(this);
    knbBass = new QwtKnob(this);
    knbBalance = new QwtKnob(this);
    knbTreble = new QwtKnob(this);

    QLabel *lblVolume = new QLabel("Volume",this);
    QLabel *lblTreble = new QLabel("Treble", this);
    QLabel *lblBass = new QLabel("Bass", this);
    QLabel *lblBalance = new QLabel("Balance", this);

    knbVolume->setRange(0.0,10,0.1);
    knbBalance->setRange(-10.0, 10.0,0.1);
    knbBalance->setScaleMaxMajor(10);
    knbTreble->setRange(-10.0, 10.0, 0.1);
    knbTreble->setScaleMaxMajor(10);
    knbBass->setRange(-10.0, 10.0,0.1);
    knbBass->setScaleMaxMajor(10);
    
    knbVolume->setGeometry(20,10,100,100);
    knbVolume->setValue(2.0);
    lblVolume->setGeometry(20,100,100,15);
    lblVolume->setAlignment(Qt::AlignCenter);
    knbVolume->setScaleMaxMajor(10);
    
    knbBalance->setGeometry(140,10,100,100);
    lblBalance->setGeometry(140,100,100,15);
    lblBalance->setAlignment(Qt::AlignCenter);

    knbTreble->setGeometry(260,10,100,100);
    lblTreble->setGeometry(260,100,100,15);
    lblTreble->setAlignment(Qt::AlignCenter);

    knbBass->setGeometry(380,10,100,100);
    lblBass->setGeometry(380,100,100,15);
    lblBass->setAlignment(Qt::AlignCenter);

    QLabel *lblLeft = new QLabel("Left [dB]",this);
    QLabel *lblRight = new QLabel("Right [dB]", this);
    
    thmLeft = new QwtThermo(this);
    thmRight = new QwtThermo(this);

    thmLeft->setGeometry(540,10,60,90);
    thmLeft->setPipeWidth(6);
    thmLeft->setRange(-40,10);
    thmLeft->setFillColor(Qt::green);
    thmLeft->setAlarmColor(Qt::red);
    thmLeft->setAlarmLevel(0.0);
    thmLeft->setAlarmEnabled(TRUE);
    
    thmRight->setGeometry(610,10,60,90);
    thmRight->setPipeWidth(6);
    thmRight->setRange(-40,10);
    thmRight->setFillColor(Qt::green);
    thmRight->setAlarmColor(Qt::red);
    thmRight->setAlarmLevel(0.0);
    thmRight->setAlarmEnabled(TRUE);
    
    lblLeft->setGeometry(550,100, 60,15);
    lblRight->setGeometry(620,100,60,15);
    
    setFixedSize(720,120);
    (void)startTimer(50);    
}

void AmpFrame::timerEvent(QTimerEvent *)
{
    double sig_l, sig_r, sig_bass, sig_mid_l, sig_mid_r, sig_trbl_l, sig_trbl_r;
    double balance;
    static double phs = 0;
    
    //
    //	This amplifier generates its own input signal...
    //

    sig_bass = (1.0 + 0.1 * knbBass->value()) *  sin(13.0 * phs);
    sig_mid_l = sin(17.0 * phs);
    sig_mid_r = cos(17.5 * phs);
    sig_trbl_l = 0.5 * (1.0 + 0.1 * knbTreble->value()) * sin(35.0 * phs);
    sig_trbl_r = 0.5 * (1.0 + 0.1 * knbTreble->value()) * sin(34.0 * phs);

    sig_l = 0.05 * master * knbVolume->value() * qwtSqr(sig_bass + sig_mid_l + sig_trbl_l);
    sig_r = 0.05 * master * knbVolume->value() * qwtSqr(sig_bass + sig_mid_r + sig_trbl_r);
    
    balance = 0.1 * knbBalance->value(); 
    if (balance > 0) 
       sig_l *= (1.0 - balance);
    else
       sig_r *= (1.0 + balance);

    if (sig_l > 0.01)
       sig_l = 20.0 * log10(sig_l);
    else
       sig_l = -40.0;

    if (sig_r > 0.01)
       sig_r = 20.0 * log10(sig_r);
    else
       sig_r = - 40.0; 
    thmLeft->setValue(sig_l);
    thmRight->setValue(sig_r);

    phs += M_PI / 100;
    if (phs > M_PI) phs = 0;
}

void AmpFrame::setMaster(double v)
{
    master = v;
}
