/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef ACTIVITYPAGE_H
#define ACTIVITYPAGE_H

#include "dialogpagebase.h"

//qt includes
#include <QListWidgetItem>
#include <QWidget>

class StateWidget;
class QGroupBox;
class QListWidget;
class QPushButton;
class QToolButton;

/**
 * @author Paul Hensgen
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class ActivityPage : public DialogPageBase
{
    Q_OBJECT
public:

    ActivityPage(QWidget * pParent, StateWidget * pWidget);
    ~ActivityPage();

    void setupPage();

    void updateActivities();

protected:

    void enableWidgets(bool state);

    /**
     *  The widget to get the activities from.
     */
    StateWidget * m_pStateWidget;

    /**
     * GUI widgets
     */
    QListWidget* m_pActivityLW;
    QGroupBox*   m_pActivityGB;
    QToolButton* m_pUpArrowB;
    QToolButton* m_pDownArrowB;
    QToolButton* m_pTopArrowB;
    QToolButton* m_pBottomArrowB;
    QPushButton* m_pDeleteActivityButton;
    QPushButton* m_pRenameButton;

public slots:

    void slotMenuSelection(QAction* action);
    void slotClicked(QListWidgetItem* item);
    void slotDoubleClicked(QListWidgetItem* item);
    void slotRightButtonPressed(const QPoint& p);

    void slotTopClicked();
    void slotUpClicked();
    void slotDownClicked();
    void slotBottomClicked();
    void slotNewActivity();
    void slotDelete();
    void slotRename();
};

#endif
