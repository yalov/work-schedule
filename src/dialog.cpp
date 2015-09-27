//----------------------------------------------------------------------------------//
//      Copyright 2015 Alexander Yalov <alexander.yalov@gmail.com>                  //
//                                                                                  //
//      This file is part of Work Schedule.                                         //
//                                                                                  //
//      Work Schedule is free software: you can redistribute it and/or modify       //
//      it under the terms of the GNU General Public License either                 //
//      version 3 of the License, or (at your option) any later version.            //
//                                                                                  //
//      Work Schedule is distributed in the hope that it will be useful,            //
//      but WITHOUT ANY WARRANTY; without even the implied warranty of              //
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               //
//      GNU General Public License for more details.                                //
//                                                                                  //
//      You should have received a copy of the GNU General Public License           //
//      along with Work Schedule.  If not, see <http://www.gnu.org/licenses/>.      //
//----------------------------------------------------------------------------------//

#include "dialog.h"
#include "aboutwindow.h"

#include <QPrintDialog>
#include <QColorDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolTip>
#include <QDesktopWidget>
#include <QApplication>


void Dialog::WriteSettings()
{
    QSettings settings("WorkSchedule.ini", QSettings::IniFormat);
    settings.setIniCodec("utf8");

    settings.beginGroup("Window");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

	settings.beginGroup("Setting");
    settings.setValue("lang", LangCurrent);
    settings.setValue("images", Checkbox_image->isChecked());
    settings.setValue("colorize", Checkbox_color->isChecked());
    settings.setValue("chars", Checkbox_char->isChecked());
    settings.setValue("images_shift", Spinbox_image->value());
    settings.setValue("CellHeight", Spinbox_CellHeight->value());
    settings.setValue("CellWidth", Spinbox_CellWidth->value());
    settings.setValue("FontSize", Spinbox_FontSize->value());
    settings.setValue("MonthSpaceBottom", Spinbox_MonthSpaceBottom->value());
    settings.setValue("MonthSpaceTop", Spinbox_MonthSpaceTop->value());
    settings.setValue("MonthSpaceBetween", Spinbox_MonthSpaceBetween->value());
	settings.endGroup();

    settings.beginGroup("Schedule");
    settings.setValue("Cycle", ScheduleCycle->text());
    settings.setValue("Date", ScheduleStart->date().toString("dd.MM.yyyy"));
	settings.endGroup();

    settings.beginGroup("Color");
    settings.setValue("Day", ColorLabels.value("Day")->Color.name());
    settings.setValue("Night", ColorLabels.value("Night")->Color.name());
    settings.setValue("Rest",  ColorLabels.value("Rest")->Color.name());
    settings.setValue("Holiday",  ColorLabels.value("Holiday")->Color.name());
    settings.endGroup();
}

//-----------------------------------------------------------------
void Dialog::ReadSettingsWindowPos()
{
    QSettings settings("WorkSchedule.ini", QSettings::IniFormat);
    settings.setIniCodec("utf8");

    QSize dialog_size = QSize(1000, 650);
    QRect screen = QApplication::desktop()->availableGeometry(this);
    QSize diff = (screen.size() - dialog_size)/2;
    int titleBarHeight = QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    QPoint dialog_pos = screen.topLeft() + QPoint(diff.width(), diff.height() - titleBarHeight/2);

    settings.beginGroup("Window");
    resize(0,0);
    move(settings.value("pos",  dialog_pos).toPoint());
    resize(settings.value("size", dialog_size).toSize());
    settings.endGroup();
}


//-----------------------------------------------------------------
void Dialog::ReadSettings()
{
    QSettings settings("WorkSchedule.ini",  QSettings::IniFormat);
    settings.setIniCodec("utf8");

	settings.beginGroup("Setting");
    loadLanguage(settings.value("lang", QLocale::system().name().split('_').front()).toString());
    Checkbox_image->setChecked(settings.value("images", false).toBool());
    Checkbox_color->setChecked(settings.value("colorize", true).toBool());
    Checkbox_char->setChecked(settings.value("chars",false).toBool());
    Spinbox_image->setValue(settings.value("images_shift",5).toInt());
    Spinbox_CellHeight->setValue(settings.value("CellHeight",20).toInt());
    Spinbox_CellWidth->setValue(settings.value("CellWidth",45).toInt());
    Spinbox_FontSize->setValue(settings.value("FontSize",14).toInt());
    Spinbox_MonthSpaceBottom->setValue(settings.value("MonthSpaceBottom",0).toInt());
    Spinbox_MonthSpaceTop->setValue(settings.value("MonthSpaceTop",0).toInt());
    Spinbox_MonthSpaceBetween->setValue(settings.value("MonthSpaceBetween",0).toInt());
	settings.endGroup();

    settings.beginGroup("Schedule");
    ScheduleCycle->setText(settings.value("Cycle",
          tr("D") + tr("D") + tr("H") + tr("N") + tr("N") + tr("R") + tr("H") + tr("H")).toString());

    ScheduleStart->setDate(QDate().fromString(
          settings.value("Date", QDate::currentDate().toString("dd.MM.yyyy") ).toString(), "dd.MM.yyyy"));

	settings.endGroup();

    settings.beginGroup("Color");
    ColorLabels.value("Day")->setColor(QColor (settings.value("Day",     QColor(Qt::darkYellow).name()).toString()));
    ColorLabels.value("Night")->setColor(QColor (settings.value("Night",     QColor(Qt::darkBlue).name()).toString()));
    ColorLabels.value("Rest")->setColor(QColor (settings.value("Rest",     QColor(Qt::darkRed).name()).toString()));
    ColorLabels.value("Holiday")->setColor(QColor (settings.value("Holiday",     QColor(Qt::darkRed).name()).toString()));
    settings.endGroup();

}

