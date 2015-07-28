/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "classifierlistitem.h"

/**
 * This class holds information used by template classes, called
 * paramaterised class in UML and a generic in Java.  It has a
 * type (usually just "class") and name.
 *
 * @short Sets up template information.
 * @author Jonathan Riddell
 * @see UMLObject
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class UMLTemplate : public UMLClassifierListItem
{
public:

    UMLTemplate(UMLObject *parent, const QString& name,
                Uml::ID::Type id = Uml::ID::None, const QString& type = QLatin1String("class"));

    explicit UMLTemplate(UMLObject *parent);

    bool operator==(const UMLTemplate &rhs) const;

    virtual void copyInto(UMLObject *lhs) const;

    virtual UMLObject* clone() const;

    virtual ~UMLTemplate();

    QString toString(Uml::SignatureType::Enum sig = Uml::SignatureType::NoSig);

    virtual QString getTypeName() const;

    virtual bool showPropertiesDialog(QWidget* parent);

    void saveToXMI(QDomDocument & qDoc, QDomElement & qElement);

protected:

    bool load(QDomElement & element);

};

#endif
