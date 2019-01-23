#ifdef QWT_QTOPIA
#include <qpe/qpeapplication.h>
#endif
#include <qapplication.h>
#include <qwt_math.h>
#include <qpainter.h>
#include "curvdemo2.h"


//------------------------------------------------------------
//      curvdemo2
//
//  This example shows a simple animation featuring
//  with several QwtCurves
//
//------------------------------------------------------------

//
//   Array Sizes
//
const int Size = 15;
const int USize = 13;

//
//   Arrays holding the values
//
double xval[Size];
double yval[Size];
double zval[Size];
double uval[USize];
double vval[USize];


//
//  CONSTRUCT MAIN WINDOW
//
MainWin::MainWin(): 
    QFrame()
{
    setFrameStyle(QFrame::Box|QFrame::Raised);
    setLineWidth(2);
    setMidLineWidth(3);
    
    QPalette p = palette();
    p.setColor(QPalette::Normal, QColorGroup::Background, 
        QColor(30,30,50));
    setPalette(p);

    //
    //  curve 1
    // 
    int i = 0;
    xMap[i].setDblRange(-1.5, 1.5 ,0);
    yMap[i].setDblRange(0.0, 6.28, 0);

    curve[i].setPen(QPen(QColor(150,150,200),2));
    curve[i].setSplineSize(150);
    curve[i].setStyle(QwtCurve::Spline,QwtCurve::Xfy);

    QwtSymbol sym;
    sym.setStyle(QwtSymbol::XCross);
    sym.setPen(QPen(Qt::yellow,2));
    sym.setSize(7);
    
    curve[i].setSymbol(sym);

    curve[i].setRawData(yval,xval,Size);
    
    //
    // curve 2
    //
    i++;
    xMap[i].setDblRange(0.0, 6.28, 0);
    yMap[i].setDblRange(-3.0, 1.1,0);
    curve[i].setPen(QPen(QColor(200,150,50), 1, Qt::DashDotDotLine));
    curve[i].setStyle(QwtCurve::Sticks);
    curve[i].setSymbol(QwtSymbol(QwtSymbol::Ellipse,
                 Qt::blue, Qt::yellow, QSize(5,5)));

    curve[i].setRawData(xval,zval,Size);

    
    //
    //  curve 3
    // 
    i++;
    xMap[i].setDblRange(-1.1, 3.0,0);
    yMap[i].setDblRange(-1.1, 3.0,0);
    curve[i].setPen(QColor(100,200,150));
    curve[i].setStyle(QwtCurve::Spline, QwtCurve::Periodic|QwtCurve::Parametric);
    curve[i].setSplineSize(200);

    curve[i].setRawData(yval,zval,Size);

    //
    //  curve 4
    //
    i++;
    xMap[i].setDblRange(-5, 1.1,0);
    yMap[i].setDblRange(-1.1, 5.0,0);
    curve[i].setPen(Qt::red);
    curve[i].setStyle(QwtCurve::Spline);
    curve[i].setSplineSize(200);

    curve[i].setRawData(uval,vval,USize);

    //
    //  initialize values
    //
    double base = 2.0 * M_PI / double(USize - 1);
    double toggle = 1.0; 
    for (i=0; i< USize; i++)
    {
    uval[i] =  toggle * cos( double(i) * base);
    vval[i] =  toggle * sin( double(i) * base);
        
    if (toggle == 1.0)
       toggle = 0.5;
    else
       toggle = 1.0;
    }

    newValues();

    //
    // start timer
    //
    (void)startTimer(250);  
}

void MainWin::drawContents(QPainter *painter)
{
    const QRect &r = contentsRect();

    for ( int i = 0; i < curveCount; i++ )
    {
        xMap[i].setIntRange(r.left(), r.right());
        yMap[i].setIntRange(r.top(), r.bottom());
        curve[i].draw(painter, xMap[i], yMap[i]);
    }
}

//
//  TIMER EVENT
//
void MainWin::timerEvent(QTimerEvent *)
{
    newValues();
    repaint();
}

//
//  RE-CALCULATE VALUES
//
void MainWin::newValues()
{
    int i;
    static double phs = 0.0;
    double s,c,u;
    
    for (i=0;i<Size;i++)
    {
        xval[i] = 6.28 * double(i) / double(Size -1);
        yval[i] = sin(xval[i] - phs);
        zval[i] = cos(3.0 * (xval[i] + phs));
    }
    
    s = 0.25 * sin(phs);
    c = sqrt(1.0 - s*s);
    for (i=0; i<USize;i++)
    {
        u = uval[i];
        uval[i] = uval[i] * c - vval[i] * s;
        vval[i] = vval[i] * c + u * s;
    }
    
    phs += 0.0628;
    if (phs > 6.28)
       phs = 0.0;
    
}

int main (int argc, char **argv)
{
#ifdef QWT_QTOPIA
    QPEApplication a(argc, argv);
#else
    QApplication a(argc, argv);
#endif

    MainWin w;

    a.setMainWidget(&w);
    w.resize(300,300);
    w.show();

    return a.exec();
}
