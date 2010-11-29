#ifndef COLORBWIDGET_H
#define COLORBWIDGET_H

#include <QWidget>
#include "ColorB/CBManager.h"

class ColorBWidget : public QWidget
{
Q_OBJECT

public:
    explicit ColorBWidget(QWidget *parent = 0);
    ~ColorBWidget();

private:
    void paintEvent(QPaintEvent *event);

private:
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

private:
    CBManager colorBManager;

signals:

public slots:

};

#endif // COLORBWIDGET_H
