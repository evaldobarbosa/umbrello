/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003      Brian Thomas <thomas@mail630.gsfc.nasa.gov>   *
 *   copyright (C) 2004-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#include "cppcodegenerator.h"

#include <QRegExp>

const char * CPPMakefileCodeDocument::DOCUMENT_ID_VALUE = "Makefile_DOC";

CPPMakefileCodeDocument::CPPMakefileCodeDocument ()
{
    setFileName(QLatin1String("Makefile")); // default name
    setFileExtension(QString());
    setID(QLatin1String(DOCUMENT_ID_VALUE)); // default id tag for this type of document
}

CPPMakefileCodeDocument::~CPPMakefileCodeDocument ()
{
}

// we add in our code blocks that describe how to generate
// the project here...
void CPPMakefileCodeDocument::updateContent()
{
    // FIX : fill in content
}

/**
 * @return      QString
 */
QString CPPMakefileCodeDocument::toString ()
{
    return QLatin1String("# cpp make build document");
}

// We overwritten by CPP language implementation to get lowercase path
QString CPPMakefileCodeDocument::getPath ()
{
    QString path = getPackage();

    // Replace all white spaces with blanks
    path.simplified();

    // Replace all blanks with underscore
    path.replace(QRegExp(QLatin1String(" ")), QLatin1String("_"));

    path.replace(QRegExp(QLatin1String("\\.")),QLatin1String("/"));
    path.replace(QRegExp(QLatin1String("::")), QLatin1String("/"));

    path = path.toLower();

    return path;
}
