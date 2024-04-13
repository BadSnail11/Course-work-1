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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *infoWidget;
    QFormLayout *formLayout;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QWidget *menuWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(791, 596);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 715, 269));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 1, 1, 1);

        infoWidget = new QWidget(centralwidget);
        infoWidget->setObjectName("infoWidget");
        formLayout = new QFormLayout(infoWidget);
        formLayout->setObjectName("formLayout");
        lineEdit = new QLineEdit(infoWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setDragEnabled(false);
        lineEdit->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::LabelRole, lineEdit);

        lineEdit_2 = new QLineEdit(infoWidget);
        lineEdit_2->setObjectName("lineEdit_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, lineEdit_2);


        gridLayout->addWidget(infoWidget, 1, 1, 1, 1);

        menuWidget = new QWidget(centralwidget);
        menuWidget->setObjectName("menuWidget");
        menuWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(222, 222, 222);\n"
"border-radius: 10px;"));
        verticalLayout_2 = new QVBoxLayout(menuWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        pushButton = new QPushButton(menuWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setAutoDefault(true);
        pushButton->setFlat(false);

        verticalLayout_2->addWidget(pushButton);


        gridLayout->addWidget(menuWidget, 0, 0, 2, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 791, 17));
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
        lineEdit->setInputMask(QString());
        lineEdit->setText(QCoreApplication::translate("MainWindow", "something", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
