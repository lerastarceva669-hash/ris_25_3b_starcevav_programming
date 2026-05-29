#include "tsp_solver.h"
#include <climits>
#include <QDebug>

TSP_Solver::TSP_Solver() {
    graph = nullptr;
    bestCost = INT_MAX;
}

void TSP_Solver::setGraph(Graph* g) {
    graph = g;
}

int TSP_Solver::reduceMatrix(QVector<QVector<int>>& matrix) {
    int totalReduction = 0;
    int size = matrix.size();

    // Вычитаем минимумы из строк
    for (int i = 0; i < size; i++) {
        int minInRow = INT_MAX;

        // Находим минимальный элемент в строке
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] >= 0 && matrix[i][j] < minInRow) {
                minInRow = matrix[i][j];
            }
        }

        // Если нашли минимум и он не бесконечность
        if (minInRow != INT_MAX && minInRow > 0) {
            totalReduction = totalReduction + minInRow;

            // Вычитаем минимум из всех элементов строки
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] >= 0) {
                    matrix[i][j] = matrix[i][j] - minInRow;
                }
            }
        }
    }

    // Вычитаем минимумы из столбцов
    for (int j = 0; j < size; j++) {
        int minInCol = INT_MAX;

        // Находим минимальный элемент в столбце
        for (int i = 0; i < size; i++) {
            if (matrix[i][j] >= 0 && matrix[i][j] < minInCol) {
                minInCol = matrix[i][j];
            }
        }

        // Если нашли минимум и он не бесконечность
        if (minInCol != INT_MAX && minInCol > 0) {
            totalReduction = totalReduction + minInCol;

            // Вычитаем минимум из всех элементов столбца
            for (int i = 0; i < size; i++) {
                if (matrix[i][j] >= 0) {
                    matrix[i][j] = matrix[i][j] - minInCol;
                }
            }
        }
    }

    return totalReduction;
}

QVector<QVector<int>> TSP_Solver::transformMatrix(QVector<QVector<int>> matrix,
                                                    int from, int to) {
    int size = matrix.size();
    QVector<QVector<int>> newMatrix = matrix;

    // Запрещаем обратный путь
    newMatrix[to][from] = -1;

    // Запрещаем строку from и столбец to
    for (int i = 0; i < size; i++) {
        newMatrix[from][i] = -1;
        newMatrix[i][to] = -1;
    }

    return newMatrix;
}

bool TSP_Solver::solve() {
    // Проверяем, что граф существует и он полный
    if (graph == nullptr || !graph->isComplete()) {
        return false;
    }

    bestPath.clear();
    bestCost = INT_MAX;
    steps.clear();

    int size = graph->getVertexCount();
    QVector<QVector<int>> matrix = graph->getMatrix();

    // Заменяем диагональные элементы на -1 (бесконечность)
    for (int i = 0; i < size; i++) {
        matrix[i][i] = -1;
    }

    // Создаем корневой узел
    Node root;
    root.reducedMatrix = matrix;
    root.path.append(0);  // начинаем с вершины 0
    root.cost = reduceMatrix(root.reducedMatrix);
    root.vertex = 0;
    root.level = 0;

    // Сохраняем первый шаг
    QPair<int, QVector<int>> firstStep;
    firstStep.first = root.cost;
    firstStep.second = root.path;
    steps.append(firstStep);

    // Очередь для хранения узлов
    QVector<Node> queue;
    queue.append(root);

    // Пока есть узлы для обработки
    while (!queue.isEmpty()) {
        // Находим узел с минимальной стоимостью
        int minIndex = 0;
        int minCost = queue[0].cost;

        for (int i = 1; i < queue.size(); i++) {
            if (queue[i].cost < minCost) {
                minCost = queue[i].cost;
                minIndex = i;
            }
        }

        // Извлекаем узел с минимальной стоимостью
        Node currentNode = queue[minIndex];
        queue.removeAt(minIndex);

        // Если достигли всех вершин
        if (currentNode.level == size - 1) {
            // Добавляем возврат в начальную вершину
            int returnCost = graph->getWeight(currentNode.vertex, 0);
            int totalCost = currentNode.cost + returnCost;

            QVector<int> completePath = currentNode.path;
            completePath.append(0);

            // Сохраняем шаг
            QPair<int, QVector<int>> step;
            step.first = totalCost;
            step.second = completePath;
            steps.append(step);

            // Проверяем, лучше ли этот путь
            if (totalCost < bestCost) {
                bestCost = totalCost;
                bestPath = completePath;
            }
            continue;
        }

        // Перебираем все возможные следующие вершины
        for (int nextVertex = 0; nextVertex < size; nextVertex++) {
            // Пропускаем уже посещенные вершины
            bool alreadyVisited = false;
            for (int i = 0; i < currentNode.path.size(); i++) {
                if (currentNode.path[i] == nextVertex) {
                    alreadyVisited = true;
                    break;
                }
            }

            // Пропускаем недоступные ребра
            if (alreadyVisited || currentNode.reducedMatrix[currentNode.vertex][nextVertex] < 0) {
                continue;
            }

            // Создаем новый узел
            Node newNode;
            newNode.level = currentNode.level + 1;
            newNode.path = currentNode.path;
            newNode.path.append(nextVertex);
            newNode.vertex = nextVertex;

            // Вычисляем стоимость
            int edgeCost = graph->getWeight(currentNode.vertex, nextVertex);
            newNode.reducedMatrix = transformMatrix(currentNode.reducedMatrix,
                                                     currentNode.vertex, nextVertex);
            int reduction = reduceMatrix(newNode.reducedMatrix);
            newNode.cost = currentNode.cost + edgeCost + reduction;

            // Сохраняем шаг
            QPair<int, QVector<int>> step;
            step.first = newNode.cost;
            step.second = newNode.path;
            steps.append(step);

            // Добавляем узел в очередь
            queue.append(newNode);
        }
    }

    return !bestPath.isEmpty();
}

QVector<int> TSP_Solver::getBestPath() const {
    return bestPath;
}

int TSP_Solver::getBestCost() const {
    return bestCost;
}

QVector<QPair<int, QVector<int>>> TSP_Solver::getSteps() const {
    return steps;
}
