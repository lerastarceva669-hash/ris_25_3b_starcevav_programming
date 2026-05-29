#include "graph.h"
#include <cmath>

Graph::Graph() {
    vertexCount = 0;
}

void Graph::setVertexCount(int count) {
    vertexCount = count;

    // Создаем матрицу смежности и заполняем нулями
    adjacencyMatrix.clear();
    adjacencyMatrix.resize(count);
    for (int i = 0; i < count; i++) {
        adjacencyMatrix[i].resize(count);
        for (int j = 0; j < count; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    // Создаем начальные позиции для вершин по кругу
    vertexPositions.clear();
    vertexPositions.resize(count);
    double centerX = 300;
    double centerY = 250;
    double radius = 180;

    for (int i = 0; i < count; i++) {
        double angle = 2 * M_PI * i / count - M_PI / 2;
        double x = centerX + radius * cos(angle);
        double y = centerY + radius * sin(angle);
        vertexPositions[i] = QPointF(x, y);
    }
}

int Graph::getVertexCount() const {
    return vertexCount;
}

void Graph::addEdge(int from, int to, int weight) {
    if (from >= 0 && from < vertexCount && to >= 0 && to < vertexCount) {
        adjacencyMatrix[from][to] = weight;
        adjacencyMatrix[to][from] = weight;  // граф неориентированный

        // Проверяем, нет ли уже такого ребра
        bool edgeExists = false;
        for (int i = 0; i < edges.size(); i++) {
            if ((edges[i].from == from && edges[i].to == to) ||
                (edges[i].from == to && edges[i].to == from)) {
                edgeExists = true;
                edges[i].weight = weight;  // обновляем вес
                break;
            }
        }

        // Если ребра нет, добавляем новое
        if (!edgeExists) {
            Edge edge(from, to, weight);
            edges.append(edge);
        }
    }
}

void Graph::removeEdge(int from, int to) {
    if (from >= 0 && from < vertexCount && to >= 0 && to < vertexCount) {
        adjacencyMatrix[from][to] = 0;
        adjacencyMatrix[to][from] = 0;

        // Удаляем ребро из списка
        for (int i = 0; i < edges.size(); i++) {
            if ((edges[i].from == from && edges[i].to == to) ||
                (edges[i].from == to && edges[i].to == from)) {
                edges.removeAt(i);
                break;
            }
        }
    }
}

bool Graph::hasEdge(int from, int to) const {
    if (from >= 0 && from < vertexCount && to >= 0 && to < vertexCount) {
        return adjacencyMatrix[from][to] > 0;
    }
    return false;
}

int Graph::getWeight(int from, int to) const {
    if (from >= 0 && from < vertexCount && to >= 0 && to < vertexCount) {
        return adjacencyMatrix[from][to];
    }
    return 0;
}

void Graph::setVertexPosition(int vertex, QPointF pos) {
    if (vertex >= 0 && vertex < vertexCount) {
        vertexPositions[vertex] = pos;
    }
}

QPointF Graph::getVertexPosition(int vertex) const {
    if (vertex >= 0 && vertex < vertexCount) {
        return vertexPositions[vertex];
    }
    return QPointF(0, 0);
}

QVector<Edge> Graph::getAllEdges() const {
    return edges;
}

QVector<QVector<int>> Graph::getMatrix() const {
    return adjacencyMatrix;
}

bool Graph::isComplete() const {
    // Проверяем, что граф полный (все вершины связаны)
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (i != j && adjacencyMatrix[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void Graph::clear() {
    vertexCount = 0;
    adjacencyMatrix.clear();
    vertexPositions.clear();
    edges.clear();
}
