#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_ 1

#include <qmainwindow.h>
#include <qtoolbutton.h>

class QSpinBox;
class QPushButton;
class RandomPlot;

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private slots:
    void showRunning(bool);
    void appendPoints(bool);

private:
    QToolBar *toolBar();
    void initWhatsThis();

private:
    QSpinBox *d_randomCount;
    QSpinBox *d_timerCount;
    QToolButton *d_startBtn;
    QToolButton *d_clearBtn;

    RandomPlot *d_plot;
};

#endif
