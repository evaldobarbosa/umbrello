/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef CLASSIFIERLISTITEM_H
#define CLASSIFIERLISTITEM_H

#include "umlobject.h"

// forward declaration
class UMLClassifier;

/**
 * Classifiers (classes, interfaces) have lists of operations,
 * attributes, templates and others.  This is a base class for
 * the items in this list.  This abstraction should remove
 * duplication of dialogs and allow for stereotypes in lists.
 *
 * @short A base class for classifier list items (e.g. attributes)
 * @author Jonathan Riddell
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class UMLClassifierListItem : public UMLObject
{
    Q_OBJECT
public:

    UMLClassifierListItem(UMLObject *parent,
                          const QString& name,
                          Uml::ID::Type id = Uml::ID::None);
    explicit UMLClassifierListItem(UMLObject *parent);
    virtual ~UMLClassifierListItem();

    virtual void setType(UMLObject *type);
    UMLClassifier * getType() const;

    void setTypeName(const QString &type);
    virtual QString getTypeName() const;

    virtual QString toString(Uml::SignatureType::Enum sig = Uml::SignatureType::NoSig);

    virtual void copyInto(UMLObject *lhs) const;

    /**
     * The abstract method UMLObject::clone() must be implemented
     * by the classes inheriting from UMLClassifierListItem.
     */
    virtual UMLObject* clone() const = 0;

};

#endif
