/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "GraphWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    GraphWidget *graphicsView;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *matrixTab;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *matrixTable;
    QPushButton *applyMatrixBtn;
    QWidget *editTab;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addVertexBtn;
    QSpinBox *removeVertexSpin;
    QPushButton *removeVertexBtn;
    QGroupBox *edgeGroup;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *fromSpin;
    QLabel *label_2;
    QSpinBox *toSpin;
    QLabel *label_3;
    QSpinBox *weightSpin;
    QPushButton *addEdgeBtn;
    QPushButton *removeEdgeBtn;
    QGroupBox *algoGroup;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpinBox *startVertexSpin;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *bfsBtn;
    QPushButton *dfsBtn;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *dijkstraBtn;
    QPushButton *floydBtn;
    QLabel *resultLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(950, 650);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new GraphWidget(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(graphicsView);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        matrixTab = new QWidget();
        matrixTab->setObjectName(QString::fromUtf8("matrixTab"));
        verticalLayout_3 = new QVBoxLayout(matrixTab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        matrixTable = new QTableWidget(matrixTab);
        matrixTable->setObjectName(QString::fromUtf8("matrixTable"));

        verticalLayout_3->addWidget(matrixTable);

        applyMatrixBtn = new QPushButton(matrixTab);
        applyMatrixBtn->setObjectName(QString::fromUtf8("applyMatrixBtn"));

        verticalLayout_3->addWidget(applyMatrixBtn);

        tabWidget->addTab(matrixTab, QString());
        editTab = new QWidget();
        editTab->setObjectName(QString::fromUtf8("editTab"));
        verticalLayout_4 = new QVBoxLayout(editTab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addVertexBtn = new QPushButton(editTab);
        addVertexBtn->setObjectName(QString::fromUtf8("addVertexBtn"));

        horizontalLayout_2->addWidget(addVertexBtn);

        removeVertexSpin = new QSpinBox(editTab);
        removeVertexSpin->setObjectName(QString::fromUtf8("removeVertexSpin"));
        removeVertexSpin->setMinimum(1);

        horizontalLayout_2->addWidget(removeVertexSpin);

        removeVertexBtn = new QPushButton(editTab);
        removeVertexBtn->setObjectName(QString::fromUtf8("removeVertexBtn"));

        horizontalLayout_2->addWidget(removeVertexBtn);


        verticalLayout_4->addLayout(horizontalLayout_2);

        edgeGroup = new QGroupBox(editTab);
        edgeGroup->setObjectName(QString::fromUtf8("edgeGroup"));
        gridLayout = new QGridLayout(edgeGroup);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(edgeGroup);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        fromSpin = new QSpinBox(edgeGroup);
        fromSpin->setObjectName(QString::fromUtf8("fromSpin"));
        fromSpin->setMinimum(1);

        gridLayout->addWidget(fromSpin, 0, 1, 1, 1);

        label_2 = new QLabel(edgeGroup);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        toSpin = new QSpinBox(edgeGroup);
        toSpin->setObjectName(QString::fromUtf8("toSpin"));
        toSpin->setMinimum(1);

        gridLayout->addWidget(toSpin, 0, 3, 1, 1);

        label_3 = new QLabel(edgeGroup);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 4, 1, 1);

        weightSpin = new QSpinBox(edgeGroup);
        weightSpin->setObjectName(QString::fromUtf8("weightSpin"));
        weightSpin->setMinimum(1);
        weightSpin->setMaximum(999);

        gridLayout->addWidget(weightSpin, 0, 5, 1, 1);

        addEdgeBtn = new QPushButton(edgeGroup);
        addEdgeBtn->setObjectName(QString::fromUtf8("addEdgeBtn"));

        gridLayout->addWidget(addEdgeBtn, 1, 0, 1, 2);

        removeEdgeBtn = new QPushButton(edgeGroup);
        removeEdgeBtn->setObjectName(QString::fromUtf8("removeEdgeBtn"));

        gridLayout->addWidget(removeEdgeBtn, 1, 2, 1, 2);


        verticalLayout_4->addWidget(edgeGroup);

        tabWidget->addTab(editTab, QString());

        verticalLayout_2->addWidget(tabWidget);

        algoGroup = new QGroupBox(centralwidget);
        algoGroup->setObjectName(QString::fromUtf8("algoGroup"));
        verticalLayout_5 = new QVBoxLayout(algoGroup);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(algoGroup);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        startVertexSpin = new QSpinBox(algoGroup);
        startVertexSpin->setObjectName(QString::fromUtf8("startVertexSpin"));
        startVertexSpin->setMinimum(1);

        horizontalLayout_3->addWidget(startVertexSpin);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        bfsBtn = new QPushButton(algoGroup);
        bfsBtn->setObjectName(QString::fromUtf8("bfsBtn"));

        horizontalLayout_4->addWidget(bfsBtn);

        dfsBtn = new QPushButton(algoGroup);
        dfsBtn->setObjectName(QString::fromUtf8("dfsBtn"));

        horizontalLayout_4->addWidget(dfsBtn);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        dijkstraBtn = new QPushButton(algoGroup);
        dijkstraBtn->setObjectName(QString::fromUtf8("dijkstraBtn"));

        horizontalLayout_5->addWidget(dijkstraBtn);

        floydBtn = new QPushButton(algoGroup);
        floydBtn->setObjectName(QString::fromUtf8("floydBtn"));

        horizontalLayout_5->addWidget(floydBtn);


        verticalLayout_5->addLayout(horizontalLayout_5);

        resultLabel = new QLabel(algoGroup);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        resultLabel->setWordWrap(true);

        verticalLayout_5->addWidget(resultLabel);


        verticalLayout_2->addWidget(algoGroup);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\321\213 \342\200\223 \320\233\320\260\320\261\320\276\321\200\320\260\321\202\320\276\321\200\320\275\320\260\321\217 \321\200\320\260\320\261\320\276\321\202\320\260 \342\204\2262", nullptr));
        applyMatrixBtn->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 \320\274\320\260\321\202\321\200\320\270\321\206\321\203", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(matrixTab), QApplication::translate("MainWindow", "\320\234\320\260\321\202\321\200\320\270\321\206\320\260", nullptr));
        addVertexBtn->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262\320\265\321\200\321\210\320\270\320\275\321\203", nullptr));
        removeVertexBtn->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\320\265\321\200\321\210\320\270\320\275\321\203", nullptr));
        edgeGroup->setTitle(QApplication::translate("MainWindow", "\320\240\320\265\320\261\321\200\320\276", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\230\320\267:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\222:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\222\320\265\321\201:", nullptr));
        addEdgeBtn->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214/\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        removeEdgeBtn->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\200\320\265\320\261\321\200\320\276", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(editTab), QApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        algoGroup->setTitle(QApplication::translate("MainWindow", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274\321\213", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202\320\276\320\262\320\260\321\217 \320\262\320\265\321\200\321\210\320\270\320\275\320\260:", nullptr));
        bfsBtn->setText(QApplication::translate("MainWindow", "BFS", nullptr));
        dfsBtn->setText(QApplication::translate("MainWindow", "DFS", nullptr));
        dijkstraBtn->setText(QApplication::translate("MainWindow", "\320\224\320\265\320\271\320\272\321\201\321\202\321\200\320\260", nullptr));
        floydBtn->setText(QApplication::translate("MainWindow", "\320\244\320\273\320\276\320\271\320\264", nullptr));
        resultLabel->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
