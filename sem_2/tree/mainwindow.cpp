#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treewidget.h"
#include <QMessageBox>
#include <cstring>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаём виджет для рисования и вставляем его на место treeWidget в UI
    treeWidget = new TreeWidget(this);
    // Заменяем "заглушку" treeWidget из UI на наш TreeWidget
    if (ui->treeWidget->layout() == nullptr) {
        // Создаём layout для parent'а если его нет
        QVBoxLayout* lay = new QVBoxLayout(ui->treeWidget);
        lay->setContentsMargins(0,0,0,0);
        lay->addWidget(treeWidget);
    }
    treeWidget->setTree(&tree);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Вставка узла
void MainWindow::on_insertButton_clicked() {
    QString keyStr = ui->keyLineEdit->text();
    if (keyStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ключ!");
        return;
    }
    bool ok;
    int key = keyStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Ключ должен быть числом!");
        return;
    }
    QString dataStr = ui->dataLineEdit->text();
    if (dataStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите данные!");
        return;
    }
    QByteArray ba = dataStr.toLocal8Bit();
    const char* data = ba.constData();

    tree.insert(key, data);
    ui->keyLineEdit->clear();
    ui->dataLineEdit->clear();
    ui->resultTextEdit->append("Узел с ключом " + QString::number(key) + " добавлен");
    treeWidget->update();   // перерисовать дерево
}

// Удаление узла
void MainWindow::on_deleteButton_clicked() {
    QString keyStr = ui->keyLineEdit->text();
    if (keyStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ключ для удаления!");
        return;
    }
    bool ok;
    int key = keyStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Ключ должен быть числом!");
        return;
    }
    tree.remove(key);
    ui->keyLineEdit->clear();
    ui->resultTextEdit->append("Узел с ключом " + QString::number(key) + " удален (если существовал)");
    treeWidget->update();
}

// Поиск элемента
void MainWindow::on_searchButton_clicked() {
    QString keyStr = ui->keyLineEdit->text();
    if (keyStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ключ для поиска!");
        return;
    }
    bool ok;
    int key = keyStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Ключ должен быть числом!");
        return;
    }
    QString result = tree.search(key);
    ui->resultTextEdit->append("Поиск ключа " + QString::number(key) + ": " + result);
    ui->keyLineEdit->clear();
}

// Балансировка
void MainWindow::on_balanceButton_clicked() {
    tree.balance();
    ui->resultTextEdit->append("Дерево сбалансировано");
    treeWidget->update();
}

// Подсчёт элементов, начинающихся с заданного символа
void MainWindow::on_countButton_clicked() {
    QString charStr = ui->charLineEdit->text();
    if (charStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите символ для подсчета!");
        return;
    }
    char ch = charStr[0].toLatin1();
    int count = tree.countByFirstChar(ch);
    ui->resultTextEdit->append("Количество элементов, начинающихся с '" +
                               QString(ch) + "': " + QString::number(count));
    ui->charLineEdit->clear();
}

// Прямой обход
void MainWindow::on_preOrderButton_clicked() {
    QString result = tree.preOrderTraversal();
    ui->resultTextEdit->append(result);
}

// Симметричный обход
void MainWindow::on_inOrderButton_clicked() {
    QString result = tree.inOrderTraversal();
    ui->resultTextEdit->append(result);
}

// Обратный обход
void MainWindow::on_postOrderButton_clicked() {
    QString result = tree.postOrderTraversal();
    ui->resultTextEdit->append(result);
}

// Очистка дерева
void MainWindow::on_clearButton_clicked() {
    tree.clear();
    ui->resultTextEdit->append("Дерево очищено");
    treeWidget->update();
}
