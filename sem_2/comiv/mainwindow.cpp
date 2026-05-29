#include "mainwindow.h"
#include <QMessageBox>
#include <QGroupBox>
#include <QTimer>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    // Создаем объекты
    graph = new Graph();
    solver = new TSP_Solver();

    // Настраиваем интерфейс
    setupUI();
    createConnections();

    // Настраиваем окно
    setWindowTitle("Задача коммивояжера - Метод ветвей и границ");
    resize(1000, 700);
}

MainWindow::~MainWindow() {
    delete graph;
    delete solver;
}

void MainWindow::setupUI() {
    // Создаем центральный виджет
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Создаем основной горизонтальный layout
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // Левая панель с управлением
    QVBoxLayout* leftPanel = new QVBoxLayout();

    // Группа "Создание графа"
    QGroupBox* createGroup = new QGroupBox("Создание графа");
    QVBoxLayout* createLayout = new QVBoxLayout(createGroup);

    QLabel* vertexLabel = new QLabel("Количество вершин:");
    vertexCountSpinBox = new QSpinBox();
    vertexCountSpinBox->setRange(2, 10);
    vertexCountSpinBox->setValue(6);

    createGraphButton = new QPushButton("Создать граф");
    createGraphButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px; }");

    createLayout->addWidget(vertexLabel);
    createLayout->addWidget(vertexCountSpinBox);
    createLayout->addWidget(createGraphButton);
    leftPanel->addWidget(createGroup);

    // Группа "Редактирование"
    QGroupBox* editGroup = new QGroupBox("Редактирование графа");
    QVBoxLayout* editLayout = new QVBoxLayout(editGroup);

    addEdgeButton = new QPushButton("Добавить ребро");
    addEdgeButton->setStyleSheet("QPushButton { background-color: #2196F3; color: white; padding: 8px; }");

    clearGraphButton = new QPushButton("Очистить граф");
    clearGraphButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; padding: 8px; }");

    QLabel* instructionLabel = new QLabel("Инструкция:\n1. Создайте граф\n2. Добавьте все ребра\n3. Нажмите 'Найти путь'");
    instructionLabel->setStyleSheet("QLabel { color: #666; padding: 5px; }");

    editLayout->addWidget(addEdgeButton);
    editLayout->addWidget(clearGraphButton);
    editLayout->addWidget(instructionLabel);
    leftPanel->addWidget(editGroup);

    // Группа "Решение"
    QGroupBox* solveGroup = new QGroupBox("Решение задачи");
    QVBoxLayout* solveLayout = new QVBoxLayout(solveGroup);

    solveButton = new QPushButton("Найти кратчайший путь");
    solveButton->setStyleSheet("QPushButton { background-color: #FF9800; color: white; padding: 8px; font-weight: bold; }");

    resultText = new QTextEdit();
    resultText->setReadOnly(true);
    resultText->setMaximumHeight(250);
    resultText->setStyleSheet("QTextEdit { background-color: #f5f5f5; }");

    solveLayout->addWidget(solveButton);
    solveLayout->addWidget(resultText);
    leftPanel->addWidget(solveGroup);

    // Статусная строка
    statusLabel = new QLabel("Готов к работе");
    statusLabel->setStyleSheet("QLabel { padding: 5px; background-color: #e0e0e0; border-radius: 3px; }");
    leftPanel->addWidget(statusLabel);

    leftPanel->addStretch();

    // Правая панель с визуализацией графа
    QVBoxLayout* rightPanel = new QVBoxLayout();

    QLabel* graphLabel = new QLabel("Визуализация графа:");
    graphLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");

    graphWidget = new GraphWidget();
    graphWidget->setMinimumSize(600, 500);
    graphWidget->setStyleSheet("QGraphicsView { border: 2px solid #ccc; background-color: white; }");

    rightPanel->addWidget(graphLabel);
    rightPanel->addWidget(graphWidget);

    // Добавляем панели в основной layout
    mainLayout->addLayout(leftPanel, 1);
    mainLayout->addLayout(rightPanel, 3);
}

