/* This file is part of KDevelop
    Copyright (C) 2002, 2003 Roberto Raggi <roberto@kdevelop.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#include "errors.h"
#include <KLocalizedString>

Error& Errors::_InternalError()
{
    static Error *error = 0;
    if (error == 0)
        error = new Error(1, -1, i18n("Internal Error"));
    return *error;
}

Error &Errors::_SyntaxError()
{
    static Error *error = 0;
    if (error == 0)
        error = new Error(2, -1, i18n("Syntax Error before '%1'"));
    return *error;
}

Error &Errors::_ParseError()
{
    static Error *error = 0;
    if (error == 0)
        error = new Error(3, -1, i18n("Parse Error before '%1'"));
    return *error;
}
