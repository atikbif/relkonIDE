#ifndef PATTERNEDITORWIDGET_H
#define PATTERNEDITORWIDGET_H

#include <QWidget>

class PatternEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PatternEditorWidget(QWidget *parent = 0);
    ~PatternEditorWidget();

signals:

public slots:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PATTERNEDITORWIDGET_H
