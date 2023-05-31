/********************************************************************************
** Form generated from reading UI file 'ymodemthread.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YMODEMTHREAD_H
#define UI_YMODEMTHREAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_YmodemThread
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *YmodemThread)
    {
        if (YmodemThread->objectName().isEmpty())
            YmodemThread->setObjectName(QStringLiteral("YmodemThread"));
        YmodemThread->resize(246, 26);
        verticalLayout = new QVBoxLayout(YmodemThread);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        retranslateUi(YmodemThread);

        QMetaObject::connectSlotsByName(YmodemThread);
    } // setupUi

    void retranslateUi(QDialog *YmodemThread)
    {
        YmodemThread->setWindowTitle(QApplication::translate("YmodemThread", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class YmodemThread: public Ui_YmodemThread {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YMODEMTHREAD_H
