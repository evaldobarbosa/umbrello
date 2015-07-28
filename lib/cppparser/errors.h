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

#ifndef ERRORS_H
#define ERRORS_H

#include <QString>


struct Error {
    int code;
    int level;
    QString text;

    Error(int c, int l, const QString& s)
        : code(c), level(l), text(s)
    {}
};

class Errors
{
public:
    static Error& _InternalError();
    static Error& _SyntaxError();
    static Error& _ParseError();
};

#define InternalError _InternalError()
#define SyntaxError _SyntaxError()
#define ParseError _ParseError()


#endif
