#ifndef VERTEXITEM_H
#define VERTEXITEM_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QBrush>

class VertexItem : public QGraphicsEllipseItem {
public:
    VertexItem(int id, const QPointF& center, qreal radius = 25,
               QGraphicsItem* parent = nullptr);

    void setHighlighted(bool highlight);
    int vertexId() const { return m_id; }

private:
    int m_id;
    QGraphicsTextItem* m_label;
    QColor m_defaultColor;
};

#endif // VERTEXITEM_H
