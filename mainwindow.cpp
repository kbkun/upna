#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_settingsdialog.h"

#include <fcntl.h>
#include "convertation.h"

extern bool imitator;

MainWindow::MainWindow(QWidget *parent,
                       QSharedPointer<PointingsUploader> pointingsUploader,
                       QSharedPointer<FrameHandler> frameHandler)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mSettingsDialog(new SettingsDialog(this))
    , rSerial(new QSerialPort(this))
    , pSerial(new QSerialPort(this))
    , mCtrlServer(new ControlServer())
	, clientCount(0)
	, isSaved(false)
    , mPointingsUploader(pointingsUploader)
    , mFrameHandler(frameHandler)
{
    ui->setupUi(this);
    resize(880, 710);
    setWindowTitle("ФПО ДУК АС РЛС \"Кама-Н\"");
	createActions();
	createMenus();
	createPanels();
    createToolBars();
    log(QTime::currentTime().toString() + " Начало работы");

    connect(getFrameHandler(), SIGNAL(readyToSend(Frame)), SLOT(print(Frame)));
    connect(mCtrlServer, SIGNAL(pTableIsValid()), SLOT(pTableIsValid()));
    connect(mCtrlServer, SIGNAL(pTableIsNotValid()), SLOT(pTableIsNotValid()));
    connect(this, SIGNAL(registrationDeviceStateChanged(bool)), mCtrlServer, SLOT(registrationDeviceStateChanged(bool)));
    connect(this, SIGNAL(pointingDeviceStateChanged(bool)), mCtrlServer, SLOT(pointingDeviceStateChanged(bool)));
    connect(getFrameHandler(), SIGNAL(readyToSend(Frame)), mCtrlServer, SLOT(publish(Frame)));
    connect(mCtrlServer, SIGNAL(clientCountChanged(int)), SLOT(clientCountChanged(int)));
    connect(execPTabButton, SIGNAL(clicked()), SLOT(executeFile()));
    connect(resetButton, SIGNAL(clicked()), SLOT(reset()));
    connect(getPointingsUploader(), SIGNAL(pt_upload(PointingTab)), getFrameHandler(), SLOT(receiveTable(PointingTab)));
    connect(mSettingsDialog, SIGNAL(settingsAccepted()), SLOT(editSettings()));

    connect(getFrameHandler(), SIGNAL(start()), getPointingsUploader(), SLOT(start()));
    connect(this, SIGNAL(start()), getPointingsUploader(), SLOT(start()));

    openSerial();
    startServer();
}

MainWindow::~MainWindow()
{
    regSerial()->close();
    pointSerial()->close();
    controlServer()->stop();
    delete ui;
}

