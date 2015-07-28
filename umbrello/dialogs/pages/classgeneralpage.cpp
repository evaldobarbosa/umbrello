/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

// my own header
#include "classgeneralpage.h"

// app includes
#include "debug_utils.h"
#include "documentationwidget.h"
#include "dialog_utils.h"
#include "classifier.h"
#include "umlobject.h"
#include "objectwidget.h"
#include "uml.h"
#include "umldoc.h"
#include "artifact.h"
#include "component.h"
#include "umlview.h"
#include "stereotype.h"
#include "umlpackagelist.h"
#include "model_utils.h"
#include "package.h"
#include "folder.h"
#include "import_utils.h"
#include "umlscene.h"
#include "umlobjectnamewidget.h"
#include "umlpackagewidget.h"
#include "umlstereotypewidget.h"
#include "umlartifacttypewidget.h"
#include "visibilityenumwidget.h"

// kde includes
#include <KLocalizedString>
#include <KMessageBox>
#include <kcombobox.h>
#include <klineedit.h>
#include <ktextedit.h>

// qt includes
#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>

ClassGeneralPage::ClassGeneralPage(UMLDoc* d, QWidget* parent, UMLObject* o)
  : DialogPageBase(parent),
    m_pObject(o),
    m_pWidget(0),
    m_pInstanceWidget(0),
    m_pUmldoc(d),
    m_pInstanceL(0),
    m_pStereoTypeL(0),
    m_pMultiCB(0),
    m_pDrawActorCB(0),
    m_pAbstractCB(0),
    m_pDeconCB(0),
    m_pExecutableCB(0),
    m_docWidget(0),
    m_nameWidget(0),
    m_instanceNameWidget(0),
    m_stereotypeWidget(0),
    m_packageWidget(0),
    m_artifactTypeWidget(0),
    m_visibilityEnumWidget(0)
{
    if (!m_pObject) {
        uWarning() << "Given UMLObject is NULL.";
        return;
    }

    setMinimumSize(310, 330);
    QVBoxLayout * topLayout = new QVBoxLayout(this);
    topLayout->setSpacing(6);

    // setup name
    UMLObject::ObjectType t = m_pObject->baseType();
    QString name = UMLObject::toI18nString(t);
    QGridLayout * m_pNameLayout = new QGridLayout();
    m_pNameLayout->setSpacing(6);
    topLayout->addLayout(m_pNameLayout, 4);

    m_nameWidget = new UMLObjectNameWidget(name, m_pObject->name());
    m_nameWidget->addToLayout(m_pNameLayout, 0);

    if (t != UMLObject::ot_Stereotype) {
        m_stereotypeWidget = new UMLStereotypeWidget(m_pObject);
        if (t == UMLObject::ot_Interface || t == UMLObject::ot_Datatype || t == UMLObject::ot_Enum) {
            m_stereotypeWidget->setEditable(false);
        }
        m_stereotypeWidget->addToLayout(m_pNameLayout, 1);
    }

    int row = 2;
    UMLClassifier *c = static_cast<UMLClassifier*>(m_pObject);
    if (c->isReference() && c->originType()) {
        QLabel *label = new QLabel(i18n("Reference:"), this);
        m_pNameLayout->addWidget(label, row, 0);
        QLabel *reference = new QLabel(c->originType()->name(), this);
        m_pNameLayout->addWidget(reference, row, 1);
        ++row;
    }

    if (t == UMLObject::ot_Class || t == UMLObject::ot_Interface) {
        m_packageWidget = new UMLPackageWidget(m_pObject);
        m_packageWidget->addToLayout(m_pNameLayout, row);
        ++row;
    }

    if (t == UMLObject::ot_Class || t == UMLObject::ot_UseCase) {
        QString abstractCaption;
        if (t == UMLObject::ot_Class) {
            abstractCaption = i18n("A&bstract class");
        } else {
            abstractCaption = i18n("A&bstract use case");
        }
        m_pAbstractCB = new QCheckBox(abstractCaption, this);
        m_pAbstractCB->setChecked(m_pObject->isAbstract());
        m_pNameLayout->addWidget(m_pAbstractCB, row, 0);
        ++row;
    }

    if (t == UMLObject::ot_Component) {
        m_pExecutableCB = new QCheckBox(i18nc("component is executable", "&Executable"), this);
        m_pExecutableCB->setChecked((static_cast<UMLComponent*>(o))->getExecutable());
        m_pNameLayout->addWidget(m_pExecutableCB, row, 0);
        ++row;
    }

    if (t == UMLObject::ot_Artifact) {
        m_artifactTypeWidget = new UMLArtifactTypeWidget(static_cast<UMLArtifact*>(o));
        m_artifactTypeWidget->addToLayout(topLayout);
    }

    // setup scope
    if (t != UMLObject::ot_Stereotype) {
        m_visibilityEnumWidget = new VisibilityEnumWidget(m_pObject, this);
        m_visibilityEnumWidget->addToLayout(topLayout);
    }

    m_docWidget = new DocumentationWidget(m_pObject, this);
    topLayout->addWidget(m_docWidget);
}

