/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2014                                                    *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#include "umlscenefinder.h"

#include "uml.h"
#include "umldoc.h"
#include "umllistview.h"
#include "umlscene.h"
#include "umlview.h"

UMLSceneFinder::UMLSceneFinder(UMLView *view)
  : UMLFinder(),
    m_id(view->umlScene()->ID())
{
}

UMLSceneFinder::~UMLSceneFinder()
{
}

int UMLSceneFinder::collect(Category category, const QString &text)
{
    Q_UNUSED(category);
    m_items.clear();
    m_index = -1;

    UMLView *view = UMLApp::app()->document()->findView(m_id);
    if (!view)
        return 0;

    UMLScene *scene = view->umlScene();
    foreach(UMLWidget* w, scene->widgetList()) {
        if (!includeObject(category, w->umlObject()))
            continue;
        if (w->name().contains(text, Qt::CaseInsensitive))
            m_items.append(w->id());
    }
    return m_items.size();
}

UMLFinder::Result UMLSceneFinder::displayNext()
{
    if (m_items.size() == 0 || UMLApp::app()->document()->findView(m_id) == 0)
        return Empty;
    if (m_index >= m_items.size()-1) {
        m_index = -1;
        return End;
    }
    return showItem(m_items.at(++m_index)) ? Found : NotFound;
}

UMLFinder::Result UMLSceneFinder::displayPrevious()
{
    if (m_items.size() == 0 || UMLApp::app()->document()->findView(m_id) == 0)
        return Empty;
    if (m_index < 1) {
        m_index = m_items.size();
        return End;
    }
    return showItem(m_items.at(--m_index)) ? Found : NotFound;
}

/**
 * Show item in diagram.
 *
 * @param id ID of uml object to show
 * @return false scene or widget not found, true otherwise
 * @return true widget has been shown
 */
bool UMLSceneFinder::showItem(Uml::ID::Type id)
{
    UMLView *view = UMLApp::app()->document()->findView(m_id);
    if (!view)
        return false;

    UMLScene *scene = view->umlScene();
    if (!scene)
        return false;

    UMLWidget *w = scene->findWidget(id);
    if (!w)
        return false;

    scene->setIsOpen(true);
    view->setZoom(100);
    if (UMLApp::app()->currentView() != view) {
        UMLApp::app()->setCurrentView(view, false);
    }
    view->centerOn(w->pos() + QPointF(w->width(), w->height())/2);
    scene->clearSelection();
    w->setSelected(true);

    // tree view item display is optional
    if (!w->umlObject()) {
        UMLApp::app()->listView()->clearSelection();
        return true;
    }
    UMLListViewItem * item = UMLApp::app()->listView()->findItem(w->umlObject()->id());
    if (!item) {
        UMLApp::app()->listView()->clearSelection();
        return true;
    }
    UMLApp::app()->listView()->setCurrentItem(item);
    return true;
}
