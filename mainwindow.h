#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdio>

#include "framehandler.h"
#include "controlserver.h"
#include "pointingsuploader.h"
#include "settingsdialog.h"
#include "kama.pb.h"
#include "frame.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, QSharedPointer<PointingsUploader> mPointingsUploader
               , QSharedPointer<FrameHandler> frameHandler
               );
    ~MainWindow();
    Ui::SettingsDialog* settingsUi;

    QSerialPort*		regSerial()			{ return rSerial; }
    QSerialPort*		pointSerial()		{ return pSerial; }
    FrameHandler*		getFrameHandler()	{ return mFrameHandler.data(); }
    PointingsUploader*  getPointingsUploader() { return mPointingsUploader.data(); }
    ControlServer*      controlServer()     { return mCtrlServer; }

private:
    Ui::MainWindow*		ui;
    SettingsDialog*     mSettingsDialog;
    QSerialPort*        rSerial;
    QSerialPort*        pSerial;
    ControlServer*      mCtrlServer;
    int					clientCount;
    bool				isSaved;
    QSharedPointer<PointingsUploader> mPointingsUploader;
    QSharedPointer<FrameHandler> mFrameHandler;

    QAction*			newAct;
    QAction*			openAct;
    QAction*			saveAct;
    QAction*			saveAsAct;
    QAction*			executeAct;
    QAction*			exitAct;
    QAction*			settingsAct;
    QAction*			helpAct;
    QAction*			aboutAct;

    QMenu*				fileMenu;
    QMenu*				configMenu;
    QMenu*				helpMenu;

    QToolBar*			mToolBar;

    QLabel*				knv008ConnectedLed;
    QLabel*				knv008ConnectedLabel;
    QLabel*             knu22ConnectedLed;
    QLabel*             knu22ConnectedLabel;
    QLabel*				armConnectedLed;
    QLabel*				armConnectedLabel;

    QLabel*				pTabRecLed;			//лампочка "Получены ЦУ"
    QLabel*             pTabRecLabel;       //транспорант "Получены ЦУ"
    QLabel*				pTabIsValidLed;		//лампочка "ЦУ корректны"
    QLabel*				pTabIsValidLabel;	//транспорант "ЦУ корректны"
    QPushButton*		openPTabButton;
    QPushButton*		savePTabButton;
    QPushButton*		execPTabButton;
    QPushButton*        startButton ;       //кнопка "Старт"
    QPushButton*        resetButton;        //кнопка "Сброс"
    QTextBrowser*       pTableError;        //ошибки таблицы целеуказний
    QTableWidget*       pTableView;         //принятая таблица целеуказаний

    QGroupBox*          timeGroupBox;
    QLCDNumber*         timeLCD;            //индикатор "время"
    QLCDNumber* 		azDegLCD;
    QLCDNumber* 		azMinLCD;
    QLCDNumber* 		azSecLCD;
    QLCDNumber* 		elDegLCD;
    QLCDNumber* 		elMinLCD;
    QLCDNumber* 		elSecLCD;
    QLabel*             manualTrackingLabel;
    QLabel*             manualSpeedTrackingLabel;
    QLabel*             autoBmanETrackingLabel;
    QLabel*             autoTrackingLabel;
    QLabel*             programmTrackingLabel;
    QLabel*             fromLinkTrackingLabel;
    QTextBrowser*       logMessage;

    void openSerial();
    void startServer();
    void createActions();
    void createMenus();
    void createToolBars();
    void createPanels();
    void knv008lReady(bool r);
    void knu22Ready(bool r);
    void ledOff();
    void fillPointingTable();
    void save(QString name);
    void log(QString s);

private slots:
    void readActivated();
	void newFile();
	void openFile();
	void saveFile();
	void saveAsFile();
	void executeFile();
	void connected();
	void disconnected();
	void pTableIsValid();
	void pTableIsNotValid();
	void reset();
	void print(Frame);
	void clientCountChanged(int count);
    void editSettings();
	void about();

signals:
    void registrationDeviceStateChanged(bool s);
    void pointingDeviceStateChanged(bool s);
    void rx(unsigned char ch);
    void start();
};

#endif // MAINWINDOW_H
