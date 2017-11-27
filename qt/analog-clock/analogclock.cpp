#include <QTimer>
#include <QTime>
#include <QPainter>
#include "analogclock.h"

AnalogClock::AnalogClock(QWidget *parent) :
    QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
    setWindowTitle("Analog Clock");
    resize(200, 200);
    // ui->setupUi(this);
}

void AnalogClock::drawClockHand(QPainter &painter,
                                float rotateDegree,
                                const QPoint * points,
                                unsigned short pointCount,
                                QColor &color)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.save();
    painter.rotate(rotateDegree);
    painter.drawConvexPolygon(points, pointCount);
    painter.restore();
}

void AnalogClock::paintEvent(QPaintEvent *event)
{
    (void)event; // we need not `event`
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };
    static const QPoint secondHand[3] = {
        QPoint(3, 8),
        QPoint(-3, 8),
        QPoint(0, -75),
    };
    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 190);
    QColor secondColor(0, 100, 255, 180);
    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    // setup painter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    // draw clock hour degree
    painter.setPen(hourColor);
    for (int i = -1; i < 12; i++) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }
    // draw clock second degree
    painter.setPen(minuteColor);
    for(int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }

    // draw hour hand
    float rotateDegree = 30.0 * ((time.hour() + time.minute() / 60.0));
    drawClockHand(painter, rotateDegree, hourHand, 3, hourColor);
    // draw minute hand
    rotateDegree = 6.0 * (time.minute() + time.second() / 60.0);
    drawClockHand(painter, rotateDegree, minuteHand, 3, minuteColor);
    // draw second hand
    rotateDegree = 6.0 * time.second();
    drawClockHand(painter, rotateDegree, secondHand, 3, secondColor);
}