void MainWindow::openSerial()
{
    if(regSerial()->isOpen())
        regSerial()->close();
    if(pointSerial()->isOpen())
        pointSerial()->close();

    QString regDevice = mSettingsDialog->ui->deviceComboBox->currentText();
    QSerialPort::BaudRate regBaud = static_cast<QSerialPort::BaudRate>(mSettingsDialog->ui->baudRateComboBox->currentText().toInt());
    QSerialPort::DataBits regDbits = static_cast<QSerialPort::DataBits>(mSettingsDialog->ui->dataBitsComboBox->currentText().toInt());
    QSerialPort::StopBits regSbits = static_cast<QSerialPort::StopBits>(mSettingsDialog->ui->stopBitsComboBox->currentText().toInt());
    QSerialPort::Parity regParity = static_cast<QSerialPort::Parity>(mSettingsDialog->ui->parityComboBox->itemData(mSettingsDialog->ui->parityComboBox->currentIndex()).toInt());
    QSerialPort::FlowControl regFlow = static_cast<QSerialPort::FlowControl>(mSettingsDialog->ui->flowControlComboBox->itemData(mSettingsDialog->ui->flowControlComboBox->currentIndex()).toInt());
    regSerial()->setPortName(regDevice);
    regSerial()->setBaudRate(regBaud);
    regSerial()->setDataBits(regDbits);
    regSerial()->setStopBits(regSbits);
    regSerial()->setParity(regParity);
    regSerial()->setFlowControl(regFlow);

    QString pointDevice = mSettingsDialog->ui->deviceComboBox_->currentText();
    QSerialPort::BaudRate pointBaud = static_cast<QSerialPort::BaudRate>(mSettingsDialog->ui->baudRateComboBox_->currentText().toInt());
    QSerialPort::DataBits pointDbits = static_cast<QSerialPort::DataBits>(mSettingsDialog->ui->dataBitsComboBox_->currentText().toInt());
    QSerialPort::StopBits pointSbits = static_cast<QSerialPort::StopBits>(mSettingsDialog->ui->stopBitsComboBox_->currentText().toInt());
    QSerialPort::Parity pointParity = static_cast<QSerialPort::Parity>(mSettingsDialog->ui->parityComboBox_->itemData(mSettingsDialog->ui->parityComboBox_->currentIndex()).toInt());
    QSerialPort::FlowControl pointFlow = static_cast<QSerialPort::FlowControl>(mSettingsDialog->ui->flowControlComboBox_->itemData(mSettingsDialog->ui->flowControlComboBox_->currentIndex()).toInt());
    pointSerial()->setPortName(pointDevice);
    pointSerial()->setBaudRate(pointBaud);
    pointSerial()->setDataBits(pointDbits);
    pointSerial()->setStopBits(pointSbits);
    pointSerial()->setParity(pointParity);
    pointSerial()->setFlowControl(pointFlow);

    if ( regSerial()->open(QIODevice::ReadOnly) ) {
        regSerial()->flush();
              connect(regSerial(), SIGNAL(readyRead()), SLOT(readActivated()));
              knv008lReady(true);
              emit registrationDeviceStateChanged(true);
              QString str = QString(QTime::currentTime().toString() + " Открыт файл устройства '"+regDevice+"'");
              connect(this, SIGNAL(rx(unsigned char)), getFrameHandler(), SLOT(receiveChar(unsigned char)));
              log(str);
    } else {
        knv008lReady(false);
        emit registrationDeviceStateChanged(false);
        QString errStr = QString(QTime::currentTime().toString() + " Не удалось открыть файл устройства '"+regDevice+"'!");
        QMessageBox::warning(this, "Ошибка", errStr);
        log(errStr);
    }

    if (pointSerial()->open(QIODevice::WriteOnly)) {
        pointSerial()->flush();
        knu22Ready(true);
        emit pointingDeviceStateChanged(true);
        QString str = QString(QTime::currentTime().toString() + " Открыт файл устройства '"+pointDevice+"'");
        log(str);
    } else {
        knu22Ready(false);
        emit pointingDeviceStateChanged(false);
        QString errStr = QString(QTime::currentTime().toString() + " Не удалось открыть файл устройства '"+pointDevice+"'!");
        QMessageBox::warning(this, "Ошибка", errStr);
        log(errStr);;
    }
}

void MainWindow::startServer()
{
    if(controlServer()->isListening())
        controlServer()->stop();
    QHostAddress hostAddress(QHostAddress::Any);
    int port = mSettingsDialog->ui->selfPortLineEdit->text().toInt();
    controlServer()->start(hostAddress, port);
}

void MainWindow::readActivated()
{
    QByteArray array = regSerial()->readAll();
    QBuffer buf(&array);
    buf.open(QIODevice::ReadOnly);
    char ch;
    while(buf.getChar(&ch)) {
        emit rx((unsigned char)ch);
    }
    buf.close();
}

