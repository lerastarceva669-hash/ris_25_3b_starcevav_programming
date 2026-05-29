#include "vertexitem.h"
#include <QPen>
#include <QFont>

VertexItem::VertexItem(int id, const QPointF& center, qreal radius,
                       QGraphicsItem* parent)
    : QGraphicsEllipseItem(center.x() - radius, center.y() - radius,
                           2 * radius, 2 * radius, parent),
      m_id(id)
{
    m_defaultColor = QColor(200, 200, 200);   // светло-серый
    setBrush(QBrush(m_defaultColor));
    setPen(QPen(Qt::black, 2));

    m_label = new QGraphicsTextItem(QString::number(id + 1), this);
    m_label->setPos(center.x() - m_label->boundingRect().width() / 2,
                    center.y() - m_label->boundingRect().height() / 2);
}

void VertexItem::setHighlighted(bool highlight) {
    if (highlight) {
        setBrush(QBrush(Qt::yellow));
    } else {
        setBrush(QBrush(m_defaultColor));
    }
}
