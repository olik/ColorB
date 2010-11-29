#include "colorbwidget.h"
#include "ColorB/CBAreaOutput.h"

ColorBWidget::ColorBWidget(QWidget *parent) : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

ColorBWidget::~ColorBWidget()
{

}

QSize ColorBWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize ColorBWidget::sizeHint() const
{
    return QSize(100, 100);
}

void ColorBWidget::paintEvent(QPaintEvent * /* event */)
{
    CBAreaOutput * areaOutput = (CBAreaOutput *)colorBManager.GetAreas().GetAt(0);
    areaOutput->DrawArea(this);
}
