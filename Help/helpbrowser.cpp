#include "helpbrowser.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QIcon>

HelpBrowser::HelpBrowser(const QString &path, const QString &fName, QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    br = new QTextBrowser;
    QPushButton *pCmdBack = new QPushButton(QIcon(":/left.ico"),"");
    QPushButton *pCmdForward = new QPushButton(QIcon(":/right.ico"),"");
    QPushButton *pCmdHome = new QPushButton(QIcon(":/home.ico"),"");
    connect(pCmdBack,SIGNAL(clicked()),br,SLOT(backward()));
    connect(pCmdForward,SIGNAL(clicked()),br,SLOT(forward()));
    connect(pCmdHome,SIGNAL(clicked()),br,SLOT(home()));
    connect(br,SIGNAL(backwardAvailable(bool)),pCmdBack,SLOT(setEnabled(bool)));
    connect(br,SIGNAL(forwardAvailable(bool)),pCmdForward,SLOT(setEnabled(bool)));

    br->setSearchPaths(QStringList() << path);

    QDesktopWidget desk;
    int minHeight = desk.availableGeometry().height()*0.6;
    int minWidth = desk.availableGeometry().width()*0.4;

    br->setMinimumSize(minWidth,minHeight);
    br->setSource(QString(fName));

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(pCmdBack);
    hLayout->addWidget(pCmdHome);
    hLayout->addWidget(pCmdForward);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(br);
    setLayout(vLayout);
    setAttribute( Qt::WA_QuitOnClose, false );
}

void HelpBrowser::goHome()
{
    br->home();
}

HelpBrowser::~HelpBrowser()
{

}

