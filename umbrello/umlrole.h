/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef UMLROLE_H
#define UMLROLE_H

#include "umlobject.h"

class UMLAssociation;

/**
 * This class contains the non-graphic representation of an association role.
 *
 * @author Brian Thomas <brian.thomas@gsfc.nasa.gov>
 * @see UMLObject
 */
class UMLRole : public UMLObject
{
    Q_OBJECT
public:

    UMLRole(UMLAssociation * parent, UMLObject * parentUMLObject, Uml::RoleType::Enum role);
    virtual ~UMLRole();

    bool operator==(const UMLRole & rhs) const;

    void setObject(UMLObject *obj);
    UMLObject* object() const;

    void setChangeability(Uml::Changeability::Enum value);
    Uml::Changeability::Enum changeability() const;

    void setMultiplicity(const QString &multi);
    QString multiplicity() const;

    UMLAssociation * parentAssociation() const;

    Uml::RoleType::Enum role() const;

    UMLObject* clone() const { return NULL; }

    void saveToXMI(QDomDocument& qDoc, QDomElement& qElement);

    virtual bool showPropertiesDialog(QWidget *parent = 0);

protected:

    bool load(QDomElement& element);

private:

    UMLAssociation *           m_pAssoc;
    Uml::RoleType::Enum        m_role;
    QString                    m_Multi;
    Uml::Changeability::Enum   m_Changeability;
};

#endif