ClassGeneralPage::ClassGeneralPage(UMLDoc* d, QWidget* parent, ObjectWidget* o)
  : DialogPageBase(parent),
    m_pObject(0),
    m_pWidget(o),
    m_pInstanceWidget(0),
    m_pUmldoc(d),
    m_pInstanceL(0),
    m_pStereoTypeL(0),
    m_pMultiCB(0),
    m_pDrawActorCB(0),
    m_pAbstractCB(0),
    m_pDeconCB(0),
    m_pExecutableCB(0),
    m_docWidget(0),
    m_nameWidget(0),
    m_instanceNameWidget(0),
    m_stereotypeWidget(0),
    m_packageWidget(0),
    m_artifactTypeWidget(0),
    m_visibilityEnumWidget(0)
{
    if (!m_pWidget) {
        uWarning() << "Given ObjectWidget is NULL.";
        return;
    }

    setMinimumSize(310, 330);
    QVBoxLayout * topLayout = new QVBoxLayout(this);
    topLayout->setSpacing(6);

    // setup name
    QGridLayout * m_pNameLayout = new QGridLayout();
    m_pNameLayout->setSpacing(6);
    topLayout->addLayout(m_pNameLayout, 4);

    m_nameWidget = new UMLObjectNameWidget(i18n("Class name:"), m_pWidget->name());
    m_nameWidget->addToLayout(m_pNameLayout, 0);

    m_instanceNameWidget = new UMLObjectNameWidget(i18n("Instance name:"), m_pWidget->instanceName());
    m_instanceNameWidget->addToLayout(m_pNameLayout, 1);

    UMLView *view = UMLApp::app()->currentView();

    m_pDrawActorCB = new QCheckBox(i18n("Draw as actor"), this);
    m_pDrawActorCB->setChecked(m_pWidget->drawAsActor());
    m_pNameLayout->addWidget(m_pDrawActorCB, 2, 0);

    if (view->umlScene()->type() == Uml::DiagramType::Collaboration) {
        m_pMultiCB = new QCheckBox(i18n("Multiple instance"), this);
        m_pMultiCB->setChecked(m_pWidget->multipleInstance());
        m_pNameLayout->addWidget(m_pMultiCB, 2, 1);
        if (m_pDrawActorCB->isChecked())
            m_pMultiCB->setEnabled(false);
    } else {  // sequence diagram
        m_pDeconCB = new QCheckBox(i18n("Show destruction"), this);
        m_pDeconCB->setChecked(m_pWidget->showDestruction());
        m_pNameLayout->addWidget(m_pDeconCB, 2, 1);
    }
    m_docWidget = new DocumentationWidget(m_pWidget, this);
    topLayout->addWidget(m_docWidget);

    if (m_pMultiCB) {
        connect(m_pDrawActorCB, SIGNAL(toggled(bool)), this, SLOT(slotActorToggled(bool)));
    }
}