//-----------------------------------------------------------------

QIcon stIcon(enum QStyle::StandardPixmap s)
{
    return QWidget().style()->standardIcon(s);
}

void Dialog::createActions()
{

#ifdef _WIN32
    QIcon refreshIcon    = QIcon(":actions-icons/view-refresh.png");
    QIcon printIcon     = QIcon(":actions-icons/document-print.png");
    QIcon defSettingIcon= QIcon(":actions-icons/document-revert");
    QIcon exitIcon      = QIcon(":actions-icons/application-exit.png");
    QIcon saveIcon      = QIcon(":actions-icons/document-save-as.png");
    QIcon aboutIcon     = QIcon(":actions-icons/help-about.png");
#else
    QIcon refreshIcon    = QIcon::fromTheme("view-refresh");
    QIcon printIcon     = QIcon::fromTheme("document-print");   //QIcon::fromTheme( "configure" );
    QIcon defSettingIcon= QIcon::fromTheme("document-revert");  //reload //gtk-refresh //stock-refresh //view-refresh //document-properties //QStyle::SP_DialogResetButton
    QIcon exitIcon      = QIcon::fromTheme("application-exit"); //QStyle::SP_DialogCloseButton
    QIcon saveIcon      = QIcon::fromTheme("document-save-as"); //QStyle::SP_DialogSaveButton
    QIcon aboutIcon     = QIcon::fromTheme("help-about");       //QStyle::SP_MessageBoxInformation
#endif
    QIcon aboutQtIcon = QIcon(":actions-icons/qt.png");


    refreshAct = new QAction(refreshIcon,tr("Refresh"), this);
    refreshAct->setShortcuts(QList<QKeySequence>() << QKeySequence(Qt::CTRL + Qt::Key_O));
    connect(refreshAct, SIGNAL(triggered()), this, SLOT(ShowCalendar()));

    printAct = new QAction(printIcon,tr("Print") + "...", this);
    printAct->setShortcuts(QKeySequence::Print);
    connect(printAct, SIGNAL(triggered()), this, SLOT(Print()));

    setDefaultSettingAct = new QAction(defSettingIcon, tr("Set default setting"), this);
    setDefaultSettingAct->setShortcuts(QList<QKeySequence>() << QKeySequence(Qt::CTRL + Qt::Key_D));
    connect(setDefaultSettingAct, SIGNAL(triggered()), this, SLOT(SetDefaultSetting()));

    exitAct = new QAction(exitIcon,tr("Exit"), this);
    exitAct->setShortcuts(QKeySequence::Close);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    //-----

    SaveAsPDFAct = new QAction(saveIcon, tr("Save as PDF")+ "...", this);
    connect(SaveAsPDFAct, SIGNAL(triggered()), this, SLOT(SaveAsPDF()));

    saveAsImageAct = new QAction(saveIcon, tr("Save as PNG")+ "...", this);
    connect(saveAsImageAct, SIGNAL(triggered()), this, SLOT(SaveAsImage()));

    saveAsAlphaImageAct = new QAction(saveIcon, tr("Save as Alpha PNG")+ "...", this);
    saveAsAlphaImageAct->setShortcuts(QKeySequence::Save);
    connect(saveAsAlphaImageAct, SIGNAL(triggered()), this, SLOT(SaveAsAlphaImage()));
    //-----

    aboutAct = new QAction(aboutIcon, tr("About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(About()));

    aboutQtAct = new QAction(aboutQtIcon, tr("About Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(AboutQt()));



    langGroup = new QActionGroup(this);
    langGroup->setExclusive(true);
    connect(langGroup, SIGNAL (triggered(QAction *)), this, SLOT (slotLanguageChanged(QAction *)));

    QDir dir(LangPath);
    QStringList fileNames = dir.entryList(QStringList("workschedule_*.qm"));

    if (!fileNames.empty())
        for (auto fileName: fileNames) // "*_de.qm"
        {
            QTranslator translator;
            translator.load(fileName, LangPath);

            auto locale = fileName.split('.').first().split('_').last();  // de

            QString lang = translator.translate("Dialog", "English");

            QAction *action = new QAction(lang, this);
            action->setCheckable(true);
            action->setData(locale);

            langGroup->addAction(action);
        }
    else
    {
        QString lang = "Default (English)";
        QAction *action = new QAction(lang, this);
        action->setCheckable(true);
        action->setChecked(true);
        langGroup->addAction(action);
    }
}


//-----------------------------------------------------------------
void Dialog::createMenus()
{
    QMenuBar * MenuBar = new QMenuBar();

    fileMenu = MenuBar->addMenu(tr("&Calendar"));
    fileMenu->addAction(refreshAct);
    fileMenu->addAction(printAct);
    fileMenu->addAction(setDefaultSettingAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    SaveMenu = MenuBar->addMenu(tr("&Save"));
    SaveMenu->addAction(SaveAsPDFAct);
    SaveMenu->addAction(saveAsImageAct);
    SaveMenu->addAction(saveAsAlphaImageAct);

    langMenu = MenuBar->addMenu(tr("&Language"));
    langMenu->addActions(langGroup->actions());
    TopLayout->setMenuBar(MenuBar);

    helpMenu = MenuBar->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

}




//-----------------------------------------------------------------
// Called every time, when a menu entry of the language menu is called
void Dialog::slotLanguageChanged(QAction* action)
{
     if(0 != action)
     {
        // load the language dependant on the action content
        loadLanguage(action->data().toString());
     }
}


//-----------------------------------------------------------------
void Dialog::loadLanguage(const QString& rLanguage)
{
    if(LangCurrent != rLanguage && !rLanguage.isEmpty())
    {
        LangCurrent = rLanguage;
        QLocale locale = QLocale(LangCurrent);
        QLocale::setDefault(locale);

       qApp->removeTranslator(Translator);
       qApp->removeTranslator(TranslatorQt);


       bool load = Translator->load(QString("workschedule_%1.qm").arg(rLanguage), LangPath);
       if (load)
            qApp->installTranslator(Translator);


       bool loadQt = TranslatorQt->load(QString("qtbaseloc_%1.qm").arg(rLanguage), LangPath);
       if (loadQt)
            qApp->installTranslator(TranslatorQt);

       if (langGroup)
       for (auto action:langGroup->actions())
       {
           if (action->data().toString() == LangCurrent)
               action->setChecked(true);
       }


    }
}


//-----------------------------------------------------------------
//QEvent::LanguageChange will always be called, if a translator object is installed in the application object
//QEvent::LocaleChange is called, when the system language is switched
void Dialog::changeEvent(QEvent* event)
{
    if(0 != event)
    {
        switch(event->type())
        {
            // this event is send if a translator is loaded
            case QEvent::LanguageChange:
            {

                retranslate();
                ShowCalendar();
                break;
            }


            // this event is send, if the system, language changes
            case QEvent::LocaleChange:
            {
                QString locale = QLocale::system().name();
                locale.truncate(locale.lastIndexOf('_'));
                loadLanguage(locale);
                break;
            }
            default:
                break;

        }
    }

    QDialog::changeEvent(event);
}

//-----------------------------------------------------------------
void Dialog::retranslate()
{
    ScheduleStart->setLocale(QLocale(LangCurrent));

    LabelScheduleStart->setText(tr("Date Start"));

    tooltip_srt = tr("Cycle schedule code:")+"<br>" + tr("<b>D</b>ay")+"<br>" +
            tr("<b>N</b>ight")+"<br>" + tr("<b>R</b>est")+"<br>" + tr("<b>H</b>oliday");
    LabelScheduleCycle->setToolTip(tooltip_srt );
    LabelScheduleCycle->setText(tr("Schedule Cycle") + "<img src=':/icons/tooltip.png'>");
    ScheduleCycle->setToolTip(tooltip_srt);
    ButtonRefresh->setText(tr("Refresh")) ;

    groupBox->setTitle(tr("Schedule setting")) ;
    Label_image->setText(tr("Icons, shifted by "));
    Checkbox_color->setText(tr("Colorize"));
    Checkbox_char->setText(tr("Chars"));

    groupBox_Color->setTitle(tr("Color setting"));

    ColorLabels.value("Day")->setText(tr("<b>D</b>ay"));
    ColorLabels.value("Night")->setText(tr("<b>N</b>ight"));
    ColorLabels.value("Rest")->setText(tr("<b>R</b>est"));
    ColorLabels.value("Holiday")->setText(tr("<b>H</b>oliday"));


    groupBox_Spinboxes->setTitle(tr("Showing setting")) ;
    Label_CellHeight->setText(tr("Cell Height"));
    Label_CellWidth->setText(tr("Cell Width"));
    Label_FontSize->setText(tr("Font Size"));
    Label_MonthSpaceBottom->setText(tr("Month Space Bottom"));
    Label_MonthSpaceTop->setText(tr("Month Space Top"));
    Label_MonthSpaceBetween->setText(tr("Month Space Between"));

    refreshAct->setText(tr("Refresh"));
    printAct->setText(tr("Print"));
    SaveAsPDFAct->setText(tr("Save as PDF"));
    saveAsImageAct ->setText(tr("Save as PNG"));
    saveAsAlphaImageAct->setText(tr("Save as Alpha PNG"));
    exitAct->setText(tr("&Exit"));
    aboutAct->setText(tr("About"));
    aboutQtAct->setText(tr("About Qt"));
    setDefaultSettingAct->setText(tr("Set default setting"));

    bool isOnlyEnStandartChar = true;
    bool isOnlyRuStandartChar = true;
    bool isOnlyBeStandartChar = true;
    for(auto ch: ScheduleCycle->text())
    {
        if (ch != 'D' && ch != 'N' && ch != 'H' && ch != 'R') isOnlyEnStandartChar = false;
        if (ch != QChar(0x0414) && ch != QChar(0x041D) && ch != QChar(0x0412) && ch != QChar(0x041E)) isOnlyRuStandartChar = false;
        if (ch != QChar(0x0414) && ch != QChar(0x041D) && ch != QChar(0x0412) && ch != QChar(0x0410)) isOnlyBeStandartChar = false;
    }

    if (isOnlyEnStandartChar || isOnlyRuStandartChar || isOnlyBeStandartChar)
    {
        QString cycle;
        for(auto ch: ScheduleCycle->text())
        {
            if (isOnlyEnStandartChar) cycle += tr(QString(ch).toStdString().c_str());
            else if (isOnlyRuStandartChar)
            {
                if      (ch == QChar(0x0414))  cycle += tr("D");
                else if ( ch == QChar(0x041D))    cycle += tr("N");
                else if ( ch == QChar(0x0412))   cycle += tr("H");
                else if ( ch == QChar(0x041E)) cycle += tr("R");

            }
            else if (isOnlyBeStandartChar)
            {
                if      (ch == QChar(0x0414))  cycle += tr("D");
                else if ( ch == QChar(0x041D))    cycle += tr("N");
                else if ( ch == QChar(0x0412))   cycle += tr("H");
                else if ( ch == QChar(0x0410)) cycle += tr("R");
            }
        }


        ScheduleCycle->setText( cycle);
    }

    createMenus();
}
//-----------------------------------------------------------------
void Dialog::SetDefaultSetting()
{
    QSettings settings("WorkSchedule.ini",  QSettings::IniFormat);
    settings.clear();
    ReadSettings();
    ShowCalendar();
}

//-----------------------------------------------------------------
Dialog::Dialog(QWidget *parent)
    : QDialog(parent), langGroup(NULL)
{
    setWindowTitle(APP_NAME);
    setWindowFlags(Qt::Window);
    setWindowIcon(QIcon(":/icons/logo.png"));

    Translator = new QTranslator();
    TranslatorQt = new QTranslator();
    LangPath = "languages";
    TopLayout = new QVBoxLayout();
    QHBoxLayout * LayoutSetting = new QHBoxLayout();
    QHBoxLayout * LayoutSetting2 = new QHBoxLayout();
    QHBoxLayout * LayoutShowing = new QHBoxLayout();

    LabelScheduleStart = new QLabel(tr("Date Start"));
    LabelScheduleStart->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    ScheduleStart = new QDateEdit();
    ScheduleStart->setMinimumDate(QDate(2000,1,1));
    ScheduleStart->setMaximumDate(QDate(2099,12,31));
    ScheduleStart->setCalendarPopup(true);
    ScheduleStart->setDisplayFormat("dd MMMM yyyy");


    tooltip_srt = tr("Cycle schedule code:")+"<br>"
            + tr("<b>D</b>ay")+"<br>"
            + tr("<b>N</b>ight")+"<br>"
            + tr("<b>R</b>est")+"<br>"
            + tr("<b>H</b>oliday");

    LabelScheduleCycle = new QLabel();
    LabelScheduleCycle->setToolTip(tooltip_srt );
    LabelScheduleCycle->setText(tr("Schedule Cycle") + "<img src=':/icons/tooltip.png'>");
    LabelScheduleCycle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    ScheduleCycle = new QLineEdit();
    ScheduleCycle->setToolTip(tooltip_srt);

    ButtonRefresh = new QPushButton(tr("Refresh"));

#ifdef _WIN32
    QIcon refreshIcon    = QIcon(":actions-icons/view-refresh.png");
#else
    QIcon refreshIcon    = QIcon::fromTheme("view-refresh");
#endif

    ButtonRefresh->setIcon(refreshIcon);

    LayoutSetting->addWidget(LabelScheduleStart);
    LayoutSetting->addWidget(ScheduleStart);
    LayoutSetting->addSpacing(50);
    LayoutSetting->addWidget(LabelScheduleCycle);
    LayoutSetting->addWidget(ScheduleCycle);
    LayoutSetting->addSpacing(50);
    LayoutSetting->addWidget(ButtonRefresh);

    TopLayout->addLayout(LayoutSetting);


    groupBox = new QGroupBox(tr("Schedule setting"));
    QVBoxLayout * LayoutCheckboxs = new QVBoxLayout();

    Checkbox_color = new QCheckBox(tr("Colorize"));

	LayoutCheckboxs->addWidget(Checkbox_color);

    QHBoxLayout * Layout_Checkbox_image = new QHBoxLayout();
    Checkbox_image = new  QCheckBox();
    Label_image = new QLabel(tr("Icons, shifted by "));
    Spinbox_image = new QSpinBox();
    Spinbox_image->setRange(-499,499);
    Spinbox_image->setEnabled(false);
    Layout_Checkbox_image->addWidget(Checkbox_image);
    Layout_Checkbox_image->addWidget(Label_image);
    Layout_Checkbox_image->addWidget(Spinbox_image);
    Layout_Checkbox_image->addSpacing(20);

    Checkbox_char = new  QCheckBox(tr("Chars"));
    LayoutCheckboxs->addLayout(Layout_Checkbox_image);
    LayoutCheckboxs->addWidget(Checkbox_char);

    groupBox->setLayout(LayoutCheckboxs);


    groupBox_Color = new QGroupBox(tr("Color setting"));
    QGridLayout * Layout_Color = new QGridLayout();

    ColorLabels.insert("Day", new ColorLabel(tr("<b>D</b>ay")));
    ColorLabels.insert("Night",new ColorLabel(tr("<b>N</b>ight")));
    ColorLabels.insert("Rest",new ColorLabel(tr("<b>R</b>est")));
    ColorLabels.insert("Holiday",new ColorLabel(tr("<b>H</b>oliday")));

    Layout_Color->addWidget(ColorLabels.value("Day"),0,0);
    Layout_Color->addWidget(ColorLabels.value("Night"),1,0);
    Layout_Color->addWidget(ColorLabels.value("Rest"),0,1);
    Layout_Color->addWidget(ColorLabels.value("Holiday"),1,1);


    groupBox_Color->setLayout(Layout_Color);


    groupBox_Spinboxes = new QGroupBox(tr("Showing setting"));
    QGridLayout * Layout_Grid = new QGridLayout();

    Spinbox_CellHeight = new QSpinBox();
    Spinbox_CellWidth = new QSpinBox();
    Spinbox_FontSize = new QSpinBox();
    Spinbox_MonthSpaceBottom = new QSpinBox();
    Spinbox_MonthSpaceTop = new QSpinBox();
    Spinbox_MonthSpaceBetween = new QSpinBox();

    Spinbox_CellHeight->setRange(5,499);
    Spinbox_CellWidth->setRange(5,499);
    Spinbox_FontSize->setRange(1,72);
    Spinbox_MonthSpaceBottom->setRange(-499, 499);
    Spinbox_MonthSpaceTop->setRange(-499, 499);
    Spinbox_MonthSpaceBetween->setRange(-499,499);
	
    Label_CellHeight = new QLabel(tr("Cell Height"));
    Label_CellWidth = new QLabel(tr("Cell Width"));
    Label_FontSize = new QLabel(tr("Font Size"));

    Label_MonthSpaceBottom = new QLabel(tr("Month Space Bottom"));
    Label_MonthSpaceTop = new QLabel(tr("Month Space Top"));
    Label_MonthSpaceBetween = new QLabel(tr("Month Space Between"));


    Layout_Grid->addWidget(Label_CellHeight, 0,0);
	Layout_Grid->addWidget(Spinbox_CellHeight, 0, 1);
    Layout_Grid->addWidget(Label_CellWidth, 1,0);
	Layout_Grid->addWidget(Spinbox_CellWidth, 1, 1);
    Layout_Grid->addWidget(Label_FontSize, 2,0);
    Layout_Grid->addWidget(Spinbox_FontSize, 2,1);
    Layout_Grid->setColumnMinimumWidth(2, 20);

    Layout_Grid->addWidget(Label_MonthSpaceBottom, 0, 3);
    Layout_Grid->addWidget(Spinbox_MonthSpaceBottom, 0, 4);
    Layout_Grid->addWidget(Label_MonthSpaceTop, 1, 3);
    Layout_Grid->addWidget(Spinbox_MonthSpaceTop, 1, 4);
    Layout_Grid->addWidget(Label_MonthSpaceBetween, 2, 3);
    Layout_Grid->addWidget(Spinbox_MonthSpaceBetween, 2, 4);

    groupBox_Spinboxes->setLayout(Layout_Grid);

    LayoutSetting2->addWidget(groupBox);
    LayoutSetting2->addStretch();
    LayoutSetting2->addWidget(groupBox_Color);
    LayoutSetting2->addStretch();
    LayoutSetting2->addWidget(groupBox_Spinboxes);

    TopLayout->addLayout(LayoutSetting2);

    scene = new QGraphicsScene();

    GraphicsOut = new QGraphicsView();
    LayoutShowing->addWidget(GraphicsOut);
    TopLayout->addLayout(LayoutShowing);

    setLayout(TopLayout);

    createActions();
    createMenus();

    ReadSettingsWindowPos();
    ReadSettings();



    connect(ButtonRefresh, SIGNAL(clicked()), this, SLOT(ShowCalendar()));

    connect(Checkbox_char,  SIGNAL(clicked()), this, SLOT(ShowCalendar()));
    connect(Checkbox_color, SIGNAL(clicked()), this, SLOT(ShowCalendar()));
    connect(Checkbox_image, SIGNAL(clicked()), this, SLOT(ShowCalendar()));

    connect(ScheduleStart, SIGNAL(dateChanged(QDate)), this, SLOT(ShowCalendar()));
    connect(ScheduleCycle, SIGNAL(textChanged(QString)), this, SLOT(ShowCalendar()));

    for (auto colorlabel: ColorLabels)
         connect(colorlabel,      SIGNAL(clicked()), this, SLOT(ColorButton()));

    connect(Spinbox_CellHeight, SIGNAL(valueChanged(int)), this, SLOT(posUpdate()));
    connect(Spinbox_CellWidth,  SIGNAL(valueChanged(int)), this, SLOT(posUpdate()));
    connect(Spinbox_FontSize,   SIGNAL(valueChanged(int)), this, SLOT(fontUpdate()));
    connect(Spinbox_MonthSpaceBottom,   SIGNAL(valueChanged(int)), this, SLOT(posUpdate()));
    connect(Spinbox_MonthSpaceTop,   SIGNAL(valueChanged(int)), this, SLOT(posUpdate()));
    connect(Spinbox_MonthSpaceBetween,   SIGNAL(valueChanged(int)), this, SLOT(posUpdate()));
    connect(Spinbox_image,      SIGNAL(valueChanged(int)), this, SLOT(posUpdate()));

    ShowCalendar();
}

//-----------------------------------------------------------------
void Dialog::posUpdate()
{
    QDate DateScheduleStart = ScheduleStart->date();
    QDate dateIterator = QDate(DateScheduleStart.year(),1,1);

    bool isShowImage = Checkbox_image->checkState();

    int cellHeight = Spinbox_CellHeight->value();
    int cellWidth = Spinbox_CellWidth->value();

    int monthTitleHeight = cellHeight * 1.7 + Spinbox_MonthSpaceBottom->value();

    int monthTop = Spinbox_MonthSpaceTop->value();
    int monthBetween = Spinbox_MonthSpaceBetween->value();

    int monthHeight = monthTitleHeight + cellHeight * 7 + 10;
    int monthWidth = cellWidth * 6 ;

    int yearHeight = cellHeight * 2 ;


    QPoint year_pos = QPoint((3 * monthWidth + 2*monthBetween)/2 - year->boundingRect().width() / 2, 0);
    year->setPos(year_pos);


    for (int y = 0; y < 4; y++)
    for (int x = 0; x < 3; x++)
    {
        QPoint Month_pos = QPoint(x*(monthWidth + monthBetween), yearHeight + y*monthHeight+ monthTop*(y+1));
        int mounth_index = dateIterator.month();
        int week_in_mouth = 1;

        months.at(3*y+x)->setPos(Month_pos + QPoint(monthWidth/2 - months.at(3*y+x)->boundingRect().width()/2 ,0));


        if (x != 1)
        for (int i=1; i<=7; i++)
        {
            if      (x == 0) weekdays.at((y*2+x/2)*7 + i-1)->setPos(Month_pos + QPoint(-1 * cellWidth,monthTitleHeight + cellHeight * (i-1)));
            else if (x == 2) weekdays.at((y*2+x/2)*7 + i-1)->setPos(Month_pos + QPoint(6 * cellWidth,monthTitleHeight + cellHeight * (i-1)));
        }

        for (;dateIterator.month() == mounth_index; dateIterator = dateIterator.addDays(1))
        {

            days.at(dateIterator.dayOfYear()-1)->setPos(Month_pos + QPoint((week_in_mouth-1) *cellWidth,
            monthTitleHeight  + (dateIterator.dayOfWeek()-1)*cellHeight
            ));


            if (isShowImage)
            {
                pics.at(dateIterator.dayOfYear()-1)->setPos(days.at(dateIterator.dayOfYear()-1)->pos().x() + cellWidth/2 + Spinbox_image->value(),
                            days.at(dateIterator.dayOfYear()-1)->pos().y() + days.at(dateIterator.dayOfYear()-1)->boundingRect().height()/2 - pics.at(dateIterator.dayOfYear()-1)->boundingRect().height()/2);

            }

            if (dateIterator.dayOfWeek() == 7)
                week_in_mouth++;
        }
    }

    scene->setSceneRect(scene->itemsBoundingRect());
}


void Dialog::fontUpdate()
{
    if (Checkbox_image->isChecked())
    {
        ShowCalendar();
        return;
    }

    int fontSize = Spinbox_FontSize->value();

    QDate DateScheduleStart = ScheduleStart->date();
    QDate dateIterator = QDate(DateScheduleStart.year(),1,1);

    bool isShowImage = Checkbox_image->checkState();

    int cellHeight = Spinbox_CellHeight->value();
    int cellWidth = Spinbox_CellWidth->value();

    int monthTitleHeight = cellHeight * 1.7 + Spinbox_MonthSpaceBottom->value();

    int monthTop = Spinbox_MonthSpaceTop->value();
    int monthBetween = Spinbox_MonthSpaceBetween->value();

    int monthHeight = monthTitleHeight + cellHeight * 7 + 10;
    int monthWidth = cellWidth * 6 ;

    int yearHeight = cellHeight * 2 ;

    Fonts.day.setPointSize(fontSize);
    Fonts.day_of_week.setPointSize(fontSize);
    Fonts.month.setPointSize(fontSize*1.5);
    Fonts.year.setPointSize(fontSize*2);


    year->setFont(Fonts.year);
    for (auto m: months) m->setFont(Fonts.month);
    for (auto w: weekdays) w->setFont(Fonts.day_of_week);
    for (auto d: days) d->setFont(Fonts.day);

    for (int y = 0; y < 4; y++)
    for (int x = 0; x < 3; x++)
    {
        int mounth_index = dateIterator.month();
        QPoint Month_pos = QPoint(x*(monthWidth + monthBetween), yearHeight + y*monthHeight+ monthTop*(y+1));
        months.at(3*y+x)->setPos(Month_pos + QPoint(monthWidth/2 - months.at(3*y+x)->boundingRect().width()/2 ,0));

        if (isShowImage)
        {
            for (;dateIterator.month() == mounth_index; dateIterator = dateIterator.addDays(1))
            {
                    pics.at(dateIterator.dayOfYear()-1)->setPos(days.at(dateIterator.dayOfYear()-1)->pos().x() + cellWidth/2 + Spinbox_image->value(),
                        days.at(dateIterator.dayOfYear()-1)->pos().y() + days.at(dateIterator.dayOfYear()-1)->boundingRect().height()/2 - pics.at(dateIterator.dayOfYear()-1)->boundingRect().height()/2);
            }
        }
    }


    scene->setSceneRect(scene->itemsBoundingRect());
}


//-----------------------------------------------------------------

void Dialog::ShowCalendar()
{
   months.clear();
   weekdays.clear();
   days.clear();
   pics.clear();


    if (Checkbox_char->isChecked() && Checkbox_image->isChecked())
    {
        QCheckBox * osender = qobject_cast<QCheckBox*>(sender());

        if (Checkbox_char == osender)
            Checkbox_image->setChecked(false);
        else
            Checkbox_char->setChecked(false);
    }

    Spinbox_image->setEnabled(Checkbox_image->isChecked());

    groupBox_Color->setVisible(Checkbox_color->isChecked());



    QDate DateScheduleStart = ScheduleStart->date();

    QDate date_iterator = QDate(DateScheduleStart.year(),1,1);

    int day_of_year = DateScheduleStart.dayOfYear();

    QString cycle = ScheduleCycle->text();

    int fontSize = Spinbox_FontSize->value();

    bool isShowImage = Checkbox_image->checkState();
    bool isShowColor = Checkbox_color->checkState();
    bool isShowChar = Checkbox_char->checkState();

    int cellHeight = Spinbox_CellHeight->value();
    int cellWidth = Spinbox_CellWidth->value();

    int monthTitleHeight = cellHeight * 1.7 + Spinbox_MonthSpaceBottom->value();

    int monthTop = Spinbox_MonthSpaceTop->value();
    int monthBetween = Spinbox_MonthSpaceBetween->value();

    int monthHeight = monthTitleHeight + cellHeight * 7 + 10;
    int monthWidth = cellWidth * 6 ;

    int yearHeight = cellHeight * 2 ;

    Fonts.day = QFont("Monospace", fontSize, QFont::Bold);
    Fonts.day.setStyleHint(QFont::TypeWriter);

    Fonts.day_of_week = QFont("Monospace", fontSize, QFont::Bold);
    Fonts.day_of_week.setStyleHint(QFont::TypeWriter);

    Fonts.month = QFont("Monospace", fontSize*1.5, QFont::Bold);
    Fonts.month.setStyleHint(QFont::TypeWriter);

    Fonts.year = QFont("Monospace", fontSize*2, QFont::Black);
    Fonts.year.setStyleHint(QFont::TypeWriter);

    QPixmap day_pic, night_pic, rest_pic, holiday_pic;

    if (isShowImage)
    {
        day_pic = QPixmap(QString("shifts/d.png"));
        night_pic = QPixmap(QString("shifts/n.png"));
        rest_pic = QPixmap(QString("shifts/r.png"));
        holiday_pic = QPixmap(QString("shifts/h.png"));


        if (!day_pic.isNull())
            day_pic = day_pic.scaled(fontSize,fontSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);

        if (!night_pic.isNull())
            night_pic = night_pic.scaled(fontSize,fontSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);

        if (!rest_pic.isNull())
            rest_pic = rest_pic.scaled(fontSize,fontSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);

        if (!holiday_pic.isNull())
            holiday_pic = holiday_pic.scaled(fontSize,fontSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }



    scene = new QGraphicsScene();


	{
        year = new QGraphicsTextItem();
        year->setPlainText(QString::number(DateScheduleStart.year()));
        year->setFont(Fonts.year);

        QPoint year_pos = QPoint((3 * monthWidth + 2*monthBetween)/2 - year->boundingRect().width() / 2, 0);
		year->setPos(year_pos);
		scene->addItem(year);
	}

    months.reserve(12);
    weekdays.reserve(7);
    days.reserve(366);
    pics.reserve(366);

    for (int y = 0; y < 4; y++)
    for (int x = 0; x < 3; x++)
    {
        QPoint Month_pos = QPoint(x*(monthWidth + monthBetween), yearHeight + y*monthHeight+ monthTop*(y+1));
        int mounth_index = date_iterator.month();
        int week_in_mouth = 1;

        months.append(new QGraphicsTextItem());
        switch (date_iterator.month())
        {
            case 1: months.back()->setPlainText(tr("January")); break;
            case 2: months.back()->setPlainText(tr("February")); break;
            case 3: months.back()->setPlainText(tr("March")); break;
            case 4: months.back()->setPlainText(tr("April")); break;
            case 5: months.back()->setPlainText(tr("May")); break;
            case 6: months.back()->setPlainText(tr("June")); break;
            case 7: months.back()->setPlainText(tr("July")); break;
            case 8: months.back()->setPlainText(tr("August")); break;
            case 9: months.back()->setPlainText(tr("September")); break;
            case 10: months.back()->setPlainText(tr("October")); break;
            case 11: months.back()->setPlainText(tr("November")); break;
            case 12: months.back()->setPlainText(tr("December")); break;
            default: break;
        }

        months.back()->setFont(Fonts.month);
        months.back()->setPos(Month_pos + QPoint(monthWidth/2 - months.back()->boundingRect().width()/2 ,0));

        scene->addItem(months.back());


        if (x != 1)
        for (int i=1; i<=7; i++)
        {
            weekdays.append( new QGraphicsTextItem());

            switch (i)
            {
                case 1: weekdays.last()->setPlainText(tr("Mon")); break;
                case 2: weekdays.last()->setPlainText(tr("Tue")); break;
                case 3: weekdays.last()->setPlainText(tr("Wed")); break;
                case 4: weekdays.last()->setPlainText(tr("Thu")); break;
                case 5: weekdays.last()->setPlainText(tr("Fri")); break;
                case 6: weekdays.last()->setPlainText(tr("Sat")); break;
                case 7: weekdays.last()->setPlainText(tr("Sun")); break;
                default: break;
            }

            weekdays.last()->setFont(Fonts.day_of_week);

            if (x == 0)
            {
                weekdays.last()->setPos(Month_pos + QPoint(-1 * cellWidth,monthTitleHeight + cellHeight * (i-1)));
                scene->addItem(weekdays.last());
            }
            else if (x == 2)
            {
                weekdays.last()->setPos(Month_pos + QPoint(6 * cellWidth,monthTitleHeight + cellHeight * (i-1)));
                scene->addItem(weekdays.last());
            }
        }

        for (;date_iterator.month() == mounth_index; date_iterator = date_iterator.addDays(1))
        {
            days.append(new QGraphicsTextItem());

            int index = ((date_iterator.dayOfYear() - day_of_year)) % cycle.length();

            if (index < 0) index += cycle.length();

            QChar ch = cycle.at(index);



            if (isShowColor)
            {
                QColor color;
                if      (ch.toLower() == 'd' || ch.toLower() == QChar(0x0434))    color = ColorLabels.value("Day")->Color;// ColorDay;
                else if (ch.toLower() == 'n' || ch.toLower() == QChar(0x043D))    color = ColorLabels.value("Night")->Color;//ColorNight;
                else if (ch.toLower() == 'h' || ch.toLower() == QChar(0x0432))    color = ColorLabels.value("Holiday")->Color;//ColorHoliday;
                else if (ch.toLower() == 'r' || ch.toLower() == QChar(0x043E)
                                             || ch.toLower() == QChar(0x0430))    color = ColorLabels.value("Rest")->Color;//ColorRest;
                else                   color = Qt::black;

                days.last()->setDefaultTextColor(color);
            }


            if (isShowChar)  days.last()->setPlainText(QString("%1").arg(date_iterator.day(),2,10, QLatin1Char( ' ' )) + ch);
            else            days.last()->setPlainText(QString("%1").arg(date_iterator.day(),2,10, QLatin1Char( ' ' )) );


            days.last()->setFont(Fonts.day);
            days.last()->setPos(Month_pos + QPoint((week_in_mouth-1) *cellWidth,
            monthTitleHeight  + (date_iterator.dayOfWeek()-1)*cellHeight
            ));


            scene->addItem(days.last());

            if (isShowImage)
            {
                if      (!day_pic.isNull() && (ch.toLower() == 'd'     || ch.toLower() == QChar(0x0434)))    pics.append( new QGraphicsPixmapItem(day_pic));
                else if (!night_pic.isNull() && (ch.toLower() == 'n'   || ch.toLower() == QChar(0x043D)))    pics.append( new QGraphicsPixmapItem(night_pic));
                else if (!holiday_pic.isNull() && (ch.toLower() == 'h' || ch.toLower() == QChar(0x0432)))    pics.append( new QGraphicsPixmapItem(holiday_pic));
                else if (!rest_pic.isNull() && (ch.toLower() == 'r'    || ch.toLower() == QChar(0x043E)
                                                                       || ch.toLower() == QChar(0x0430)))    pics.append( new QGraphicsPixmapItem(rest_pic));
                else                   pics.append( new QGraphicsPixmapItem());

                pics.back()->setPos(days.last()->pos().x() + cellWidth/2 + Spinbox_image->value(),
                            days.last()->pos().y() + days.last()->boundingRect().height()/2 - pics.back()->boundingRect().height()/2);

                scene->addItem(pics.last());
            }

            if (date_iterator.dayOfWeek() == 7)
                week_in_mouth++;
        }
    }
    GraphicsOut->setScene(scene);
}

//-----------------------------------------------------------------

Dialog::~Dialog()
{

}

//-----------------------------------------------------------------

void Dialog::Print()
{

    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    QPrintDialog dlg(&printer);
    if(dlg.exec()==QDialog::Accepted) {
        QPainter p(&printer);
        scene->render(&p);
        p.end();
    }
}

//-----------------------------------------------------------------

void Dialog::SaveAsPDF()
{
    QPrinter printer( QPrinter::HighResolution );
       printer.setPageSize( QPrinter::A4 );
       printer.setOrientation( QPrinter::Portrait );
       printer.setOutputFormat( QPrinter::PdfFormat );

       QString filters("Portable Document Format (*.pdf);;All files (*.*)");

	   QString filepath = QFileDialog::getSaveFileName(0, tr("Save file"), 
		   QDir::homePath() + QDir::separator() + "Work Schedule " +
		   ScheduleStart->date().toString("yyyy") + ".pdf",
           filters);

       if (!filepath.isEmpty())
       {
           printer.setOutputFileName( filepath );
		   QPainter p(&printer);
           scene->render( &p );
           p.end();
       }
}

//-----------------------------------------------------------------

void Dialog::SaveAsImage()
{
    scene->setBackgroundBrush(Qt::white);

    scene->clearSelection();                                                  // Selections would also render to the file
    scene->setSceneRect(scene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    image.fill(Qt::transparent);                                              // Start all pixels transparent

    QString filters("Portable Network Graphics (*.png);;All files (*.*)");

    QString filepath = QFileDialog::getSaveFileName(0, tr("Save image"),
                       QDir::homePath() + QDir::separator() + "Work Schedule "+
                       ScheduleStart->date().toString("yyyy")+".png", filters);


    QPainter painter(&image);
    scene->render(&painter);
    image.save(filepath);

    scene->setBackgroundBrush(Qt::NoBrush);
}

//-----------------------------------------------------------------

void Dialog::SaveAsAlphaImage()
{

    scene->clearSelection();
    scene->setSceneRect(scene->itemsBoundingRect());
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QString filters("Portable Network Graphics (*.png);;All files (*.*)");

    QString filepath = QFileDialog::getSaveFileName(0, tr("Save image"),
                       QDir::homePath() + QDir::separator() + "Work Schedule "+
                       ScheduleStart->date().toString("yyyy")+".png",  filters);

    QPainter painter(&image);
    scene->render(&painter);
    image.save(filepath);
}

//-----------------------------------------------------------------


void Dialog::closeEvent(QCloseEvent *event)
{
    WriteSettings();
    event->accept();
}

//-----------------------------------------------------------------

void Dialog::ColorButton()
{
    ColorLabel * colorLabel = qobject_cast<ColorLabel*>(sender());
    QColor chosenColor = colorLabel->Color;

    chosenColor = QColorDialog::getColor(chosenColor, this, QString(), QColorDialog::DontUseNativeDialog);

    if (chosenColor.isValid())
    {
        colorLabel->setColor(chosenColor);
    }

    ShowCalendar();
}


//-----------------------------------------------------------------

void Dialog::About()
{
    AboutWindow * about = new AboutWindow();
    about->show();
}

//-----------------------------------------------------------------

void Dialog::AboutQt()
{
    QMessageBox::aboutQt(this);
}
