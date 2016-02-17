#ifndef DEBUGGERFORM_H
#define DEBUGGERFORM_H

// класс GUI для отладчика

#include <QWidget>
#include "VarDef/compositevar.h"
#include <QTreeWidgetItem>
#include "VarDef/idstorage.h"
#include "VarDef/varscreator.h"
#include "VarDef/namesortiterator.h"
#include <QHash>
#include "memstorage.h"
#include "Scanner/scanmanager.h"
#include "requestscheduler.h"
#include "bitio.h"
#include "anio.h"
#include <QGroupBox>
#include <QCheckBox>
#include "memviewdescription.h"
#include <QKeyEvent>

namespace Ui {
class DebuggerForm;
}

class DebuggerForm : public QWidget
{
    Q_OBJECT

    static const unsigned char memViewRowCount = 15;
    static const unsigned char memViewColumnCount = 30;
    MemViewDescription *memView;

    VarsCreator& varOwner;
    NameSortIterator* iter; // итератор для перемещения по основному дереву
    QHash<QString,QTreeWidgetItem*> idWidgetItem;   // переменные в основном GUI дереве
    QHash<QString,QTreeWidgetItem*> idActiveWidgetItem; // опрашиваемые переменные
    QMultiHash<int,BitIO*> ioHash;  // адрес - переменная (для вкладки входов/выходов)
    QMultiHash<int,AnIO*> anIoHash; // адрес - переменная
    QHash<QString,QLineEdit*> ioComments;   // название входа - комментарий
    QHash<QString,bool> ioCheck;    // название группы входов - состояние (свёрнута/развёрнута)
    MemStorage memStor; // хранилище памяти
    ScanManager* scan;  // управление процессом опроса
    RequestScheduler scheduler; // планировщик запросов

    VarItem wrVar;      // переменная для записи
    QCheckBox *adc8bit;
    QVector<QGroupBox*> ioBoxes;

    void clearMemViewTable(void);
    void updateMemViewRequests(void);
    void createTree();
    void updateTrees();
    void treeBuilder(const QString& varID, QTreeWidgetItem &item);// построение дерева с узла/переменной с идентификатором varID
    void updateValuesTree(void);    // обновление обоих деревьев
    void updateComPortList(void);
    void buildIO(void); // построение вкладки входов/выходов
    void buildDIO(void);
    void updateIOFoldedState(void);
    QGroupBox* addDIO(const QString & name, int startAddress, int bitCnt);
    QGroupBox* addAIO(const QString &grName, const QString &ioName, int addr, int startNum, int endNum);
    void buildAIO(void);
    void updateIOVarGUI(const QString &id);
    void updateVarGUI(const QString &id);
    void updateMemVarGUI(const QString &id);


public:
    explicit DebuggerForm(VarsCreator& vCr, QWidget *parent = 0);
    void saveView();    // сохранить состояние отладчика в файл
    void openView();    // загрузить состояние отладчика из файла
    void clearView();
    void tabChanged();
    void setNetAddress(int value);
    ~DebuggerForm();

private slots:
    // слот добавления переменной к дереву просмотра
    void on_treeWidgetMain_itemDoubleClicked(QTreeWidgetItem *item, int column);
    // удаление переменной из дерева просмотра
    void on_treeWidgetWatch_itemDoubleClicked(QTreeWidgetItem *item, int column);
    // старт опроса контроллеров отладчиком
    void on_startButton_clicked();
    // остановить опрос
    void on_stopButton_clicked();
    // вызывается хранилищем памяти для обновления значений переменных
    void updateMemory(QStringList ids);
    // обновление счётчиков корректного и ошибочного опроса
    void updateCorrErrAnswerCount(int cnt, bool correctFlag);
    // вывести текстовое сообщение в лог
    void getMessageFromDebugProcess(QString message);
    // обновить время ПЛК (GUI отображение)
    void getTimeStr(QString timeStr);
    // обновить список COM портов
    void on_pushButtonCOMUpdate_clicked();
    // автопоиск контроллера
    void on_pushButtonAutoSearch_clicked();
    // скрытие/отображение лога работы
    void on_checkBoxLog_clicked();
    // обновление времени ПЛК (команда по протоколу)
    void on_pushButtonTimeWrite_clicked();
    // запрос контекстного меню дерева просмотра - редактирование переменных
    void on_treeWidgetWatch_customContextMenuRequested(const QPoint &pos);
    void writeVar();    // записать значение, введённое в диалоге редактирования
    void inOutClicked();    // команда на запись дискретного входа/выхода
    void anInOutClicked();  // команда на запись аналогового входа/выхода
    // переключение между вкладками отладчика
    void on_tabWidget_currentChanged(int index);
    // 8 bit mode changed
    void adc8bitChanged(void);


    void on_pushButtonPing_clicked();

    void boxToggled(bool fl);
    void openInputs(void);
    void saveInputs(void);

    void on_lineEditTime_returnPressed();

    void on_lineEditMemStartAddr_textChanged(const QString &arg1);

    void on_comboBoxMemType_currentIndexChanged(const QString &arg1);
    void memViewCellPressed(int r, int c);

public slots:
    void on_updateButton_clicked(); // запрос обновления деревьев
    void openProject(void);
    void saveProject(void);
    void newProject(void);
    void updTree(void);
    void stopDebugger(void);
private:
    Ui::DebuggerForm *ui;

};

#endif // DEBUGGERFORM_H
