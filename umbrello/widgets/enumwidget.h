/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef ENUMWIDGET_H
#define ENUMWIDGET_H

#include "umlwidget.h"

#define ENUM_MARGIN 5

/**
 * Defines a graphical version of the enum.  Most of the functionality
 * will come from the @ref UMLWidget class from which class inherits from.
 *
 * @short A graphical version of an enum.
 * @author Jonathan Riddell
 * @see UMLWidget
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class EnumWidget : public UMLWidget
{
    Q_OBJECT
public:
    explicit EnumWidget(UMLScene *scene, UMLObject* o);
    virtual ~EnumWidget();

    bool showPackage() const;
    void setShowPackage(bool _status);
    void toggleShowPackage();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    virtual bool loadFromXMI(QDomElement& qElement);
    virtual void saveToXMI(QDomDocument& qDoc, QDomElement& qElement);

public Q_SLOTS:
    virtual void slotMenuSelection(QAction* action);

protected:
    QSizeF minimumSize() const;

    bool m_showPackage;
};

#endif
