/********************************************************************************
** Form generated from reading UI file 'settingsform.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSFORM_H
#define UI_SETTINGSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsForm
{
public:
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButtonFromPLC;
    QPushButton *pushButtonToPLC;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_10;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_4;
    QLabel *label_7;
    QComboBox *comboBoxPcProtocol;
    QLabel *label_8;
    QComboBox *comboBoxPcSpeed;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLineEdit *lineEditMAC;
    QLineEdit *lineEditIP;
    QLabel *label_4;
    QLabel *label_12;
    QLineEdit *lineEditGATE;
    QLabel *label_14;
    QLineEdit *lineEditMASK;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QComboBox *comboBoxProgProtocol;
    QLabel *label_6;
    QComboBox *comboBoxProgSpeed;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radioButtonNoEmulation;
    QRadioButton *radioButtonInputEmulation;
    QRadioButton *radioButtonInputOutputEmulation;
    QCheckBox *checkBoxModbus;
    QCheckBox *checkBoxSD;
    QLabel *label_9;
    QCheckBox *checkBoxDisplay;
    QComboBox *comboBoxPLCType;
    QPushButton *pushButtonPortListUpdate;
    QSpinBox *spinBoxEMemSize;
    QGridLayout *gridLayout;
    QSpinBox *spinBoxProgAddr;
    QLabel *label_2;
    QSpinBox *spinBoxNetAddr;
    QLabel *label;
    QLineEdit *lineEditProjectDefenition;
    QLabel *label_10;
    QLabel *label_13;
    QLabel *label_11;
    QComboBox *comboBoxPrPort;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QWidget *tab_2;
    QGridLayout *gridLayout_9;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QRadioButton *radioButtonOneByte;
    QRadioButton *radioButtonTwoBytes;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radioButtonFourBytes;
    QTableWidget *tableWidget;

    void setupUi(QWidget *SettingsForm)
    {
        if (SettingsForm->objectName().isEmpty())
            SettingsForm->setObjectName(QStringLiteral("SettingsForm"));
        SettingsForm->resize(953, 776);
        gridLayout_6 = new QGridLayout(SettingsForm);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalSpacer_4 = new QSpacerItem(943, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_4, 1, 1, 1, 1);

        pushButtonFromPLC = new QPushButton(SettingsForm);
        pushButtonFromPLC->setObjectName(QStringLiteral("pushButtonFromPLC"));

        gridLayout_6->addWidget(pushButtonFromPLC, 1, 2, 1, 1);

        pushButtonToPLC = new QPushButton(SettingsForm);
        pushButtonToPLC->setObjectName(QStringLiteral("pushButtonToPLC"));

        gridLayout_6->addWidget(pushButtonToPLC, 1, 3, 1, 1);

        scrollArea = new QScrollArea(SettingsForm);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 916, 747));
        gridLayout_10 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_8 = new QGridLayout(tab);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        groupBox_8 = new QGroupBox(tab);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setMaximumSize(QSize(16777215, 720));
        gridLayout_7 = new QGridLayout(groupBox_8);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        groupBox_4 = new QGroupBox(groupBox_8);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_4->addWidget(label_7, 0, 0, 1, 1);

        comboBoxPcProtocol = new QComboBox(groupBox_4);
        comboBoxPcProtocol->addItem(QString());
        comboBoxPcProtocol->addItem(QString());
        comboBoxPcProtocol->setObjectName(QStringLiteral("comboBoxPcProtocol"));

        gridLayout_4->addWidget(comboBoxPcProtocol, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_4->addWidget(label_8, 1, 0, 1, 1);

        comboBoxPcSpeed = new QComboBox(groupBox_4);
        comboBoxPcSpeed->addItem(QString());
        comboBoxPcSpeed->addItem(QString());
        comboBoxPcSpeed->addItem(QString());
        comboBoxPcSpeed->addItem(QString());
        comboBoxPcSpeed->addItem(QString());
        comboBoxPcSpeed->addItem(QString());
        comboBoxPcSpeed->setObjectName(QStringLiteral("comboBoxPcSpeed"));

        gridLayout_4->addWidget(comboBoxPcSpeed, 1, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_4);


        gridLayout_7->addWidget(groupBox_4, 2, 1, 1, 2);

        groupBox_2 = new QGroupBox(groupBox_8);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        lineEditMAC = new QLineEdit(groupBox_2);
        lineEditMAC->setObjectName(QStringLiteral("lineEditMAC"));

        gridLayout_2->addWidget(lineEditMAC, 1, 1, 1, 1);

        lineEditIP = new QLineEdit(groupBox_2);
        lineEditIP->setObjectName(QStringLiteral("lineEditIP"));

        gridLayout_2->addWidget(lineEditIP, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 2, 0, 1, 1);

        lineEditGATE = new QLineEdit(groupBox_2);
        lineEditGATE->setObjectName(QStringLiteral("lineEditGATE"));

        gridLayout_2->addWidget(lineEditGATE, 2, 1, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_2->addWidget(label_14, 3, 0, 1, 1);

        lineEditMASK = new QLineEdit(groupBox_2);
        lineEditMASK->setObjectName(QStringLiteral("lineEditMASK"));

        gridLayout_2->addWidget(lineEditMASK, 3, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        gridLayout_7->addWidget(groupBox_2, 1, 1, 1, 2);

        groupBox_3 = new QGroupBox(groupBox_8);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        comboBoxProgProtocol = new QComboBox(groupBox_3);
        comboBoxProgProtocol->addItem(QString());
        comboBoxProgProtocol->addItem(QString());
        comboBoxProgProtocol->setObjectName(QStringLiteral("comboBoxProgProtocol"));

        gridLayout_3->addWidget(comboBoxProgProtocol, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        comboBoxProgSpeed = new QComboBox(groupBox_3);
        comboBoxProgSpeed->addItem(QString());
        comboBoxProgSpeed->addItem(QString());
        comboBoxProgSpeed->addItem(QString());
        comboBoxProgSpeed->addItem(QString());
        comboBoxProgSpeed->addItem(QString());
        comboBoxProgSpeed->addItem(QString());
        comboBoxProgSpeed->setObjectName(QStringLiteral("comboBoxProgSpeed"));

        gridLayout_3->addWidget(comboBoxProgSpeed, 1, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_3);


        gridLayout_7->addWidget(groupBox_3, 3, 1, 1, 2);

        groupBox_6 = new QGroupBox(groupBox_8);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        verticalLayout_5 = new QVBoxLayout(groupBox_6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        radioButtonNoEmulation = new QRadioButton(groupBox_6);
        radioButtonNoEmulation->setObjectName(QStringLiteral("radioButtonNoEmulation"));
        radioButtonNoEmulation->setChecked(true);

        verticalLayout_5->addWidget(radioButtonNoEmulation);

        radioButtonInputEmulation = new QRadioButton(groupBox_6);
        radioButtonInputEmulation->setObjectName(QStringLiteral("radioButtonInputEmulation"));

        verticalLayout_5->addWidget(radioButtonInputEmulation);

        radioButtonInputOutputEmulation = new QRadioButton(groupBox_6);
        radioButtonInputOutputEmulation->setObjectName(QStringLiteral("radioButtonInputOutputEmulation"));

        verticalLayout_5->addWidget(radioButtonInputOutputEmulation);

        checkBoxModbus = new QCheckBox(groupBox_6);
        checkBoxModbus->setObjectName(QStringLiteral("checkBoxModbus"));

        verticalLayout_5->addWidget(checkBoxModbus);


        gridLayout_7->addWidget(groupBox_6, 8, 1, 1, 2);

        checkBoxSD = new QCheckBox(groupBox_8);
        checkBoxSD->setObjectName(QStringLiteral("checkBoxSD"));

        gridLayout_7->addWidget(checkBoxSD, 10, 1, 1, 2);

        label_9 = new QLabel(groupBox_8);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_7->addWidget(label_9, 11, 1, 1, 1);

        checkBoxDisplay = new QCheckBox(groupBox_8);
        checkBoxDisplay->setObjectName(QStringLiteral("checkBoxDisplay"));

        gridLayout_7->addWidget(checkBoxDisplay, 9, 1, 1, 2);

        comboBoxPLCType = new QComboBox(groupBox_8);
        comboBoxPLCType->setObjectName(QStringLiteral("comboBoxPLCType"));

        gridLayout_7->addWidget(comboBoxPLCType, 11, 2, 1, 1);

        pushButtonPortListUpdate = new QPushButton(groupBox_8);
        pushButtonPortListUpdate->setObjectName(QStringLiteral("pushButtonPortListUpdate"));

        gridLayout_7->addWidget(pushButtonPortListUpdate, 14, 1, 1, 2);

        spinBoxEMemSize = new QSpinBox(groupBox_8);
        spinBoxEMemSize->setObjectName(QStringLiteral("spinBoxEMemSize"));
        spinBoxEMemSize->setMinimum(10);
        spinBoxEMemSize->setMaximum(10000);

        gridLayout_7->addWidget(spinBoxEMemSize, 5, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spinBoxProgAddr = new QSpinBox(groupBox_8);
        spinBoxProgAddr->setObjectName(QStringLiteral("spinBoxProgAddr"));
        spinBoxProgAddr->setMaximum(255);

        gridLayout->addWidget(spinBoxProgAddr, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox_8);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spinBoxNetAddr = new QSpinBox(groupBox_8);
        spinBoxNetAddr->setObjectName(QStringLiteral("spinBoxNetAddr"));
        spinBoxNetAddr->setMaximum(255);

        gridLayout->addWidget(spinBoxNetAddr, 0, 1, 1, 1);

        label = new QLabel(groupBox_8);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        gridLayout_7->addLayout(gridLayout, 0, 1, 1, 2);

        lineEditProjectDefenition = new QLineEdit(groupBox_8);
        lineEditProjectDefenition->setObjectName(QStringLiteral("lineEditProjectDefenition"));

        gridLayout_7->addWidget(lineEditProjectDefenition, 7, 1, 1, 2);

        label_10 = new QLabel(groupBox_8);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_7->addWidget(label_10, 13, 1, 1, 1);

        label_13 = new QLabel(groupBox_8);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_7->addWidget(label_13, 6, 1, 1, 1);

        label_11 = new QLabel(groupBox_8);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_7->addWidget(label_11, 5, 1, 1, 1);

        comboBoxPrPort = new QComboBox(groupBox_8);
        comboBoxPrPort->setObjectName(QStringLiteral("comboBoxPrPort"));

        gridLayout_7->addWidget(comboBoxPrPort, 13, 2, 1, 1);


        gridLayout_8->addWidget(groupBox_8, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 174, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(390, 675, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_9 = new QGridLayout(tab_2);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        radioButtonOneByte = new QRadioButton(groupBox_5);
        radioButtonOneByte->setObjectName(QStringLiteral("radioButtonOneByte"));
        radioButtonOneByte->setChecked(true);

        gridLayout_5->addWidget(radioButtonOneByte, 0, 0, 1, 1);

        radioButtonTwoBytes = new QRadioButton(groupBox_5);
        radioButtonTwoBytes->setObjectName(QStringLiteral("radioButtonTwoBytes"));

        gridLayout_5->addWidget(radioButtonTwoBytes, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(143, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 3, 1, 1);

        radioButtonFourBytes = new QRadioButton(groupBox_5);
        radioButtonFourBytes->setObjectName(QStringLiteral("radioButtonFourBytes"));

        gridLayout_5->addWidget(radioButtonFourBytes, 0, 2, 1, 1);

        tableWidget = new QTableWidget(groupBox_5);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(tableWidget, 1, 0, 3, 4);


        gridLayout_9->addWidget(groupBox_5, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout_10->addWidget(tabWidget, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_6->addWidget(scrollArea, 0, 0, 1, 4);


        retranslateUi(SettingsForm);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingsForm);
    } // setupUi

    void retranslateUi(QWidget *SettingsForm)
    {
        SettingsForm->setWindowTitle(QApplication::translate("SettingsForm", "Form", nullptr));
        pushButtonFromPLC->setText(QApplication::translate("SettingsForm", "\320\237\321\200\320\276\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
        pushButtonToPLC->setText(QApplication::translate("SettingsForm", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", nullptr));
        groupBox_8->setTitle(QString());
        groupBox_4->setTitle(QApplication::translate("SettingsForm", "\320\272\320\260\320\275\320\260\320\273 P\320\241", nullptr));
        label_7->setText(QApplication::translate("SettingsForm", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273:", nullptr));
        comboBoxPcProtocol->setItemText(0, QApplication::translate("SettingsForm", "RTU/BIN", nullptr));
        comboBoxPcProtocol->setItemText(1, QApplication::translate("SettingsForm", "ASCII", nullptr));

        label_8->setText(QApplication::translate("SettingsForm", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214:", nullptr));
        comboBoxPcSpeed->setItemText(0, QApplication::translate("SettingsForm", "4800", nullptr));
        comboBoxPcSpeed->setItemText(1, QApplication::translate("SettingsForm", "9600", nullptr));
        comboBoxPcSpeed->setItemText(2, QApplication::translate("SettingsForm", "19200", nullptr));
        comboBoxPcSpeed->setItemText(3, QApplication::translate("SettingsForm", "38400", nullptr));
        comboBoxPcSpeed->setItemText(4, QApplication::translate("SettingsForm", "57600", nullptr));
        comboBoxPcSpeed->setItemText(5, QApplication::translate("SettingsForm", "115200", nullptr));

        groupBox_2->setTitle(QString());
        label_3->setText(QApplication::translate("SettingsForm", "IP \320\260\320\264\321\200\320\265\321\201:", nullptr));
        lineEditMAC->setInputMask(QApplication::translate("SettingsForm", "HH:HH:HH:HH:HH:HH;_", nullptr));
        lineEditIP->setInputMask(QApplication::translate("SettingsForm", "000.000.000.000;_", nullptr));
        label_4->setText(QApplication::translate("SettingsForm", "MAC \320\260\320\264\321\200\320\265\321\201", nullptr));
        label_12->setText(QApplication::translate("SettingsForm", "\320\250\320\273\321\216\320\267:", nullptr));
        lineEditGATE->setInputMask(QApplication::translate("SettingsForm", "000.000.000.000;_", nullptr));
        label_14->setText(QApplication::translate("SettingsForm", "\320\234\320\260\321\201\320\272\320\260:", nullptr));
        lineEditMASK->setInputMask(QApplication::translate("SettingsForm", "000.000.000.000;_", nullptr));
        groupBox_3->setTitle(QApplication::translate("SettingsForm", "\320\272\320\260\320\275\320\260\320\273 PROG", nullptr));
        label_5->setText(QApplication::translate("SettingsForm", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273:", nullptr));
        comboBoxProgProtocol->setItemText(0, QApplication::translate("SettingsForm", "RTU/BIN", nullptr));
        comboBoxProgProtocol->setItemText(1, QApplication::translate("SettingsForm", "ASCII", nullptr));

        label_6->setText(QApplication::translate("SettingsForm", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214:", nullptr));
        comboBoxProgSpeed->setItemText(0, QApplication::translate("SettingsForm", "4800", nullptr));
        comboBoxProgSpeed->setItemText(1, QApplication::translate("SettingsForm", "9600", nullptr));
        comboBoxProgSpeed->setItemText(2, QApplication::translate("SettingsForm", "19200", nullptr));
        comboBoxProgSpeed->setItemText(3, QApplication::translate("SettingsForm", "38400", nullptr));
        comboBoxProgSpeed->setItemText(4, QApplication::translate("SettingsForm", "57600", nullptr));
        comboBoxProgSpeed->setItemText(5, QApplication::translate("SettingsForm", "115200", nullptr));

        groupBox_6->setTitle(QString());
        radioButtonNoEmulation->setText(QApplication::translate("SettingsForm", "\320\255\320\274\321\203\320\273\321\217\321\206\320\270\321\217 \320\276\321\202\320\272\320\273\321\216\321\207\320\265\320\275\320\260", nullptr));
        radioButtonInputEmulation->setText(QApplication::translate("SettingsForm", "\320\255\320\274\321\203\320\273\321\217\321\206\320\270\321\217 \320\262\321\205\320\276\320\264\320\276\320\262", nullptr));
        radioButtonInputOutputEmulation->setText(QApplication::translate("SettingsForm", "\320\255\320\274\321\203\320\273\321\217\321\206\320\270\321\217 \320\262\321\205\320\276\320\264\320\276\320\262/\320\262\321\213\321\205\320\276\320\264\320\276\320\262", nullptr));
        checkBoxModbus->setText(QApplication::translate("SettingsForm", "Modbus Master \321\215\320\274\321\203\320\273\321\217\321\206\320\270\321\217", nullptr));
        checkBoxSD->setText(QApplication::translate("SettingsForm", "\320\237\320\276\320\264\320\264\320\265\321\200\320\266\320\272\320\260 SD \320\272\320\260\321\200\321\202\321\213", nullptr));
        label_9->setText(QApplication::translate("SettingsForm", "\320\242\320\270\320\277 \320\272\320\276\320\275\321\202\321\200\320\276\320\273\320\273\320\265\321\200\320\260:", nullptr));
        checkBoxDisplay->setText(QApplication::translate("SettingsForm", "\320\240\320\260\320\267\321\200\320\265\321\210\320\270\321\202\321\214 \320\277\321\203\320\273\321\214\321\202 \320\275\320\260 \320\272\320\260\320\275\320\260\320\273\320\265 PU", nullptr));
        pushButtonPortListUpdate->setText(QApplication::translate("SettingsForm", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\321\200\321\202\320\276\320\262", nullptr));
        label_2->setText(QApplication::translate("SettingsForm", "\320\220\320\264\321\200\320\265\321\201 \320\277\321\200\320\270 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\270:", nullptr));
        label->setText(QApplication::translate("SettingsForm", "\320\241\320\265\321\202\320\265\320\262\320\276\320\271 \320\260\320\264\321\200\320\265\321\201:", nullptr));
        label_10->setText(QApplication::translate("SettingsForm", "\320\237\320\276\321\200\321\202 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217:", nullptr));
        label_13->setText(QApplication::translate("SettingsForm", "\320\276\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \320\277\321\200\320\276\320\265\320\272\321\202\320\260:", nullptr));
        label_11->setText(QApplication::translate("SettingsForm", "\320\240\320\260\321\201\321\210. \320\277\320\260\320\274\321\217\321\202\321\214 \320\277\320\276\320\273\321\214\320\267 (\321\200\320\265\320\263):", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SettingsForm", "\320\237\320\233\320\232", nullptr));
        groupBox_5->setTitle(QString());
        radioButtonOneByte->setText(QApplication::translate("SettingsForm", "1 \320\261\320\260\320\271\321\202", nullptr));
        radioButtonTwoBytes->setText(QApplication::translate("SettingsForm", "2 \320\261\320\260\320\271\321\202\320\260", nullptr));
        radioButtonFourBytes->setText(QApplication::translate("SettingsForm", "4 \320\261\320\260\320\271\321\202\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SettingsForm", "\320\227\320\260\320\262\320\276\320\264\321\201\320\272\320\270\320\265 \321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsForm: public Ui_SettingsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSFORM_H
