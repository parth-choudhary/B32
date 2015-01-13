/********************************************************************************
** Form generated from reading UI file 'mainwindow2.ui'
**
** Created: Wed Jun 19 20:28:26 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW2_H
#define UI_MAINWINDOW2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow2
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QMenu *menuSCREAM;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow2)
    {
        if (MainWindow2->objectName().isEmpty())
            MainWindow2->setObjectName(QString::fromUtf8("MainWindow2"));
        MainWindow2->resize(1030, 445);
        centralWidget = new QWidget(MainWindow2);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(450, 0, 80, 26));
        MainWindow2->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow2);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1030, 23));
        menuSCREAM = new QMenu(menuBar);
        menuSCREAM->setObjectName(QString::fromUtf8("menuSCREAM"));
        MainWindow2->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow2);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow2->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow2);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow2->setStatusBar(statusBar);

        menuBar->addAction(menuSCREAM->menuAction());

        retranslateUi(MainWindow2);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow2, SLOT(clicked()));

        QMetaObject::connectSlotsByName(MainWindow2);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow2)
    {
        MainWindow2->setWindowTitle(QApplication::translate("MainWindow2", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow2", "Next", 0, QApplication::UnicodeUTF8));
        menuSCREAM->setTitle(QApplication::translate("MainWindow2", "SCREAM", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow2: public Ui_MainWindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW2_H
