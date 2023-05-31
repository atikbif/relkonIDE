/********************************************************************************
** Form generated from reading UI file 'sysframreadwrite.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSFRAMREADWRITE_H
#define UI_SYSFRAMREADWRITE_H

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

class Ui_SysFramReadWrite
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QDialog *SysFramReadWrite)
    {
        if (SysFramReadWrite->objectName().isEmpty())
            SysFramReadWrite->setObjectName(QStringLiteral("SysFramReadWrite"));
        SysFramReadWrite->resize(320, 74);
        verticalLayout = new QVBoxLayout(SysFramReadWrite);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(SysFramReadWrite);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        progressBar = new QProgressBar(SysFramReadWrite);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);


        retranslateUi(SysFramReadWrite);

        QMetaObject::connectSlotsByName(SysFramReadWrite);
    } // setupUi

    void retranslateUi(QDialog *SysFramReadWrite)
    {
        SysFramReadWrite->setWindowTitle(QApplication::translate("SysFramReadWrite", "\320\241\320\270\321\201\321\202\320\265\320\274\320\275\321\213\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\237\320\233\320\232", 0));
        label->setText(QApplication::translate("SysFramReadWrite", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class SysFramReadWrite: public Ui_SysFramReadWrite {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSFRAMREADWRITE_H
