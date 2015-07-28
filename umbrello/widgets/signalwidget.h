/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
***************************************************************************/

#ifndef SIGNALWIDGET_H
#define SIGNALWIDGET_H

#include "floatingtextwidget.h"
#include "linkwidget.h"
#include "umlwidget.h"
#include "worktoolbar.h"

#define SIGNAL_MARGIN 5
#define SIGNAL_WIDTH 45
#define SIGNAL_HEIGHT 15

/**
 * Represents a Send signal, Accept signal or Time event on an
 * Activity diagram.
 */
class SignalWidget : public UMLWidget
{
    Q_OBJECT
    Q_ENUMS(SignalType)
public:
    /// Enumeration that codes the different types of signal.
    enum SignalType
    {
        Send = 0,
        Accept,
        Time
    };

    explicit SignalWidget(UMLScene * scene, SignalType signalType = Send, Uml::ID::Type id = Uml::ID::None);
    virtual ~SignalWidget();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void setX(qreal newX);
    void setY(qreal newY);

    virtual void setName(const QString &strName);

    SignalType signalType() const;
    QString signalTypeStr() const;
    void setSignalType(SignalType signalType);

    virtual void  showPropertiesDialog();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *me);

    virtual bool loadFromXMI(QDomElement & qElement);
    virtual void saveToXMI(QDomDocument & qDoc, QDomElement & qElement);

public Q_SLOTS:
    virtual void slotMenuSelection(QAction* action);

protected:
    QSizeF minimumSize() const;

    /**
     * Save the value of the widget to know how to move the floatingtext
     */
    int m_oldX;
    int m_oldY;

    // Only for the time event
    /**
     * This is a pointer to the Floating Text widget which displays the
     * name of the signal widget.
     */
    FloatingTextWidget* m_pName;

    SignalType m_signalType; ///< Type of signal

protected Q_SLOTS:
    void slotTextDestroyed();
};

#endif
