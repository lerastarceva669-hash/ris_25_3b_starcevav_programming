#include "graphwidget.h"
#include <QtMath>
#include <QQueue>
#include <QStack>
#include <set>
#include <climits>

GraphWidget::GraphWidget(QWidget* parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);

    animTimer = new QTimer(this);
    connect(animTimer, &QTimer::timeout, this, &GraphWidget::nextAnimationStep);
}

void GraphWidget::setGraph(Graph* g) {
    graph = g;
}

void GraphWidget::drawGraph() {
    if (!graph) return;
    clearGraph();

    int n = graph->vertexCount();
    qreal radius = 150;
    QPointF center(0, 0);

    // Вершины по кругу
    for (int i = 0; i < n; ++i) {
        qreal angle = 2.0 * M_PI * i / n - M_PI / 2.0;
        QPointF pos(center.x() + radius * cos(angle),
                    center.y() + radius * sin(angle));
        VertexItem* v = new VertexItem(i, pos, 25);
        scene->addItem(v);
        vertexItems.append(v);
    }

    // Рёбра
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w = graph->getWeight(i, j);
            if (w != -1) {
                QPointF fromCenter = vertexItems[i]->sceneBoundingRect().center();
                QPointF toCenter = vertexItems[j]->sceneBoundingRect().center();
                QLineF line(fromCenter, toCenter);
                qreal len = line.length();
                qreal r = 25;
                QPointF p1 = fromCenter + (toCenter - fromCenter) * (r / len);
                QPointF p2 = toCenter - (toCenter - fromCenter) * (r / len);

                EdgeItem* edge = new EdgeItem(p1, p2, w);
                edge->setIds(i, j);
                scene->addItem(edge);
                edgeItems.append(edge);
                edgeMap[qMakePair(i, j)] = edge;
            }
        }
    }
    scene->setSceneRect(scene->itemsBoundingRect().adjusted(-20, -20, 20, 20));
}

void GraphWidget::clearGraph() {
    for (auto item : vertexItems) {
        scene->removeItem(item);
        delete item;
    }
    vertexItems.clear();
    for (auto item : edgeItems) {
        scene->removeItem(item);
        delete item;
    }
    edgeItems.clear();
    edgeMap.clear();
}

QPointF GraphWidget::vertexPosition(int index) const {
    if (index >= 0 && index < vertexItems.size())
        return vertexItems[index]->sceneBoundingRect().center();
    return QPointF();
}

bool GraphWidget::isAnimating() const {
    return animTimer->isActive();
}

void GraphWidget::animateBFS(int start) {
    if (!graph || isAnimating()) return;
    QList<AnimStep> steps;
    int n = graph->vertexCount();
    QVector<bool> seen(n, false);
    QQueue<int> q;
    q.enqueue(start);
    seen[start] = true;
    steps.append({AnimStep::VisitVertex, start, -1, -1});

    while (!q.empty()) {
        int v = q.dequeue();
        std::vector<int> neighbors = graph->getNeighbors(v);
        for (int nb : neighbors) {
            if (!seen[nb]) {
                seen[nb] = true;
                q.enqueue(nb);
                steps.append({AnimStep::TraverseEdge, -1, v, nb});
                steps.append({AnimStep::VisitVertex, nb, -1, -1});
            }
        }
        // Помечаем завершение обработки вершины (чтобы убрать подсветку)
        steps.append({AnimStep::FinishVertex, v, -1, -1});
    }
    runAnimation(steps);
}

void GraphWidget::animateDFS(int start) {
    if (!graph || isAnimating()) return;
    QList<AnimStep> steps;
    int n = graph->vertexCount();
    QVector<bool> seen(n, false);
    QStack<int> st;
    st.push(start);
    while (!st.empty()) {
        int v = st.pop();
        if (!seen[v]) {
            seen[v] = true;
            steps.append({AnimStep::VisitVertex, v, -1, -1});
            std::vector<int> neighbors = graph->getNeighbors(v);
            for (int i = neighbors.size() - 1; i >= 0; --i) {
                int nb = neighbors[i];
                if (!seen[nb]) {
                    st.push(nb);
                    // Ребро будет пройдено позже, но мы можем добавить шаг
                    steps.append({AnimStep::TraverseEdge, -1, v, nb});
                }
            }
            steps.append({AnimStep::FinishVertex, v, -1, -1});
        }
    }
    runAnimation(steps);
}

void GraphWidget::animateDijkstra(int start) {
    if (!graph || isAnimating()) return;
    QList<AnimStep> steps;
    int n = graph->vertexCount();
    std::vector<int> dist, prev, order;
    graph->dijkstra(start, dist, prev, order);

    // Формируем шаги: когда вершина финализируется – показываем её
    for (int v : order) {
        steps.append({AnimStep::VisitVertex, v, -1, -1});
        // Если есть предок, покажем пройденное ребро (релаксация уже выполнена)
        if (prev[v] != -1) {
            steps.append({AnimStep::TraverseEdge, -1, prev[v], v});
        }
        steps.append({AnimStep::FinishVertex, v, -1, -1});
    }
    runAnimation(steps);
}

void GraphWidget::runAnimation(const QList<AnimStep>& steps) {
    resetHighlights();
    animSteps = steps;
    currentStep = 0;
    if (!animSteps.isEmpty()) {
        animTimer->start(600);
    }
}

void GraphWidget::nextAnimationStep() {
    if (currentStep >= animSteps.size()) {
        animTimer->stop();
        // Через секунду после окончания сбросим подсветку
        QTimer::singleShot(2000, this, &GraphWidget::resetHighlights);
        return;
    }

    const AnimStep& step = animSteps[currentStep];
    if (step.type == AnimStep::VisitVertex) {
        if (step.vertex >= 0 && step.vertex < vertexItems.size())
            vertexItems[step.vertex]->setHighlighted(true);
    }
    else if (step.type == AnimStep::FinishVertex) {
        if (step.vertex >= 0 && step.vertex < vertexItems.size())
            vertexItems[step.vertex]->setHighlighted(false);
    }
    else if (step.type == AnimStep::TraverseEdge) {
        auto it = edgeMap.find(qMakePair(step.from, step.to));
        if (it != edgeMap.end()) {
            it.value()->setHighlighted(true);
            // Запустим таймер, чтобы через 300 мс убрать подсветку ребра
            QTimer::singleShot(300, this, [this, edge = it.value()]() {
                if (edge) edge->setHighlighted(false);
            });
        }
    }
    currentStep++;
}

void GraphWidget::resetHighlights() {
    for (auto v : vertexItems) v->setHighlighted(false);
    for (auto e : edgeItems) e->setHighlighted(false);
}
