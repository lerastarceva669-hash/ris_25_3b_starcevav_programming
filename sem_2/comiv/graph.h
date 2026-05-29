#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <QPointF>
#include <climits>

// Структура для хранения ребра графа
struct Edge {
    int from;       // от какой вершины
    int to;         // к какой вершине
    int weight;     // вес ребра

    Edge() {
        from = 0;
        to = 0;
        weight = 0;
    }

    Edge(int f, int t, int w) {
        from = f;
        to = t;
        weight = w;
    }
};

// Класс для хранения графа
class Graph {
private:
    int vertexCount;                           // количество вершин
    QVector<QVector<int>> adjacencyMatrix;     // матрица смежности
    QVector<QPointF> vertexPositions;          // координаты вершин для отрисовки
    QVector<Edge> edges;                       // список всех ребер

public:
    Graph();

    void setVertexCount(int count);
    int getVertexCount() const;

    void addEdge(int from, int to, int weight);
    void removeEdge(int from, int to);
    bool hasEdge(int from, int to) const;
    int getWeight(int from, int to) const;

    void setVertexPosition(int vertex, QPointF pos);
    QPointF getVertexPosition(int vertex) const;

    QVector<Edge> getAllEdges() const;
    QVector<QVector<int>> getMatrix() const;

    bool isComplete() const;  // проверка на полноту графа
    void clear();
};

#endif // GRAPH_H
