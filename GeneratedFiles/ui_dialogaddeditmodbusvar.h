/********************************************************************************
** Form generated from reading UI file 'dialogaddeditmodbusvar.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGADDEDITMODBUSVAR_H
#define UI_DIALOGADDEDITMODBUSVAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_DialogAddEditModbusVar
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButtonRead;
    QSpacerItem *horizontalSpacer_3;
    QRadioButton *radioButtonWrite;
    QLabel *label_2;
    QComboBox *comboBoxMemType;
    QLabel *label;
    QLabel *label_3;
    QComboBox *comboBoxCanalType;
    QLabel *label_5;
    QLabel *label_4;
    QLineEdit *lineEditVarName;
    QSpinBox *spinBoxMemAddr;
    QCheckBox *checkBoxEnable;
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxNetAddress;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonEscape;
    QLabel *label_6;
    QLineEdit *lineEditComment;

    void setupUi(QDialog *DialogAddEditModbusVar)
    {
        if (DialogAddEditModbusVar->objectName().isEmpty())
            DialogAddEditModbusVar->setObjectName(QStringLiteral("DialogAddEditModbusVar"));
        DialogAddEditModbusVar->resize(231, 285);
        gridLayout = new QGridLayout(DialogAddEditModbusVar);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(DialogAddEditModbusVar);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        radioButtonRead = new QRadioButton(groupBox);
        radioButtonRead->setObjectName(QStringLiteral("radioButtonRead"));

        gridLayout_2->addWidget(radioButtonRead, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(66, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        radioButtonWrite = new QRadioButton(groupBox);
        radioButtonWrite->setObjectName(QStringLiteral("radioButtonWrite"));

        gridLayout_2->addWidget(radioButtonWrite, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox, 6, 0, 1, 2);

        label_2 = new QLabel(DialogAddEditModbusVar);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        comboBoxMemType = new QComboBox(DialogAddEditModbusVar);
        comboBoxMemType->addItem(QString());
        comboBoxMemType->addItem(QString());
        comboBoxMemType->addItem(QString());
        comboBoxMemType->addItem(QString());
        comboBoxMemType->setObjectName(QStringLiteral("comboBoxMemType"));

        gridLayout->addWidget(comboBoxMemType, 2, 1, 1, 1);

        label = new QLabel(DialogAddEditModbusVar);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(DialogAddEditModbusVar);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        comboBoxCanalType = new QComboBox(DialogAddEditModbusVar);
        comboBoxCanalType->addItem(QString());
        comboBoxCanalType->setObjectName(QStringLiteral("comboBoxCanalType"));

        gridLayout->addWidget(comboBoxCanalType, 1, 1, 1, 1);

        label_5 = new QLabel(DialogAddEditModbusVar);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_4 = new QLabel(DialogAddEditModbusVar);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        lineEditVarName = new QLineEdit(DialogAddEditModbusVar);
        lineEditVarName->setObjectName(QStringLiteral("lineEditVarName"));

        gridLayout->addWidget(lineEditVarName, 0, 1, 1, 1);

        spinBoxMemAddr = new QSpinBox(DialogAddEditModbusVar);
        spinBoxMemAddr->setObjectName(QStringLiteral("spinBoxMemAddr"));
        spinBoxMemAddr->setMaximum(65535);

        gridLayout->addWidget(spinBoxMemAddr, 4, 1, 1, 1);

        checkBoxEnable = new QCheckBox(DialogAddEditModbusVar);
        checkBoxEnable->setObjectName(QStringLiteral("checkBoxEnable"));

        gridLayout->addWidget(checkBoxEnable, 8, 0, 1, 1);

        pushButtonOK = new QPushButton(DialogAddEditModbusVar);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));

        gridLayout->addWidget(pushButtonOK, 10, 1, 1, 1);

        spinBoxNetAddress = new QSpinBox(DialogAddEditModbusVar);
        spinBoxNetAddress->setObjectName(QStringLiteral("spinBoxNetAddress"));
        spinBoxNetAddress->setMinimum(1);
        spinBoxNetAddress->setMaximum(255);

        gridLayout->addWidget(spinBoxNetAddress, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 9, 0, 1, 1);

        pushButtonEscape = new QPushButton(DialogAddEditModbusVar);
        pushButtonEscape->setObjectName(QStringLiteral("pushButtonEscape"));
        pushButtonEscape->setAutoDefault(false);

        gridLayout->addWidget(pushButtonEscape, 10, 0, 1, 1);

        label_6 = new QLabel(DialogAddEditModbusVar);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        lineEditComment = new QLineEdit(DialogAddEditModbusVar);
        lineEditComment->setObjectName(QStringLiteral("lineEditComment"));

        gridLayout->addWidget(lineEditComment, 5, 1, 1, 1);


        retranslateUi(DialogAddEditModbusVar);
        QObject::connect(pushButtonOK, SIGNAL(clicked()), DialogAddEditModbusVar, SLOT(accept()));
        QObject::connect(pushButtonEscape, SIGNAL(clicked()), DialogAddEditModbusVar, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogAddEditModbusVar);
    } // setupUi

    void retranslateUi(QDialog *DialogAddEditModbusVar)
    {
        DialogAddEditModbusVar->setWindowTitle(QApplication::translate("DialogAddEditModbusVar", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("DialogAddEditModbusVar", "\321\200\320\265\320\266\320\270\320\274", nullptr));
        radioButtonRead->setText(QApplication::translate("DialogAddEditModbusVar", "\321\207\321\202\320\265\320\275\320\270\320\265", nullptr));
        radioButtonWrite->setText(QApplication::translate("DialogAddEditModbusVar", "\320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        label_2->setText(QApplication::translate("DialogAddEditModbusVar", "\320\272\320\260\320\275\320\260\320\273:", nullptr));
        comboBoxMemType->setItemText(0, QApplication::translate("DialogAddEditModbusVar", "Disrete Inputs", nullptr));
        comboBoxMemType->setItemText(1, QApplication::translate("DialogAddEditModbusVar", "Coils", nullptr));
        comboBoxMemType->setItemText(2, QApplication::translate("DialogAddEditModbusVar", "Holding Registers", nullptr));
        comboBoxMemType->setItemText(3, QApplication::translate("DialogAddEditModbusVar", "Input Registers", nullptr));

        label->setText(QApplication::translate("DialogAddEditModbusVar", "\320\270\320\274\321\217 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271:", nullptr));
        label_3->setText(QApplication::translate("DialogAddEditModbusVar", "\321\201\320\265\321\202\320\265\320\262\320\276\320\271 \320\260\320\264\321\200\320\265\321\201:", nullptr));
        comboBoxCanalType->setItemText(0, QApplication::translate("DialogAddEditModbusVar", "CAN_MB", nullptr));

        label_5->setText(QApplication::translate("DialogAddEditModbusVar", "\320\220\320\264\321\200\320\265\321\201 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271:", nullptr));
        label_4->setText(QApplication::translate("DialogAddEditModbusVar", "\321\202\320\270\320\277 \320\277\320\260\320\274\321\217\321\202\320\270:", nullptr));
        checkBoxEnable->setText(QApplication::translate("DialogAddEditModbusVar", "\320\276\320\277\321\200\320\276\321\201", nullptr));
        pushButtonOK->setText(QApplication::translate("DialogAddEditModbusVar", "OK", nullptr));
        pushButtonEscape->setText(QApplication::translate("DialogAddEditModbusVar", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        label_6->setText(QApplication::translate("DialogAddEditModbusVar", "\320\232\320\276\320\274\320\274\320\265\320\275\321\202\320\260\321\200\320\270\320\271:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogAddEditModbusVar: public Ui_DialogAddEditModbusVar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDEDITMODBUSVAR_H
