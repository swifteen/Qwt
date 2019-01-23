#include <math.h>
#ifdef QWT_QTOPIA
#include <qpe/qpeapplication.h>
#endif
#include <qapplication.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qwt_slider.h>
#include "sliders.h"

//------------------------------------------------------------
//      curvdemo1
//
//  This example program features some of the different
//  display styles of the QwtCurve class
//------------------------------------------------------------


SliderDemo::SliderDemo(QWidget *p): QWidget(p)
{
    QwtSlider *sldV1 = new QwtSlider(this, 0,
        Qt::Vertical, QwtSlider::Left, QwtSlider::BgSlot);
    QwtSlider *sldV2 = new QwtSlider(this, 0, 
        Qt::Vertical, QwtSlider::None, QwtSlider::BgTrough);
    QwtSlider *sldV3 = new QwtSlider(this, 0, 
        Qt::Vertical, QwtSlider::Right, QwtSlider::BgBoth);
    
    QwtSlider *sldH1 = new QwtSlider(this, 0, 
        Qt::Horizontal, QwtSlider::Top, QwtSlider::BgTrough);
    QwtSlider *sldH2 = new QwtSlider(this, 0, 
        Qt::Horizontal, QwtSlider::None, QwtSlider::BgBoth);
    QwtSlider *sldH3 = new QwtSlider(this, 0, 
        Qt::Horizontal, QwtSlider::Bottom, QwtSlider::BgSlot);

    //
    //  Slider Properties
    //
    sldV1->setRange(0.0, 100.0, 1.0, 5);
    sldV1->setScaleMaxMinor(5);
    
    sldV2->setRange(0.0,100.0,1.0, 10);

    sldV3->setThumbWidth(20);
    sldV3->setBorderWidth(1);
    sldV3->setRange(0.0, 4.0, 0.01);
    sldV3->setScale(1.0, 1.0e4, TRUE);
    sldV3->setScaleMaxMinor(10);
    
    sldH1->setThumbWidth(10);
    sldH1->setRange(-10.0, 10.0, 1.0, 0); // paging disabled

    sldH2->setRange(0.0, 1.0, 0.01, 5);
    sldH3->setRange(1000.0, 3000.0, 10.0, 10);

    sldH3->setThumbWidth(25);
    sldH3->setThumbLength(12);
    
    QLabel *lblV1 = new QLabel("0.0",this);
    QLabel *lblV2 = new QLabel("0.0",this);
    lblV3 = new QLabel("0.0",this);
    QLabel *lblH1 = new QLabel("0.0",this);
    QLabel *lblH2 = new QLabel("0.0",this);
    QLabel *lblH3 = new QLabel("0.0",this);

    QLabel *lblHTitle = new QLabel("Horizontal Sliders", this);
    QLabel *lblVTitle = new QLabel("Vertical Sliders", this);
    lblHTitle->setFont(QFont("Helvetica", 14, QFont::Bold));
    lblHTitle->setAlignment(Qt::AlignHCenter);
    lblVTitle->setFont(lblHTitle->font());
    lblVTitle->setAlignment(Qt::AlignHCenter);
    
    QGridLayout *lytGrid = new QGridLayout(this, 5,5,10,10);
    
    lytGrid->addMultiCellWidget(lblVTitle, 0,0,0,2);
    lytGrid->addMultiCellWidget(lblHTitle, 0,0,3,4);

    lytGrid->addMultiCellWidget(sldV1, 1,3,0,0, Qt::AlignRight);
    lytGrid->addMultiCellWidget(sldV2, 1,3,1,1, Qt::AlignHCenter);
    lytGrid->addMultiCellWidget(sldV3, 1,3, 2, 2, Qt::AlignLeft);
    
    lytGrid->addWidget(sldH1, 1, 3, Qt::AlignTop);
    lytGrid->addWidget(sldH2, 2, 3, Qt::AlignVCenter);
    lytGrid->addWidget(sldH3, 3, 3, Qt::AlignBottom);

    lblV1->setFixedSize(60,30);
    lblV1->setAlignment(Qt::AlignHCenter);
    lblV2->setFixedSize(60,30);
    lblV2->setAlignment(Qt::AlignHCenter);
    lblV3->setFixedSize(60,30);
    lblV3->setAlignment(Qt::AlignLeft);
    
    lytGrid->addWidget(lblV1, 4, 0, Qt::AlignRight);
    lytGrid->addWidget(lblV2, 4, 1, Qt::AlignHCenter);
    lytGrid->addWidget(lblV3, 4, 2, Qt::AlignLeft);

    lblH1->setFixedWidth(30);
    lblH2->setFixedWidth(30);
    lblH3->setFixedWidth(30);
    lblH1->setAlignment(Qt::AlignVCenter);
    lblH2->setAlignment(Qt::AlignVCenter);
    lblH3->setAlignment(Qt::AlignVCenter);

    lytGrid->addWidget(lblH1, 1, 4, Qt::AlignVCenter);
    lytGrid->addWidget(lblH2, 2, 4, Qt::AlignVCenter);
    lytGrid->addWidget(lblH3, 3, 4, Qt::AlignVCenter);

    lytGrid->setColStretch(0,1);
    lytGrid->setColStretch(1,3);
    lytGrid->setColStretch(2,1);
    lytGrid->setColStretch(3,10);
    lytGrid->setColStretch(4,0);

    lytGrid->setRowStretch(0,1);
    lytGrid->setRowStretch(1,3);
    lytGrid->setRowStretch(2,10);
    lytGrid->setRowStretch(3,3);
    lytGrid->setRowStretch(4,0);

    connect(sldH1, SIGNAL(valueChanged(double)), lblH1, SLOT(setNum(double)));
    connect(sldH2, SIGNAL(valueChanged(double)), lblH2, SLOT(setNum(double)));
    connect(sldH3, SIGNAL(valueChanged(double)), lblH3, SLOT(setNum(double)));
    connect(sldV1, SIGNAL(valueChanged(double)), lblV1, SLOT(setNum(double)));
    connect(sldV2, SIGNAL(valueChanged(double)), lblV2, SLOT(setNum(double)));
    connect(sldV3, SIGNAL(valueChanged(double)), SLOT(setV3(double)));
        
}

void SliderDemo::setV3(double value)
{
    lblV3->setNum(pow(10.0, value));
}

int main (int argc, char **argv)
{
#ifdef QWT_QTOPIA
    QPEApplication a(argc, argv);
#else
    QApplication a(argc, argv);
#endif

    QApplication::setFont(QFont("Helvetica",10));

    SliderDemo w(0);

    a.setMainWidget(&w);
    w.show();

    return a.exec();
}
