/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2004-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef CLASSIFIERWIDGET_H
#define CLASSIFIERWIDGET_H

#include "basictypes.h"
#include "umlobject.h"
#include "umlwidget.h"

class AssociationWidget;
class FloatingTextWidget;
class QPainter;
class UMLClassifier;

/**
 * @short Common implementation for class widget and interface widget
 *
 * @author Oliver Kellogg
 * @author Gopala Krishna
 *
 * @see UMLWidget
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class ClassifierWidget : public UMLWidget
{
    Q_OBJECT
    Q_ENUMS(VisualProperty)
public:
    /**
     * This enumeration lists the visual properties that can be easily
     * set, reset and toggled and all these operate on an integer
     * which stores all the flag status.
     */
    enum VisualProperty {
        ShowStereotype         = 0x1,
        ShowOperations         = 0x2,
        ShowPublicOnly         = 0x4,
        ShowVisibility         = 0x8,
        ShowPackage            = 0x10,
        ShowAttributes         = 0x20,
        DrawAsCircle           = 0x40,
        ShowOperationSignature = 0x60,  ///< only in setter
        ShowAttributeSignature = 0x80,   ///< only in setter
        DrawAsPackage          = 0x100,
        ShowDocumentation      = 0x200,
    };

    Q_DECLARE_FLAGS(VisualProperties, VisualProperty)

    ClassifierWidget(UMLScene * scene, UMLClassifier * o);
    ClassifierWidget(UMLScene * scene, UMLPackage * o);
    virtual ~ClassifierWidget();

    UMLClassifier *classifier() const;

    VisualProperties visualProperties() const;
    void setVisualProperties(VisualProperties properties);

    bool visualProperty(VisualProperty property) const;
    void setVisualProperty(VisualProperty property, bool enable = true);
    void setVisualPropertyCmd(VisualProperty property, bool enable = true);
    void toggleVisualProperty(VisualProperty property);

    int displayedAttributes() const;
    int displayedOperations() const;

    Uml::SignatureType::Enum attributeSignature() const;
    void setAttributeSignature(Uml::SignatureType::Enum sig);

    Uml::SignatureType::Enum operationSignature() const;
    void setOperationSignature(Uml::SignatureType::Enum sig);

    void setShowAttSigs(bool _show);
    void toggleShowAttSigs();

    bool getDrawAsCircle() const;
    void setDrawAsCircle(bool drawAsCircle);
    void toggleDrawAsCircle();

    void changeToClass();
    void changeToInterface();
    void changeToPackage();

    AssociationWidget *classAssociationWidget() const;
    void setClassAssociationWidget(AssociationWidget *assocwidget);
//    virtual void adjustAssociations(int x, int y);
 
    UMLWidget* onWidget(const QPointF& p);
    UMLWidget* widgetWithID(Uml::ID::Type id);

    virtual void setDocumentation(const QString& doc);

    QSizeF calculateSize(bool withExtensions = true) const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    virtual QPainterPath shape() const;

    virtual void saveToXMI(QDomDocument & qDoc, QDomElement & qElement);
    virtual bool loadFromXMI(QDomElement & qElement);

public Q_SLOTS:
    virtual void slotMenuSelection(QAction* action);

private Q_SLOTS:
    void slotShowAttributes(bool state);
    void slotShowOperations(bool state);

private:
    void updateSignatureTypes();
    QSize calculateTemplatesBoxSize() const;

    QSizeF minimumSize() const;

    void drawAsCircle(QPainter *p, const QStyleOptionGraphicsItem *option);
    QSize calculateAsCircleSize() const;

    void drawAsPackage(QPainter *painter, const QStyleOptionGraphicsItem *option);
    QSize calculateAsPackageSize() const;

    int displayedMembers(UMLObject::ObjectType ot) const;
    void drawMembers(QPainter *painter, UMLObject::ObjectType ot, Uml::SignatureType::Enum sigType,
                     int x, int y, int fontHeight);

    static const int MARGIN;           ///< text width margin
    static const int CIRCLE_SIZE;      ///< size of circle when interface is rendered as such
    static const int SOCKET_INCREMENT; ///< augmentation of circle for socket (required interface)

    VisualProperties   m_visualProperties;
    Uml::SignatureType::Enum m_attributeSignature;   ///< Loaded/saved item.
    Uml::SignatureType::Enum m_operationSignature;   ///< Loaded/saved item.
    AssociationWidget *m_pAssocWidget; ///< related AssociationWidget in case this classifier acts as an association class
    FloatingTextWidget *m_pInterfaceName;  ///< Separate widget for name in case of interface drawn as circle

};

Q_DECLARE_OPERATORS_FOR_FLAGS(ClassifierWidget::VisualProperties)

#endif
