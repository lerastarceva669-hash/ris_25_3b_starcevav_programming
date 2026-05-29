#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QTimer>
#include "graph.h"

// Класс для отображения вершины графа
class VertexItem : public QGraphicsEllipseItem {
private:
    int vertexNumber;
    QGraphicsTextItem* label;

public:
    VertexItem(int number, qreal x, qreal y, qreal radius = 20);
    int getVertexNumber() const;
    void updatePosition(qreal x, qreal y);
    QGraphicsTextItem* getLabel() { return label; }
};

// Класс для отображения ребра графа
class EdgeItem : public QGraphicsLineItem {
private:
    int fromVertex;
    int toVertex;
    QGraphicsTextItem* weightLabel;

public:
    EdgeItem(int from, int to, int weight, QPointF start, QPointF end);
    int getFromVertex() const;
    int getToVertex() const;
    void updateWeight(int newWeight);
    void updatePosition(QPointF start, QPointF end);
};

// Главный класс для визуализации графа
class GraphWidget : public QGraphicsView {
    Q_OBJECT

private:
    QGraphicsScene* scene;
    Graph* graph;
    QVector<VertexItem*> vertexItems;
    QVector<EdgeItem*> edgeItems;

    bool isAddingEdge;          // режим добавления ребра
    int firstSelectedVertex;    // первая выбранная вершина для ребра
    bool isMovingVertex;        // режим перемещения вершины
    int movingVertexIndex;      // индекс перемещаемой вершины
    QPointF lastMousePos;       // последняя позиция мыши в координатах сцены

    // Для анимации пути
    QVector<QGraphicsLineItem*> pathLines;
    QTimer* animationTimer;
    int currentStep;
    QVector<int> pathToAnimate;

    void drawGraph();
    void drawEdge(int from, int to);
    void updateEdgesForVertex(int vertexIndex);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

public:
    GraphWidget(QWidget* parent = nullptr);
    ~GraphWidget();

    void setGraph(Graph* g);
    void updateGraph();
    void setAddingEdgeMode(bool mode);
    void animatePath(QVector<int> path);

signals:
    void vertexSelected(int vertex);
    void edgeAdded(int from, int to, int weight);
    void vertexMoved(int vertex, QPointF newPos);
};

#endif // GRAPHWIDGET_H
