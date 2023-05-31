/********************************************************************************
** Form generated from reading UI file 'lcdform.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LCDFORM_H
#define UI_LCDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LCDForm
{
public:

    void setupUi(QWidget *LCDForm)
    {
        if (LCDForm->objectName().isEmpty())
            LCDForm->setObjectName(QStringLiteral("LCDForm"));
        LCDForm->resize(485, 389);

        retranslateUi(LCDForm);

        QMetaObject::connectSlotsByName(LCDForm);
    } // setupUi

    void retranslateUi(QWidget *LCDForm)
    {
        LCDForm->setWindowTitle(QApplication::translate("LCDForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LCDForm: public Ui_LCDForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LCDFORM_H
