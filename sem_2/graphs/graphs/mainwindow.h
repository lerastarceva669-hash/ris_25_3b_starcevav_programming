#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include "graphwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddVertex();
    void onRemoveVertex();
    void onAddEdge();
    void onRemoveEdge();
    void onApplyMatrix();

    void onBFS();
    void onDFS();
    void onDijkstra();
    void onFloyd();

    void updateMatrixTable();
    void updateSpinRanges();

private:
    Ui::MainWindow *ui;
    Graph graph;
    // Указатель на продвинутый виджет уже есть в ui->graphicsView
    GraphWidget* graphWidget() const;
};

#endif // MAINWINDOW_H
