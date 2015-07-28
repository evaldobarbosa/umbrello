/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef UMLAPPPRIVATE_H
#define UMLAPPPRIVATE_H

// app includes
#include "finddialog.h"
#include "findresults.h"
#include "uml.h"

// kde includes
#include <ktexteditor/configinterface.h>
#include <ktexteditor/document.h>
#include <ktexteditor/editor.h>
#if QT_VERSION < 0x050000
#include <ktexteditor/editorchooser.h>
#endif
#include <ktexteditor/view.h>

// qt includes
#include <QFile>
#include <QFileInfo>
#include <QListWidget>
#include <QObject>

class QWidget;

/**
 * Class UMLAppPrivate holds private class members/methods
 * to reduce the size of the public class and to speed up
 * recompiling.
 * The migration to this class is not complete yet.
 **/
class UMLAppPrivate : public QObject
{
    Q_OBJECT
public:
    QWidget *parent;
    FindDialog findDialog;
    FindResults findResults;
    QListWidget *logWindow;         ///< Logging window.

    KTextEditor::Editor *editor;
    KTextEditor::View *view;
    KTextEditor::Document *document;

    explicit UMLAppPrivate(QWidget *_parent)
      : parent(_parent),
        findDialog(_parent),
        view(0),
        document(0)
    {
#if QT_VERSION >= 0x050000
        editor = KTextEditor::Editor::instance();
#else
        editor = KTextEditor::EditorChooser::editor();
#endif
        logWindow = new QListWidget;
        connect(logWindow, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(slotLogWindowItemDoubleClicked(QListWidgetItem *)));
    }

    ~UMLAppPrivate()
    {
        delete logWindow;
    }

public slots:
    void slotLogWindowItemDoubleClicked(QListWidgetItem *item)
    {
        QStringList columns = item->text().split(QChar::fromLatin1(':'));

        QFileInfo file(columns[0]);
        if (!file.exists())
            return;

        document = editor->createDocument(0);
        view = document->createView(parent);
#if QT_VERSION >= 0x050000
        view->document()->openUrl(QUrl(columns[0]));
#else
        view->document()->openUrl(columns[0]);
#endif
        view->document()->setReadWrite(false);
        view->setCursorPosition(KTextEditor::Cursor(columns[1].toInt()-1,columns[2].toInt()));
        KTextEditor::ConfigInterface *iface = qobject_cast<KTextEditor::ConfigInterface*>(view);
        if(iface)
            iface->setConfigValue(QString::fromLatin1("line-numbers"), true);

        SinglePageDialogBase *dialog = new SinglePageDialogBase(parent);
        dialog->setMainWidget(view);
        dialog->setMinimumSize(800, 800);
        dialog->exec();
        delete dialog;
        delete document;
    }
};

#endif
