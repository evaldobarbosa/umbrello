/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef ACTIVITYWIDGET_H
#define ACTIVITYWIDGET_H

#include "umlwidget.h"
#include "worktoolbar.h"

#define ACTIVITY_MARGIN 5
#define ACTIVITY_WIDTH 30
#define ACTIVITY_HEIGHT 10

/**
 * This class is the graphical version of a UML Activity.  A ActivityWidget is created
 * by a @ref UMLView.  An ActivityWidget belongs to only one @ref UMLView instance.
 * When the @ref UMLView instance that this class belongs to, it will be automatically deleted.
 *
 * The ActivityWidget class inherits from the @ref UMLWidget class which adds most of the functionality
 * to this class.
 *
 * @short  A graphical version of a UML Activity.
 * @author Paul Hensgen <phensgen@techie.com>
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class ActivityWidget : public UMLWidget
{
    Q_OBJECT
    Q_ENUMS(ActivityType)
public:
    enum ActivityType
    {
        Initial = 0,
        Normal,
        End,
        Final,
        Branch,
        Invok,
        Param
    };

    explicit ActivityWidget(UMLScene * scene, ActivityType activityType = Normal, Uml::ID::Type id = Uml::ID::None);
    virtual ~ActivityWidget();

    ActivityType activityType() const;
    QString activityTypeStr() const;
    void setActivityType(ActivityType activityType);

    static bool isActivity(WorkToolBar::ToolBar_Buttons tbb,
                            ActivityType& resultType);

    QString preconditionText() const;
    void setPreconditionText(const QString&);

    QString postconditionText() const;
    void setPostconditionText(const QString&);

    virtual void showPropertiesDialog();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    virtual void moveWidgetBy(qreal diffX, qreal diffY);

    virtual bool loadFromXMI(QDomElement & qElement);
    virtual void saveToXMI(QDomDocument & qDoc, QDomElement & qElement);

    void constrain(qreal& width, qreal& height);

signals:
    /**
     * Emitted when the activity widget is moved.
     * Provides the delta X and delta Y amount by which the widget was moved
     * relative to the previous position.
     * Slots into PinWidget::slotActMoved()
     * @param diffX The difference between previous and new X value.
     * @param diffY The difference between previous and new Y value.
     */
    void sigActMoved(qreal diffX, qreal diffY);

public Q_SLOTS:
    virtual void slotMenuSelection(QAction* action);

protected:
    virtual QSizeF minimumSize() const;
    virtual QSizeF maximumSize();

    ActivityType m_activityType; ///< Type of activity.

    QString m_preconditionText;
    QString m_postconditionText;
};

#endif
