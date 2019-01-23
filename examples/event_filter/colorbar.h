#include <qwidget.h>

class ColorBar: public QWidget
{
    Q_OBJECT
    Q_PROPERTY( Orientation orientation READ orientation WRITE setOrientation )
    Q_PROPERTY( QColor light READ light WRITE setLight )
    Q_PROPERTY( QColor dark READ dark WRITE setDark )

public:
    ColorBar(Qt::Orientation = Qt::Horizontal, 
        QWidget * = NULL, const char *name = 0);

    virtual void setOrientation(Orientation o);
    Orientation orientation() const { return d_orientation; }

    void setRange(const QColor &light, const QColor &dark);
    void setLight(const QColor &light);
    void setDark(const QColor &dark);

    QColor light() const { return d_light; }
    QColor dark() const { return d_dark; }

signals:
    void selected(const QColor &);

protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);

    void drawColorBar(QPainter *, const QRect &) const;

private:
    Qt::Orientation d_orientation;
    QColor d_light;
    QColor d_dark;
};
