#ifndef BINTREE_H
#define BINTREE_H

#include <QString>
#include <QPainter>
#include <QPoint>

// Структура узла дерева
struct Node {
    char* data;          // информационное поле
    int key;             // ключ узла
    Node* left;          // левый потомок
    Node* right;         // правый потомок
};

// Класс бинарного дерева поиска
class BinTree {
private:
    Node* root;          // корень дерева

    // Вспомогательные функции
    Node* createNode(int key, const char* value);
    void destroyTree(Node* node);

    // Функции для вставки и удаления
    Node* insertNode(Node* node, int key, const char* value);
    Node* deleteNode(Node* node, int key);
    Node* findMin(Node* node);

    // Функция поиска
    Node* searchNode(Node* node, int key);

    // Функции обхода
    void preOrder(Node* node, QString& result);
    void inOrder(Node* node, QString& result);
    void postOrder(Node* node, QString& result);

    // Функция для подсчета элементов, начинающихся с заданного символа
    int countStartingWithChar(Node* node, char ch);

    // Функция для балансировки
    Node* balanceTree(Node* node);
    void storeInArray(Node* node, Node** arr, int& index);
    Node* buildBalancedTree(Node** arr, int start, int end);
    int countNodes(Node* node);

    // Функции для рисования
    void drawTree(QPainter& painter, Node* node, int x, int y, int level, int offset);
    void drawNode(QPainter& painter, int x, int y, int key, const char* data);

public:
    BinTree();
    ~BinTree();

    // Основные операции
    void insert(int key, const char* value);
    void remove(int key);
    QString search(int key);

    // Функции обхода
    QString preOrderTraversal();
    QString inOrderTraversal();
    QString postOrderTraversal();

    // Подсчет элементов, начинающихся с заданного символа
    int countByFirstChar(char ch);

    // Балансировка
    void balance();

    // Функции рисования
    void draw(QPainter& painter, int width, int height);

    // Получение корня (для UI)
    Node* getRoot();

    // Очистка дерева
    void clear();
};

#endif // BINTREE_H
