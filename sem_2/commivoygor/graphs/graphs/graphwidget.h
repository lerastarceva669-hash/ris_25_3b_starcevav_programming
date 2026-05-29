#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QMap>
#include <QPair>
#include <QList>

#include "graph.h"
#include "vertexitem.h"
#include "edgeitem.h"

struct AnimStep {
    enum Type { VisitVertex, FinishVertex, TraverseEdge };
    Type type;
    int vertex;   // для Visit/Finish
    int from;     // для TraverseEdge
    int to;
};

class GraphWidget : public QGraphicsView {
    Q_OBJECT
public:
    explicit GraphWidget(QWidget* parent = nullptr);

    void setGraph(Graph* g);
    void drawGraph();

    void animateBFS(int start);
    void animateDFS(int start);
    void animateDijkstra(int start);

    bool isAnimating() const;

public slots:
    void nextAnimationStep();

private:
    void clearGraph();
    void runAnimation(const QList<AnimStep>& steps);
    void resetHighlights();
    QPointF vertexPosition(int index) const;

    Graph* graph = nullptr;
    QGraphicsScene* scene = nullptr;
    QList<VertexItem*> vertexItems;
    QList<EdgeItem*> edgeItems;
    QMap<QPair<int,int>, EdgeItem*> edgeMap;   // (from, to) -> ребро

    QTimer* animTimer = nullptr;
    QList<AnimStep> animSteps;
    int currentStep = 0;
};

#endif // GRAPHWIDGET_H
