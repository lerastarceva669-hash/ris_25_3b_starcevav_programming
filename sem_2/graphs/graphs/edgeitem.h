#ifndef EDGEITEM_H
#define EDGEITEM_H

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsPolygonItem>
#include <QPen>

class EdgeItem : public QGraphicsLineItem {
public:
    EdgeItem(const QPointF& from, const QPointF& to, int weight,
             QGraphicsItem* parent = nullptr);

    void setIds(int fromId, int toId) { m_fromId = fromId; m_toId = toId; }
    int fromId() const { return m_fromId; }
    int toId() const { return m_toId; }

    void setHighlighted(bool highlight);

private:
    void createArrowHead(const QPointF& from, const QPointF& to);

    int m_fromId = -1;
    int m_toId = -1;
    QGraphicsTextItem* m_label;
    QGraphicsPolygonItem* m_arrowHead;
    QColor m_defaultColor;
};

#endif // EDGEITEM_H
