#include "bintree.h"
#include <cstring>
#include <QDebug>

BinTree::BinTree() {
    root = nullptr;
}

BinTree::~BinTree() {
    destroyTree(root);
}

// Создание нового узла
Node* BinTree::createNode(int key, const char* value) {
    Node* newNode = new Node();
    newNode->key = key;

    // Выделяем память и копируем строку
    int length = 0;
    while (value[length] != '\0') {
        length++;
    }

    newNode->data = new char[length + 1];
    for (int i = 0; i < length; i++) {
        newNode->data[i] = value[i];
    }
    newNode->data[length] = '\0';

    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

// Уничтожение дерева
void BinTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete[] node->data;
        delete node;
    }
}

// Вставка узла
Node* BinTree::insertNode(Node* node, int key, const char* value) {
    // Если дошли до пустого места, создаем новый узел
    if (node == nullptr) {
        return createNode(key, value);
    }

    // Идем в левое поддерево если ключ меньше
    if (key < node->key) {
        node->left = insertNode(node->left, key, value);
    }
    // Идем в правое поддерево если ключ больше
    else if (key > node->key) {
        node->right = insertNode(node->right, key, value);
    }
    // Если ключ равен, обновляем данные
    else {
        delete[] node->data;
        int length = 0;
        while (value[length] != '\0') {
            length++;
        }
        node->data = new char[length + 1];
        for (int i = 0; i < length; i++) {
            node->data[i] = value[i];
        }
        node->data[length] = '\0';
    }

    return node;
}

// Поиск минимального узла
Node* BinTree::findMin(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }

    return current;
}

// Удаление узла
Node* BinTree::deleteNode(Node* node, int key) {
    if (node == nullptr) {
        return nullptr;
    }

    // Ищем узел для удаления
    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    }
    else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    }
    else {
        // Нашли узел для удаления

        // Случай 1: узел без потомков (лист)
        if (node->left == nullptr && node->right == nullptr) {
            delete[] node->data;
            delete node;
            return nullptr;
        }

        // Случай 2: узел с одним потомком
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete[] node->data;
            delete node;
            return temp;
        }

        if (node->right == nullptr) {
            Node* temp = node->left;
            delete[] node->data;
            delete node;
            return temp;
        }

        // Случай 3: узел с двумя потомками
        Node* temp = findMin(node->right);
        node->key = temp->key;

        // Копируем данные
        delete[] node->data;
        int length = 0;
        while (temp->data[length] != '\0') {
            length++;
        }
        node->data = new char[length + 1];
        for (int i = 0; i < length; i++) {
            node->data[i] = temp->data[i];
        }
        node->data[length] = '\0';

        node->right = deleteNode(node->right, temp->key);
    }

    return node;
}

// Поиск узла по ключу
Node* BinTree::searchNode(Node* node, int key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (key == node->key) {
        return node;
    }

    if (key < node->key) {
        return searchNode(node->left, key);
    }
    else {
        return searchNode(node->right, key);
    }
}

// Прямой обход (корень -> левое -> правое)
void BinTree::preOrder(Node* node, QString& result) {
    if (node != nullptr) {
        result += "(" + QString::number(node->key) + ": " + QString(node->data) + ") ";
        preOrder(node->left, result);
        preOrder(node->right, result);
    }
}

// Симметричный обход (левое -> корень -> правое)
void BinTree::inOrder(Node* node, QString& result) {
    if (node != nullptr) {
        inOrder(node->left, result);
        result += "(" + QString::number(node->key) + ": " + QString(node->data) + ") ";
        inOrder(node->right, result);
    }
}

// Обратный обход (левое -> правое -> корень)
void BinTree::postOrder(Node* node, QString& result) {
    if (node != nullptr) {
        postOrder(node->left, result);
        postOrder(node->right, result);
        result += "(" + QString::number(node->key) + ": " + QString(node->data) + ") ";
    }
}

// Подсчет узлов, данные которых начинаются с заданного символа
int BinTree::countStartingWithChar(Node* node, char ch) {
    if (node == nullptr) {
        return 0;
    }

    int count = 0;

    // Проверяем текущий узел
    if (node->data[0] == ch) {
        count = 1;
    }

    // Считаем в левом и правом поддеревьях
    count = count + countStartingWithChar(node->left, ch);
    count = count + countStartingWithChar(node->right, ch);

    return count;
}

