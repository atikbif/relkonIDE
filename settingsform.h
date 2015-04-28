#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include "settingsbase.h"
#include <QTableWidgetItem>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public SettingsBase
{
    Q_OBJECT

    const int columnCount = 10;
    const int rowCount = 103;
    unsigned int codeWord = 0x5280;

    static const int settingsSize = 2048;

    void printFactorySettings(void); // вывод таблицы заводских установок
    void guiToData(void);
protected:
    void updateData();  // обновление GUI в соответствии с данными
    void writeToBin(QByteArray &outData);   // запись данных в бинарный массив
public:
    explicit SettingsForm(SettingsBase *parent = 0);
    ~SettingsForm();
    void clearSettings(void);
    void saveSettings(void);    // сохранить настройки в файл
    void openSettings(void);    // прочитать настройки из файла
    void readFromBin(const QByteArray inpData); // прочитать настройки из бинарного массива
private slots:
    void on_tableWidget_itemChanged(QTableWidgetItem *item);    // реакция на изменение ячейки с заводской установкой
    void radioButtonBytes_toggled();    // переключение представления установок - 1,2,4 байта

    void on_pushButtonFromPLC_clicked();    // обработка команды чтения с ПЛК

    void on_pushButtonToPLC_clicked();  // обработка команды записи в ПЛК

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
