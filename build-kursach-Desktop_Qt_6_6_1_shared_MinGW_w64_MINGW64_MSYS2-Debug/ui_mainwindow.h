/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *infoWidget;
    QWidget *menuWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *ordersButton;
    QPushButton *transportsButton;
    QPushButton *passagesButton;
    QPushButton *accountsButton;
    QPushButton *logoutButton;
    QWidget *tableWidget;
    QGridLayout *gridLayout_2;
    QPushButton *addButton;
    QWidget *sortWidget;
    QHBoxLayout *horizontalLayout;
    QComboBox *sortOBox;
    QComboBox *sortTBox;
    QComboBox *sortPBox;
    QPushButton *orderButton;
    QLineEdit *findEdit;
    QPushButton *findButton;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 600);
        MainWindow->setMinimumSize(QSize(1000, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        infoWidget = new QWidget(centralwidget);
        infoWidget->setObjectName("infoWidget");
        infoWidget->setMinimumSize(QSize(200, 0));
        infoWidget->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(infoWidget, 0, 2, 1, 1);

        menuWidget = new QWidget(centralwidget);
        menuWidget->setObjectName("menuWidget");
        menuWidget->setMinimumSize(QSize(75, 0));
        menuWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(222, 222, 222);\n"
"border-radius: 10px;"));
        verticalLayout_2 = new QVBoxLayout(menuWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        ordersButton = new QPushButton(menuWidget);
        ordersButton->setObjectName("ordersButton");
        ordersButton->setMinimumSize(QSize(0, 100));
        ordersButton->setAutoDefault(true);
        ordersButton->setFlat(false);

        verticalLayout_2->addWidget(ordersButton);

        transportsButton = new QPushButton(menuWidget);
        transportsButton->setObjectName("transportsButton");
        transportsButton->setMinimumSize(QSize(0, 100));

        verticalLayout_2->addWidget(transportsButton);

        passagesButton = new QPushButton(menuWidget);
        passagesButton->setObjectName("passagesButton");
        passagesButton->setMinimumSize(QSize(0, 100));

        verticalLayout_2->addWidget(passagesButton);

        accountsButton = new QPushButton(menuWidget);
        accountsButton->setObjectName("accountsButton");
        accountsButton->setMinimumSize(QSize(0, 100));

        verticalLayout_2->addWidget(accountsButton);

        logoutButton = new QPushButton(menuWidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setMinimumSize(QSize(0, 100));

        verticalLayout_2->addWidget(logoutButton);


        gridLayout->addWidget(menuWidget, 0, 0, 2, 1);

        tableWidget = new QWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        gridLayout_2 = new QGridLayout(tableWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        addButton = new QPushButton(tableWidget);
        addButton->setObjectName("addButton");
        addButton->setMinimumSize(QSize(600, 0));

        gridLayout_2->addWidget(addButton, 2, 1, 1, 1);

        sortWidget = new QWidget(tableWidget);
        sortWidget->setObjectName("sortWidget");
        horizontalLayout = new QHBoxLayout(sortWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        sortOBox = new QComboBox(sortWidget);
        sortOBox->addItem(QString());
        sortOBox->addItem(QString());
        sortOBox->addItem(QString());
        sortOBox->setObjectName("sortOBox");

        horizontalLayout->addWidget(sortOBox);

        sortTBox = new QComboBox(sortWidget);
        sortTBox->addItem(QString());
        sortTBox->addItem(QString());
        sortTBox->addItem(QString());
        sortTBox->addItem(QString());
        sortTBox->setObjectName("sortTBox");

        horizontalLayout->addWidget(sortTBox);

        sortPBox = new QComboBox(sortWidget);
        sortPBox->addItem(QString());
        sortPBox->addItem(QString());
        sortPBox->addItem(QString());
        sortPBox->setObjectName("sortPBox");

        horizontalLayout->addWidget(sortPBox);

        orderButton = new QPushButton(sortWidget);
        orderButton->setObjectName("orderButton");

        horizontalLayout->addWidget(orderButton);

        findEdit = new QLineEdit(sortWidget);
        findEdit->setObjectName("findEdit");

        horizontalLayout->addWidget(findEdit);

        findButton = new QPushButton(sortWidget);
        findButton->setObjectName("findButton");

        horizontalLayout->addWidget(findButton);


        gridLayout_2->addWidget(sortWidget, 0, 1, 1, 1);

        tableView = new QTableView(tableWidget);
        tableView->setObjectName("tableView");
        tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked);
        tableView->setShowGrid(true);
        tableView->setWordWrap(false);

        gridLayout_2->addWidget(tableView, 1, 1, 1, 1);


        gridLayout->addWidget(tableWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ordersButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\320\260\320\267\321\213", nullptr));
        transportsButton->setText(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\260\320\275\321\201\320\277\320\276\321\200\321\202", nullptr));
        passagesButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\271\321\201\321\213", nullptr));
        accountsButton->setText(QCoreApplication::translate("MainWindow", "\320\220\320\272\320\272\320\260\321\203\320\275\321\202\321\213", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\271\321\202\320\270", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        sortOBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \342\204\226", nullptr));
        sortOBox->setItemText(1, QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \320\260\320\273\321\204\320\260\320\262\320\270\321\202\321\203", nullptr));
        sortOBox->setItemText(2, QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \320\274\320\260\321\201\321\201\320\265", nullptr));

        sortOBox->setCurrentText(QString());
        sortOBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276...", nullptr));
        sortTBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \342\204\226", nullptr));
        sortTBox->setItemText(1, QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \320\260\320\273\321\204\320\260\320\262\320\270\321\202\321\203", nullptr));
        sortTBox->setItemText(2, QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \320\263\321\200\321\203\320\267\320\276\320\277\320\276\320\264\321\212\320\265\320\274\320\275\320\276\321\201\321\202\320\270", nullptr));
        sortTBox->setItemText(3, QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \321\200\320\260\321\201\321\205\320\276\320\264\321\203", nullptr));

        sortTBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276...", nullptr));
        sortPBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \342\204\226", nullptr));
        sortPBox->setItemText(1, QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \321\201\321\202\320\276\320\270\320\274\320\276\321\201\321\202\320\270", nullptr));
        sortPBox->setItemText(2, QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \320\264\320\260\321\202\320\265", nullptr));

        sortPBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276...", nullptr));
        orderButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\200\321\217\320\264\320\276\320\272 \320\277\320\276 \320\262\320\276\320\267\321\200\320\260\321\201\321\202\320\260\320\275\320\270\321\216", nullptr));
        findEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275", nullptr));
        findButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
