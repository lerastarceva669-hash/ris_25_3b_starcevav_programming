#include "treewidget.h"

TreeWidget::TreeWidget(QWidget *parent) : QWidget(parent), tree(nullptr) {
    // белый фон, чтобы было видно рисунок
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);
}

void TreeWidget::setTree(BinTree* t) {
    tree = t;
    update();  // перерисовать
}

void TreeWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // Рисуем белый фон
    painter.fillRect(rect(), Qt::white);
    // Если дерево задано – рисуем его на всём виджете
    if (tree != nullptr) {
        tree->draw(painter, width(), height());
    }
}
