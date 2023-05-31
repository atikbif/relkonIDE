/********************************************************************************
** Form generated from reading UI file 'modbusconfdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODBUSCONFDIALOG_H
#define UI_MODBUSCONFDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ModbusConfDialog
{
public:
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QPushButton *pushButtonEnableAll;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonAddVar;
    QPushButton *pushButtonDel;
    QPushButton *pushButtonDisableAll;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpinBox *spinBoxMaxLength;
    QLabel *label_3;
    QLabel *label_2;
    QSpinBox *spinBoxMaxBreak;
    QLabel *label;
    QSpinBox *spinBoxDelay;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonESC;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *ModbusConfDialog)
    {
        if (ModbusConfDialog->objectName().isEmpty())
            ModbusConfDialog->setObjectName(QStringLiteral("ModbusConfDialog"));
        ModbusConfDialog->resize(1157, 423);
        gridLayout_2 = new QGridLayout(ModbusConfDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tableWidget = new QTableWidget(ModbusConfDialog);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font);
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font);
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setFont(font);
        tableWidget->setStyleSheet(QLatin1String("QHeaderView::section {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                      stop:0 #616161, stop: 0.5 #505050,\n"
"                                      stop: 0.6 #434343, stop:1 #656565);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"}\n"
"\n"
"QTableWidget QTableCornerButton::section {\n"
"         background: darkGray;\n"
"         border: 2px outset black;\n"
"     }\n"
"\n"
"QTableView { gridline-color: green; }"));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        gridLayout_2->addWidget(tableWidget, 0, 0, 6, 1);

        groupBox_3 = new QGroupBox(ModbusConfDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        pushButtonEnableAll = new QPushButton(groupBox_3);
        pushButtonEnableAll->setObjectName(QStringLiteral("pushButtonEnableAll"));

        gridLayout_4->addWidget(pushButtonEnableAll, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 4, 0, 1, 1);

        pushButtonEdit = new QPushButton(groupBox_3);
        pushButtonEdit->setObjectName(QStringLiteral("pushButtonEdit"));

        gridLayout_4->addWidget(pushButtonEdit, 1, 0, 1, 1);

        pushButtonAddVar = new QPushButton(groupBox_3);
        pushButtonAddVar->setObjectName(QStringLiteral("pushButtonAddVar"));

        gridLayout_4->addWidget(pushButtonAddVar, 0, 0, 1, 1);

        pushButtonDel = new QPushButton(groupBox_3);
        pushButtonDel->setObjectName(QStringLiteral("pushButtonDel"));

        gridLayout_4->addWidget(pushButtonDel, 5, 0, 1, 1);

        pushButtonDisableAll = new QPushButton(groupBox_3);
        pushButtonDisableAll->setObjectName(QStringLiteral("pushButtonDisableAll"));

        gridLayout_4->addWidget(pushButtonDisableAll, 3, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_3, 0, 1, 2, 1);

        groupBox = new QGroupBox(ModbusConfDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spinBoxMaxLength = new QSpinBox(groupBox);
        spinBoxMaxLength->setObjectName(QStringLiteral("spinBoxMaxLength"));
        spinBoxMaxLength->setMinimum(1);
        spinBoxMaxLength->setMaximum(32);
        spinBoxMaxLength->setValue(16);

        gridLayout->addWidget(spinBoxMaxLength, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        spinBoxMaxBreak = new QSpinBox(groupBox);
        spinBoxMaxBreak->setObjectName(QStringLiteral("spinBoxMaxBreak"));
        spinBoxMaxBreak->setMaximum(32);
        spinBoxMaxBreak->setValue(3);

        gridLayout->addWidget(spinBoxMaxBreak, 1, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        spinBoxDelay = new QSpinBox(groupBox);
        spinBoxDelay->setObjectName(QStringLiteral("spinBoxDelay"));
        spinBoxDelay->setMinimum(3);
        spinBoxDelay->setMaximum(10000);

        gridLayout->addWidget(spinBoxDelay, 2, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 5, 1, 1, 1);

        groupBox_2 = new QGroupBox(ModbusConfDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButtonOK = new QPushButton(groupBox_2);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));

        gridLayout_3->addWidget(pushButtonOK, 0, 0, 1, 1);

        pushButtonESC = new QPushButton(groupBox_2);
        pushButtonESC->setObjectName(QStringLiteral("pushButtonESC"));

        gridLayout_3->addWidget(pushButtonESC, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 3, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);


        retranslateUi(ModbusConfDialog);
        QObject::connect(pushButtonOK, SIGNAL(clicked()), ModbusConfDialog, SLOT(accept()));
        QObject::connect(pushButtonESC, SIGNAL(clicked()), ModbusConfDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ModbusConfDialog);
    } // setupUi

    void retranslateUi(QDialog *ModbusConfDialog)
    {
        ModbusConfDialog->setWindowTitle(QApplication::translate("ModbusConfDialog", "Modbus \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ModbusConfDialog", "\320\270\320\274\321\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ModbusConfDialog", "\320\272\320\260\320\275\320\260\320\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ModbusConfDialog", "\321\201\320\265\321\202. \320\260\320\264\321\200\320\265\321\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("ModbusConfDialog", "\321\202\320\270\320\277 \320\277\320\260\320\274\321\217\321\202\320\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("ModbusConfDialog", "\321\207\321\202\320\265\320\275\320\270\320\265/\320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("ModbusConfDialog", "\320\260\320\264\321\200\320\265\321\201 \320\262 \320\277\320\260\320\274\321\217\321\202\320\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("ModbusConfDialog", "\320\276\320\277\321\200\320\276\321\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("ModbusConfDialog", "\320\272\320\276\320\274\320\274\320\265\320\275\321\202\320\260\321\200\320\270\320\271", nullptr));
        groupBox_3->setTitle(QApplication::translate("ModbusConfDialog", "\320\237\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\260\321\217", nullptr));
        pushButtonEnableAll->setText(QApplication::translate("ModbusConfDialog", "\320\276\320\277\321\200\320\260\321\210\320\270\320\262\320\260\321\202\321\214 \320\262\321\201\320\265", nullptr));
        pushButtonEdit->setText(QApplication::translate("ModbusConfDialog", "\321\200\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        pushButtonAddVar->setText(QApplication::translate("ModbusConfDialog", "\320\264\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButtonDel->setText(QApplication::translate("ModbusConfDialog", "\321\203\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        pushButtonDisableAll->setText(QApplication::translate("ModbusConfDialog", "\320\267\320\260\320\277\321\200\320\265\321\202\320\270\321\202\321\214 \320\262\321\201\320\265", nullptr));
        groupBox->setTitle(QString());
        label_3->setText(QApplication::translate("ModbusConfDialog", "\320\274\320\260\320\272\321\201. \320\277\321\200\320\276\320\274\320\265\320\266\321\203\321\202\320\276\320\272:", nullptr));
        label_2->setText(QApplication::translate("ModbusConfDialog", "\320\274\320\260\320\272\321\201. \320\264\320\273\320\270\320\275\320\260 \320\267\320\260\320\277\321\200\320\276\321\201\320\260:", nullptr));
        label->setText(QApplication::translate("ModbusConfDialog", "\320\277\320\265\321\200\320\270\320\276\320\264 \320\276\320\277\321\200\320\276\321\201\320\260, \320\274\321\201", nullptr));
        groupBox_2->setTitle(QString());
        pushButtonOK->setText(QApplication::translate("ModbusConfDialog", "OK", nullptr));
        pushButtonESC->setText(QApplication::translate("ModbusConfDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModbusConfDialog: public Ui_ModbusConfDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODBUSCONFDIALOG_H
