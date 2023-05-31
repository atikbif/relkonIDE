/********************************************************************************
** Form generated from reading UI file 'dialogwordcolors.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGWORDCOLORS_H
#define UI_DIALOGWORDCOLORS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DialogWordColors
{
public:
    QGridLayout *gridLayout_2;
    QListWidget *listWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogWordColors)
    {
        if (DialogWordColors->objectName().isEmpty())
            DialogWordColors->setObjectName(QStringLiteral("DialogWordColors"));
        DialogWordColors->resize(277, 312);
        gridLayout_2 = new QGridLayout(DialogWordColors);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        listWidget = new QListWidget(DialogWordColors);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout_2->addWidget(listWidget, 0, 0, 1, 1);

        groupBox = new QGroupBox(DialogWordColors);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setFlat(false);

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DialogWordColors);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(DialogWordColors);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogWordColors, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogWordColors, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogWordColors);
    } // setupUi

    void retranslateUi(QDialog *DialogWordColors)
    {
        DialogWordColors->setWindowTitle(QApplication::translate("DialogWordColors", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\206\320\262\320\265\321\202\320\276\320\262\320\276\320\271 \321\201\321\205\320\265\320\274\321\213", nullptr));
        groupBox->setTitle(QApplication::translate("DialogWordColors", "\320\246\320\262\320\265\321\202", nullptr));
        pushButton->setText(QApplication::translate("DialogWordColors", "\320\270\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        checkBox->setText(QApplication::translate("DialogWordColors", "\320\241\320\276\320\261\321\201\321\202\320\262\320\265\320\275\320\275\321\213\320\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogWordColors: public Ui_DialogWordColors {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWORDCOLORS_H
