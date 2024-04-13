/********************************************************************************
** Form generated from reading UI file 'authwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHWINDOW_H
#define UI_AUTHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthWindow
{
public:
    QGridLayout *gridLayout;
    QWidget *authCentralWidget;
    QGridLayout *gridLayout_2;
    QFrame *authFrame;
    QGridLayout *gridLayout_3;
    QWidget *authWidget;
    QVBoxLayout *verticalLayout;
    QLabel *authLabel;
    QWidget *authEnterWidget;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *companyLine;
    QLineEdit *loginLine;
    QLineEdit *passwordLine;
    QPushButton *authEnterButton;
    QPushButton *registrationButton;

    void setupUi(QDialog *AuthWindow)
    {
        if (AuthWindow->objectName().isEmpty())
            AuthWindow->setObjectName("AuthWindow");
        AuthWindow->resize(532, 532);
        AuthWindow->setMinimumSize(QSize(532, 532));
        AuthWindow->setMaximumSize(QSize(532, 532));
        gridLayout = new QGridLayout(AuthWindow);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        authCentralWidget = new QWidget(AuthWindow);
        authCentralWidget->setObjectName("authCentralWidget");
        gridLayout_2 = new QGridLayout(authCentralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(9, 9, 9, 9);
        authFrame = new QFrame(authCentralWidget);
        authFrame->setObjectName("authFrame");
        authFrame->setFrameShape(QFrame::StyledPanel);
        authFrame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(authFrame);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setVerticalSpacing(6);
        gridLayout_3->setContentsMargins(100, 100, 100, 100);
        authWidget = new QWidget(authFrame);
        authWidget->setObjectName("authWidget");
        authWidget->setMinimumSize(QSize(300, 300));
        authWidget->setMaximumSize(QSize(300, 300));
        authWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(222, 222, 222);\n"
"border-radius: 30px solid;"));
        verticalLayout = new QVBoxLayout(authWidget);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(30, 40, 30, 20);
        authLabel = new QLabel(authWidget);
        authLabel->setObjectName("authLabel");
        QFont font;
        font.setPointSize(17);
        authLabel->setFont(font);
        authLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(authLabel);

        authEnterWidget = new QWidget(authWidget);
        authEnterWidget->setObjectName("authEnterWidget");
        verticalLayout_2 = new QVBoxLayout(authEnterWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 60, 0, 30);
        companyLine = new QLineEdit(authEnterWidget);
        companyLine->setObjectName("companyLine");
        companyLine->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        companyLine->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(companyLine);

        loginLine = new QLineEdit(authEnterWidget);
        loginLine->setObjectName("loginLine");
        loginLine->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        loginLine->setMaxLength(20);
        loginLine->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(loginLine);

        passwordLine = new QLineEdit(authEnterWidget);
        passwordLine->setObjectName("passwordLine");
        passwordLine->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        passwordLine->setMaxLength(20);
        passwordLine->setEchoMode(QLineEdit::Password);
        passwordLine->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(passwordLine);

        authEnterButton = new QPushButton(authEnterWidget);
        authEnterButton->setObjectName("authEnterButton");
        authEnterButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_2->addWidget(authEnterButton);

        registrationButton = new QPushButton(authEnterWidget);
        registrationButton->setObjectName("registrationButton");
        registrationButton->setAutoDefault(false);
        registrationButton->setFlat(true);

        verticalLayout_2->addWidget(registrationButton);


        verticalLayout->addWidget(authEnterWidget);


        gridLayout_3->addWidget(authWidget, 0, 0, 1, 1);


        gridLayout_2->addWidget(authFrame, 0, 0, 1, 1);


        gridLayout->addWidget(authCentralWidget, 0, 0, 1, 1);


        retranslateUi(AuthWindow);

        QMetaObject::connectSlotsByName(AuthWindow);
    } // setupUi

    void retranslateUi(QDialog *AuthWindow)
    {
        AuthWindow->setWindowTitle(QCoreApplication::translate("AuthWindow", "Dialog", nullptr));
        authLabel->setText(QCoreApplication::translate("AuthWindow", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        companyLine->setPlaceholderText(QCoreApplication::translate("AuthWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\272\320\276\320\274\320\277\320\260\320\275\320\270\320\270", nullptr));
        loginLine->setPlaceholderText(QCoreApplication::translate("AuthWindow", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        passwordLine->setPlaceholderText(QCoreApplication::translate("AuthWindow", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        authEnterButton->setText(QCoreApplication::translate("AuthWindow", "\320\222\320\276\320\271\321\202\320\270", nullptr));
#if QT_CONFIG(shortcut)
        authEnterButton->setShortcut(QCoreApplication::translate("AuthWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        registrationButton->setText(QCoreApplication::translate("AuthWindow", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217 \320\272\320\260\320\272 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthWindow: public Ui_AuthWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHWINDOW_H
