/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef COMBINEDFRAGMENTWIDGET_H
#define COMBINEDFRAGMENTWIDGET_H

#include "umlwidget.h"
#include "worktoolbar.h"
#include "floatingdashlinewidget.h"

#include <QList>

#define COMBINED_FRAGMENT_MARGIN 5
#define COMBINED_FRAGMENT_WIDTH 100
#define COMBINED_FRAGMENT_HEIGHT 50

/**
 * This class is the graphical version of a UML combined fragment.  A combinedfragmentWidget is created
 * by a @ref UMLView.  An combinedfragmentWidget belongs to only one @ref UMLView instance.
 * When the @ref UMLView instance that this class belongs to, it will be automatically deleted.
 *
 * The combinedfragmentWidget class inherits from the @ref UMLWidget class which adds most of the functionality
 * to this class.
 *
 * @short  A graphical version of a UML combined fragment.
 * @author Hassan KOUCH <hkouch@hotmail.com>
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class CombinedFragmentWidget : public UMLWidget
{
    Q_OBJECT

public:
    enum CombinedFragmentType
    {
        Ref = 0,
        Opt,
        Break,
        Loop,
        Neg,
        Crit,
        Ass,
        Alt,
        Par
    };

    explicit CombinedFragmentWidget(UMLScene * scene,
                                    CombinedFragmentType combinedfragmentType = Ref,
                                    Uml::ID::Type id = Uml::ID::None);
    virtual ~CombinedFragmentWidget();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    CombinedFragmentType combinedFragmentType() const;
    CombinedFragmentType combinedFragmentType(const QString& combinedfragmentType) const;
    void setCombinedFragmentType(CombinedFragmentType combinedfragmentType);
    void setCombinedFragmentType(const QString& combinedfragmentType);

    void askNameForWidgetType(UMLWidget* &targetWidget, const QString& dialogTitle,
                      const QString& dialogPrompt, const QString& defaultName);

    void saveToXMI(QDomDocument & qDoc, QDomElement & qElement);
    bool loadFromXMI(QDomElement & qElement);
    void removeDashLine(FloatingDashLineWidget *line);

    virtual void cleanup();

public slots:
    void slotMenuSelection(QAction* action);


protected:
    QSizeF minimumSize() const;

    /// Type of CombinedFragment.
    CombinedFragmentType m_CombinedFragment;

private:
    /// Dash lines of an alternative or parallel combined fragment
    QList<FloatingDashLineWidget*> m_dashLines ;

};

#endif
