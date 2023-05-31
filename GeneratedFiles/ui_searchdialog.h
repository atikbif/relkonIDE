/********************************************************************************
** Form generated from reading UI file 'searchdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDIALOG_H
#define UI_SEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SearchDialog
{
public:
    QGridLayout *gridLayout_2;
    QComboBox *comboBoxSearch;
    QPushButton *pushButtonSearch;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEditReplace;
    QPushButton *pushButtonReplace;
    QPushButton *pushButtonReplaceAll;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonForward;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBoxWholeWord;
    QRadioButton *radioButtonBackward;
    QCheckBox *checkBoxRound;
    QCheckBox *checkBoxCaseSens;
    QListWidget *listWidget;

    void setupUi(QDialog *SearchDialog)
    {
        if (SearchDialog->objectName().isEmpty())
            SearchDialog->setObjectName(QStringLiteral("SearchDialog"));
        SearchDialog->resize(666, 375);
        QIcon icon;
        icon.addFile(QStringLiteral(":/srch_32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        SearchDialog->setWindowIcon(icon);
        SearchDialog->setInputMethodHints(Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        gridLayout_2 = new QGridLayout(SearchDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        comboBoxSearch = new QComboBox(SearchDialog);
        comboBoxSearch->setObjectName(QStringLiteral("comboBoxSearch"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxSearch->sizePolicy().hasHeightForWidth());
        comboBoxSearch->setSizePolicy(sizePolicy);
        comboBoxSearch->setEditable(true);

        gridLayout_2->addWidget(comboBoxSearch, 0, 0, 1, 1);

        pushButtonSearch = new QPushButton(SearchDialog);
        pushButtonSearch->setObjectName(QStringLiteral("pushButtonSearch"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonSearch->sizePolicy().hasHeightForWidth());
        pushButtonSearch->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButtonSearch, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        lineEditReplace = new QLineEdit(SearchDialog);
        lineEditReplace->setObjectName(QStringLiteral("lineEditReplace"));
        lineEditReplace->setEchoMode(QLineEdit::Normal);

        gridLayout_2->addWidget(lineEditReplace, 1, 0, 1, 1);

        pushButtonReplace = new QPushButton(SearchDialog);
        pushButtonReplace->setObjectName(QStringLiteral("pushButtonReplace"));

        gridLayout_2->addWidget(pushButtonReplace, 1, 1, 1, 1);

        pushButtonReplaceAll = new QPushButton(SearchDialog);
        pushButtonReplaceAll->setObjectName(QStringLiteral("pushButtonReplaceAll"));

        gridLayout_2->addWidget(pushButtonReplaceAll, 1, 2, 1, 1);

        groupBox = new QGroupBox(SearchDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButtonForward = new QRadioButton(groupBox);
        radioButtonForward->setObjectName(QStringLiteral("radioButtonForward"));

        gridLayout->addWidget(radioButtonForward, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(409, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        checkBoxWholeWord = new QCheckBox(groupBox);
        checkBoxWholeWord->setObjectName(QStringLiteral("checkBoxWholeWord"));

        gridLayout->addWidget(checkBoxWholeWord, 0, 2, 1, 1);

        radioButtonBackward = new QRadioButton(groupBox);
        radioButtonBackward->setObjectName(QStringLiteral("radioButtonBackward"));

        gridLayout->addWidget(radioButtonBackward, 1, 0, 1, 1);

        checkBoxRound = new QCheckBox(groupBox);
        checkBoxRound->setObjectName(QStringLiteral("checkBoxRound"));
        checkBoxRound->setChecked(true);

        gridLayout->addWidget(checkBoxRound, 1, 1, 1, 1);

        checkBoxCaseSens = new QCheckBox(groupBox);
        checkBoxCaseSens->setObjectName(QStringLiteral("checkBoxCaseSens"));

        gridLayout->addWidget(checkBoxCaseSens, 1, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 2, 0, 1, 3);

        listWidget = new QListWidget(SearchDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout_2->addWidget(listWidget, 3, 0, 1, 3);


        retranslateUi(SearchDialog);

        QMetaObject::connectSlotsByName(SearchDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchDialog)
    {
        SearchDialog->setWindowTitle(QApplication::translate("SearchDialog", "\320\237\320\276\320\270\321\201\320\272/\320\227\320\260\320\274\320\265\320\275\320\260", nullptr));
        pushButtonSearch->setText(QApplication::translate("SearchDialog", "\320\235\320\260\320\271\321\202\320\270 (Ctrl+F)", nullptr));
        lineEditReplace->setInputMask(QString());
        pushButtonReplace->setText(QApplication::translate("SearchDialog", "\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214 (Ctrl+H)", nullptr));
        pushButtonReplaceAll->setText(QApplication::translate("SearchDialog", "\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214 \320\262\321\201\321\221", nullptr));
        groupBox->setTitle(QString());
        radioButtonForward->setText(QApplication::translate("SearchDialog", "\320\262\320\277\320\265\321\200\321\221\320\264", nullptr));
        checkBoxWholeWord->setText(QApplication::translate("SearchDialog", "\321\202\320\276\320\273\321\214\320\272\320\276 \321\206\320\265\320\273\321\213\320\265 \321\201\320\273\320\276\320\262\320\260", nullptr));
        radioButtonBackward->setText(QApplication::translate("SearchDialog", "\320\275\320\260\320\267\320\260\320\264", nullptr));
        checkBoxRound->setText(QApplication::translate("SearchDialog", "\320\267\320\260\321\206\320\270\320\272\320\273\320\270\321\202\321\214", nullptr));
        checkBoxCaseSens->setText(QApplication::translate("SearchDialog", "\321\201 \321\203\321\207\321\221\321\202\320\276\320\274 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchDialog: public Ui_SearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDIALOG_H
