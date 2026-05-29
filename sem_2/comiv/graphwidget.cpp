#include "graphwidget.h"
#include <QInputDialog>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <cmath>

// Конструктор вершины
VertexItem::VertexItem(int number, qreal x, qreal y, qreal radius) {
    vertexNumber = number;
    setRect(-radius, -radius, radius * 2, radius * 2);
    setPos(x, y);  // Устанавливаем позицию вершины

    // Устанавливаем цвет вершины
    setBrush(QColor(100, 150, 255));
    setPen(QPen(Qt::black, 2));

    // Отключаем стандартное перемещение Qt
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);

    // Создаем метку с номером вершины
    label = new QGraphicsTextItem(QString::number(number + 1));
    label->setPos(-5, -10);
    label->setDefaultTextColor(Qt::white);
    label->setParentItem(this);

    // Устанавливаем Z-значение, чтобы вершины были поверх ребер
    setZValue(1);
}

int VertexItem::getVertexNumber() const {
    return vertexNumber;
}

void VertexItem::updatePosition(qreal x, qreal y) {
    setPos(x, y);
}

// Конструктор ребра
EdgeItem::EdgeItem(int from, int to, int weight, QPointF start, QPointF end) {
    fromVertex = from;
    toVertex = to;

    setLine(start.x(), start.y(), end.x(), end.y());
    setPen(QPen(Qt::darkGray, 2));

    // Создаем метку с весом ребра
    QPointF labelPos((start.x() + end.x()) / 2, (start.y() + end.y()) / 2);
    weightLabel = new QGraphicsTextItem(QString::number(weight));
    weightLabel->setPos(labelPos.x() - 10, labelPos.y() - 10);
    weightLabel->setDefaultTextColor(Qt::red);
    weightLabel->setParentItem(this);

    // Устанавливаем Z-значение, чтобы ребра были под вершинами
    setZValue(0);
}

int EdgeItem::getFromVertex() const {
    return fromVertex;
}

int EdgeItem::getToVertex() const {
    return toVertex;
}

void EdgeItem::updateWeight(int newWeight) {
    weightLabel->setPlainText(QString::number(newWeight));
}

void EdgeItem::updatePosition(QPointF start, QPointF end) {
    setLine(start.x(), start.y(), end.x(), end.y());
    QPointF labelPos((start.x() + end.x()) / 2, (start.y() + end.y()) / 2);
    weightLabel->setPos(labelPos.x() - 10, labelPos.y() - 10);
}

// Конструктор виджета графа
GraphWidget::GraphWidget(QWidget* parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);
    setScene(scene);

    graph = nullptr;
    isAddingEdge = false;
    firstSelectedVertex = -1;
    isMovingVertex = false;
    movingVertexIndex = -1;
    currentStep = 0;

    animationTimer = new QTimer(this);

    // Настраиваем отображение
    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Включаем отслеживание мыши
    setMouseTracking(true);
}

GraphWidget::~GraphWidget() {
    // Сцена удаляется автоматически при удалении виджета
}

void GraphWidget::setGraph(Graph* g) {
    graph = g;
    updateGraph();
}

void GraphWidget::updateGraph() {
    // Очищаем сцену
    scene->clear();
    vertexItems.clear();
    edgeItems.clear();
    pathLines.clear();

    if (graph == nullptr) {
        return;
    }

    // Рисуем граф
    drawGraph();
}

void GraphWidget::drawGraph() {
    int vertexCount = graph->getVertexCount();

    // Рисуем ребра СНАЧАЛА, чтобы они были под вершинами
    QVector<Edge> edges = graph->getAllEdges();
    for (int i = 0; i < edges.size(); i++) {
        int from = edges[i].from;
        int to = edges[i].to;
        int weight = edges[i].weight;

        QPointF start = graph->getVertexPosition(from);
        QPointF end = graph->getVertexPosition(to);

        EdgeItem* edge = new EdgeItem(from, to, weight, start, end);
        scene->addItem(edge);
        edgeItems.append(edge);
    }

    // Рисуем вершины ПОТОМ, чтобы они были поверх ребер
    for (int i = 0; i < vertexCount; i++) {
        QPointF pos = graph->getVertexPosition(i);
        VertexItem* vertex = new VertexItem(i, pos.x(), pos.y());
        scene->addItem(vertex);
        vertexItems.append(vertex);
    }
}

