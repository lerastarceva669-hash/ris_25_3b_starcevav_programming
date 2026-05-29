#include "edgeitem.h"
#include <QtMath>
#include <QPen>

EdgeItem::EdgeItem(const QPointF& from, const QPointF& to, int weight,
                   QGraphicsItem* parent)
    : QGraphicsLineItem(QLineF(from, to), parent)
{
    m_defaultColor = Qt::black;
    setPen(QPen(m_defaultColor, 1.5));
    createArrowHead(from, to);

    // Текст веса посередине
    m_label = new QGraphicsTextItem(QString::number(weight), this);
    QPointF mid = (from + to) / 2.0;
    m_label->setPos(mid.x() - 10, mid.y() - 20);
}

void EdgeItem::createArrowHead(const QPointF& from, const QPointF& to) {
    QLineF line(from, to);
    if (line.length() < 1) return;

    double angle = std::atan2(-line.dy(), line.dx());
    qreal arrowSize = 12;
    QPointF arrowP1 = to + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                   cos(angle - M_PI / 3) * arrowSize);
    QPointF arrowP2 = to + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                   cos(angle - M_PI + M_PI / 3) * arrowSize);

    QPolygonF arrowHead;
    arrowHead << to << arrowP1 << arrowP2;

    m_arrowHead = new QGraphicsPolygonItem(arrowHead, this);
    m_arrowHead->setBrush(Qt::black);
    m_arrowHead->setPen(Qt::NoPen);
}

void EdgeItem::setHighlighted(bool highlight) {
    if (highlight) {
        setPen(QPen(Qt::red, 2.5));
        if (m_arrowHead) m_arrowHead->setBrush(Qt::red);
    } else {
        setPen(QPen(m_defaultColor, 1.5));
        if (m_arrowHead) m_arrowHead->setBrush(m_defaultColor);
    }
}
