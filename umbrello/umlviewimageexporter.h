/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2006-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef UMLVIEWIMAGEEXPORTER_H
#define UMLVIEWIMAGEEXPORTER_H

#include "umlviewimageexportermodel.h"

#if QT_VERSION < 0x050000
#include <kurl.h>
#endif

#include <QString>
#if QT_VERSION >= 0x050000
#include <QUrl>
#endif

class UMLScene;
class UMLFileDialog;

/**
 * Exports the scene as an image.
 * This class takes care of asking the user the needed parameters and
 * then exports the scene.
 */
class UMLViewImageExporter
{
public:

    explicit UMLViewImageExporter(UMLScene* scene);
    virtual ~UMLViewImageExporter();

    void exportView();
#if QT_VERSION >= 0x050000
    QUrl    getImageURL() const { return m_imageURL; }
#else
    KUrl    getImageURL() const { return m_imageURL; }
#endif
    QString getImageMimeType() const { return m_imageMimeType; }

private:

    UMLScene* m_scene;          ///< The scene to export.
#if QT_VERSION >= 0x050000
    QUrl      m_imageURL;       ///< The URL used to save the image.
#else
    KUrl      m_imageURL;       ///< The URL used to save the image.
#endif
    QString   m_imageMimeType;  ///< The mime type used to save the image.

    bool getParametersFromUser();

    bool prepareExport();
    void prepareFileDialog(UMLFileDialog *fileDialog);

};

#endif
