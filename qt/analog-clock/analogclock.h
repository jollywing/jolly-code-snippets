#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>

class AnalogClock : public QWidget
{
    Q_OBJECT

public:
    explicit AnalogClock(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    void drawClockHand(QPainter &painter, float rotateDegree,
                       const QPoint * points, unsigned short pointCount,
                       QColor &color);
};

#endif // ANALOGCLOCK_H
