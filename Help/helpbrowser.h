#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QWidget>
#include <QString>
#include <QTextBrowser>

class HelpBrowser : public QWidget
{
    Q_OBJECT
    QTextBrowser *br;
public:
    explicit HelpBrowser(const QString &path, const QString &fName, QWidget *parent = 0);
    void goHome(void);
    ~HelpBrowser();

signals:

public slots:

};

#endif // HELPBROWSER_H
