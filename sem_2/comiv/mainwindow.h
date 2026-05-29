#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include "graph.h"
#include "graphwidget.h"
#include "tsp_solver.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Graph* graph;
    GraphWidget* graphWidget;
    TSP_Solver* solver;

    // Элементы интерфейса
    QSpinBox* vertexCountSpinBox;
    QPushButton* createGraphButton;
    QPushButton* addEdgeButton;
    QPushButton* clearGraphButton;
    QPushButton* solveButton;
    QTextEdit* resultText;
    QLabel* statusLabel;

    void setupUI();
    void createConnections();
    void updateResultText();

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onCreateGraph();
    void onAddEdge();
    void onClearGraph();
    void onSolve();
    void onVertexMoved(int vertex, QPointF pos);
    void onEdgeAdded(int from, int to, int weight);
};

#endif // MAINWINDOW_H
