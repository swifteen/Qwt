#ifdef QWT_QTOPIA
#include <qpe/qpeapplication.h>
#endif
#include <qapplication.h>
#include <qframe.h>
#include <qwt_dimap.h>
#include <qwt_curve.h>
#include <qcolor.h>
#include <qpainter.h>
#include <math.h>

//------------------------------------------------------------
//      curvdemo1
//
//  This example program features some of the different
//  display styles of the QwtCurve class
//------------------------------------------------------------


//
//   Array Sizes
//
const int Size = 27;
const int CurvCnt = 5;

//
//   Arrays holding the values
//
double xval[Size];
double yval[Size];
QwtDiMap xMap; 
QwtDiMap yMap;

class MainWin : public QFrame 
{

public:

    QwtCurve crv[CurvCnt];

public:

    MainWin();
    
protected:

    void drawContents(QPainter *p);
};

MainWin::MainWin(): 
    QFrame()
{
    int i;

    xMap.setDblRange(-0.5, 10.5, 0);
    yMap.setDblRange(-1.1, 1.1, 0);

    //
    //  Frame style
    //  
    setFrameStyle(QFrame::Box|QFrame::Raised);
    setLineWidth(2);
    setMidLineWidth(3);

    //
    // Calculate values
    //
    for(i=0; i<Size;i++)
    {   xval[i] = double(i) * 10.0 / double(Size - 1);
        yval[i] = sin(xval[i]) * cos(2.0 * xval[i]);
    }
    
    //
    //  define curve styles
    // 
    QwtSymbol sym;
    sym.setStyle(QwtSymbol::Cross);
    sym.setPen(Qt::black);
    sym.setSize(5);
    crv[0].setSymbol(sym);
    crv[0].setPen(Qt::darkGreen);
    crv[0].setStyle(QwtCurve::Spline);

    sym.setStyle(QwtSymbol::Ellipse);
    sym.setPen(Qt::blue);
    sym.setBrush(Qt::yellow);
    sym.setSize(5);
    crv[1].setSymbol(sym);
    crv[1].setPen(Qt::red);
    crv[1].setStyle(QwtCurve::Sticks);

    crv[2].setPen(Qt::darkBlue);
    crv[2].setStyle(QwtCurve::Lines);

    crv[3].setPen(Qt::darkCyan);
    crv[3].setStyle(QwtCurve::Steps);

    sym.setStyle(QwtSymbol::XCross);
    sym.setPen(Qt::darkMagenta);
    crv[4].setSymbol(sym);
    crv[4].setStyle(QwtCurve::NoCurve);

    //
    // attach data
    //
    for(i=0;i<CurvCnt;i++)
        crv[i].setRawData(xval,yval,Size);
}


//
//  REDRAW CONTENTS
//
void MainWin::drawContents(QPainter *p)
{
    int deltay,i;

    QRect r = contentsRect();

    deltay = r.height() / CurvCnt - 1;

    r.setHeight(deltay);

    //
    //  draw curves
    //
    for (i=0;i<CurvCnt;i++)
    {
        xMap.setIntRange(r.left(), r.right());
        yMap.setIntRange(r.top(), r.bottom());

        crv[i].draw(p, xMap, yMap);
        r.moveBy(0,deltay);     
    }

    //
    // draw titles
    //
    r = contentsRect();     // reset r
    p->setFont(QFont("Helvetica", 8));
    
	const int alignment = Qt::AlignTop|Qt::AlignHCenter;

    p->setPen(Qt::black);
    p->drawText(0,r.top(),r.width(), p->fontMetrics().height(),
        alignment, "Style: Spline, Symbol: Cross");
    
    r.moveBy(0,deltay);
    p->drawText(0,r.top(),r.width(), p->fontMetrics().height(),
        alignment, "Style: Sticks, Symbol: Ellipse");
    
    r.moveBy(0,deltay);
    p->drawText(0,r.top(),r.width(), p->fontMetrics().height(),
        alignment, "Style: Lines, Symbol: None");
    
    r.moveBy(0,deltay);
    p->drawText(0, r.top(),r.width(), p->fontMetrics().height(),
        alignment, "Style: Steps, Symbol: None");
    
    r.moveBy(0,deltay);
    p->drawText(0,r.top(),r.width(), p->fontMetrics().height(),
        alignment, "Style: NoCurve, Symbol: XCross");
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
    w.resize(300,600);
    w.show();

    return a.exec();
}
