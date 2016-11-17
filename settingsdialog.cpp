#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
    , mSettings("upna", "upna")
{
    ui->setupUi(this);
    comPortsInfo();
    comPortParametres();
    readSettings();

    connect(ui->buttonOK, SIGNAL(clicked()), SLOT(apply()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::comPortsInfo()
{
    ui->deviceComboBox->clear();
    ui->deviceComboBox_->clear();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QStringList list;
        list << info.portName()
          << info.systemLocation()
          << (info.isBusy() ? QObject::tr("Занят") : QObject::tr("Свободен"));
//        qDebug() << list;
        ui->deviceComboBox->addItem(list.first(), list);
        ui->deviceComboBox_->addItem(list.first(), list);
    }
}

void SettingsDialog::comPortParametres()
{
    ui->baudRateComboBox->addItem(QStringLiteral("1200"),   QSerialPort::Baud1200);
    ui->baudRateComboBox->addItem(QStringLiteral("2400"),   QSerialPort::Baud2400);
    ui->baudRateComboBox->addItem(QStringLiteral("4800"),   QSerialPort::Baud4800);
    ui->baudRateComboBox->addItem(QStringLiteral("9600"),   QSerialPort::Baud9600);
    ui->baudRateComboBox->addItem(QStringLiteral("19200"),  QSerialPort::Baud19200);
    ui->baudRateComboBox->addItem(QStringLiteral("38400"),  QSerialPort::Baud38400);
    ui->baudRateComboBox->addItem(QStringLiteral("57600"),  QSerialPort::Baud57600);
    ui->baudRateComboBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudRateComboBox->setCurrentIndex(3);

    ui->baudRateComboBox_->addItem(QStringLiteral("1200"),   QSerialPort::Baud1200);
    ui->baudRateComboBox_->addItem(QStringLiteral("2400"),   QSerialPort::Baud2400);
    ui->baudRateComboBox_->addItem(QStringLiteral("4800"),   QSerialPort::Baud4800);
    ui->baudRateComboBox_->addItem(QStringLiteral("9600"),   QSerialPort::Baud9600);
    ui->baudRateComboBox_->addItem(QStringLiteral("19200"),  QSerialPort::Baud19200);
    ui->baudRateComboBox_->addItem(QStringLiteral("38400"),  QSerialPort::Baud38400);
    ui->baudRateComboBox_->addItem(QStringLiteral("57600"),  QSerialPort::Baud57600);
    ui->baudRateComboBox_->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudRateComboBox_->setCurrentIndex(3);

    ui->dataBitsComboBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsComboBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsComboBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsComboBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsComboBox->setCurrentIndex(3);

    ui->dataBitsComboBox_->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsComboBox_->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsComboBox_->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsComboBox_->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsComboBox_->setCurrentIndex(3);

    ui->parityComboBox->addItem(QStringLiteral("None"), QSerialPort::NoParity);
    ui->parityComboBox->addItem(QStringLiteral("Even"), QSerialPort::EvenParity);
    ui->parityComboBox->addItem(QStringLiteral("Odd"),  QSerialPort::OddParity);
    ui->parityComboBox->setCurrentIndex(0);

    ui->parityComboBox_->addItem(QStringLiteral("None"), QSerialPort::NoParity);
    ui->parityComboBox_->addItem(QStringLiteral("Even"), QSerialPort::EvenParity);
    ui->parityComboBox_->addItem(QStringLiteral("Odd"),  QSerialPort::OddParity);
    ui->parityComboBox_->setCurrentIndex(0);

    ui->stopBitsComboBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    ui->stopBitsComboBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
    ui->stopBitsComboBox->setCurrentIndex(1);

    ui->stopBitsComboBox_->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    ui->stopBitsComboBox_->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
    ui->stopBitsComboBox_->setCurrentIndex(1);

    ui->flowControlComboBox->addItem(QStringLiteral("None"),     QSerialPort::NoFlowControl);
    ui->flowControlComboBox->addItem(QStringLiteral("RTS/CTS"),  QSerialPort::HardwareControl);
    ui->flowControlComboBox->addItem(QStringLiteral("XON/XOFF"), QSerialPort::SoftwareControl);
    ui->flowControlComboBox->setCurrentIndex(0);

    ui->flowControlComboBox_->addItem(QStringLiteral("None"),     QSerialPort::NoFlowControl);
    ui->flowControlComboBox_->addItem(QStringLiteral("RTS/CTS"),  QSerialPort::HardwareControl);
    ui->flowControlComboBox_->addItem(QStringLiteral("XON/XOFF"), QSerialPort::SoftwareControl);
    ui->flowControlComboBox_->setCurrentIndex(0);
}

void SettingsDialog::readSettings()
{
    mSettings.beginGroup("serial_port_0");
        ui->deviceComboBox->setCurrentIndex(mSettings.value("device_idx").toInt());
        ui->baudRateComboBox->setCurrentIndex(mSettings.value("baud_idx").toInt());
        ui->dataBitsComboBox->setCurrentIndex(mSettings.value("dbits_idx").toInt());
        ui->stopBitsComboBox->setCurrentIndex(mSettings.value("sbits_idx").toInt());
        ui->parityComboBox->setCurrentIndex(mSettings.value("parity_idx").toInt());
        ui->flowControlComboBox->setCurrentIndex(mSettings.value("flow_idx").toInt());
    mSettings.endGroup();

    mSettings.beginGroup("serial_port_1");
        ui->deviceComboBox_->setCurrentIndex(mSettings.value("device_idx").toInt());
        ui->baudRateComboBox_->setCurrentIndex(mSettings.value("baud_idx").toInt());
        ui->dataBitsComboBox_->setCurrentIndex(mSettings.value("dbits_idx").toInt());
        ui->stopBitsComboBox_->setCurrentIndex(mSettings.value("sbits_idx").toInt());
        ui->parityComboBox_->setCurrentIndex(mSettings.value("parity_idx").toInt());
        ui->flowControlComboBox_->setCurrentIndex(mSettings.value("flow_idx").toInt());
    mSettings.endGroup();

    mSettings.beginGroup("network");
        ui->selfPortLineEdit->setText(mSettings.value("port", "55700").toString());
    mSettings.endGroup();
}

void SettingsDialog::writeSettings()
{
    mSettings.beginGroup("serial_port_0");
        mSettings.setValue("device_idx",    ui->deviceComboBox->currentIndex());
        mSettings.setValue("baud_idx",      ui->baudRateComboBox->currentIndex());
        mSettings.setValue("dbits_idx",     ui->dataBitsComboBox->currentIndex());
        mSettings.setValue("sbits_idx",     ui->stopBitsComboBox->currentIndex());
        mSettings.setValue("parity_idx",    ui->parityComboBox->currentIndex());
        mSettings.setValue("flow_idx",      ui->flowControlComboBox->currentIndex());

        mSettings.setValue("device",	ui->deviceComboBox->currentText() );
        mSettings.setValue("baud",      static_cast<QSerialPort::BaudRate>(ui->baudRateComboBox->itemData(ui->baudRateComboBox->currentIndex()).toInt()));
        mSettings.setValue("dbits",     static_cast<QSerialPort::DataBits>(ui->dataBitsComboBox->itemData(ui->dataBitsComboBox->currentIndex()).toInt()));
        mSettings.setValue("sbits", 	static_cast<QSerialPort::StopBits>(ui->stopBitsComboBox->itemData(ui->stopBitsComboBox->currentIndex()).toInt()));
        mSettings.setValue("parity",	static_cast<QSerialPort::Parity>(ui->parityComboBox->itemData(ui->parityComboBox->currentIndex()).toInt()));
        mSettings.setValue("flow",		static_cast<QSerialPort::FlowControl>(ui->flowControlComboBox->itemData(ui->parityComboBox->currentIndex()).toInt()));
    mSettings.endGroup();

    mSettings.beginGroup("serial_port_1");
        mSettings.setValue("device_idx",    ui->deviceComboBox_->currentIndex());
        mSettings.setValue("baud_idx",      ui->baudRateComboBox_->currentIndex());
        mSettings.setValue("dbits_idx",     ui->dataBitsComboBox_->currentIndex());
        mSettings.setValue("sbits_idx",     ui->stopBitsComboBox_->currentIndex());
        mSettings.setValue("parity_idx",    ui->parityComboBox_->currentIndex());
        mSettings.setValue("flow_idx",      ui->flowControlComboBox_->currentIndex());

        mSettings.setValue("device",	ui->deviceComboBox_->currentText() );
        mSettings.setValue("baud",      static_cast<QSerialPort::BaudRate>(ui->baudRateComboBox_->itemData(ui->baudRateComboBox_->currentIndex()).toInt()));
        mSettings.setValue("dbits",     static_cast<QSerialPort::DataBits>(ui->dataBitsComboBox_->itemData(ui->dataBitsComboBox_->currentIndex()).toInt()));
        mSettings.setValue("sbits", 	static_cast<QSerialPort::StopBits>(ui->stopBitsComboBox_->itemData(ui->stopBitsComboBox_->currentIndex()).toInt()));
        mSettings.setValue("parity",	static_cast<QSerialPort::Parity>(ui->parityComboBox_->itemData(ui->parityComboBox_->currentIndex()).toInt()));
        mSettings.setValue("flow",		static_cast<QSerialPort::FlowControl>(ui->flowControlComboBox_->itemData(ui->parityComboBox_->currentIndex()).toInt()));
    mSettings.endGroup();

    mSettings.beginGroup("network");
        mSettings.setValue("port",      ui->selfPortLineEdit->text());
    mSettings.endGroup();
}

void SettingsDialog::apply()
{
    writeSettings();
    hide();
    emit settingsAccepted();
}
