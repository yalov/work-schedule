#---------------------------------------------------#
#                                                   #
# Project created by QtCreator 2015-06-12T14:37:20  #
#                                                   #
#----------------------------------------------------------------------------------#
#      Copyright 2015 Alexander Yalov <alexander.yalov@gmail.com>                  #
#                                                                                  #
#      This file is part of Work Schedule.                                         #
#                                                                                  #
#      Work Schedule is free software: you can redistribute it and/or modify       #
#      it under the terms of the GNU General Public License either                 #
#      version 3 of the License, or (at your option) any later version.            #
#                                                                                  #
#      Work Schedule is distributed in the hope that it will be useful,            #
#      but WITHOUT ANY WARRANTY; without even the implied warranty of              #
#      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               #
#      GNU General Public License for more details.                                #
#                                                                                  #
#      You should have received a copy of the GNU General Public License           #
#      along with Work Schedule.  If not, see <http://www.gnu.org/licenses/>.      #
#----------------------------------------------------------------------------------#


QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4):{
    CONFIG += c++11
    QT += widgets
    win32:RC_ICONS += icons\icon.ico
}else: {
    QMAKE_CXXFLAGS += -std=c++11
}

TEMPLATE = app

VERSION = 1.9.4
TARGET = "Work Schedule"
QMAKE_TARGET_COPYRIGHT = Alexander Yalov


QMAKE_TARGET_DESCRIPTION = $$TARGET
DEFINES += 'DEVELOP_NAME=\'\"$$QMAKE_TARGET_COPYRIGHT\"\''
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += 'APP_NAME=\'\"$$TARGET\"\''


TRANSLATIONS = languages/workschedule_ru.ts languages/workschedule_be.ts languages/workschedule_en.ts

RESOURCES += \
    resource.qrc

DISTFILES +=

HEADERS += \
    src/aboutwindow.h \
    src/colorlabel.h \
    src/dialog.h

SOURCES += \
    src/colorlabel.cpp \
    src/dialog.cpp \
    src/main.cpp
