#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include "graph.h"
#include <QVector>
#include <QPair>

// Класс для решения задачи коммивояжера
class TSP_Solver {
private:
    Graph* graph;                          // указатель на граф
    QVector<int> bestPath;                // лучший найденный путь
    int bestCost;                         // стоимость лучшего пути
    QVector<QPair<int, QVector<int>>> steps; // шаги решения для визуализации

    // Вспомогательная структура для хранения узла дерева решений
    struct Node {
        QVector<QVector<int>> reducedMatrix;  // редуцированная матрица
        QVector<int> path;                    // текущий путь
        int cost;                             // стоимость
        int vertex;                           // последняя добавленная вершина
        int level;                            // уровень в дереве
    };

    // Редукция матрицы (вычитание минимальных элементов)
    int reduceMatrix(QVector<QVector<int>>& matrix);

    // Преобразование матрицы для следующего шага
    QVector<QVector<int>> transformMatrix(QVector<QVector<int>> matrix,
                                           int from, int to);

public:
    TSP_Solver();

    void setGraph(Graph* g);
    bool solve();                          // решение задачи
    QVector<int> getBestPath() const;      // получить лучший путь
    int getBestCost() const;               // получить стоимость
    QVector<QPair<int, QVector<int>>> getSteps() const; // получить шаги для анимации
};

#endif // TSP_SOLVER_H