void MainWindow::createActions()
{
	newAct = new QAction(QIcon(":/images/document-new.png"), tr("&Новыя таблица целеуказаний"), this);
	newAct->setShortcut(tr("Ctrl+Chift+n"));
	newAct->setStatusTip(tr("Создать файл целеуказаний"));
	QObject::connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

	openAct = new QAction(QIcon(":/images/document-open.png"), tr("&Открыть"), this);
	openAct->setShortcut(tr("Ctrl+Chift+o"));
	openAct->setStatusTip(tr("Открыть файл целеуказаний"));
	QObject::connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

	saveAct = new QAction(QIcon(":/images/document-save.png"), tr("&Сохранить"), this);
	saveAct->setShortcut(tr("Ctrl+Chift+s"));
	saveAct->setStatusTip(tr("Сохранить файл целеуказаний"));
	saveAct->setEnabled(false);
	QObject::connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

	saveAsAct = new QAction(QIcon(":/images/document-save-as.png"), tr("Сохранить &как"), this);
	saveAsAct->setShortcut(tr("Ctrl+Chift+a"));
	saveAsAct->setStatusTip(tr("Сохранить файл целеуказаний как"));
  saveAsAct->setEnabled(false);
	QObject::connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAsFile()));

	exitAct = new QAction(QIcon(":/images/system-shutdown.png"),tr("В&ыход"), this);
	exitAct->setShortcut(tr("Ctrl+Shift+Q"));
	exitAct->setStatusTip(tr("Выйти из программы и выключить АРМ ДУ"));
	QObject::connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	executeAct = new QAction(QIcon(":/images/svn-commit.png"), tr("&Исполнить"), this);
	executeAct->setShortcut(tr("Ctrl+Shift+e"));
	executeAct->setStatusTip(tr("Отправить на исполнение файл целеуказний"));
	executeAct->setEnabled(false);
	QObject::connect(executeAct, SIGNAL(triggered()), this, SLOT(executeFile()));

	settingsAct = new QAction(QIcon(":/images/applications-system.png"), tr("&Параметры"), this);
	settingsAct->setShortcut(tr("Ctrl+Shift+T"));
	settingsAct->setStatusTip(tr("Изменить параметры соединения"));
    QObject::connect(settingsAct, SIGNAL(triggered()), mSettingsDialog, SLOT(show()));

	helpAct = new QAction(QIcon(":/images/help-contents.png"),tr("&Помощь"), this);
	helpAct->setShortcut(tr("F1"));
	helpAct->setStatusTip(tr("Показать помощь"));

	aboutAct = new QAction(QIcon(":/images/about.png"),tr("&О программе"), this);
	aboutAct->setStatusTip(tr("Показать инфорамацию о программе"));
	QObject::connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&Файл"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(executeAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	configMenu = menuBar()->addMenu(tr("&Настройки"));
	configMenu->addAction(settingsAct);

	helpMenu = menuBar()->addMenu(tr("&Справка"));
	helpMenu->addAction(helpAct);
	helpMenu->addSeparator();
	helpMenu->addAction(aboutAct);
}

void MainWindow::createToolBars()
{
	mToolBar = new QToolBar();
	mToolBar->addAction(newAct);
	mToolBar->addAction(openAct);
	mToolBar->addAction(saveAct);
	mToolBar->addAction(saveAsAct);
	mToolBar->addSeparator();
	mToolBar->addAction(executeAct);
	mToolBar->addSeparator();
	mToolBar->addAction(settingsAct);
	mToolBar->addSeparator();
	mToolBar->addAction(helpAct);
	addToolBar(Qt::TopToolBarArea, mToolBar);
}

