#include "graph.h"
#include <queue>
#include <stack>
#include <set>
#include <climits>

Graph::Graph() : n(0) {}

void Graph::initializeDefault() {
    n = 6;
    adj.assign(n, std::vector<int>(n, -1));
    // Рёбра согласно варианту
    addEdge(0, 3, 28);  // 1→4
    addEdge(0, 1, 10);  // 1→2
    addEdge(1, 2, 14);  // 2→3
    addEdge(2, 3, 18);  // 3→4
    addEdge(3, 4, 20);  // 4→5
    addEdge(4, 5, 30);  // 5→6
    addEdge(4, 2, 15);  // 5→3
    addEdge(5, 0, 19);  // 6→1
}

int Graph::vertexCount() const { return n; }

void Graph::addVertex() {
    for (auto& row : adj) {
        row.push_back(-1);
    }
    adj.push_back(std::vector<int>(n + 1, -1));
    n++;
}

void Graph::removeVertex(int index) {
    if (index < 0 || index >= n) return;
    adj.erase(adj.begin() + index);
    for (auto& row : adj) {
        row.erase(row.begin() + index);
    }
    n--;
}

void Graph::addEdge(int from, int to, int weight) {
    if (from >= 0 && from < n && to >= 0 && to < n) {
        adj[from][to] = weight;
    }
}

void Graph::removeEdge(int from, int to) {
    if (from >= 0 && from < n && to >= 0 && to < n) {
        adj[from][to] = -1;
    }
}

int Graph::getWeight(int from, int to) const {
    if (from >= 0 && from < n && to >= 0 && to < n)
        return adj[from][to];
    return -1;
}

std::vector<int> Graph::getNeighbors(int vertex) const {
    std::vector<int> neighbors;
    for (int i = 0; i < n; ++i) {
        if (adj[vertex][i] != -1)
            neighbors.push_back(i);
    }
    return neighbors;
}

const std::vector<std::vector<int>>& Graph::matrix() const {
    return adj;
}

void Graph::setMatrix(const std::vector<std::vector<int>>& mat) {
    adj = mat;
    n = adj.size();
}

// BFS – возвращает порядок посещения вершин
std::vector<int> Graph::bfs(int start) const {
    std::vector<int> visited;
    std::vector<bool> seen(n, false);
    std::queue<int> q;
    q.push(start);
    seen[start] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        visited.push_back(v);
        std::vector<int> neighbors = getNeighbors(v);
        for (int nb : neighbors) {
            if (!seen[nb]) {
                seen[nb] = true;
                q.push(nb);
            }
        }
    }
    return visited;
}

// DFS (нерекурсивный)
std::vector<int> Graph::dfs(int start) const {
    std::vector<int> visited;
    std::vector<bool> seen(n, false);
    std::stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int v = st.top();
        st.pop();
        if (!seen[v]) {
            seen[v] = true;
            visited.push_back(v);
            std::vector<int> neighbors = getNeighbors(v);
            // Кладём в стек в обратном порядке, чтобы обходить как в рекурсии
            for (int i = neighbors.size() - 1; i >= 0; --i) {
                int nb = neighbors[i];
                if (!seen[nb]) {
                    st.push(nb);
                }
            }
        }
    }
    return visited;
}

void Graph::dijkstra(int start,
                     std::vector<int>& dist,
                     std::vector<int>& prev,
                     std::vector<int>& visitOrder) const {
    dist.assign(n, INT_MAX);
    prev.assign(n, -1);
    dist[start] = 0;
    std::set<std::pair<int,int>> pq;
    pq.insert({0, start});
    visitOrder.clear();
    while (!pq.empty()) {
        int d = pq.begin()->first;
        int v = pq.begin()->second;
        pq.erase(pq.begin());
        visitOrder.push_back(v);
        for (int to = 0; to < n; ++to) {
            if (adj[v][to] != -1) {
                int w = adj[v][to];
                if (dist[v] + w < dist[to]) {
                    pq.erase({dist[to], to});
                    dist[to] = dist[v] + w;
                    prev[to] = v;
                    pq.insert({dist[to], to});
                }
            }
        }
    }
}

void Graph::floydWarshall(std::vector<std::vector<int>>& dist,
                          std::vector<std::vector<int>>& next) const {
    dist = adj;
    next.assign(n, std::vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] != -1) {
                next[i][j] = j;
            }
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != -1 && dist[k][j] != -1) {
                    int through = dist[i][k] + dist[k][j];
                    if (dist[i][j] == -1 || through < dist[i][j]) {
                        dist[i][j] = through;
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }
}
