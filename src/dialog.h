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

#ifndef DIALOG_H
#define DIALOG_H

#include "colorlabel.h"

#include <QDialog>
#include <QtGui/QtGui>
#include <QtCore/QtCore>

#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QGroupBox>

#include <QPushButton>
#include <QRadioButton>

#include <QLabel>

#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>

#include <QActionGroup>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QPushButton>

#include <QVBoxLayout>





class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();


private:
    void WriteSettings();
    void ReadSettingsWindowPos();
    void ReadSettings();
    void closeEvent(QCloseEvent *event);
    void retranslate();
    void loadLanguage(const QString& rLanguage);  // loads a language by the given language shortcur (e.g. de, en)
    void changeEvent(QEvent*);   // this event is called, when a new translator is loaded or the system language is changed


private slots:
    void Print();
    void ShowCalendar();
    void SaveAsPDF();
    void SaveAsImage();
    void SaveAsAlphaImage();
    void About();
    void AboutQt();
    void ColorButton();
    void SetDefaultSetting();
    void slotLanguageChanged(QAction* action);  // this slot is called by the language menu actions
    void posUpdate();
    void fontUpdate();

private:
    void createActions();
    void createMenus();
    QMenu *fileMenu;
    QMenu *SaveMenu;
    QMenu *helpMenu;
    QMenu *langMenu;

    QAction *refreshAct;
    QAction *printAct;
    QAction *SaveAsPDFAct;
    QAction *saveAsImageAct;
    QAction *saveAsAlphaImageAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *setDefaultSettingAct;
    QActionGroup* langGroup;

    QTranslator * Translator;
    QTranslator * TranslatorQt;
    QString LangCurrent;
    QString LangPath;

private:
    QGraphicsTextItem * year;
    QList<QGraphicsTextItem*> months;
    QList<QGraphicsTextItem*> weekdays;
    QList<QGraphicsTextItem*> days;
    QList<QGraphicsPixmapItem*> pics;

    struct {
        QFont day;
        QFont day_of_week;
        QFont month;
        QFont year;
    } Fonts;


private:

    QLabel * LabelScheduleStart;
    QString tooltip_srt;
    QLabel * LabelScheduleCycle ;
    QPushButton * ButtonRefresh ;
    QGroupBox *groupBox ;
    QLabel * Label_image;
    QGroupBox *groupBox_Spinboxes ;

    QVBoxLayout * TopLayout ;

    QDateEdit * ScheduleStart;
    QLineEdit * ScheduleCycle;
    QGraphicsView * GraphicsOut;
    QGraphicsScene * scene ;

    QCheckBox * Checkbox_image;
    QSpinBox * Spinbox_image;
    QCheckBox * Checkbox_color;
    QCheckBox * Checkbox_char;

    QLabel * Label_CellHeight;
    QLabel * Label_CellWidth;
    QLabel * Label_FontSize;
    QLabel * Label_MonthSpaceBottom;
    QLabel * Label_MonthSpaceTop;
    QLabel * Label_MonthSpaceBetween;

    QSpinBox * Spinbox_CellHeight;
    QSpinBox * Spinbox_CellWidth;
    QSpinBox * Spinbox_FontSize;
    QSpinBox * Spinbox_MonthSpaceBottom;
    QSpinBox * Spinbox_MonthSpaceTop;
    QSpinBox * Spinbox_MonthSpaceBetween;

    QGroupBox *groupBox_Color;
    QMap<QString, ColorLabel*> ColorLabels;
};

#endif // DIALOG_H