void MainWindow::createPanels()
{
	QGridLayout* mainLayout = new QGridLayout();
	QGroupBox* linkGroupBox = new QGroupBox("Индикаторы связи");
	QGroupBox* pTableGroupBox = new QGroupBox("Целеуказания");
	QGroupBox* mainWorkGroupBox = new QGroupBox("Работа");
	mainLayout->addWidget(linkGroupBox, 0, 0);
	mainLayout->addWidget(pTableGroupBox, 1, 0);
	mainLayout->addWidget(mainWorkGroupBox, 0, 1, 2, 1);
	centralWidget()->setLayout(mainLayout);
	/*
	 * -------------------Панель "ИНДИКАТОРЫ СВЯЗИ"-------------------
	 */
	QGridLayout* linkLayout = new QGridLayout;
	linkLayout->setSpacing(10);

    knv008ConnectedLed = new QLabel(this);
    knu22ConnectedLed = new QLabel(this);
	armConnectedLed = new QLabel(this);
    knv008ConnectedLed->setScaledContents(true);
    knu22ConnectedLed->setScaledContents(true);
	armConnectedLed->setScaledContents(true);
    knv008ConnectedLed->setMaximumSize(17, 17);
    knu22ConnectedLed->setMaximumSize(17, 17);
	armConnectedLed->setMaximumSize(17, 17);
    QPixmap pixmap = QPixmap(":/images/ledred.png");
    knv008ConnectedLed->setPixmap(pixmap);
    knu22ConnectedLed->setPixmap(pixmap);
    armConnectedLed->setPixmap(pixmap);
    knv008ConnectedLabel = new QLabel("Нет связи с КНВ-008");
    knv008ConnectedLabel->setStyleSheet("color: red");
    knv008ConnectedLabel->setWordWrap(true);
    knu22ConnectedLabel = new QLabel("Нет связи с КНУ22");
    knu22ConnectedLabel->setStyleSheet("color: red");
    knu22ConnectedLabel->setWordWrap(true);
	armConnectedLabel = new QLabel("Нет связи с АРМ ДУ");
    armConnectedLabel->setStyleSheet("color: red");
	armConnectedLabel->setWordWrap(true);

    linkLayout->addWidget(knv008ConnectedLed, 0, 0);
    linkLayout->addWidget(knv008ConnectedLabel, 0, 1);
    linkLayout->addWidget(knu22ConnectedLed, 1, 0);
    linkLayout->addWidget(knu22ConnectedLabel, 1, 1);
    linkLayout->addWidget(armConnectedLed, 2, 0);
    linkLayout->addWidget(armConnectedLabel, 2, 1);

	linkGroupBox->setLayout(linkLayout);
	/*
	 *  ------------------ПАНЕЛЬ "ЦЕЛЕУКАЗАНИЯ"------------------------
	 */
	QGridLayout* pTableLayout = new QGridLayout;
	pTableLayout->setSpacing(10);

	//транспорант "Получены ЦУ"
	pTabRecLed = new QLabel(this);
	pTabRecLed->setScaledContents(true);
	pTabRecLed->setMaximumSize(17, 17);
	pTabRecLabel = new QLabel("Получены целеуказания");
	pTabRecLabel->setWordWrap(true);

	//лампочка "ЦУ коректны"
	pTabIsValidLed = new QLabel(this);
	pTabIsValidLed->setScaledContents(true);
	pTabIsValidLed->setMaximumSize(17, 17);
	pTabIsValidLabel = new QLabel("Целеуказания корректны");
	pTabIsValidLabel->setWordWrap(true);

	//таблица "Полученные ЦУ"
    pTableView = new QTableWidget(0, 4);
	QStringList lst;
    lst << "Время" << "Азимут" << "Угол места" << "Калибр. пар-р";
	pTableView->setHorizontalHeaderLabels(lst);

	//кнопка "Исполнить"
	execPTabButton = new QPushButton("Исполнить");
	execPTabButton->setStyleSheet("font: 14pt; color: green");
	execPTabButton->setEnabled(false);

	//кнопка "Сброс"
	resetButton = new QPushButton("Сброс");
	resetButton->setStyleSheet("font: 14pt; color: red");

	//ошибки таблицы ЦУ
	pTableError = new QTextBrowser;
	pTableError->setMaximumHeight(64);
	pTableError->setText("Ошибки таблицы целеуказаний");
	pTableError->setEnabled(false);

	pTableLayout->addWidget(pTabRecLed, 0, 0);
	pTableLayout->addWidget(pTabRecLabel, 0, 1);
	pTableLayout->addWidget(pTabIsValidLed, 0, 2);
	pTableLayout->addWidget(pTabIsValidLabel, 0, 3);
	pTableLayout->addWidget(pTableView, 2, 0, 1, 4);
	pTableLayout->addWidget(execPTabButton, 3, 0, 1, 2);
	pTableLayout->addWidget(resetButton, 3, 2, 1, 2);
	pTableLayout->addWidget(pTableError, 4, 0, 1, 4);

	pTableGroupBox->setLayout(pTableLayout);
	/*
	 *  ------------------ПАНЕЛЬ "РАБОТА"------------------------
	 */
    QGridLayout* mainWorkLayout = new QGridLayout();
	mainWorkLayout->setSpacing(10);

	//индикатор "Время"
	timeGroupBox =  new QGroupBox("Время:");
	timeLCD = new QLCDNumber;
    timeLCD->setFixedHeight(72);
	timeLCD->setDigitCount(12);
	timeLCD->setStyleSheet("color: yellow; background: black");
	QBoxLayout* timeLayout =  new QBoxLayout(QBoxLayout::TopToBottom);
	timeLayout->addWidget(timeLCD);
	timeGroupBox->setLayout(timeLayout);

	//индикаторы "азимут" и "угол места"
	azDegLCD = new QLCDNumber;
    azDegLCD->setMinimumHeight(72);
	azDegLCD->setDigitCount(3);
	azDegLCD->setStyleSheet("color: yellow; background: black");
	azMinLCD = new QLCDNumber;
	azMinLCD->setDigitCount(3);
	azMinLCD->setStyleSheet("color: yellow; background: black");
	azSecLCD = new QLCDNumber;
	azSecLCD->setDigitCount(3);
	azSecLCD->setStyleSheet("color: yellow; background: black");
	elDegLCD = new QLCDNumber;
	elDegLCD->setDigitCount(3);
	elDegLCD->setStyleSheet("color: yellow; background: black");
	elMinLCD = new QLCDNumber;
	elMinLCD->setDigitCount(3);
	elMinLCD->setStyleSheet("color: yellow; background: black");
	elSecLCD = new QLCDNumber;
	elSecLCD->setDigitCount(3);
	elSecLCD->setStyleSheet("color: yellow; background: black");
	QGroupBox* azimuthGroupBox = new QGroupBox("Азимут (град/мин/сек):");
	QBoxLayout* azimuthLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	QGroupBox* elevationGroupBox = new QGroupBox("Угол места (град/мин/сек):");
	QBoxLayout* elevationLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	azimuthLayout->addWidget(azDegLCD);
	azimuthLayout->addWidget(azMinLCD);
	azimuthLayout->addWidget(azSecLCD);
	elevationLayout->addWidget(elDegLCD);
	elevationLayout->addWidget(elMinLCD);
	elevationLayout->addWidget(elSecLCD);
	azimuthGroupBox->setLayout(azimuthLayout);
	elevationGroupBox->setLayout(elevationLayout);

	//"условия сопровождения в канале углов"
	QGroupBox* trackingModeGroupBox = new QGroupBox("Условия сопровождения:");
	QBoxLayout* trackingModeLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	manualTrackingLabel = new QLabel("РУ");
    manualTrackingLabel->setFixedSize(56, 56);
	manualTrackingLabel->setAlignment(Qt::AlignCenter);
    manualSpeedTrackingLabel = new QLabel("РУ\nскор");
    manualSpeedTrackingLabel->setFixedSize(56, 56);
    manualSpeedTrackingLabel->setWordWrap(true);
    manualSpeedTrackingLabel->setAlignment(Qt::AlignCenter);
    autoBmanETrackingLabel = new QLabel(QString("АСb\nРУe"));
    autoBmanETrackingLabel->setFixedSize(56, 56);
    autoBmanETrackingLabel->setWordWrap(true);
    autoBmanETrackingLabel->setAlignment(Qt::AlignCenter);
	autoTrackingLabel = new QLabel("АС");
    autoTrackingLabel->setFixedSize(56, 56);
	autoTrackingLabel->setAlignment(Qt::AlignCenter);
    programmTrackingLabel = new QLabel("ПН");
    programmTrackingLabel->setFixedSize(56, 56);
    programmTrackingLabel->setAlignment(Qt::AlignCenter);
    fromLinkTrackingLabel = new QLabel("ЦУк");
    fromLinkTrackingLabel->setFixedSize(56, 56);
    fromLinkTrackingLabel->setAlignment(Qt::AlignCenter);
	trackingModeLayout->addStretch(1);
	trackingModeLayout->addWidget(manualTrackingLabel);
    trackingModeLayout->addWidget(manualSpeedTrackingLabel);
    trackingModeLayout->addWidget(autoBmanETrackingLabel);
	trackingModeLayout->addWidget(autoTrackingLabel);
    trackingModeLayout->addWidget(programmTrackingLabel);
    trackingModeLayout->addWidget(fromLinkTrackingLabel);
	trackingModeLayout->addStretch(1);
	trackingModeGroupBox->setLayout(trackingModeLayout);
	ledOff();

    //протокол работы
    QGroupBox* logGroupBox = new QGroupBox(tr("Журнал работы"));
    QGridLayout* logLayout = new QGridLayout;
    logMessage = new QTextBrowser;
//    logMessage->setMaximumHeight(128);
    logLayout->addWidget(logMessage);
    logGroupBox->setLayout(logLayout);

    mainWorkLayout->addWidget(timeGroupBox, 1, 0, 1, 2);
    mainWorkLayout->addWidget(azimuthGroupBox, 2, 0);
    mainWorkLayout->addWidget(elevationGroupBox, 2, 1);
    mainWorkLayout->addWidget(trackingModeGroupBox, 3, 0, 1, 2);
    mainWorkLayout->addWidget(logGroupBox, 4, 0, 1, 2);

	mainWorkGroupBox->setLayout(mainWorkLayout);

	centralWidget()->show();
}

