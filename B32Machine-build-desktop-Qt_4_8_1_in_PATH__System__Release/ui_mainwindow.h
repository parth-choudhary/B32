/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Jun 19 20:28:26 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label1;
    QLineEdit *txtSourceFIleName;
    QPushButton *btnSourceBrowse;
    QPushButton *btnAssemble;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(434, 348);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label1 = new QLabel(centralWidget);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(30, 130, 91, 17));
        txtSourceFIleName = new QLineEdit(centralWidget);
        txtSourceFIleName->setObjectName(QString::fromUtf8("txtSourceFIleName"));
        txtSourceFIleName->setGeometry(QRect(110, 120, 201, 31));
        btnSourceBrowse = new QPushButton(centralWidget);
        btnSourceBrowse->setObjectName(QString::fromUtf8("btnSourceBrowse"));
        btnSourceBrowse->setGeometry(QRect(330, 120, 81, 27));
        btnAssemble = new QPushButton(centralWidget);
        btnAssemble->setObjectName(QString::fromUtf8("btnAssemble"));
        btnAssemble->setGeometry(QRect(150, 230, 98, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 434, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label1->setText(QApplication::translate("MainWindow", "Filename:", 0, QApplication::UnicodeUTF8));
        btnSourceBrowse->setText(QApplication::translate("MainWindow", "Browse..", 0, QApplication::UnicodeUTF8));
        btnAssemble->setText(QApplication::translate("MainWindow", "Run", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
