/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonLoadProgr;
    QPushButton *pushButtonLoadSFRAM;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QPushButton *pushButtonReadProgr;
    QPushButton *pushButtonReadSFRAM;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBoxNetAddr;
    QPushButton *pushButtonUpd;
    QPushButton *pushButtonSearch;
    QComboBox *comboBoxComPorts;
    QLabel *label_4;
    QLineEdit *lineEditCan;
    QLineEdit *lineEditProt;
    QLineEdit *lineEditSpeed;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(443, 200);
        QIcon icon;
        icon.addFile(QStringLiteral(":/main.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButtonLoadProgr = new QPushButton(groupBox_2);
        pushButtonLoadProgr->setObjectName(QStringLiteral("pushButtonLoadProgr"));

        gridLayout_2->addWidget(pushButtonLoadProgr, 0, 0, 1, 1);

        pushButtonLoadSFRAM = new QPushButton(groupBox_2);
        pushButtonLoadSFRAM->setObjectName(QStringLiteral("pushButtonLoadSFRAM"));

        gridLayout_2->addWidget(pushButtonLoadSFRAM, 1, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButtonReadProgr = new QPushButton(groupBox_3);
        pushButtonReadProgr->setObjectName(QStringLiteral("pushButtonReadProgr"));

        gridLayout_3->addWidget(pushButtonReadProgr, 0, 0, 1, 1);

        pushButtonReadSFRAM = new QPushButton(groupBox_3);
        pushButtonReadSFRAM->setObjectName(QStringLiteral("pushButtonReadSFRAM"));

        gridLayout_3->addWidget(pushButtonReadSFRAM, 1, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 1, 1, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBoxNetAddr = new QSpinBox(groupBox);
        spinBoxNetAddr->setObjectName(QStringLiteral("spinBoxNetAddr"));

        gridLayout->addWidget(spinBoxNetAddr, 0, 1, 1, 1);

        pushButtonUpd = new QPushButton(groupBox);
        pushButtonUpd->setObjectName(QStringLiteral("pushButtonUpd"));

        gridLayout->addWidget(pushButtonUpd, 1, 2, 1, 1);

        pushButtonSearch = new QPushButton(groupBox);
        pushButtonSearch->setObjectName(QStringLiteral("pushButtonSearch"));

        gridLayout->addWidget(pushButtonSearch, 0, 2, 1, 1);

        comboBoxComPorts = new QComboBox(groupBox);
        comboBoxComPorts->setObjectName(QStringLiteral("comboBoxComPorts"));

        gridLayout->addWidget(comboBoxComPorts, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        lineEditCan = new QLineEdit(groupBox);
        lineEditCan->setObjectName(QStringLiteral("lineEditCan"));
        lineEditCan->setReadOnly(true);

        gridLayout->addWidget(lineEditCan, 3, 1, 1, 2);

        lineEditProt = new QLineEdit(groupBox);
        lineEditProt->setObjectName(QStringLiteral("lineEditProt"));
        lineEditProt->setReadOnly(true);

        gridLayout->addWidget(lineEditProt, 4, 1, 1, 2);

        lineEditSpeed = new QLineEdit(groupBox);
        lineEditSpeed->setObjectName(QStringLiteral("lineEditSpeed"));
        lineEditSpeed->setReadOnly(true);

        gridLayout->addWidget(lineEditSpeed, 2, 1, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 5, 1, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 2, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\321\207\320\270\320\272 1.0", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260", 0));
        pushButtonLoadProgr->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\260", 0));
        pushButtonLoadSFRAM->setText(QApplication::translate("MainWindow", "\320\241\320\270\321\201\321\202. \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\320\247\321\202\320\265\320\275\320\270\320\265", 0));
        pushButtonReadProgr->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\260", 0));
        pushButtonReadSFRAM->setText(QApplication::translate("MainWindow", "\320\241\320\270\321\201\321\202. \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\237\320\233\320\232", 0));
        label->setText(QApplication::translate("MainWindow", "\320\241\320\265\321\202\320\265\320\262\320\276\320\271 \320\260\320\264\321\200\320\265\321\201:", 0));
        pushButtonUpd->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", 0));
        pushButtonSearch->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", 0));
        label_4->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202:", 0));
        label_2->setText(QApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214:", 0));
        label_3->setText(QApplication::translate("MainWindow", "\320\232\320\260\320\275\320\260\320\273:", 0));
        label_5->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
