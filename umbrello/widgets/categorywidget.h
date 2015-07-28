/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef CATEGORYWIDGET_H
#define CATEGORYWIDGET_H

#include "umlwidget.h"

#define UC_MARGIN 5
#define UC_RADIUS 30

class UMLCategory;

/**
 * This class is the graphical version of a UMLCategory.  A CategoryWidget is created
 * by a @ref UMLView.  An CategoryWidget belongs to only one @ref UMLView instance.
 * When the @ref UMLView instance that this class belongs to, it will be automatically deleted.
 *
 * If the Category class that this CategoryWidget is displaying is deleted, the @ref UMLView will
 * make sure that this instance is also deleted.
 *
 * The CategoryWidget class inherits from the @ref UMLWidget class which adds most of the functionality
 * to this class.
 *
 * @short  A graphical version of a UMLCategory.
 * @author Sharan Rao
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class CategoryWidget : public UMLWidget
{
    Q_OBJECT
public:
    CategoryWidget(UMLScene * scene, UMLCategory *o);
    virtual ~CategoryWidget();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void saveToXMI(QDomDocument & qDoc, QDomElement & qElement);
    // For loading we can use the loadFromXMI() inherited from UMLWidget.

protected:
    QSizeF minimumSize() const;

public slots:
    void slotMenuSelection(QAction* action);

};

#endif
