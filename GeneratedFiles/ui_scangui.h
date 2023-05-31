/********************************************************************************
** Form generated from reading UI file 'scangui.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANGUI_H
#define UI_SCANGUI_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ScanGUI
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *ScanGUI)
    {
        if (ScanGUI->objectName().isEmpty())
            ScanGUI->setObjectName(QStringLiteral("ScanGUI"));
        ScanGUI->resize(280, 40);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ScanGUI->sizePolicy().hasHeightForWidth());
        ScanGUI->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/srch_32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ScanGUI->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(ScanGUI);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ScanGUI);

        QMetaObject::connectSlotsByName(ScanGUI);
    } // setupUi

    void retranslateUi(QDialog *ScanGUI)
    {
        ScanGUI->setWindowTitle(QApplication::translate("ScanGUI", "\320\237\320\276\320\270\321\201\320\272 \320\272\320\276\320\275\321\202\321\200\320\276\320\273\320\273\320\265\321\200\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScanGUI: public Ui_ScanGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANGUI_H
