/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created: Thu Oct 8 15:39:30 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *buttonsLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonOK;
    QPushButton *buttonCancel;
    QGroupBox *groupBox;
    QWidget *layoutWidget_2;
    QGridLayout *deviceTabLayout;
    QSpacerItem *spacer1;
    QGroupBox *frameGroupBox;
    QGridLayout *_5;
    QGridLayout *frameLayout;
    QLabel *wordBitsLabel;
    QComboBox *dataBitsComboBox;
    QLabel *stopBitsLabel;
    QComboBox *stopBitsComboBox;
    QLabel *parityLabel;
    QComboBox *parityComboBox;
    QLabel *baudRateLabel;
    QComboBox *baudRateComboBox;
    QLabel *deviceLabel;
    QComboBox *flowControlComboBox;
    QLabel *flowControlLabel;
    QComboBox *deviceComboBox;
    QSpacerItem *spacer3;
    QSpacerItem *spacer2;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget_3;
    QGridLayout *deviceTabLayout_;
    QSpacerItem *spacer1_2;
    QComboBox *baudRateComboBox_;
    QComboBox *flowControlComboBox_;
    QGroupBox *frameGroupBox_;
    QGridLayout *_6;
    QGridLayout *frameLayout_;
    QLabel *parityLabel_;
    QComboBox *parityComboBox_;
    QLabel *wordBitsLabel_;
    QComboBox *dataBitsComboBox_;
    QLabel *stopBitsLabel_;
    QComboBox *stopBitsComboBox_;
    QSpacerItem *spacer3_2;
    QLabel *deviceLabel_;
    QLabel *baudRateLabel_;
    QComboBox *deviceComboBox_;
    QSpacerItem *spacer2_2;
    QLabel *flowControlLabel_;
    QGroupBox *groupBox_3;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *selfPortLineEdit;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(578, 640);
        horizontalLayoutWidget = new QWidget(SettingsDialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(14, 590, 551, 31));
        buttonsLayout = new QHBoxLayout(horizontalLayoutWidget);
        buttonsLayout->setSpacing(6);
        buttonsLayout->setContentsMargins(11, 11, 11, 11);
        buttonsLayout->setObjectName(QString::fromUtf8("buttonsLayout"));
        buttonsLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonsLayout->addItem(horizontalSpacer);

        buttonOK = new QPushButton(horizontalLayoutWidget);
        buttonOK->setObjectName(QString::fromUtf8("buttonOK"));

        buttonsLayout->addWidget(buttonOK);

        buttonCancel = new QPushButton(horizontalLayoutWidget);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));

        buttonsLayout->addWidget(buttonCancel);

        groupBox = new QGroupBox(SettingsDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(5, 120, 571, 231));
        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 30, 551, 195));
        deviceTabLayout = new QGridLayout(layoutWidget_2);
        deviceTabLayout->setSpacing(6);
        deviceTabLayout->setContentsMargins(11, 11, 11, 11);
        deviceTabLayout->setObjectName(QString::fromUtf8("deviceTabLayout"));
        deviceTabLayout->setContentsMargins(0, 0, 0, 0);
        spacer1 = new QSpacerItem(281, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        deviceTabLayout->addItem(spacer1, 1, 3, 1, 2);

        frameGroupBox = new QGroupBox(layoutWidget_2);
        frameGroupBox->setObjectName(QString::fromUtf8("frameGroupBox"));
        _5 = new QGridLayout(frameGroupBox);
        _5->setSpacing(6);
        _5->setContentsMargins(11, 11, 11, 11);
        _5->setObjectName(QString::fromUtf8("_5"));
        frameLayout = new QGridLayout();
        frameLayout->setSpacing(6);
        frameLayout->setObjectName(QString::fromUtf8("frameLayout"));
        wordBitsLabel = new QLabel(frameGroupBox);
        wordBitsLabel->setObjectName(QString::fromUtf8("wordBitsLabel"));
        wordBitsLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wordBitsLabel->setWordWrap(false);

        frameLayout->addWidget(wordBitsLabel, 0, 0, 1, 2);

        dataBitsComboBox = new QComboBox(frameGroupBox);
        dataBitsComboBox->setObjectName(QString::fromUtf8("dataBitsComboBox"));

        frameLayout->addWidget(dataBitsComboBox, 0, 2, 1, 1);

        stopBitsLabel = new QLabel(frameGroupBox);
        stopBitsLabel->setObjectName(QString::fromUtf8("stopBitsLabel"));
        stopBitsLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        stopBitsLabel->setWordWrap(false);

        frameLayout->addWidget(stopBitsLabel, 1, 0, 1, 2);

        stopBitsComboBox = new QComboBox(frameGroupBox);
        stopBitsComboBox->setObjectName(QString::fromUtf8("stopBitsComboBox"));

        frameLayout->addWidget(stopBitsComboBox, 1, 2, 1, 1);

        parityLabel = new QLabel(frameGroupBox);
        parityLabel->setObjectName(QString::fromUtf8("parityLabel"));
        parityLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        parityLabel->setWordWrap(false);

        frameLayout->addWidget(parityLabel, 2, 0, 1, 1);

        parityComboBox = new QComboBox(frameGroupBox);
        parityComboBox->setObjectName(QString::fromUtf8("parityComboBox"));

        frameLayout->addWidget(parityComboBox, 2, 1, 1, 2);


        _5->addLayout(frameLayout, 0, 0, 1, 1);


        deviceTabLayout->addWidget(frameGroupBox, 2, 2, 2, 1);

        baudRateLabel = new QLabel(layoutWidget_2);
        baudRateLabel->setObjectName(QString::fromUtf8("baudRateLabel"));
        baudRateLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        baudRateLabel->setWordWrap(false);

        deviceTabLayout->addWidget(baudRateLabel, 1, 0, 1, 1);

        baudRateComboBox = new QComboBox(layoutWidget_2);
        baudRateComboBox->setObjectName(QString::fromUtf8("baudRateComboBox"));

        deviceTabLayout->addWidget(baudRateComboBox, 1, 1, 1, 2);

        deviceLabel = new QLabel(layoutWidget_2);
        deviceLabel->setObjectName(QString::fromUtf8("deviceLabel"));
        deviceLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        deviceLabel->setWordWrap(false);

        deviceTabLayout->addWidget(deviceLabel, 0, 0, 1, 1);

        flowControlComboBox = new QComboBox(layoutWidget_2);
        flowControlComboBox->setObjectName(QString::fromUtf8("flowControlComboBox"));

        deviceTabLayout->addWidget(flowControlComboBox, 0, 4, 1, 1);

        flowControlLabel = new QLabel(layoutWidget_2);
        flowControlLabel->setObjectName(QString::fromUtf8("flowControlLabel"));
        flowControlLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        flowControlLabel->setWordWrap(false);

        deviceTabLayout->addWidget(flowControlLabel, 0, 3, 1, 1);

        deviceComboBox = new QComboBox(layoutWidget_2);
        deviceComboBox->setObjectName(QString::fromUtf8("deviceComboBox"));
        deviceComboBox->setEditable(true);

        deviceTabLayout->addWidget(deviceComboBox, 0, 1, 1, 2);

        spacer3 = new QSpacerItem(20, 120, QSizePolicy::Minimum, QSizePolicy::Expanding);

        deviceTabLayout->addItem(spacer3, 3, 4, 2, 1);

        spacer2 = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        deviceTabLayout->addItem(spacer2, 2, 0, 1, 2);

        groupBox_2 = new QGroupBox(SettingsDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(5, 350, 571, 231));
        layoutWidget_3 = new QWidget(groupBox_2);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 30, 551, 191));
        deviceTabLayout_ = new QGridLayout(layoutWidget_3);
        deviceTabLayout_->setSpacing(6);
        deviceTabLayout_->setContentsMargins(11, 11, 11, 11);
        deviceTabLayout_->setObjectName(QString::fromUtf8("deviceTabLayout_"));
        deviceTabLayout_->setContentsMargins(0, 0, 0, 0);
        spacer1_2 = new QSpacerItem(281, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        deviceTabLayout_->addItem(spacer1_2, 1, 3, 1, 2);

        baudRateComboBox_ = new QComboBox(layoutWidget_3);
        baudRateComboBox_->setObjectName(QString::fromUtf8("baudRateComboBox_"));

        deviceTabLayout_->addWidget(baudRateComboBox_, 1, 1, 1, 2);

        flowControlComboBox_ = new QComboBox(layoutWidget_3);
        flowControlComboBox_->setObjectName(QString::fromUtf8("flowControlComboBox_"));

        deviceTabLayout_->addWidget(flowControlComboBox_, 0, 4, 1, 1);

        frameGroupBox_ = new QGroupBox(layoutWidget_3);
        frameGroupBox_->setObjectName(QString::fromUtf8("frameGroupBox_"));
        _6 = new QGridLayout(frameGroupBox_);
        _6->setSpacing(6);
        _6->setContentsMargins(11, 11, 11, 11);
        _6->setObjectName(QString::fromUtf8("_6"));
        frameLayout_ = new QGridLayout();
        frameLayout_->setSpacing(6);
        frameLayout_->setObjectName(QString::fromUtf8("frameLayout_"));
        parityLabel_ = new QLabel(frameGroupBox_);
        parityLabel_->setObjectName(QString::fromUtf8("parityLabel_"));
        parityLabel_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        parityLabel_->setWordWrap(false);

        frameLayout_->addWidget(parityLabel_, 2, 0, 1, 1);

        parityComboBox_ = new QComboBox(frameGroupBox_);
        parityComboBox_->setObjectName(QString::fromUtf8("parityComboBox_"));

        frameLayout_->addWidget(parityComboBox_, 2, 1, 1, 2);

        wordBitsLabel_ = new QLabel(frameGroupBox_);
        wordBitsLabel_->setObjectName(QString::fromUtf8("wordBitsLabel_"));
        wordBitsLabel_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wordBitsLabel_->setWordWrap(false);

        frameLayout_->addWidget(wordBitsLabel_, 0, 0, 1, 2);

        dataBitsComboBox_ = new QComboBox(frameGroupBox_);
        dataBitsComboBox_->setObjectName(QString::fromUtf8("dataBitsComboBox_"));

        frameLayout_->addWidget(dataBitsComboBox_, 0, 2, 1, 1);

        stopBitsLabel_ = new QLabel(frameGroupBox_);
        stopBitsLabel_->setObjectName(QString::fromUtf8("stopBitsLabel_"));
        stopBitsLabel_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        stopBitsLabel_->setWordWrap(false);

        frameLayout_->addWidget(stopBitsLabel_, 1, 0, 1, 2);

        stopBitsComboBox_ = new QComboBox(frameGroupBox_);
        stopBitsComboBox_->setObjectName(QString::fromUtf8("stopBitsComboBox_"));

        frameLayout_->addWidget(stopBitsComboBox_, 1, 2, 1, 1);


        _6->addLayout(frameLayout_, 0, 0, 1, 1);


        deviceTabLayout_->addWidget(frameGroupBox_, 2, 2, 2, 1);

        spacer3_2 = new QSpacerItem(20, 120, QSizePolicy::Minimum, QSizePolicy::Expanding);

        deviceTabLayout_->addItem(spacer3_2, 3, 4, 2, 1);

        deviceLabel_ = new QLabel(layoutWidget_3);
        deviceLabel_->setObjectName(QString::fromUtf8("deviceLabel_"));
        deviceLabel_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        deviceLabel_->setWordWrap(false);

        deviceTabLayout_->addWidget(deviceLabel_, 0, 0, 1, 1);

        baudRateLabel_ = new QLabel(layoutWidget_3);
        baudRateLabel_->setObjectName(QString::fromUtf8("baudRateLabel_"));
        baudRateLabel_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        baudRateLabel_->setWordWrap(false);

        deviceTabLayout_->addWidget(baudRateLabel_, 1, 0, 1, 1);

        deviceComboBox_ = new QComboBox(layoutWidget_3);
        deviceComboBox_->setObjectName(QString::fromUtf8("deviceComboBox_"));
        deviceComboBox_->setEditable(true);

        deviceTabLayout_->addWidget(deviceComboBox_, 0, 1, 1, 2);

        spacer2_2 = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        deviceTabLayout_->addItem(spacer2_2, 2, 0, 1, 2);

        flowControlLabel_ = new QLabel(layoutWidget_3);
        flowControlLabel_->setObjectName(QString::fromUtf8("flowControlLabel_"));
        flowControlLabel_->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        flowControlLabel_->setWordWrap(false);

        deviceTabLayout_->addWidget(flowControlLabel_, 0, 3, 1, 1);

        groupBox_3 = new QGroupBox(SettingsDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(5, 30, 571, 80));
        gridLayoutWidget = new QWidget(groupBox_3);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 551, 51));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        selfPortLineEdit = new QLineEdit(gridLayoutWidget);
        selfPortLineEdit->setObjectName(QString::fromUtf8("selfPortLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(selfPortLineEdit->sizePolicy().hasHeightForWidth());
        selfPortLineEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(selfPortLineEdit, 0, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        horizontalLayoutWidget->raise();
        layoutWidget_2->raise();
        groupBox->raise();
        groupBox_2->raise();
        groupBox_3->raise();

        retranslateUi(SettingsDialog);
        QObject::connect(buttonCancel, SIGNAL(clicked()), SettingsDialog, SLOT(reject()));
        QObject::connect(buttonOK, SIGNAL(clicked()), SettingsDialog, SLOT(accept()));

        dataBitsComboBox->setCurrentIndex(-1);
        baudRateComboBox->setCurrentIndex(-1);
        flowControlComboBox->setCurrentIndex(-1);
        deviceComboBox->setCurrentIndex(-1);
        baudRateComboBox_->setCurrentIndex(-1);
        flowControlComboBox_->setCurrentIndex(-1);
        dataBitsComboBox_->setCurrentIndex(-1);
        deviceComboBox_->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", 0, QApplication::UnicodeUTF8));
        buttonOK->setText(QApplication::translate("SettingsDialog", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("SettingsDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SettingsDialog", "\320\220\320\237\320\237\320\241\320\270\320\240\320\230", 0, QApplication::UnicodeUTF8));
        frameGroupBox->setTitle(QApplication::translate("SettingsDialog", "\320\232\320\260\320\264\321\200\321\213", 0, QApplication::UnicodeUTF8));
        wordBitsLabel->setText(QApplication::translate("SettingsDialog", "\320\221\320\270\321\202\321\213 \320\264\320\260\320\275\320\275\321\213\321\205:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dataBitsComboBox->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\260 \320\261\320\270\321\202 \320\264\320\260\320\275\320\275\321\213\321\205 \320\262 \320\272\320\260\320\264\321\200\320\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        dataBitsComboBox->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        stopBitsLabel->setText(QApplication::translate("SettingsDialog", "\320\241\321\202\320\276\320\277\320\276\320\262\321\213\320\265 \320\261\320\270\321\202\321\213:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        stopBitsComboBox->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\260 \321\201\321\202\320\276\320\277\320\276\320\262\321\213\321\205 \320\261\320\270\321\202 \320\262 \320\272\320\260\320\264\321\200\320\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        parityLabel->setText(QApplication::translate("SettingsDialog", "\320\247\321\221\321\202\320\275\320\276\321\201\321\202\321\214:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        parityComboBox->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \321\201\320\277\320\276\321\201\320\276\320\261\320\260 \320\277\321\200\320\276\320\262\320\265\321\200\320\272\320\270 \320\275\320\260 \321\207\321\221\321\202\320\275\320\276\321\201\321\202\321\214", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        baudRateLabel->setText(QApplication::translate("SettingsDialog", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        baudRateComboBox->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\270 (\320\261\320\270\321\202/\321\201)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        deviceLabel->setText(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        flowControlComboBox->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \321\201\320\277\320\276\321\201\320\276\320\261\320\260 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\277\320\276\321\202\320\276\320\272\320\276\320\274", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        flowControlComboBox->setWhatsThis(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \321\201\320\277\320\276\321\201\320\276\320\261\320\260 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\277\320\276\321\202\320\276\320\272\320\276\320\274", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        flowControlLabel->setText(QApplication::translate("SettingsDialog", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\276\321\202\320\276\320\272\320\276\320\274:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        deviceComboBox->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \320\270\320\274\320\265\320\275\320\270 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\260", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox_2->setTitle(QApplication::translate("SettingsDialog", "\320\232\320\235\320\243\320\237\320\235", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        baudRateComboBox_->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\270 (\320\261\320\270\321\202/\321\201)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        flowControlComboBox_->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \321\201\320\277\320\276\321\201\320\276\320\261\320\260 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\277\320\276\321\202\320\276\320\272\320\276\320\274", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        flowControlComboBox_->setWhatsThis(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \321\201\320\277\320\276\321\201\320\276\320\261\320\260 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\277\320\276\321\202\320\276\320\272\320\276\320\274", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        frameGroupBox_->setTitle(QApplication::translate("SettingsDialog", "\320\232\320\260\320\264\321\200\321\213", 0, QApplication::UnicodeUTF8));
        parityLabel_->setText(QApplication::translate("SettingsDialog", "\320\247\321\221\321\202\320\275\320\276\321\201\321\202\321\214:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        parityComboBox_->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \321\201\320\277\320\276\321\201\320\276\320\261\320\260 \320\277\321\200\320\276\320\262\320\265\321\200\320\272\320\270 \320\275\320\260 \321\207\321\221\321\202\320\275\320\276\321\201\321\202\321\214", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        wordBitsLabel_->setText(QApplication::translate("SettingsDialog", "\320\221\320\270\321\202\321\213 \320\264\320\260\320\275\320\275\321\213\321\205:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dataBitsComboBox_->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\260 \320\261\320\270\321\202 \320\264\320\260\320\275\320\275\321\213\321\205 \320\262 \320\272\320\260\320\264\321\200\320\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        dataBitsComboBox_->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        stopBitsLabel_->setText(QApplication::translate("SettingsDialog", "\320\241\321\202\320\276\320\277\320\276\320\262\321\213\320\265 \320\261\320\270\321\202\321\213:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        stopBitsComboBox_->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\260 \321\201\321\202\320\276\320\277\320\276\320\262\321\213\321\205 \320\261\320\270\321\202 \320\262 \320\272\320\260\320\264\321\200\320\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        deviceLabel_->setText(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276:", 0, QApplication::UnicodeUTF8));
        baudRateLabel_->setText(QApplication::translate("SettingsDialog", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        deviceComboBox_->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \320\270\320\274\320\265\320\275\320\270 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\260", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        flowControlLabel_->setText(QApplication::translate("SettingsDialog", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\276\321\202\320\276\320\272\320\276\320\274:", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("SettingsDialog", "\320\241\320\265\321\202\321\214", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        selfPortLineEdit->setToolTip(QApplication::translate("SettingsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 UDP-\320\277\320\276\321\200\321\202\320\260 \320\264\320\273 \320\277\321\200\320\270\321\221\320\274\320\260 \320\246\320\243 \320\276\321\202 \320\220\320\240\320\234 \320\224\320\243", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        selfPortLineEdit->setInputMask(QApplication::translate("SettingsDialog", "00000", 0, QApplication::UnicodeUTF8));
        selfPortLineEdit->setText(QApplication::translate("SettingsDialog", "33790", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SettingsDialog", "\320\241\320\265\321\202\320\265\320\262\320\276\320\271 \320\277\320\276\321\200\321\202:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
