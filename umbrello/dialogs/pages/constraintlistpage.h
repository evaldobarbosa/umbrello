/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef CONSTRAINTLISTPAGE_H
#define CONSTRAINTLISTPAGE_H

//app includes
#include "umlclassifierlistitemlist.h"
#include "classifierlistpage.h"

//qt  includes
#include <QWidget>

#if QT_VERSION < 0x050000
class KAction;
class KMenu;
#else
class QAction;
class QMenu;
#endif

/**
 * A dialog page to display entity constraint properties.
 *
 * @short An extension to the classifier list dialog page to display constraint properties.
 * @author Sharan Rao
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class ConstraintListPage : public ClassifierListPage
{
    Q_OBJECT
public:

    ConstraintListPage(QWidget* parent, UMLClassifier* classifier,
                       UMLDoc* doc, UMLObject::ObjectType type);
    virtual ~ConstraintListPage();

private:

#if QT_VERSION >= 0x050000
    QAction* newUniqueConstraintAction;
    QAction* newPrimaryKeyConstraintAction;
    QAction* newForeignKeyConstraintAction;
    QAction* newCheckConstraintAction;
#else
    KAction* newUniqueConstraintAction;
    KAction* newPrimaryKeyConstraintAction;
    KAction* newForeignKeyConstraintAction;
    KAction* newCheckConstraintAction;
#endif
    void setupActions();

private slots:

    void slotNewUniqueConstraint();
    void slotNewPrimaryKeyConstraint();
    void slotNewForeignKeyConstraint();
    void slotNewCheckConstraint();
    virtual UMLClassifierListItemList getItemList();

protected:

    bool greaterThan(UMLObject::ObjectType ct1, UMLObject::ObjectType ct2);

#if QT_VERSION >= 0x050000
    QMenu* buttonMenu;
#else
    KMenu* buttonMenu;
#endif

};

#endif