void MainWindow::knv008lReady(bool r)
{
    QString str;
	if(r) {
		QPixmap pixmap(":/images/ledgreen.png");
        str = "Есть связь с КНВ-008";
        knv008ConnectedLed->setPixmap(pixmap);
        knv008ConnectedLabel->setText(str);
        knv008ConnectedLabel->setStyleSheet("color: green");
	} else {
		QPixmap pixmap(":/images/ledred.png");
        str = "Нет связи с КНВ-008";
        knv008ConnectedLed->setPixmap(pixmap);
        knv008ConnectedLabel->setText(str);
        knv008ConnectedLabel->setStyleSheet("color: red");
	}
    log(str);
}

void MainWindow::knu22Ready(bool r)
{
    QString str;
    if(r) {
        QPixmap pixmap(":/images/ledgreen.png");
        str = "Есть связь с КНУ22";
        knu22ConnectedLed->setPixmap(pixmap);
        knu22ConnectedLabel->setText(str);
        knu22ConnectedLabel->setStyleSheet("color: green");
    } else {
        QPixmap pixmap(":/images/ledred.png");
        str = "Нет связи с КНУ22";
        knu22ConnectedLed->setPixmap(pixmap);
        knu22ConnectedLabel->setText(str);
        knu22ConnectedLabel->setStyleSheet("color: red");
    }
    log(str);
}

