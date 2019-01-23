#ifdef QWT_QTOPIA
#include <qpe/qpeapplication.h>
#endif
#include <qapplication.h>
#include "tunerfrm.h"
#include "ampfrm.h"
#include "radio.h"

MainWin::MainWin(): QWidget()
{
    TunerFrame *frmTuner = new TunerFrame(this);
    frmTuner->setFrameStyle(QFrame::Panel|QFrame::Raised);

    AmpFrame *frmAmp = new AmpFrame(this);
    frmAmp->setFrameStyle(QFrame::Panel|QFrame::Raised);
    setFixedSize(720,240);

    frmTuner->move(0,0);
    frmAmp->move(0,120);
    
    connect(frmTuner, SIGNAL(fieldChanged(double)), 
        frmAmp, SLOT(setMaster(double)));

    frmTuner->setFreq(90.0);    
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
    w.show();

    return a.exec();
}











