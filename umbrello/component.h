/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef COMPONENT_H
#define COMPONENT_H

#include "package.h"

/**
 * This class contains the non-graphical information required for a
 * UML Component.
 * This class inherits from @ref UMLPackage which contains most
 * of the information.
 *
 * @short Non-graphical information for a Component.
 * @author Jonathan Riddell
 * @see UMLCanvasObject
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class UMLComponent : public UMLPackage
{
    Q_OBJECT
public:
    explicit UMLComponent(const QString & name = QString(), Uml::ID::Type id = Uml::ID::None);
    virtual ~UMLComponent();

    virtual UMLObject* clone() const;

    void saveToXMI(QDomDocument & qDoc, QDomElement & qElement);

    void setExecutable(bool executable);
    bool getExecutable();

protected:
    bool load(QDomElement & element);

private:
    bool m_executable;  ///< holds whether this is an executable component or not
};

#endif