void MainWindow::ledOff()
{
    QPixmap pixmap(":/images/ledoff.png");
    pTabRecLed->setPixmap(pixmap);
    pTabIsValidLed->setPixmap(pixmap);
    pTabRecLabel->setStyleSheet("color: grey");
    pTabIsValidLabel->setStyleSheet("color: grey");
    manualTrackingLabel->setStyleSheet("background-color: lightgreen; font: 16pt");
	manualTrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);
    manualSpeedTrackingLabel->setStyleSheet("background-color: lightgreen; font: 16pt");
    manualSpeedTrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);
    autoBmanETrackingLabel->setStyleSheet("background-color: lightgreen; font: 16pt");
    autoBmanETrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);
    autoTrackingLabel->setStyleSheet("background-color: lightgreen; font: 16pt");
    autoTrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);
    programmTrackingLabel->setStyleSheet("background-color: lightgreen; font: 16pt;");
    programmTrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);
    fromLinkTrackingLabel->setStyleSheet("background-color: lightgreen; font: 16pt");
    fromLinkTrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);
}

void MainWindow::fillPointingTable()
{
    google::protobuf::RepeatedPtrField<kama::protocol::PointingTableItem>::const_iterator it = controlServer()->getPT().item().begin();
    QString logStr;
    int i;
    for(i = 0; it != controlServer()->getPT().item().end(); ++it, ++i) {
        if(pTableView->rowCount() < i + 1) pTableView->setRowCount(pTableView->rowCount() + 1);
        kama::protocol::PointingTableItem tmp = *it;
        QString tmpStr;
        QDateTime time = QDateTime::fromString(QString::fromStdString(controlServer()->getPT().time()));
        if (time.isNull()) time = QDateTime(QDate::currentDate(), QTime(0,0,0));
        double secs, msecs;
        msecs = modf(tmp.time(), &secs);
        time = time.addSecs((int)secs).addMSecs((int)(msecs * 100));
        tmpStr = time.toString("hh:mm:ss");
        logStr.append(tmpStr).append("\t");
        QTableWidgetItem* i0 = new QTableWidgetItem(tmpStr);
        pTableView->setItem(i, 0, i0);
        DecToDeg g = decToDeg(tmp.azimuth());
        tmpStr.clear();
        tmpStr.append(QString::number(g.deg)).append(QChar(176)).append(QString::number(g.min)).append("'").append(QString::number(g.sec)).append("''");
        logStr.append(tmpStr).append("\t");
        i0 = new QTableWidgetItem(tmpStr);
        pTableView->setItem(i, 1, i0);
        g = decToDeg(tmp.elevation());
        tmpStr.clear();
        tmpStr.append(QString::number(g.deg)).append(QChar(176)).append(QString::number(g.min)).append("'").append(QString::number(g.sec)).append("''");
        logStr.append(tmpStr).append("\n");
        i0 = new QTableWidgetItem(tmpStr);
        pTableView->setItem(i, 2, i0);
    }
    log(logStr);
}

