/********************************************************************************
** Form generated from reading UI file 'dialoggotostring.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGGOTOSTRING_H
#define UI_DIALOGGOTOSTRING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_DialogGoToString
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBoxStrNum;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogGoToString)
    {
        if (DialogGoToString->objectName().isEmpty())
            DialogGoToString->setObjectName(QStringLiteral("DialogGoToString"));
        DialogGoToString->resize(174, 67);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogGoToString->sizePolicy().hasHeightForWidth());
        DialogGoToString->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(DialogGoToString);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(DialogGoToString);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBoxStrNum = new QSpinBox(DialogGoToString);
        spinBoxStrNum->setObjectName(QStringLiteral("spinBoxStrNum"));
        spinBoxStrNum->setMinimum(1);
        spinBoxStrNum->setMaximum(10000);

        gridLayout->addWidget(spinBoxStrNum, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(DialogGoToString);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 2);


        retranslateUi(DialogGoToString);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogGoToString, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogGoToString, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogGoToString);
    } // setupUi

    void retranslateUi(QDialog *DialogGoToString)
    {
        DialogGoToString->setWindowTitle(QApplication::translate("DialogGoToString", "\320\237\320\265\321\200\320\265\321\205\320\276\320\264 \320\272 \321\201\321\202\321\200\320\276\320\272\320\265", nullptr));
        label->setText(QApplication::translate("DialogGoToString", "\320\235\320\276\320\274\320\265\321\200 \321\201\321\202\321\200\320\276\320\272\320\270:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogGoToString: public Ui_DialogGoToString {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGGOTOSTRING_H
