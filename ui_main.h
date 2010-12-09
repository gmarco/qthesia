/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created: Thu Dec 9 20:58:19 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLaden;
    QAction *actionAbspielen;
    QWidget *centralwidget;
    QScrollBar *horizontalScrollBar;
    QMenuBar *menubar;
    QMenu *menuDatei;
    QMenu *menuMIDI;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionLaden = new QAction(MainWindow);
        actionLaden->setObjectName(QString::fromUtf8("actionLaden"));
        actionAbspielen = new QAction(MainWindow);
        actionAbspielen->setObjectName(QString::fromUtf8("actionAbspielen"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalScrollBar = new QScrollBar(centralwidget);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(160, 540, 160, 16));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuDatei = new QMenu(menubar);
        menuDatei->setObjectName(QString::fromUtf8("menuDatei"));
        menuMIDI = new QMenu(menubar);
        menuMIDI->setObjectName(QString::fromUtf8("menuMIDI"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuDatei->menuAction());
        menubar->addAction(menuMIDI->menuAction());
        menuDatei->addAction(actionLaden);
        menuMIDI->addAction(actionAbspielen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionLaden->setText(QApplication::translate("MainWindow", "Laden", 0, QApplication::UnicodeUTF8));
        actionAbspielen->setText(QApplication::translate("MainWindow", "abspielen", 0, QApplication::UnicodeUTF8));
        menuDatei->setTitle(QApplication::translate("MainWindow", "Datei", 0, QApplication::UnicodeUTF8));
        menuMIDI->setTitle(QApplication::translate("MainWindow", "MIDI", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