void MainWindow::createConnections() {
    // Подключаем сигналы и слоты
    connect(createGraphButton, &QPushButton::clicked, this, &MainWindow::onCreateGraph);
    connect(addEdgeButton, &QPushButton::clicked, this, &MainWindow::onAddEdge);
    connect(clearGraphButton, &QPushButton::clicked, this, &MainWindow::onClearGraph);
    connect(solveButton, &QPushButton::clicked, this, &MainWindow::onSolve);

    connect(graphWidget, &GraphWidget::vertexMoved, this, &MainWindow::onVertexMoved);
    connect(graphWidget, &GraphWidget::edgeAdded, this, &MainWindow::onEdgeAdded);
}

void MainWindow::onCreateGraph() {
    int vertexCount = vertexCountSpinBox->value();

    // Создаем граф
    graph->setVertexCount(vertexCount);
    graphWidget->setGraph(graph);

    statusLabel->setText(QString("Создан граф с %1 вершинами. Добавьте все ребра.").arg(vertexCount));
    resultText->clear();
}

void MainWindow::onAddEdge() {
    if (graph->getVertexCount() == 0) {
        QMessageBox::warning(this, "Предупреждение", "Сначала создайте граф!");
        return;
    }

    // Переключаем режим добавления ребер
    bool isAddingMode = addEdgeButton->text() == "Добавить ребро";

    if (isAddingMode) {
        addEdgeButton->setText("Режим: кликните 2 вершины");
        addEdgeButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px; }");
        graphWidget->setAddingEdgeMode(true);

        // Через 5 секунд возвращаем кнопку в исходное состояние
        QTimer::singleShot(5000, this, [this]() {
            addEdgeButton->setText("Добавить ребро");
            addEdgeButton->setStyleSheet("QPushButton { background-color: #2196F3; color: white; padding: 8px; }");
            graphWidget->setAddingEdgeMode(false);
        });
    }
}

void MainWindow::onClearGraph() {
    graph->clear();
    graphWidget->setGraph(graph);
    resultText->clear();
    statusLabel->setText("Граф очищен. Создайте новый граф.");
}

void MainWindow::onSolve() {
    if (graph->getVertexCount() == 0) {
        QMessageBox::warning(this, "Предупреждение", "Сначала создайте граф!");
        return;
    }

    if (!graph->isComplete()) {
        QMessageBox::warning(this, "Предупреждение",
                             "Граф должен быть полным! Все вершины должны быть связаны друг с другом.");
        return;
    }

    // Решаем задачу
    solver->setGraph(graph);

    if (solver->solve()) {
        QVector<int> bestPath = solver->getBestPath();
        int bestCost = solver->getBestCost();

        // Выводим результат
        updateResultText();

        // Запускаем анимацию пути
        graphWidget->animatePath(bestPath);

        statusLabel->setText(QString("Найден оптимальный путь! Длина: %1").arg(bestCost));
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось найти решение!");
    }
}

void MainWindow::updateResultText() {
    QVector<int> bestPath = solver->getBestPath();
    int bestCost = solver->getBestCost();
    QVector<QPair<int, QVector<int>>> steps = solver->getSteps();

    QString text = "=== РЕЗУЛЬТАТ РЕШЕНИЯ ===\n\n";

    text += "Оптимальный путь:\n";
    for (int i = 0; i < bestPath.size(); i++) {
        text += QString::number(bestPath[i] + 1);
        if (i < bestPath.size() - 1) {
            text += " -> ";
        }
    }

    text += QString("\n\nДлина пути: %1\n\n").arg(bestCost);

    text += "=== ШАГИ РЕШЕНИЯ ===\n";
    int stepsToShow = steps.size();
    if (stepsToShow > 15) {
        stepsToShow = 15;  // показываем не более 15 шагов
    }

    for (int i = 0; i < stepsToShow; i++) {
        text += QString("Шаг %1: стоимость = %2, путь: ")
                .arg(i + 1).arg(steps[i].first);

        for (int j = 0; j < steps[i].second.size(); j++) {
            text += QString::number(steps[i].second[j] + 1);
            if (j < steps[i].second.size() - 1) {
                text += "-";
            }
        }
        text += "\n";
    }

    if (steps.size() > 15) {
        text += "...\n(показаны первые 15 шагов)";
    }

    resultText->setText(text);
}

void MainWindow::onVertexMoved(int vertex, QPointF pos) {
    // Обновляем позицию вершины в графе
    graph->setVertexPosition(vertex, pos);
}

void MainWindow::onEdgeAdded(int from, int to, int weight) {
    statusLabel->setText(QString("Добавлено ребро %1-%2 с весом %3")
                        .arg(from + 1).arg(to + 1).arg(weight));
}