void MainWindow::log(QString s)
{
    logMessage->append(s);
}

void MainWindow::save(QString name)
{
	kama::protocol::Envelope msg;
    msg.mutable_pointing_table_setting_req()->mutable_table()->CopyFrom(controlServer()->getPT());
		QFile f(name);
		qDebug() << "file: " << f.fileName();
		if(!f.open(QIODevice::WriteOnly)) {
            QString errStr = QString("Не удалось записать файл целеуказаний на диск'").append(f.fileName()).append("'!");
			QMessageBox::warning(this, "Ошибка", errStr);
			return;
		}
		f.write(serializeDelimited(msg));
		qDebug() << "SAVED:\n" << QString::fromStdString(msg.Utf8DebugString());
		f.close();
		isSaved = true;
}

void MainWindow::newFile()
{

}

void MainWindow::openFile()
{
    QString pTabFileName =  QFileDialog::getOpenFileName(0, "Выбор файла", "", "все файлы (*);;");
	if(pTabFileName.isEmpty()) return;
	QFile f(pTabFileName);
	if(!f.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл целеуказаний'"+pTabFileName+"'!");
		return;
	}
	const QByteArray& data = f.readAll();
	f.close();
	size_t bytesConsumed = 0;
	const QSharedPointer<kama::protocol::Envelope>& msg = parseDelimited<kama::protocol::Envelope>(data.constData(), data.size(), bytesConsumed);
	if(msg) {
        controlServer()->processMessage(*msg, 0, false);
	}
}

void MainWindow::saveFile()
{
	if(isSaved) return;
	QDate date = QDate::currentDate();
    QDir home = QDir::home();
    QString path = home.absolutePath().append("/pointingtables/");
    QString objName = QString::fromStdString(controlServer()->getPT().object_type());
    if(objName.isEmpty()) objName = "noname";
    QString fileName = path + date.toString("dd_MM_yy") + "_" + objName;
	QFile f(fileName);
	int n = 1;
	for(;; n++) {
		if(!f.exists()) {
			break;
		}
        qDebug() << "Файл с именем " << f.fileName() << " уже существует";
		QString newFileName = fileName + QString::number(n);
        f.setFileName(newFileName);
	}
	save(f.fileName());
}

void MainWindow::saveAsFile()
{
	kama::protocol::Envelope msg;
    QString pTabFileName =  QFileDialog::getSaveFileName(0, "Выбор файла", "", "таблицы целеуказаний(*.pt);;все файлы (*);;");
	if(pTabFileName.isEmpty()) return;
    save(pTabFileName);
}

void MainWindow::executeFile()
{
    log("Таблица ЦУ принята к исполнению");
    mPointingsUploader->upload(controlServer()->getSlicedPT(), pointSerial());
    emit start();
}

void MainWindow::editSettings()
{
    openSerial();
    startServer();
}

void MainWindow::connected()
{
    armConnectedLabel->setText("Есть связь с АРМ ДУ");
    armConnectedLabel->setStyleSheet("color: green");
    QPixmap pixmap(":/images/ledgreen.png");
    armConnectedLed->setPixmap(pixmap);
}

void MainWindow::disconnected()
{
	armConnectedLabel->setText("Нет связи с АРМ ДУ");
	armConnectedLed->setStyleSheet("color: red");
	QPixmap pixmap(":/images/ledred.png");
	armConnectedLed->setPixmap(pixmap);
}

void MainWindow::pTableIsValid()
{
	QPixmap pixmap(":/images/ledgreen.png");
	pTabIsValidLabel->setText("Целеуказания корректны");
    pTabIsValidLabel->setStyleSheet("color: green");
    pTabIsValidLed->setPixmap(pixmap);
    pTabRecLabel->setStyleSheet("color: green");
    pTabRecLed->setPixmap(pixmap);
    log("Получена новая таблица ЦУ. ЦУ корректны");
    fillPointingTable();
    pTableError->setEnabled(false);
    pTableError->setText("Ошибки таблицы целеуказаний");
    isSaved = false;
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
    executeAct->setEnabled(true);
    execPTabButton->setEnabled(true);
}

