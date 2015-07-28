/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003      Brian Thomas <thomas@mail630.gsfc.nasa.gov>   *
 *   copyright (C) 2004-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef CODEPARAMETER_H
#define CODEPARAMETER_H

#include "basictypes.h"
#include "codecomment.h"

class ClassifierCodeDocument;
class UMLObject;

/**
 * class CodeParameter
 * A parameter on some type of code.
 */
class CodeParameter : public QObject
{
    Q_OBJECT
public:

    CodeParameter(ClassifierCodeDocument* doc, UMLObject* parentObj);
    virtual ~CodeParameter();

    ClassifierCodeDocument* getParentDocument();

    UMLObject* getParentObject();

    bool getAbstract();

    bool getStatic();

    QString getName() const;

    virtual QString getTypeName();

    Uml::Visibility::Enum getVisibility() const;

    virtual void setInitialValue(const QString &new_var);
    virtual QString getInitialValue();

    void setComment(CodeComment* comment);
    CodeComment* getComment();

    // the id of this parameter is the same as the parent UMLObject id.
    QString ID();

    virtual void updateContent() = 0;

protected:

    virtual void setAttributesOnNode(QDomDocument& doc, QDomElement& blockElement);
    virtual void setAttributesFromNode(QDomElement& element);

private:

    ClassifierCodeDocument* m_parentDocument;
    UMLObject*              m_parentObject;
    CodeComment*            m_comment;
    QString                 m_initialValue;  ///< initial value of this code parameter

    void initFields(ClassifierCodeDocument* doc, UMLObject* obj);

public slots:

    void syncToParent();

};

#endif // CODEPARAMETER_H
