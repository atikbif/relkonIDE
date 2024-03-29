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
#include "QuickWatch/varwatchermanager.h"

namespace Ui {
class DebuggerForm;
}


class DebuggerForm : public QWidget
{
    Q_OBJECT

    static const unsigned char memViewRowCount = 20;
    static const unsigned char memViewColumnCount = 16;
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
    QString lastOpenInpFile;    // последний открытый файл с состоянием входов и переменных отладчика
    QString lastSaveInpFile;    // последний открытый файл с состоянием входов и переменных отладчика
    VarItem wrVar;      // переменная для записи
    QCheckBox *adc8bit;
    QVector<QGroupBox*> ioBoxes;
    VarWatcherManager* quick;
    QString plcType;
    int memStartAddr;
    int memLength;
    int startCheckTmr=0;    // счётчик для вывода сообщения о неподключенном контроллере при старте

    int ioNum = 1;

    void clearMemViewTable();
    void updateMemViewRequests(void);   // формирование очереди запросов планировщика для просмотра памяти
    void createTree();  // построение дерева переменных проекта
    void treeBuilder(const QString& varID, QTreeWidgetItem &item);// построение дерева с узла/переменной с идентификатором varID
    void updateValuesTree(void);    // обновление обоих деревьев
    void updateComPortList(void);
    void buildIO(void); // построение вкладки входов/выходов
    void buildDIO(void);
    void buildAIO(void);
    void updateIOFoldedState(void); // сворачивает/разворачивает все QGroupBox вх/вых в соответсвии с состоянием ioCheck
    QGroupBox* addDIO(const QString & name, int startAddress, int bitCnt); // создаёт QGroupBox с дискретными вх/вых
    QVector<QGroupBox*> addAIO(const QString &grName, const QString &ioName, int addr, int startNum, int endNum);
    void updateIOVarGUI(const QString &id); // обновление GUI вх/вых по значению переменной
    void updateVarGUI(const QString &id);   // обновление GUI опрашиваемых переменных
    void updateMemVarGUI(const QString &id);    // обновление ячеек таблицы при опросе памяти
    void updateMatchboxVisibility();    // скрытие неиспользуемых входов/выходов
    int getIOAddrByName(const QString &name);   // возвращает адрес дискретного или аналогового вх/вых по имени
    void openInputs(const QString &fName);  // открыть файл с состоянием входов и опрашиваемых переменных и записать их в контроллер

public:
    explicit DebuggerForm(VarsCreator& vCr, QWidget *parent = 0);
    void saveView();    // сохранить состояние отладчика в файл
    void openView();    // загрузить состояние отладчика из файла
    void clearView();
    void tabChanged();
    void setNetAddress(int value);
    void closeQuickWatch();
    void setIP(const QString &ip);
    ~DebuggerForm();

private slots:
    void on_treeWidgetMain_itemDoubleClicked(QTreeWidgetItem *item, int column);    // слот добавления переменной к дереву просмотра
    void on_treeWidgetWatch_itemDoubleClicked(QTreeWidgetItem *item, int column);   // удаление переменной из дерева просмотра
    void on_startButton_clicked();  // старт опроса контроллеров отладчиком
    void on_stopButton_clicked();   // остановить опрос
    void on_pushButtonCOMUpdate_clicked();  // обновить список COM портов
    void on_pushButtonAutoSearch_clicked(); // автопоиск контроллера
    void on_pushButtonTimeWrite_clicked();  // обновление времени ПЛК (команда по протоколу)
    void on_treeWidgetWatch_customContextMenuRequested(const QPoint &pos);  // запрос контекстного меню дерева просмотра - редактирование переменных
    void on_tabWidget_currentChanged(int index);    // переключение между вкладками отладчика
    void on_lineEditTime_returnPressed();   // запись введённого времени в контроллер
    void on_pushButtonPing_clicked();
    void on_lineEditMemStartAddr_textChanged(const QString &arg1);  // изменение стартового адреса при опросе памяти
    void on_comboBoxMemType_currentIndexChanged(const QString &arg1);   // смена типа опрашиваемой памяти
    void on_pushButtonOpenLastInp_clicked();
    void on_updateButton_clicked(); // запрос обновления деревьев

    void updateMemory(QStringList ids); // вызывается хранилищем памяти для обновления значений переменных
    void updateCorrErrAnswerCount(int cnt, bool correctFlag);   // обновление счётчиков корректного и ошибочного опроса
    void getErrMessageFromDebugProcess(QString message);   // вывести сообщение об ошибке в окно
    void getTimeStr(QString timeStr);   // обновить время ПЛК (GUI отображение)

    void inOutClicked();    // команда на запись дискретного входа/выхода
    void anInOutClicked();  // команда на запись аналогового входа/выхода
    void boxToggled(bool fl);   // изменение видимости блоков вх/вых
    void openInputs(void);  // загрузить состояние входов и опрашиваемых переменных в плк
    void saveInputs(void);  // сохранить состояние входов и опрашиваемых переменных в файл
    void memViewCellPressed(int r, int c);
    void adc8bitChanged(void);  // 8 bit mode changed
    void on_checkBoxQuickWatch_toggled(bool checked);
    void closeQuickWatchWindow();

    void on_pushButtonClear_clicked();
    void on_spinBoxByteCnt_valueChanged(int arg1);
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonSaveVars_clicked();
    void on_pushButtonLoadVars_clicked();

    void on_checkBoxHexMem_clicked();
    void writeVar();    // записать значение, введённое в диалоге редактирования

    void on_pushButtonSaveLastInp_clicked();

signals:
    void quickInfo(QStringList names, QStringList values);
public slots:
    void getQuickWatchInfo();
    void openProject(void);
    void saveProject(void);
    void newProject(void);
    void updTree(void);
    void stopDebugger(void);
    void newPLCType(const QString &value);
private:
    Ui::DebuggerForm *ui;
};

#endif // DEBUGGERFORM_H
