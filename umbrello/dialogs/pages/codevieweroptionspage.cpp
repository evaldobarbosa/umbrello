/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002                                                    *
 *   Luis De la Parra <luis@delaparra.org>                                 *
 *   copyright (C) 2003-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

// own header
#include "codevieweroptionspage.h"

// qt/kde includes
#include <kcolorbutton.h>


CodeViewerOptionsPage::CodeViewerOptionsPage(Settings::CodeViewerState options, QWidget *parent, const char *name)
  : DialogPageBase(parent),
    m_options(options)
{
    setObjectName(QLatin1String(name));
    setupUi(this);

    // set widget stuff
    /*
        fontChooser->setFont(options.font);
        selectColorButton->setColor (options.selectedColor);
        fontColorButton->setColor (options.fontColor);
        paperColorButton->setColor (options.paperColor);
        editBlockColorButton->setColor (options.editBlockColor);
        nonEditBlockColorButton->setColor (options.nonEditBlockColor);
        umlObjectColorButton->setColor (options.umlObjectColor);
     */
}

CodeViewerOptionsPage::~CodeViewerOptionsPage()
{
}

void CodeViewerOptionsPage::apply()
{
    /*
        m_options.umlObjectColor = umlObjectColorButton->color();
        m_options.editBlockColor = editBlockColorButton->color();
        m_options.nonEditBlockColor = nonEditBlockColorButton->color();
        m_options.selectedColor = selectColorButton->color();
        m_options.paperColor = paperColorButton->color();
        m_options.fontColor = fontColorButton->color();
        m_options.font = fontChooser->font();
     */
    emit applyClicked();
}

Settings::CodeViewerState CodeViewerOptionsPage::getOptions()
{
    return m_options;
}

