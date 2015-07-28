/***************************************************************************
                          codegenerationpolicypage.h  -  description
                             -------------------
    begin                : Tue Jul 29 2003
    copyright            : (C) 2003 by Brian Thomas
    email                : brian.thomas@gsfc.nasa.gov
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2004-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef CODEGENERATIONPOLICYPAGE_H
#define CODEGENERATIONPOLICYPAGE_H

#include "dialogpagebase.h"

class CodeGenPolicyExt;

/**
 * @author Brian Thomas
 */
class CodeGenerationPolicyPage : public DialogPageBase
{
    Q_OBJECT
public:
    explicit CodeGenerationPolicyPage (QWidget *parent=0, const char *name=0, CodeGenPolicyExt * policy = 0);

    virtual ~CodeGenerationPolicyPage();

    void setDefaults();

protected:

    CodeGenPolicyExt * m_parentPolicy;

public slots:

    virtual void apply();


};

#endif

