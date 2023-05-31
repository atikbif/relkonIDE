/********************************************************************************
** Form generated from reading UI file 'debuggerform.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGGERFORM_H
#define UI_DEBUGGERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebuggerForm
{
public:
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_9;
    QLCDNumber *lcdNumberError;
    QLCDNumber *lcdNumberCorrect;
    QPushButton *startButton;
    QPushButton *updateButton;
    QPushButton *stopButton;
    QTabWidget *tabWidgetCanal;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QComboBox *comboBoxCOM;
    QComboBox *comboBoxProtocol;
    QLabel *label_4;
    QComboBox *comboBoxSpeed;
    QPushButton *pushButtonCOMUpdate;
    QLabel *label;
    QSpinBox *spinBoxNetAddress;
    QLineEdit *lineEditCanal;
    QPushButton *pushButtonAutoSearch;
    QWidget *tab_2;
    QGridLayout *gridLayout_5;
    QLabel *label_7;
    QPushButton *pushButtonPing;
    QLineEdit *lineEditIP;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButtonCOM;
    QCheckBox *checkBoxLog;
    QRadioButton *radioButtonUDP;
    QCheckBox *checkBoxQuickWatch;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QPushButton *pushButtonOpenInp;
    QPushButton *pushButtonSaveInp;
    QPushButton *pushButtonOpenLastInp;
    QPushButton *pushButtonSaveLastInp;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditTime;
    QPushButton *pushButtonTimeWrite;
    QTextBrowser *textBrowserRequests;
    QTabWidget *tabWidget;
    QWidget *tabVar;
    QGridLayout *gridLayout;
    QPushButton *pushButtonSaveVars;
    QPushButton *pushButtonLoadVars;
    QPushButton *pushButtonDown;
    QPushButton *pushButtonUp;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonClear;
    QSpacerItem *horizontalSpacer_3;
    QTreeWidget *treeWidgetWatch;
    QTreeWidget *treeWidgetMain;
    QWidget *tabInOut;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *tab_3;
    QGridLayout *gridLayout_7;
    QLabel *label_8;
    QLabel *label_3;
    QComboBox *comboBoxMemType;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEditMemStartAddr;
    QSpinBox *spinBoxByteCnt;
    QTableWidget *tableWidgetMem;
    QCheckBox *checkBoxHexMem;

    void setupUi(QWidget *DebuggerForm)
    {
        if (DebuggerForm->objectName().isEmpty())
            DebuggerForm->setObjectName(QStringLiteral("DebuggerForm"));
        DebuggerForm->resize(1005, 755);
        gridLayout_6 = new QGridLayout(DebuggerForm);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        groupBox_2 = new QGroupBox(DebuggerForm);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy1);
        groupBox_6->setMaximumSize(QSize(1000, 16777215));
        gridLayout_9 = new QGridLayout(groupBox_6);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        lcdNumberError = new QLCDNumber(groupBox_6);
        lcdNumberError->setObjectName(QStringLiteral("lcdNumberError"));
        sizePolicy.setHeightForWidth(lcdNumberError->sizePolicy().hasHeightForWidth());
        lcdNumberError->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(170, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lcdNumberError->setPalette(palette);
        lcdNumberError->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_9->addWidget(lcdNumberError, 1, 0, 1, 1);

        lcdNumberCorrect = new QLCDNumber(groupBox_6);
        lcdNumberCorrect->setObjectName(QStringLiteral("lcdNumberCorrect"));
        sizePolicy.setHeightForWidth(lcdNumberCorrect->sizePolicy().hasHeightForWidth());
        lcdNumberCorrect->setSizePolicy(sizePolicy);
        QPalette palette1;
        QBrush brush2(QColor(0, 85, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        QBrush brush3(QColor(0, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        lcdNumberCorrect->setPalette(palette1);
        lcdNumberCorrect->setInputMethodHints(Qt::ImhDialableCharactersOnly|Qt::ImhDigitsOnly|Qt::ImhEmailCharactersOnly|Qt::ImhFormattedNumbersOnly|Qt::ImhLatinOnly|Qt::ImhLowercaseOnly|Qt::ImhUppercaseOnly|Qt::ImhUrlCharactersOnly);
        lcdNumberCorrect->setFrameShape(QFrame::Box);
        lcdNumberCorrect->setFrameShadow(QFrame::Raised);
        lcdNumberCorrect->setSmallDecimalPoint(false);
        lcdNumberCorrect->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_9->addWidget(lcdNumberCorrect, 0, 0, 1, 1);

        startButton = new QPushButton(groupBox_6);
        startButton->setObjectName(QStringLiteral("startButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(2);
        sizePolicy2.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy2);
        startButton->setAutoFillBackground(false);
        startButton->setAutoDefault(false);
        startButton->setFlat(false);

        gridLayout_9->addWidget(startButton, 2, 0, 1, 1);

        updateButton = new QPushButton(groupBox_6);
        updateButton->setObjectName(QStringLiteral("updateButton"));
        updateButton->setEnabled(true);
        updateButton->setLayoutDirection(Qt::LeftToRight);
        updateButton->setAutoFillBackground(false);
        updateButton->setFlat(false);

        gridLayout_9->addWidget(updateButton, 4, 0, 1, 1);

        stopButton = new QPushButton(groupBox_6);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setEnabled(false);
        sizePolicy2.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy2);

        gridLayout_9->addWidget(stopButton, 3, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox_6);

        tabWidgetCanal = new QTabWidget(groupBox_2);
        tabWidgetCanal->setObjectName(QStringLiteral("tabWidgetCanal"));
        sizePolicy1.setHeightForWidth(tabWidgetCanal->sizePolicy().hasHeightForWidth());
        tabWidgetCanal->setSizePolicy(sizePolicy1);
        tabWidgetCanal->setTabPosition(QTabWidget::West);
        tabWidgetCanal->setTabShape(QTabWidget::Triangular);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 2, 0, 1, 2);

        comboBoxCOM = new QComboBox(tab);
        comboBoxCOM->addItem(QString());
        comboBoxCOM->setObjectName(QStringLiteral("comboBoxCOM"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBoxCOM->sizePolicy().hasHeightForWidth());
        comboBoxCOM->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(comboBoxCOM, 0, 0, 1, 2);

        comboBoxProtocol = new QComboBox(tab);
        comboBoxProtocol->addItem(QString());
        comboBoxProtocol->addItem(QString());
        comboBoxProtocol->setObjectName(QStringLiteral("comboBoxProtocol"));
        sizePolicy3.setHeightForWidth(comboBoxProtocol->sizePolicy().hasHeightForWidth());
        comboBoxProtocol->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(comboBoxProtocol, 3, 2, 1, 1);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 3, 0, 1, 2);

        comboBoxSpeed = new QComboBox(tab);
        comboBoxSpeed->addItem(QString());
        comboBoxSpeed->addItem(QString());
        comboBoxSpeed->addItem(QString());
        comboBoxSpeed->addItem(QString());
        comboBoxSpeed->addItem(QString());
        comboBoxSpeed->addItem(QString());
        comboBoxSpeed->setObjectName(QStringLiteral("comboBoxSpeed"));
        sizePolicy3.setHeightForWidth(comboBoxSpeed->sizePolicy().hasHeightForWidth());
        comboBoxSpeed->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(comboBoxSpeed, 2, 2, 1, 1);

        pushButtonCOMUpdate = new QPushButton(tab);
        pushButtonCOMUpdate->setObjectName(QStringLiteral("pushButtonCOMUpdate"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButtonCOMUpdate->sizePolicy().hasHeightForWidth());
        pushButtonCOMUpdate->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(pushButtonCOMUpdate, 0, 2, 1, 1);

        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 4, 0, 1, 1);

        spinBoxNetAddress = new QSpinBox(tab);
        spinBoxNetAddress->setObjectName(QStringLiteral("spinBoxNetAddress"));
        spinBoxNetAddress->setMaximum(255);

        gridLayout_3->addWidget(spinBoxNetAddress, 4, 2, 1, 1);

        lineEditCanal = new QLineEdit(tab);
        lineEditCanal->setObjectName(QStringLiteral("lineEditCanal"));
        lineEditCanal->setEnabled(false);

        gridLayout_3->addWidget(lineEditCanal, 7, 0, 1, 3);

        pushButtonAutoSearch = new QPushButton(tab);
        pushButtonAutoSearch->setObjectName(QStringLiteral("pushButtonAutoSearch"));
        sizePolicy3.setHeightForWidth(pushButtonAutoSearch->sizePolicy().hasHeightForWidth());
        pushButtonAutoSearch->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(pushButtonAutoSearch, 6, 0, 1, 3);

        tabWidgetCanal->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_5 = new QGridLayout(tab_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 0, 0, 1, 1);

        pushButtonPing = new QPushButton(tab_2);
        pushButtonPing->setObjectName(QStringLiteral("pushButtonPing"));

        gridLayout_5->addWidget(pushButtonPing, 0, 1, 1, 1);

        lineEditIP = new QLineEdit(tab_2);
        lineEditIP->setObjectName(QStringLiteral("lineEditIP"));

        gridLayout_5->addWidget(lineEditIP, 1, 0, 1, 2);

        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_5->addWidget(label_2, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 85, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 3, 1, 1, 1);

        tabWidgetCanal->addTab(tab_2, QString());

        horizontalLayout_2->addWidget(tabWidgetCanal);

        groupBox = new QGroupBox(groupBox_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        radioButtonCOM = new QRadioButton(groupBox);
        radioButtonCOM->setObjectName(QStringLiteral("radioButtonCOM"));
        radioButtonCOM->setChecked(true);

        gridLayout_2->addWidget(radioButtonCOM, 3, 0, 1, 1);

        checkBoxLog = new QCheckBox(groupBox);
        checkBoxLog->setObjectName(QStringLiteral("checkBoxLog"));
        checkBoxLog->setEnabled(true);
        checkBoxLog->setLayoutDirection(Qt::LeftToRight);
        checkBoxLog->setChecked(false);

        gridLayout_2->addWidget(checkBoxLog, 5, 0, 1, 1);

        radioButtonUDP = new QRadioButton(groupBox);
        radioButtonUDP->setObjectName(QStringLiteral("radioButtonUDP"));

        gridLayout_2->addWidget(radioButtonUDP, 3, 1, 1, 1);

        checkBoxQuickWatch = new QCheckBox(groupBox);
        checkBoxQuickWatch->setObjectName(QStringLiteral("checkBoxQuickWatch"));
        checkBoxQuickWatch->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(checkBoxQuickWatch, 6, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 7, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox);

        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        gridLayout_8 = new QGridLayout(groupBox_3);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        pushButtonOpenInp = new QPushButton(groupBox_5);
        pushButtonOpenInp->setObjectName(QStringLiteral("pushButtonOpenInp"));

        gridLayout_4->addWidget(pushButtonOpenInp, 0, 0, 1, 1);

        pushButtonSaveInp = new QPushButton(groupBox_5);
        pushButtonSaveInp->setObjectName(QStringLiteral("pushButtonSaveInp"));

        gridLayout_4->addWidget(pushButtonSaveInp, 0, 1, 1, 1);

        pushButtonOpenLastInp = new QPushButton(groupBox_5);
        pushButtonOpenLastInp->setObjectName(QStringLiteral("pushButtonOpenLastInp"));
        pushButtonOpenLastInp->setEnabled(false);

        gridLayout_4->addWidget(pushButtonOpenLastInp, 1, 0, 1, 1);

        pushButtonSaveLastInp = new QPushButton(groupBox_5);
        pushButtonSaveLastInp->setObjectName(QStringLiteral("pushButtonSaveLastInp"));
        pushButtonSaveLastInp->setEnabled(false);

        gridLayout_4->addWidget(pushButtonSaveLastInp, 1, 1, 1, 1);


        gridLayout_8->addWidget(groupBox_5, 1, 0, 1, 1);

        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        sizePolicy3.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy3);
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEditTime = new QLineEdit(groupBox_4);
        lineEditTime->setObjectName(QStringLiteral("lineEditTime"));
        lineEditTime->setEnabled(true);
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lineEditTime->sizePolicy().hasHeightForWidth());
        lineEditTime->setSizePolicy(sizePolicy5);
        lineEditTime->setReadOnly(false);

        verticalLayout->addWidget(lineEditTime);

        pushButtonTimeWrite = new QPushButton(groupBox_4);
        pushButtonTimeWrite->setObjectName(QStringLiteral("pushButtonTimeWrite"));
        pushButtonTimeWrite->setEnabled(false);
        sizePolicy4.setHeightForWidth(pushButtonTimeWrite->sizePolicy().hasHeightForWidth());
        pushButtonTimeWrite->setSizePolicy(sizePolicy4);

        verticalLayout->addWidget(pushButtonTimeWrite);


        gridLayout_8->addWidget(groupBox_4, 0, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox_3);

        textBrowserRequests = new QTextBrowser(groupBox_2);
        textBrowserRequests->setObjectName(QStringLiteral("textBrowserRequests"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(10);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(textBrowserRequests->sizePolicy().hasHeightForWidth());
        textBrowserRequests->setSizePolicy(sizePolicy6);
        textBrowserRequests->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_2->addWidget(textBrowserRequests);


        gridLayout_6->addWidget(groupBox_2, 1, 0, 1, 1);

        tabWidget = new QTabWidget(DebuggerForm);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(3);
        sizePolicy7.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy7);
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabPosition(QTabWidget::West);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabWidget->setDocumentMode(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        tabVar = new QWidget();
        tabVar->setObjectName(QStringLiteral("tabVar"));
        gridLayout = new QGridLayout(tabVar);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButtonSaveVars = new QPushButton(tabVar);
        pushButtonSaveVars->setObjectName(QStringLiteral("pushButtonSaveVars"));

        gridLayout->addWidget(pushButtonSaveVars, 3, 10, 1, 1);

        pushButtonLoadVars = new QPushButton(tabVar);
        pushButtonLoadVars->setObjectName(QStringLiteral("pushButtonLoadVars"));

        gridLayout->addWidget(pushButtonLoadVars, 3, 11, 1, 1);

        pushButtonDown = new QPushButton(tabVar);
        pushButtonDown->setObjectName(QStringLiteral("pushButtonDown"));

        gridLayout->addWidget(pushButtonDown, 3, 8, 1, 1);

        pushButtonUp = new QPushButton(tabVar);
        pushButtonUp->setObjectName(QStringLiteral("pushButtonUp"));

        gridLayout->addWidget(pushButtonUp, 3, 7, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 9, 1, 1);

        pushButtonClear = new QPushButton(tabVar);
        pushButtonClear->setObjectName(QStringLiteral("pushButtonClear"));

        gridLayout->addWidget(pushButtonClear, 3, 5, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 6, 1, 1);

        treeWidgetWatch = new QTreeWidget(tabVar);
        treeWidgetWatch->setObjectName(QStringLiteral("treeWidgetWatch"));
        QSizePolicy sizePolicy8(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy8.setHorizontalStretch(5);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(treeWidgetWatch->sizePolicy().hasHeightForWidth());
        treeWidgetWatch->setSizePolicy(sizePolicy8);
        treeWidgetWatch->setSortingEnabled(false);

        gridLayout->addWidget(treeWidgetWatch, 0, 5, 3, 7);

        treeWidgetMain = new QTreeWidget(tabVar);
        QFont font;
        font.setKerning(true);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setFont(0, font);
        treeWidgetMain->setHeaderItem(__qtreewidgetitem);
        treeWidgetMain->setObjectName(QStringLiteral("treeWidgetMain"));
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy9.setHorizontalStretch(3);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(treeWidgetMain->sizePolicy().hasHeightForWidth());
        treeWidgetMain->setSizePolicy(sizePolicy9);
        treeWidgetMain->setFrameShape(QFrame::StyledPanel);
        treeWidgetMain->setFrameShadow(QFrame::Sunken);
        treeWidgetMain->setAutoExpandDelay(-1);
        treeWidgetMain->header()->setCascadingSectionResizes(false);

        gridLayout->addWidget(treeWidgetMain, 0, 0, 4, 5);

        tabWidget->addTab(tabVar, QString());
        tabInOut = new QWidget();
        tabInOut->setObjectName(QStringLiteral("tabInOut"));
        horizontalLayout = new QHBoxLayout(tabInOut);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        scrollArea = new QScrollArea(tabInOut);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        sizePolicy8.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy8);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 671, 493));
        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        scrollArea_2 = new QScrollArea(tabInOut);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        QSizePolicy sizePolicy10(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy10.setHorizontalStretch(2);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy10);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 267, 493));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout->addWidget(scrollArea_2);

        tabWidget->addTab(tabInOut, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_7 = new QGridLayout(tab_3);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_7->addWidget(label_8, 0, 3, 1, 1);

        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_7->addWidget(label_3, 0, 1, 1, 1);

        comboBoxMemType = new QComboBox(tab_3);
        comboBoxMemType->addItem(QString());
        comboBoxMemType->addItem(QString());
        comboBoxMemType->setObjectName(QStringLiteral("comboBoxMemType"));

        gridLayout_7->addWidget(comboBoxMemType, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(668, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer, 0, 6, 1, 1);

        lineEditMemStartAddr = new QLineEdit(tab_3);
        lineEditMemStartAddr->setObjectName(QStringLiteral("lineEditMemStartAddr"));
        QSizePolicy sizePolicy11(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(lineEditMemStartAddr->sizePolicy().hasHeightForWidth());
        lineEditMemStartAddr->setSizePolicy(sizePolicy11);

        gridLayout_7->addWidget(lineEditMemStartAddr, 0, 2, 1, 1);

        spinBoxByteCnt = new QSpinBox(tab_3);
        spinBoxByteCnt->setObjectName(QStringLiteral("spinBoxByteCnt"));
        spinBoxByteCnt->setMinimum(1);
        spinBoxByteCnt->setMaximum(256);

        gridLayout_7->addWidget(spinBoxByteCnt, 0, 4, 1, 1);

        tableWidgetMem = new QTableWidget(tab_3);
        tableWidgetMem->setObjectName(QStringLiteral("tableWidgetMem"));

        gridLayout_7->addWidget(tableWidgetMem, 1, 0, 1, 7);

        checkBoxHexMem = new QCheckBox(tab_3);
        checkBoxHexMem->setObjectName(QStringLiteral("checkBoxHexMem"));
        checkBoxHexMem->setLayoutDirection(Qt::RightToLeft);

        gridLayout_7->addWidget(checkBoxHexMem, 0, 5, 1, 1);

        tabWidget->addTab(tab_3, QString());

        gridLayout_6->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(DebuggerForm);

        tabWidgetCanal->setCurrentIndex(0);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(DebuggerForm);
    } // setupUi

    void retranslateUi(QWidget *DebuggerForm)
    {
        DebuggerForm->setWindowTitle(QApplication::translate("DebuggerForm", "Form", nullptr));
        groupBox_2->setTitle(QString());
        groupBox_6->setTitle(QString());
        startButton->setText(QApplication::translate("DebuggerForm", "\321\201\321\202\320\260\321\200\321\202", nullptr));
        updateButton->setText(QString());
        stopButton->setText(QApplication::translate("DebuggerForm", "\321\201\321\202\320\276\320\277", nullptr));
        label_5->setText(QApplication::translate("DebuggerForm", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214:", nullptr));
        comboBoxCOM->setItemText(0, QApplication::translate("DebuggerForm", "COM1", nullptr));

        comboBoxProtocol->setItemText(0, QApplication::translate("DebuggerForm", "BIN", nullptr));
        comboBoxProtocol->setItemText(1, QApplication::translate("DebuggerForm", "ASCII", nullptr));

        label_4->setText(QApplication::translate("DebuggerForm", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273:", nullptr));
        comboBoxSpeed->setItemText(0, QApplication::translate("DebuggerForm", "4800", nullptr));
        comboBoxSpeed->setItemText(1, QApplication::translate("DebuggerForm", "9600", nullptr));
        comboBoxSpeed->setItemText(2, QApplication::translate("DebuggerForm", "19200", nullptr));
        comboBoxSpeed->setItemText(3, QApplication::translate("DebuggerForm", "38400", nullptr));
        comboBoxSpeed->setItemText(4, QApplication::translate("DebuggerForm", "57600", nullptr));
        comboBoxSpeed->setItemText(5, QApplication::translate("DebuggerForm", "115200", nullptr));

        pushButtonCOMUpdate->setText(QApplication::translate("DebuggerForm", "\320\276\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        label->setText(QApplication::translate("DebuggerForm", "\320\241\320\265\321\202\320\265\320\262\320\276\320\271 \320\260\320\264\321\200\320\265\321\201:", nullptr));
        pushButtonAutoSearch->setText(QApplication::translate("DebuggerForm", "\320\277\320\276\320\270\321\201\320\272", nullptr));
        tabWidgetCanal->setTabText(tabWidgetCanal->indexOf(tab), QApplication::translate("DebuggerForm", "COM", nullptr));
        label_7->setText(QApplication::translate("DebuggerForm", "IP \320\260\320\264\321\200\320\265\321\201:", nullptr));
        pushButtonPing->setText(QApplication::translate("DebuggerForm", "PING", nullptr));
        label_2->setText(QApplication::translate("DebuggerForm", "\320\277\320\276\321\200\321\202: 12144", nullptr));
        tabWidgetCanal->setTabText(tabWidgetCanal->indexOf(tab_2), QApplication::translate("DebuggerForm", "UDP", nullptr));
        groupBox->setTitle(QString());
        radioButtonCOM->setText(QApplication::translate("DebuggerForm", "COM", nullptr));
        checkBoxLog->setText(QApplication::translate("DebuggerForm", "\320\273\320\276\320\263", nullptr));
        radioButtonUDP->setText(QApplication::translate("DebuggerForm", "UDP", nullptr));
        checkBoxQuickWatch->setText(QApplication::translate("DebuggerForm", "\320\261\321\213\321\201\321\202\321\200. \320\277\321\200\320\276\321\201\320\274.", nullptr));
        groupBox_3->setTitle(QString());
        groupBox_5->setTitle(QApplication::translate("DebuggerForm", "\320\241\320\273\320\265\320\277\320\276\320\272 \320\262\321\205\320\276\320\264\320\276\320\262", nullptr));
        pushButtonOpenInp->setText(QApplication::translate("DebuggerForm", "\320\267\320\260\320\263\321\200.", nullptr));
        pushButtonSaveInp->setText(QApplication::translate("DebuggerForm", "\321\201\320\276\321\205\321\200.\320\272\320\260\320\272", nullptr));
        pushButtonOpenLastInp->setText(QApplication::translate("DebuggerForm", "\320\267\320\260\320\263\321\200. \320\277\320\276\321\201\320\273.", nullptr));
        pushButtonSaveLastInp->setText(QApplication::translate("DebuggerForm", "\321\201\320\276\321\205\321\200.", nullptr));
        groupBox_4->setTitle(QApplication::translate("DebuggerForm", "\320\222\321\200\320\265\320\274\321\217 \320\237\320\233\320\232", nullptr));
        pushButtonTimeWrite->setText(QApplication::translate("DebuggerForm", "\320\241\320\270\320\275\321\205\321\200. \321\201 \320\237\320\232", nullptr));
        pushButtonSaveVars->setText(QApplication::translate("DebuggerForm", "\321\201\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        pushButtonLoadVars->setText(QApplication::translate("DebuggerForm", "\320\267\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        pushButtonDown->setText(QApplication::translate("DebuggerForm", "\320\236\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        pushButtonUp->setText(QApplication::translate("DebuggerForm", "\320\237\320\276\320\264\320\275\321\217\321\202\321\214", nullptr));
        pushButtonClear->setText(QApplication::translate("DebuggerForm", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidgetWatch->headerItem();
        ___qtreewidgetitem->setText(5, QApplication::translate("DebuggerForm", "\320\272\320\276\320\274\320\274\320\265\320\275\321\202\320\260\321\200\320\270\320\271", nullptr));
        ___qtreewidgetitem->setText(4, QApplication::translate("DebuggerForm", "\321\202\320\270\320\277", nullptr));
        ___qtreewidgetitem->setText(3, QApplication::translate("DebuggerForm", "\320\260\320\264\321\200\320\265\321\201", nullptr));
        ___qtreewidgetitem->setText(2, QApplication::translate("DebuggerForm", "\320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265 HEX", nullptr));
        ___qtreewidgetitem->setText(1, QApplication::translate("DebuggerForm", "\320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265 DEC", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("DebuggerForm", "\320\270\320\274\321\217", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidgetMain->headerItem();
        ___qtreewidgetitem1->setText(1, QApplication::translate("DebuggerForm", "\321\202\320\270\320\277 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        ___qtreewidgetitem1->setText(0, QApplication::translate("DebuggerForm", "\320\230\320\274\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabVar), QApplication::translate("DebuggerForm", "\320\237\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\320\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabInOut), QApplication::translate("DebuggerForm", "\320\222\321\205\320\276\320\264\321\213/\320\262\321\213\321\205\320\276\320\264\321\213", nullptr));
        label_8->setText(QApplication::translate("DebuggerForm", "\320\272\320\276\320\273-\320\262\320\276 \320\261\320\260\320\271\321\202:", nullptr));
        label_3->setText(QApplication::translate("DebuggerForm", "\320\260\320\264\321\200\320\265\321\201:", nullptr));
        comboBoxMemType->setItemText(0, QApplication::translate("DebuggerForm", "FRAM", nullptr));
        comboBoxMemType->setItemText(1, QApplication::translate("DebuggerForm", "RAM", nullptr));

        lineEditMemStartAddr->setText(QApplication::translate("DebuggerForm", "0x00", nullptr));
        checkBoxHexMem->setText(QApplication::translate("DebuggerForm", "HEX", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("DebuggerForm", "\320\277\320\260\320\274\321\217\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DebuggerForm: public Ui_DebuggerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGGERFORM_H
