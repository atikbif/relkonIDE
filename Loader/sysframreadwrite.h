#ifndef SYSFRAMREADWRITE_H
#define SYSFRAMREADWRITE_H

#include <QDialog>

namespace Ui {
class SysFramReadWrite;
}

class SysFramReadWrite : public QDialog
{
    Q_OBJECT

public:
    explicit SysFramReadWrite(QWidget *parent = 0);
    ~SysFramReadWrite();

private:
    Ui::SysFramReadWrite *ui;
};

#endif // SYSFRAMREADWRITE_H
