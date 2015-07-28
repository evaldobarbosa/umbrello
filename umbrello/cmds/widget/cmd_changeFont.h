/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef CMD_CHANGEFONT_H
#define CMD_CHANGEFONT_H

#include "cmd_baseWidgetCommand.h"

#include <QFont>

class UMLWidget;

namespace Uml
{
    class CmdChangeFont : public CmdBaseWidgetCommand
    {
        public:
            CmdChangeFont(UMLWidget* widget, QFont font);

            void undo();
            void redo();

        private:
            QFont         m_newFont;
            QFont         m_oldFont;
    };
}

#endif // CMD_CHANGEFONT_H