void MainWindow::pTableIsNotValid()
{
	QPixmap pixmap(":/images/ledred.png");
	pTabIsValidLabel->setText("Целеуказания не корректны");
    pTabIsValidLabel->setStyleSheet("color: red");
    pTabIsValidLed->setPixmap(pixmap);
    pTabRecLabel->setStyleSheet("color: red");
    pTabRecLed->setPixmap(pixmap);
    log("Получена новая таблица ЦУ. ЦУ не корректны");
    fillPointingTable();
    pTableError->setEnabled(true);
    pTableError->setText(controlServer()->error());
    isSaved = false;
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
    executeAct->setEnabled(false);
    execPTabButton->setEnabled(false);
}

void MainWindow::reset()
{
	QPixmap pixmap(":/images/ledoff.png");
	pTabIsValidLabel->setText("Целеуказания корректны");
	pTabIsValidLabel->setStyleSheet("color: grey");
	pTabIsValidLed->setPixmap(pixmap);
	pTabRecLabel->setStyleSheet("color: grey");
	pTabRecLed->setPixmap(pixmap);
	pTableView->clear();
	QStringList lst;
    lst << "Время" << "Азимут" << "Угол места" << "Калибр. пар-р";
	pTableView->setHorizontalHeaderLabels(lst);
	pTableView->setRowCount(0);
	pTableError->setText("Ошибки таблицы целеуказаний");
	pTableError->setEnabled(false);
    controlServer()->clearPT();
	saveAct->setEnabled(false);
	saveAsAct->setEnabled(false);
	executeAct->setEnabled(false);
	execPTabButton->setEnabled(false);
}

void MainWindow::print(Frame f)
{
    if(f.timeMode) timeGroupBox->setTitle("Время московское:");
    else timeGroupBox->setTitle("Время от КП:");
    timeLCD->display(f.time.time().toString());
    DecToDeg deg = decToDeg(f.azimuth);
    azDegLCD->display(deg.deg);
    azMinLCD->display(deg.min);
    azSecLCD->display(deg.sec);
    deg = decToDeg(f.elevation);
    elDegLCD->display(deg.deg);
    elMinLCD->display(deg.min);
    elSecLCD->display(deg.sec);
    ledOff();
    QPixmap pixmap;
    if(f.trackingMode == 0) {
        manualTrackingLabel->setStyleSheet("background-color: yellow; font: 16pt");
        manualTrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }
    else if(f.trackingMode == 1) {
        autoBmanETrackingLabel->setStyleSheet("background-color: yellow; font: 16pt");
        autoBmanETrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }
    else if(f.trackingMode == 2) {
        autoTrackingLabel->setStyleSheet("background-color: yellow; font: 16pt");
    	autoTrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }
    else if(f.trackingMode == 4) {
        programmTrackingLabel->setStyleSheet("background-color: yellow; font: 16pt");
        programmTrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }
    else if(f.trackingMode == 5) {
        fromLinkTrackingLabel->setStyleSheet("background-color: yellow; font: 16pt");
        fromLinkTrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }
    else if(f.trackingMode == 6) {
        manualSpeedTrackingLabel->setStyleSheet("background-color: yellow; font: 16pt");
        manualSpeedTrackingLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }
}

void MainWindow::clientCountChanged(int count)
{
	clientCount = count;
    qDebug() << "clientCount: " << clientCount;
	if(clientCount) {
        armConnectedLabel->setText("Есть связь с АРМ ДУ");
        armConnectedLabel->setStyleSheet("color: green");
        QPixmap pixmap(":/images/ledgreen.png");
        armConnectedLed->setPixmap(pixmap);
	} else {
        armConnectedLabel->setText("Нет связи с АРМ ДУ");
        armConnectedLed->setStyleSheet("color: red");
        QPixmap pixmap(":/images/ledred.png");
        armConnectedLed->setPixmap(pixmap);
	}
}

void MainWindow::about()
{
    QString info = QString("<p><h3></b>ФПО ДУК АС РЛС \"Кама-Н\"</h3></p> \
                           <p><h5>CЮИТ.00128-01</h5></p> \
                           <p><h5>ОАО \"КБ\"Кунцево\", 2014</h5></p>");
    QMessageBox::about(this, "О программе", info);
}
