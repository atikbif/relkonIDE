/********************************************************************************
** Form generated from reading UI file 'dialogwritevar.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGWRITEVAR_H
#define UI_DIALOGWRITEVAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogWriteVar
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogWriteVar)
    {
        if (DialogWriteVar->objectName().isEmpty())
            DialogWriteVar->setObjectName(QStringLiteral("DialogWriteVar"));
        DialogWriteVar->resize(203, 88);
        verticalLayout_2 = new QVBoxLayout(DialogWriteVar);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(DialogWriteVar);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(DialogWriteVar);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        buttonBox = new QDialogButtonBox(DialogWriteVar);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(DialogWriteVar);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogWriteVar, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogWriteVar, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogWriteVar);
    } // setupUi

    void retranslateUi(QDialog *DialogWriteVar)
    {
        DialogWriteVar->setWindowTitle(QApplication::translate("DialogWriteVar", "\320\227\320\260\320\277\320\270\321\201\321\214 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271", nullptr));
        label->setText(QApplication::translate("DialogWriteVar", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogWriteVar: public Ui_DialogWriteVar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWRITEVAR_H
