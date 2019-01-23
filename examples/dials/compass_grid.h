#include <qgrid.h>

class CompassGrid: public QGrid
{
public:
    CompassGrid(QWidget *parent);

private:
	void createCompass(int pos);
};