ClassGeneralPage::ClassGeneralPage(UMLDoc* d, QWidget* parent, UMLWidget* widget)
  : DialogPageBase(parent),
    m_pObject(0),
    m_pWidget(0),
    m_pInstanceWidget(widget),
    m_pUmldoc(d),
    m_pInstanceL(0),
    m_pStereoTypeL(0),
    m_pMultiCB(0),
    m_pDrawActorCB(0),
    m_pAbstractCB(0),
    m_pDeconCB(0),
    m_pExecutableCB(0),
    m_docWidget(0),
    m_nameWidget(0),
    m_instanceNameWidget(0),
    m_stereotypeWidget(0),
    m_packageWidget(0),
    m_artifactTypeWidget(0),
    m_visibilityEnumWidget(0)
{
    setMinimumSize(310, 330);
    QVBoxLayout * topLayout = new QVBoxLayout(this);
    topLayout->setSpacing(6);

    // setup name
    QGridLayout * m_pNameLayout = new QGridLayout();
    m_pNameLayout->setSpacing(6);
    topLayout->addLayout(m_pNameLayout, 4);

    QString typeName = UMLWidget::toI18nString(widget->baseType());
    m_nameWidget = new UMLObjectNameWidget(typeName, widget->name());
    m_nameWidget->addToLayout(m_pNameLayout, 0);

    if (widget->umlObject()) {
        m_stereotypeWidget = new UMLStereotypeWidget(widget->umlObject());
        m_stereotypeWidget->addToLayout(m_pNameLayout, 1);
    }

    m_instanceNameWidget = new UMLObjectNameWidget(i18n("Instance name:"), widget->instanceName());
    m_instanceNameWidget->addToLayout(m_pNameLayout, 2);

    m_docWidget = new DocumentationWidget(widget, this);
    topLayout->addWidget(m_docWidget);
}

ClassGeneralPage::~ClassGeneralPage()
{
}

/**
 * Will move information from the dialog into the object.
 * Call when the ok or apply button is pressed.
 */
void ClassGeneralPage::apply()
{
    QString name = m_nameWidget->text();
    m_docWidget->apply();

    if (m_pObject) {

        if (m_stereotypeWidget) {
            m_stereotypeWidget->apply();
        }

        UMLObject::ObjectType t = m_pObject->baseType();
        if (t == UMLObject::ot_Class || t == UMLObject::ot_Interface) {
            m_packageWidget->apply();
        }

        if (m_pAbstractCB) {
            m_pObject->setAbstract(m_pAbstractCB->isChecked());
        }

        //make sure unique name
        UMLObject *o = m_pUmldoc->findUMLObject(name);
        if (o && m_pObject != o) {
             KMessageBox::sorry(this, i18n("The name you have chosen\nis already being used.\nThe name has been reset."),
                                i18n("Name is Not Unique"), 0);
             m_nameWidget->reset();
        } else {
             m_pObject->setName(name);
        }

        if (t != UMLObject::ot_Stereotype) {
            if (m_visibilityEnumWidget)
                m_visibilityEnumWidget->apply();
        }

        if (m_pObject->baseType() == UMLObject::ot_Component) {
            (static_cast<UMLComponent*>(m_pObject))->setExecutable(m_pExecutableCB->isChecked());
        }

        if (m_pObject->baseType() == UMLObject::ot_Artifact) {
            m_artifactTypeWidget->apply();
            m_pObject->emitModified();
        }
    } // end if m_pObject
    else if (m_pWidget) {
        m_pWidget->setInstanceName(m_instanceNameWidget->text());
        if (m_pMultiCB) {
            m_pWidget->setMultipleInstance(m_pMultiCB->isChecked());
        }
        m_pWidget->setDrawAsActor(m_pDrawActorCB->isChecked());
        if (m_pDeconCB) {
            m_pWidget->setShowDestruction(m_pDeconCB->isChecked());
        }
        UMLObject * o = m_pWidget->umlObject();
        if (!o) {
            uError() << "UML object of widget is zero.";
            return;
        }
        UMLObject * old = m_pUmldoc->findUMLObject(name);
        if (old && o != old) {
            KMessageBox::sorry(this, i18n("The name you have chosen\nis already being used.\nThe name has been reset."),
                               i18n("Name is Not Unique"), 0);
            m_nameWidget->reset();
        } else {
            o->setName(name);
        }
    } // end if m_pWidget
    else if (m_pInstanceWidget) {
        m_pInstanceWidget->setInstanceName(m_instanceNameWidget->text());
        UMLObject* o = m_pInstanceWidget->umlObject();
        if (!o) {
            uError() << "UML object of instance widget is zero.";
            return;
        }

        UMLObject* old = m_pUmldoc->findUMLObject(name);
        if (old && o != old) {
            KMessageBox::sorry(this, i18n("The name you have chosen\nis already being used.\nThe name has been reset."),
                               i18n("Name is Not Unique"), 0);
            m_nameWidget->reset();
        } else {
            o->setName(name);
        }
    } // end if m_pInstanceWidget
}

/**
 * When the draw as actor check box is toggled, the draw
 * as multi instance need to be enabled/disabled. They
 * both can't be available at the same time.
 */
void ClassGeneralPage::slotActorToggled(bool state)
{
    if (m_pMultiCB) {
        m_pMultiCB->setEnabled(!state);
    }
}

