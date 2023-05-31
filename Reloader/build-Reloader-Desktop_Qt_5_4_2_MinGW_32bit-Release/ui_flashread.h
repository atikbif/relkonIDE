/********************************************************************************
** Form generated from reading UI file 'flashread.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLASHREAD_H
#define UI_FLASHREAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FlashRead
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QDialog *FlashRead)
    {
        if (FlashRead->objectName().isEmpty())
            FlashRead->setObjectName(QStringLiteral("FlashRead"));
        FlashRead->resize(400, 84);
        verticalLayout = new QVBoxLayout(FlashRead);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(FlashRead);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        progressBar = new QProgressBar(FlashRead);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);


        retranslateUi(FlashRead);

        QMetaObject::connectSlotsByName(FlashRead);
    } // setupUi

    void retranslateUi(QDialog *FlashRead)
    {
        FlashRead->setWindowTitle(QApplication::translate("FlashRead", "\320\247\321\202\320\265\320\275\320\270\320\265 \320\272\320\276\320\264\320\260 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", 0));
        label->setText(QApplication::translate("FlashRead", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class FlashRead: public Ui_FlashRead {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLASHREAD_H
