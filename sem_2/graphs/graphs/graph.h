#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
public:
    Graph();

    // Инициализация графа по варианту (6 вершин)
    void initializeDefault();

    int vertexCount() const;
    void addVertex();
    void removeVertex(int index);    // index: 0..n-1
    void addEdge(int from, int to, int weight);
    void removeEdge(int from, int to);
    int getWeight(int from, int to) const;
    std::vector<int> getNeighbors(int vertex) const;

    const std::vector<std::vector<int>>& matrix() const;
    void setMatrix(const std::vector<std::vector<int>>& mat);

    // Алгоритмы (возвращают порядок посещения или списки рёбер для анимации)
    std::vector<int> bfs(int start) const;
    std::vector<int> dfs(int start) const;
    void dijkstra(int start,
                  std::vector<int>& dist,
                  std::vector<int>& prev,
                  std::vector<int>& visitOrder) const;
    void floydWarshall(std::vector<std::vector<int>>& dist,
                       std::vector<std::vector<int>>& next) const;

private:
    int n;                                    // количество вершин (0..n-1)
    std::vector<std::vector<int>> adj;        // -1 – нет ребра
};

#endif // GRAPH_H