// Подсчет общего количества узлов
int BinTree::countNodes(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right);
}

// Сохранение узлов в массив (для балансировки)
void BinTree::storeInArray(Node* node, Node** arr, int& index) {
    if (node != nullptr) {
        storeInArray(node->left, arr, index);
        arr[index] = node;
        index = index + 1;
        storeInArray(node->right, arr, index);
    }
}

// Построение сбалансированного дерева из массива
Node* BinTree::buildBalancedTree(Node** arr, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = (start + end) / 2;
    Node* node = arr[mid];

    node->left = buildBalancedTree(arr, start, mid - 1);
    node->right = buildBalancedTree(arr, mid + 1, end);

    return node;
}

// Балансировка дерева
Node* BinTree::balanceTree(Node* node) {
    int n = countNodes(node);

    if (n == 0) {
        return nullptr;
    }

    // Создаем массив указателей на узлы
    Node** arr = new Node*[n];
    int index = 0;

    // Заполняем массив в порядке симметричного обхода
    storeInArray(node, arr, index);

    // Строим сбалансированное дерево
    Node* balancedRoot = buildBalancedTree(arr, 0, n - 1);

    delete[] arr;
    return balancedRoot;
}

// Функция для рисования узла
void BinTree::drawNode(QPainter& painter, int x, int y, int key, const char* data) {
    // Рисуем круг
    painter.setBrush(Qt::lightGray);
    painter.setPen(Qt::black);
    painter.drawEllipse(x - 20, y - 20, 40, 40);

    // Пишем ключ и данные
    QString text = QString::number(key) + ":" + QString(data);
    painter.drawText(x - 18, y - 5, text);
}

// Функция для рисования дерева
void BinTree::drawTree(QPainter& painter, Node* node, int x, int y, int level, int offset) {
    if (node == nullptr) {
        return;
    }

    // Рисуем линии к потомкам
    if (node->left != nullptr) {
        int childX = x - offset;
        int childY = y + 60;
        painter.drawLine(x, y + 20, childX, childY - 20);
    }

    if (node->right != nullptr) {
        int childX = x + offset;
        int childY = y + 60;
        painter.drawLine(x, y + 20, childX, childY - 20);
    }

    // Рисуем текущий узел
    drawNode(painter, x, y, node->key, node->data);

    // Рекурсивно рисуем поддеревья
    int newOffset = offset / 2;
    if (newOffset < 20) {
        newOffset = 20;
    }

    drawTree(painter, node->left, x - offset, y + 60, level + 1, newOffset);
    drawTree(painter, node->right, x + offset, y + 60, level + 1, newOffset);
}

// ============= Публичные методы =============

void BinTree::insert(int key, const char* value) {
    root = insertNode(root, key, value);
}

void BinTree::remove(int key) {
    root = deleteNode(root, key);
}

QString BinTree::search(int key) {
    Node* node = searchNode(root, key);
    if (node != nullptr) {
        return QString(node->data);
    }
    return "Не найдено";
}

QString BinTree::preOrderTraversal() {
    QString result = "Прямой обход: ";
    preOrder(root, result);
    if (result == "Прямой обход: ") {
        result = "Дерево пустое";
    }
    return result;
}

QString BinTree::inOrderTraversal() {
    QString result = "Симметричный обход: ";
    inOrder(root, result);
    if (result == "Симметричный обход: ") {
        result = "Дерево пустое";
    }
    return result;
}

QString BinTree::postOrderTraversal() {
    QString result = "Обратный обход: ";
    postOrder(root, result);
    if (result == "Обратный обход: ") {
        result = "Дерево пустое";
    }
    return result;
}

int BinTree::countByFirstChar(char ch) {
    return countStartingWithChar(root, ch);
}

void BinTree::balance() {
    if (root != nullptr) {
        root = balanceTree(root);
    }
}

void BinTree::draw(QPainter& painter, int width, int height) {
    if (root != nullptr) {
        drawTree(painter, root, width / 2, 40, 0, width / 4);
    }
}

Node* BinTree::getRoot() {
    return root;
}

void BinTree::clear() {
    destroyTree(root);
    root = nullptr;
}
