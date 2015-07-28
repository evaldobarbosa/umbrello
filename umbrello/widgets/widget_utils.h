/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2004-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef WIDGET_UTILS_H
#define WIDGET_UTILS_H

#include "basictypes.h"
#include "messagewidgetlist.h"
#include "umlwidgetlist.h"

#include <QBrush>
#include <QDomDocument>
#include <QPointF>
#include <QLineF>
#include <QPolygonF>

class QGraphicsItem;
class QGraphicsRectItem;

/**
 * General purpose widget utilities.
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
namespace Widget_Utils
{
    UMLWidget* findWidget(Uml::ID::Type id,
                          const UMLWidgetList& widgets,
                          const MessageWidgetList* messages = 0);

    QGraphicsRectItem* decoratePoint(const QPointF& p, QGraphicsItem* parent = 0);

    void drawCrossInEllipse(QPainter *p, const QRectF& ellipse);
    void drawTriangledRect(QPainter *painter, const QRectF& rect, const QSizeF& triSize);
//    void drawArrowHead(QPainter *painter, const QPointF& arrowPos,
//                       const QSizeF& arrowSize, Qt::ArrowType arrowType,
//                       bool solid = false);
//    void drawRoundedRect(QPainter *painter, const QRectF& rect, qreal xRadius,
//            qreal yRadius, Uml::Corners corners);

    QString pointToString(const QPointF& point);
    QPointF stringToPoint(const QString& str);

    bool loadPixmapFromXMI(QDomElement &qElement, QPixmap &pixmap);
    void savePixmapToXMI(QDomDocument &qDoc, QDomElement &qElement, const QPixmap& pixmap);

    bool loadGradientFromXMI(QDomElement &qElement, QGradient *&gradient);
    void saveGradientToXMI(QDomDocument &qDoc, QDomElement &qElement, const QGradient *gradient);

    bool loadBrushFromXMI(QDomElement &qElement, QBrush &brush);
    void saveBrushToXMI(QDomDocument &qDoc, QDomElement &qElement,
                        const QBrush& brush);

    bool hasSmallerX(const UMLWidget* widget1, const UMLWidget* widget2);
    bool hasSmallerY(const UMLWidget* widget1, const UMLWidget* widget2);

    QLineF closestPoints(const QPolygonF& self, const QPolygonF& other);
}

#endif
