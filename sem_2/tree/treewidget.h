#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QPainter>
#include "bintree.h"

class TreeWidget : public QWidget {
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = nullptr);
    void setTree(BinTree* t);  // указатель на дерево
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    BinTree* tree;  // указатель на дерево (не владеет)
};

#endif // TREEWIDGET_H
