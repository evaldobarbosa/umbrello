/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2012-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef LAYOUTGENERATOR_H

#include "dotgenerator.h"
#include "optionstate.h"

//// qt includes
#include <QRectF>

/**
 * The class LayoutGenerator provides calculated layouts of diagrams.
 *
 * It uses the dot executable from the graphviz package for calculation
 * of widget positions.
 *
 * The implementation calls dot with information from the displayed
 * widgets and associations by creating a temporary dot file based on a
 * layout configure file, which is located in the umbrello/layouts subdir of
 * the "data" resource type. The config file is determined from the
 * type of the currently displayed diagram and the layout chosen by the user.
 *
 * Dot creates a file containing the calculated widget positions.
 * The widget positions are retrieved from this file and used to move
 * widgets on the provided diagram. Additional points in association lines
 * are removed.
 *
 * @author Ralf Habacker <ralf.habacker@freenet.de>
 */
class LayoutGenerator : public DotGenerator
{
public:
    typedef QHash<QString,QRectF> NodeType;
    typedef QList<QPointF> EdgePoints;
    typedef QHash<QString,EdgePoints> EdgeType;
    typedef QMap<QString,QStringList> ParameterList;

    LayoutGenerator();

    bool isEnabled();
    static QString currentDotPath();
    bool generate(UMLScene *scene, const QString &variant = QString());
    bool apply(UMLScene *scene);
    static bool availableConfigFiles(UMLScene *scene, QHash<QString,QString> &configFiles);
    QPoint origin(const QString &id);
    bool readGeneratedDotFile(const QString &fileName);
    bool parseLine(const QString &line);
    bool splitParameters(QMap<QString,QStringList> &map, const QString &s);
    QPointF mapToScene(const QPointF &p);

protected:
    QRectF m_boundingRect;
    NodeType m_nodes;      ///< list of nodes found in parsed dot file
    EdgeType m_edges;      ///< list of edges found in parsed dot file
    QHash<QString, QPointF> m_edgeLabelPosition; ///< contains global node parameters
    QString m_dotPath;     ///< contains path to dot executable

    friend QDebug operator<<(QDebug out, LayoutGenerator &c);
};

#if 0
static QDebug operator<<(QDebug out, LayoutGenerator &c);
#endif

#endif
