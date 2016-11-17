#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QNetworkInterface>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    Ui::SettingsDialog *ui;
    
private:
    QSettings mSettings;
    void comPortsInfo();
    void comPortParametres();
    void readSettings();
    void writeSettings();

private slots:
    void apply();

signals:
    void settingsAccepted();

public slots:

};

#endif // SETTINGSDIALOG_H
