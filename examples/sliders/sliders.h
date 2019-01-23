#include <qwidget.h>

class QLabel;

class SliderDemo : public QWidget
{
    Q_OBJECT
public:
    SliderDemo(QWidget *p);

private slots:
    void setV3(double);

private:
    QLabel *lblV3;
};