void GraphWidget::updateEdgesForVertex(int vertexIndex) {
    // Обновляем все ребра, связанные с данной вершиной
    for (int i = 0; i < edgeItems.size(); i++) {
        if (edgeItems[i]->getFromVertex() == vertexIndex) {
            QPointF start = graph->getVertexPosition(vertexIndex);
            QPointF end = graph->getVertexPosition(edgeItems[i]->getToVertex());
            edgeItems[i]->updatePosition(start, end);
        } else if (edgeItems[i]->getToVertex() == vertexIndex) {
            QPointF start = graph->getVertexPosition(edgeItems[i]->getFromVertex());
            QPointF end = graph->getVertexPosition(vertexIndex);
            edgeItems[i]->updatePosition(start, end);
        }
    }
}

void GraphWidget::drawEdge(int from, int to) {
    // Проверяем, что ребро еще не существует
    bool edgeExists = false;
    int existingIndex = -1;

    for (int i = 0; i < edgeItems.size(); i++) {
        if ((edgeItems[i]->getFromVertex() == from && edgeItems[i]->getToVertex() == to) ||
            (edgeItems[i]->getFromVertex() == to && edgeItems[i]->getToVertex() == from)) {
            edgeExists = true;
            existingIndex = i;
            break;
        }
    }

    if (edgeExists) {
        // Ребро уже есть, удаляем его
        QGraphicsItem* item = dynamic_cast<QGraphicsItem*>(edgeItems[existingIndex]);
        scene->removeItem(item);
        delete edgeItems[existingIndex];
        edgeItems.removeAt(existingIndex);
        graph->removeEdge(from, to);
        return;
    }

    // Запрашиваем вес ребра
    bool ok;
    int weight = QInputDialog::getInt(this, "Вес ребра",
                                       "Введите вес ребра:", 5, 1, 999, 1, &ok);

    if (ok) {
        // Добавляем ребро в граф
        graph->addEdge(from, to, weight);

        // Рисуем ребро
        QPointF start = graph->getVertexPosition(from);
        QPointF end = graph->getVertexPosition(to);

        EdgeItem* edge = new EdgeItem(from, to, weight, start, end);
        scene->addItem(edge);
        edgeItems.append(edge);

        emit edgeAdded(from, to, weight);
    }
}

void GraphWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        // Преобразуем координаты мыши в координаты сцены
        QPoint mousePos = event->pos();
        QPointF scenePos = mapToScene(mousePos);

        // Проверяем, попали ли по элементу сцены
        QGraphicsItem* item = scene->itemAt(scenePos, transform());

        if (item != nullptr) {
            VertexItem* vertex = nullptr;

            // Проверяем, является ли элемент вершиной
            vertex = dynamic_cast<VertexItem*>(item);

            // Если нет, проверяем родительский элемент
            if (vertex == nullptr && item->parentItem() != nullptr) {
                vertex = dynamic_cast<VertexItem*>(item->parentItem());
            }

            if (vertex != nullptr) {
                int vertexNumber = vertex->getVertexNumber();

                if (isAddingEdge) {
                    // Режим добавления ребра
                    if (firstSelectedVertex == -1) {
                        // Выбираем первую вершину
                        firstSelectedVertex = vertexNumber;
                        vertex->setBrush(QColor(255, 200, 100));
                        vertex->update();
                    } else {
                        // Выбираем вторую вершину и создаем ребро
                        if (firstSelectedVertex != vertexNumber) {
                            drawEdge(firstSelectedVertex, vertexNumber);
                        }

                        // Сбрасываем выбор
                        if (firstSelectedVertex >= 0 && firstSelectedVertex < vertexItems.size()) {
                            vertexItems[firstSelectedVertex]->setBrush(QColor(100, 150, 255));
                            vertexItems[firstSelectedVertex]->update();
                        }
                        firstSelectedVertex = -1;
                    }
                } else {
                    // Начинаем перемещение вершины
                    isMovingVertex = true;
                    movingVertexIndex = vertexNumber;
                    lastMousePos = scenePos;  // Запоминаем позицию в координатах сцены

                    // Меняем курсор
                    setCursor(Qt::ClosedHandCursor);

                    emit vertexSelected(vertexNumber);
                }

                return;  // Не передаем событие дальше
            }
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void GraphWidget::mouseMoveEvent(QMouseEvent* event) {
    if (isMovingVertex && movingVertexIndex >= 0 && movingVertexIndex < vertexItems.size()) {
        // Преобразуем координаты мыши в координаты сцены
        QPoint mousePos = event->pos();
        QPointF currentScenePos = mapToScene(mousePos);

        // Вычисляем смещение
        QPointF delta = currentScenePos - lastMousePos;

        // Получаем текущую позицию вершины
        QPointF currentPos = graph->getVertexPosition(movingVertexIndex);

        // Вычисляем новую позицию
        QPointF newPos = currentPos + delta;

        // Ограничиваем перемещение в пределах сцены
        if (newPos.x() < 30) newPos.setX(30);
        if (newPos.x() > 770) newPos.setX(770);
        if (newPos.y() < 30) newPos.setY(30);
        if (newPos.y() > 570) newPos.setY(570);

        // Обновляем позицию вершины в графе
        graph->setVertexPosition(movingVertexIndex, newPos);

        // Обновляем позицию вершины на сцене
        vertexItems[movingVertexIndex]->updatePosition(newPos.x(), newPos.y());

        // Обновляем все связанные ребра
        updateEdgesForVertex(movingVertexIndex);

        // Запоминаем текущую позицию в координатах сцены
        lastMousePos = currentScenePos;

        emit vertexMoved(movingVertexIndex, newPos);

        return;  // Не передаем событие дальше
    }

    QGraphicsView::mouseMoveEvent(event);
}

void GraphWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && isMovingVertex) {
        isMovingVertex = false;
        movingVertexIndex = -1;

        // Возвращаем обычный курсор
        setCursor(Qt::ArrowCursor);

        return;  // Не передаем событие дальше
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void GraphWidget::setAddingEdgeMode(bool mode) {
    isAddingEdge = mode;

    if (mode) {
        setCursor(Qt::CrossCursor);  // Меняем курсор для режима добавления
    } else {
        setCursor(Qt::ArrowCursor);

        if (firstSelectedVertex != -1) {
            // Сбрасываем выбор вершины
            if (firstSelectedVertex >= 0 && firstSelectedVertex < vertexItems.size()) {
                vertexItems[firstSelectedVertex]->setBrush(QColor(100, 150, 255));
                vertexItems[firstSelectedVertex]->update();
            }
            firstSelectedVertex = -1;
        }
    }
}

void GraphWidget::animatePath(QVector<int> path) {
    // Удаляем предыдущую анимацию
    for (int i = 0; i < pathLines.size(); i++) {
        scene->removeItem(pathLines[i]);
        delete pathLines[i];
    }
    pathLines.clear();

    if (path.size() < 2) {
        return;
    }

    pathToAnimate = path;
    currentStep = 0;

    // Отключаем предыдущие соединения таймера
    disconnect(animationTimer, SIGNAL(timeout()), nullptr, nullptr);

    // Создаем новое соединение для анимации
    connect(animationTimer, &QTimer::timeout, this, [this]() {
        if (currentStep < pathToAnimate.size() - 1) {
            int from = pathToAnimate[currentStep];
            int to = pathToAnimate[currentStep + 1];

            if (from < graph->getVertexCount() && to < graph->getVertexCount()) {
                QPointF start = graph->getVertexPosition(from);
                QPointF end = graph->getVertexPosition(to);

                // Создаем цветную линию для пути
                QGraphicsLineItem* line = new QGraphicsLineItem();
                line->setLine(start.x(), start.y(), end.x(), end.y());

                // Выбираем цвет в зависимости от шага
                QPen pen;
                pen.setWidth(3);

                if (currentStep == 0) {
                    pen.setColor(QColor(0, 200, 0));  // зеленый для начала
                } else if (currentStep == pathToAnimate.size() - 2) {
                    pen.setColor(QColor(200, 0, 0));  // красный для конца
                } else {
                    pen.setColor(QColor(0, 0, 200));  // синий для середины
                }

                line->setPen(pen);
                line->setZValue(0.5);  // между ребрами и вершинами
                scene->addItem(line);
                pathLines.append(line);
            }

            currentStep++;
        } else {
            animationTimer->stop();
        }
    });

    animationTimer->start(500);  // задержка 500 мс между шагами
}
