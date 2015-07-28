/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2014                                                    *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include "ui_finddialog.h"

#include "singlepagedialogbase.h"
#include "umlfinder.h"

/**
  * Class FindDialog provides the ui part for selecting find attributes.
  *
  * @author: Ralf Habacker <ralf.habacker@freenet.de>
  */
class FindDialog : public SinglePageDialogBase, private Ui::FindDialog
{
    Q_OBJECT
public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();
    QString text();
    UMLFinder::Filter filter();
    UMLFinder::Category category();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void slotFilterButtonClicked(int button);
};

#endif // FINDDIALOG_H
