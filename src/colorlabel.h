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

#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QLabel>
#include <QWidget>

class ColorLabel : public QLabel
{
    Q_OBJECT

public:
    ColorLabel(QString text = "" , QColor chosenColor = Qt::black);
    void mousePressEvent(QMouseEvent *);
    void setColor(QColor color);
    QColor Color;


signals:
    void clicked();

};

#endif // COLORLABEL_H
