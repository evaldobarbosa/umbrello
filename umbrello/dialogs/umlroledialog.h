/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/


#ifndef UMLROLEDIALOG_H
#define UMLROLEDIALOG_H

//kde includes
#include "singlepagedialogbase.h"

/**
 * @author Paul Hensgen
 */
class UMLRole;
class UMLRoleProperties;

class UMLRoleDialog : public SinglePageDialogBase
{
    Q_OBJECT
public:

    /**
     *   Constructor
     */
    UMLRoleDialog(QWidget * parent, UMLRole * pRole);

    /**
     *   Deconstructor
     */
    ~UMLRoleDialog();

protected:

    void setupDialog();

    bool apply();

    /**
     * The role to represent.
     */
    UMLRole * m_pRole;

private:

    UMLRoleProperties * m_pRoleProps;

public slots:
};

#endif
