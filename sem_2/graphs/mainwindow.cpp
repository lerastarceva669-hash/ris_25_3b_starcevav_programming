#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация графа по варианту
    graph.initializeDefault();

    // ui->graphicsView теперь сразу GraphWidget* (продвинут в ui)
    ui->graphicsView->setGraph(&graph);
    ui->graphicsView->drawGraph();

    updateMatrixTable();
    updateSpinRanges();

    // Сигналы кнопок редактирования
    connect(ui->addVertexBtn, &QPushButton::clicked, this, &MainWindow::onAddVertex);
    connect(ui->removeVertexBtn, &QPushButton::clicked, this, &MainWindow::onRemoveVertex);
    connect(ui->addEdgeBtn, &QPushButton::clicked, this, &MainWindow::onAddEdge);
    connect(ui->removeEdgeBtn, &QPushButton::clicked, this, &MainWindow::onRemoveEdge);
    connect(ui->applyMatrixBtn, &QPushButton::clicked, this, &MainWindow::onApplyMatrix);

    // Сигналы алгоритмов
    connect(ui->bfsBtn, &QPushButton::clicked, this, &MainWindow::onBFS);
    connect(ui->dfsBtn, &QPushButton::clicked, this, &MainWindow::onDFS);
    connect(ui->dijkstraBtn, &QPushButton::clicked, this, &MainWindow::onDijkstra);
    connect(ui->floydBtn, &QPushButton::clicked, this, &MainWindow::onFloyd);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateMatrixTable() {
    int n = graph.vertexCount();
    ui->matrixTable->setRowCount(n);
    ui->matrixTable->setColumnCount(n);
    QStringList headers;
    for (int i = 1; i <= n; ++i) headers << QString::number(i);
    ui->matrixTable->setHorizontalHeaderLabels(headers);
    ui->matrixTable->setVerticalHeaderLabels(headers);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w = graph.getWeight(i, j);
            QTableWidgetItem* item = new QTableWidgetItem();
            if (w == -1) {
                item->setText("∞");
            } else {
                item->setText(QString::number(w));
            }
            item->setTextAlignment(Qt::AlignCenter);
            ui->matrixTable->setItem(i, j, item);
        }
    }
}

void MainWindow::updateSpinRanges() {
    int n = graph.vertexCount();
    ui->removeVertexSpin->setMaximum(n);
    ui->fromSpin->setMaximum(n);
    ui->toSpin->setMaximum(n);
    ui->startVertexSpin->setMaximum(n);
}

void MainWindow::onAddVertex() {
    graph.addVertex();
    ui->graphicsView->drawGraph();
    updateMatrixTable();
    updateSpinRanges();
}

void MainWindow::onRemoveVertex() {
    int index = ui->removeVertexSpin->value() - 1; // 0-based
    if (index < 0 || index >= graph.vertexCount()) return;
    graph.removeVertex(index);
    ui->graphicsView->drawGraph();
    updateMatrixTable();
    updateSpinRanges();
}

void MainWindow::onAddEdge() {
    int from = ui->fromSpin->value() - 1;
    int to = ui->toSpin->value() - 1;
    int weight = ui->weightSpin->value();
    if (from < 0 || from >= graph.vertexCount() || to < 0 || to >= graph.vertexCount()) return;
    graph.addEdge(from, to, weight);
    ui->graphicsView->drawGraph();
    updateMatrixTable();
}

void MainWindow::onRemoveEdge() {
    int from = ui->fromSpin->value() - 1;
    int to = ui->toSpin->value() - 1;
    graph.removeEdge(from, to);
    ui->graphicsView->drawGraph();
    updateMatrixTable();
}

void MainWindow::onApplyMatrix() {
    int n = graph.vertexCount();
    // Считываем всю таблицу
    std::vector<std::vector<int>> newMat(n, std::vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            QTableWidgetItem* item = ui->matrixTable->item(i, j);
            if (item) {
                QString text = item->text().trimmed();
                if (text == "∞" || text.isEmpty()) {
                    newMat[i][j] = -1;
                } else {
                    bool ok;
                    int w = text.toInt(&ok);
                    if (ok && w > 0)
                        newMat[i][j] = w;
                    else
                        newMat[i][j] = -1;
                }
            }
        }
    }
    graph.setMatrix(newMat);
    ui->graphicsView->drawGraph();
    updateMatrixTable();
    updateSpinRanges();
}

void MainWindow::onBFS() {
    if (ui->graphicsView->isAnimating()) return;
    int start = ui->startVertexSpin->value() - 1;
    ui->graphicsView->animateBFS(start);
    ui->resultLabel->setText("BFS запущен...");
}

void MainWindow::onDFS() {
    if (ui->graphicsView->isAnimating()) return;
    int start = ui->startVertexSpin->value() - 1;
    ui->graphicsView->animateDFS(start);
    ui->resultLabel->setText("DFS запущен...");
}

void MainWindow::onDijkstra() {
    if (ui->graphicsView->isAnimating()) return;
    int start = ui->startVertexSpin->value() - 1;
    ui->graphicsView->animateDijkstra(start);
    // Вычислим результат для вывода
    std::vector<int> dist, prev, order;
    graph.dijkstra(start, dist, prev, order);
    QString res = "Дейкстра от вершины " + QString::number(start+1) + ":\n";
    for (int i = 0; i < graph.vertexCount(); ++i) {
        if (dist[i] == INT_MAX)
            res += "до " + QString::number(i+1) + " нет пути\n";
        else
            res += "до " + QString::number(i+1) + " = " + QString::number(dist[i]) + "\n";
    }
    ui->resultLabel->setText(res);
}

void MainWindow::onFloyd() {
    std::vector<std::vector<int>> dist, next;
    graph.floydWarshall(dist, next);
    int n = graph.vertexCount();

    // Покажем матрицу расстояний в диалоговом окне
    QDialog* dlg = new QDialog(this);
    dlg->setWindowTitle("Флойд – матрица кратчайших расстояний");
    QVBoxLayout* lay = new QVBoxLayout(dlg);
    QTextEdit* text = new QTextEdit(dlg);
    text->setReadOnly(true);
    QString result;
    result += "Матрица расстояний:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == -1) result += " ∞";
            else result += " " + QString::number(dist[i][j]);
        }
        result += "\n";
    }
    result += "\nМатрица next (следующая вершина):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (next[i][j] == -1) result += " -";
            else result += " " + QString::number(next[i][j] + 1);
        }
        result += "\n";
    }
    text->setPlainText(result);
    lay->addWidget(text);
    QDialogButtonBox* btn = new QDialogButtonBox(QDialogButtonBox::Ok, dlg);
    connect(btn, &QDialogButtonBox::accepted, dlg, &QDialog::accept);
    lay->addWidget(btn);
    dlg->resize(400, 500);
    dlg->exec();
    delete dlg;
}
