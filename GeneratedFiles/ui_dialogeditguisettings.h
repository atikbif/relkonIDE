/********************************************************************************
** Form generated from reading UI file 'dialogeditguisettings.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGEDITGUISETTINGS_H
#define UI_DIALOGEDITGUISETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogEditGUISettings
{
public:
    QGridLayout *gridLayout_3;
    QLabel *label;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEditSysFont;
    QPushButton *pushButtonSysFont;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLineEdit *lineEditEdFont;
    QPushButton *pushButtonEdFont;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonColors;

    void setupUi(QDialog *DialogEditGUISettings)
    {
        if (DialogEditGUISettings->objectName().isEmpty())
            DialogEditGUISettings->setObjectName(QStringLiteral("DialogEditGUISettings"));
        DialogEditGUISettings->resize(366, 163);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogEditGUISettings->sizePolicy().hasHeightForWidth());
        DialogEditGUISettings->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(DialogEditGUISettings);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label = new QLabel(DialogEditGUISettings);
        label->setObjectName(QStringLiteral("label"));
        label->setFrameShape(QFrame::Box);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label, 0, 0, 1, 3);

        groupBox = new QGroupBox(DialogEditGUISettings);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEditSysFont = new QLineEdit(groupBox);
        lineEditSysFont->setObjectName(QStringLiteral("lineEditSysFont"));
        lineEditSysFont->setEnabled(false);

        gridLayout_2->addWidget(lineEditSysFont, 0, 0, 1, 1);

        pushButtonSysFont = new QPushButton(groupBox);
        pushButtonSysFont->setObjectName(QStringLiteral("pushButtonSysFont"));

        gridLayout_2->addWidget(pushButtonSysFont, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(DialogEditGUISettings);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEditEdFont = new QLineEdit(groupBox_2);
        lineEditEdFont->setObjectName(QStringLiteral("lineEditEdFont"));
        lineEditEdFont->setEnabled(false);

        gridLayout->addWidget(lineEditEdFont, 0, 0, 1, 1);

        pushButtonEdFont = new QPushButton(groupBox_2);
        pushButtonEdFont->setObjectName(QStringLiteral("pushButtonEdFont"));

        gridLayout->addWidget(pushButtonEdFont, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 1, 1, 1);

        pushButtonOK = new QPushButton(DialogEditGUISettings);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));

        gridLayout_3->addWidget(pushButtonOK, 2, 1, 1, 1);

        pushButtonColors = new QPushButton(DialogEditGUISettings);
        pushButtonColors->setObjectName(QStringLiteral("pushButtonColors"));

        gridLayout_3->addWidget(pushButtonColors, 2, 0, 1, 1);


        retranslateUi(DialogEditGUISettings);
        QObject::connect(pushButtonOK, SIGNAL(clicked()), DialogEditGUISettings, SLOT(accept()));

        QMetaObject::connectSlotsByName(DialogEditGUISettings);
    } // setupUi

    void retranslateUi(QDialog *DialogEditGUISettings)
    {
        DialogEditGUISettings->setWindowTitle(QApplication::translate("DialogEditGUISettings", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\201\321\200\320\265\320\264\321\213", nullptr));
        label->setText(QApplication::translate("DialogEditGUISettings", "\320\224\320\273\321\217 \320\262\321\201\321\202\321\203\320\277\320\273\320\265\320\275\320\270\321\217 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\320\271 \320\262 \321\201\320\270\320\273\321\203 \320\275\320\265\320\276\320\261\321\205\320\276\320\264\320\270\320\274 \320\277\320\265\321\200\320\265\320\267\320\260\320\277\321\203\321\201\320\272 \321\201\321\200\320\265\320\264\321\213.", nullptr));
        groupBox->setTitle(QApplication::translate("DialogEditGUISettings", "\320\241\320\270\321\201\321\202\320\265\320\274\320\275\321\213\320\271 \321\210\321\200\320\270\321\204\321\202", nullptr));
        pushButtonSysFont->setText(QApplication::translate("DialogEditGUISettings", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        groupBox_2->setTitle(QApplication::translate("DialogEditGUISettings", "\320\250\321\200\320\270\321\204\321\202 \321\200\320\265\320\264\320\260\320\272\321\202\320\276\321\200\320\260", nullptr));
        pushButtonEdFont->setText(QApplication::translate("DialogEditGUISettings", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        pushButtonOK->setText(QApplication::translate("DialogEditGUISettings", "OK", nullptr));
        pushButtonColors->setText(QApplication::translate("DialogEditGUISettings", "\321\206\320\262\320\265\321\202\320\276\320\262\320\260\321\217 \321\201\321\205\320\265\320\274\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogEditGUISettings: public Ui_DialogEditGUISettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGEDITGUISETTINGS_H
