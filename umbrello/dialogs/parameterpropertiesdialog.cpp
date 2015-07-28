/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

// own header
#include "parameterpropertiesdialog.h"

// local includes
#include "attribute.h"
#include "classifier.h"
#include "debug_utils.h"
#include "documentationwidget.h"
#include "umlstereotypewidget.h"
#include "umltemplatelist.h"
#include "template.h"
#include "umldoc.h"
#include "dialog_utils.h"
#include "object_factory.h"
#include "stereotype.h"

// kde includes
#include <KComboBox>
#include <KLineEdit>
#include <KLocalizedString>
#include <KMessageBox>

// qt includes
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLayout>
#include <QRadioButton>
#include <QVBoxLayout>

/**
 * Constructs a ParameterPropertiesDialog.
 * @param parent   the parent of the dialog
 * @param doc      UMLDoc instance for access to classifiers and stereotypes
 * @param attr     the parameter to represent
 */
ParameterPropertiesDialog::ParameterPropertiesDialog(QWidget * parent, UMLDoc * doc, UMLAttribute * attr)
  : SinglePageDialogBase(parent)
{
    Q_ASSERT(attr);
    setCaption(i18n("Parameter Properties"));

    m_pUmldoc = doc;
    m_pAtt = attr;

    int margin = fontMetrics().height();
    setMinimumSize(300, 400);
    //disableResize();
    QFrame *frame = new QFrame(this);
    setMainWidget(frame);
    QVBoxLayout * topLayout = new QVBoxLayout(frame);
    topLayout->setSpacing(10);
    topLayout->setMargin(margin);

    m_pParmGB = new QGroupBox(i18n("Properties"));
    topLayout->addWidget(m_pParmGB);

    QGridLayout * propLayout = new QGridLayout(m_pParmGB);
    propLayout->setSpacing(10);
    propLayout->setMargin(margin);

    m_pTypeL = new QLabel(i18n("&Type:"), m_pParmGB);
    propLayout->addWidget(m_pTypeL, 0, 0);

    m_pTypeCB = new KComboBox(m_pParmGB);
    propLayout->addWidget(m_pTypeCB, 0, 1);
    m_pTypeL->setBuddy(m_pTypeCB);

    Dialog_Utils::makeLabeledEditField(propLayout, 1,
                                    m_pNameL, i18nc("property name", "&Name:"),
                                    m_pNameLE, attr->name());

    Dialog_Utils::makeLabeledEditField(propLayout, 2,
                                    m_pInitialL, i18n("&Initial value:"),
                                    m_pInitialLE, attr->getInitialValue());

    m_stereotypeWidget = new UMLStereotypeWidget(m_pAtt);
    m_stereotypeWidget->addToLayout(propLayout, 3);

    m_pKindGB =  new QGroupBox(i18n("Passing Direction"));
    m_pKindGB->setToolTip(i18n("\"in\" is a readonly parameter, \"out\" is a writeonly parameter and \"inout\" is a parameter for reading and writing."));

    QHBoxLayout * kindLayout = new QHBoxLayout(m_pKindGB);
    kindLayout->setMargin(margin);

    m_pIn =  new QRadioButton(QString::fromLatin1("in"), m_pKindGB);
    kindLayout->addWidget(m_pIn);

    m_pInOut =  new QRadioButton(QString::fromLatin1("inout"), m_pKindGB);
    kindLayout->addWidget(m_pInOut);

    m_pOut =  new QRadioButton(QString::fromLatin1("out"), m_pKindGB);
    kindLayout->addWidget(m_pOut);

    topLayout->addWidget(m_pKindGB);

    m_docWidget = new DocumentationWidget(m_pAtt);
    topLayout->addWidget(m_docWidget);

    // Check the proper Kind radiobutton.
    if (attr) {
        Uml::ParameterDirection::Enum kind = attr->getParmKind();
        if (kind == Uml::ParameterDirection::Out)
            m_pOut->setChecked(true);
        else if (kind == Uml::ParameterDirection::InOut)
            m_pInOut->setChecked(true);
        else
            m_pIn->setChecked(true);
    } else
        m_pIn->setChecked(true);

    // manage types
    m_pTypeCB->setDuplicatesEnabled(false); // only allow one of each type in box
    m_pTypeCB->setEditable(true);
#if QT_VERSION < 0x050000
    m_pTypeCB->setCompletionMode(KGlobalSettings::CompletionPopup);
#endif
//    m_pTypeCB->setCompleter(...);
    if (attr) {
        insertTypesSorted(attr->getTypeName());
    }

    // set tab order
    setTabOrder(m_pKindGB, m_pTypeCB);
    setTabOrder(m_pTypeCB, m_pNameLE);
    setTabOrder(m_pNameLE, m_pInitialLE);
    setTabOrder(m_pInitialLE, m_stereotypeWidget);
    setTabOrder(m_stereotypeWidget, m_pIn);
    setTabOrder(m_pIn, m_docWidget);
    m_pNameLE->setFocus();
}

/**
 * Standard destructor.
 */
ParameterPropertiesDialog::~ParameterPropertiesDialog()
{
}

QString ParameterPropertiesDialog::getName()
{
    return m_pNameLE->text();
}

QString ParameterPropertiesDialog::getInitialValue()
{
    return m_pInitialLE->text();
}

QString ParameterPropertiesDialog::getTypeName()
{
    return m_pTypeCB->currentText();
}

/**
 * Inserts @p type into the type-combobox as well as its completion object.
 * The combobox is cleared and all types together with the optional new one
 * sorted and then added again.
 * @param type   a new type to add and selected
 */
void ParameterPropertiesDialog::insertTypesSorted(const QString& type)
{
    QStringList types;
    // add template parameters
    UMLClassifier *pConcept = dynamic_cast<UMLClassifier*>(m_pAtt->parent()->parent());
    if (pConcept == NULL) {
        uError() << "ParameterPropertiesDialog: grandparent of " << m_pAtt->name()
                 << " is not a UMLClassifier";
    } else {
        UMLTemplateList tmplParams(pConcept->getTemplateList());
        foreach(UMLTemplate* t, tmplParams) {
            types << t->name();
        }
    }
    // now add the Concepts
    UMLClassifierList namesList(m_pUmldoc->concepts());
    foreach(UMLClassifier* obj, namesList) {
        types << obj->fullyQualifiedName();
    }
    // add the given parameter
    if (!types.contains(type)) {
        types << type;
    }
    types.sort();

    m_pTypeCB->clear();
    m_pTypeCB->insertItems(-1, types);

    // select the given parameter
    int currentIndex = m_pTypeCB->findText(type);
    if (currentIndex > -1) {
        m_pTypeCB->setCurrentIndex(currentIndex);
    }
}

/**
 * Return the kind of the parameter (in, out, or inout).
 * @return  The Uml::ParameterDirection::Enum corresponding to
 *          the selected "Kind" radiobutton.
 */
Uml::ParameterDirection::Enum ParameterPropertiesDialog::getParmKind()
{
    Uml::ParameterDirection::Enum pk = Uml::ParameterDirection::In;
    if (m_pOut->isChecked())
        pk = Uml::ParameterDirection::Out;
    else if (m_pInOut->isChecked())
        pk = Uml::ParameterDirection::InOut;
    return pk;
}

/**
 * Validates the fields in the dialog box.
 * @return success state
 */
bool ParameterPropertiesDialog::validate()
{
    // currently only validates whether the name is not null.
    if (getName().trimmed().length() == 0) {
            KMessageBox::error(this, i18n("You have entered an invalid parameter name."),
                               i18n("Parameter Name Invalid"), 0);
            return false;
    }
    return true;
}

bool ParameterPropertiesDialog::apply()
{
    if (m_pAtt != NULL) {

        m_pAtt->setName(getName());         // set the name
        m_pAtt->setParmKind(getParmKind());  // set the direction
        m_stereotypeWidget->apply();

        // set the type name
        QString typeName = m_pTypeCB->currentText();
        UMLClassifier * pConcept = dynamic_cast<UMLClassifier*>(m_pAtt->parent()->parent());
        if (pConcept == NULL) {
            uError() << "grandparent of " << m_pAtt->name() << " is not a UMLClassifier";
        } else {
            UMLTemplate *tmplParam = pConcept->findTemplate(typeName);
            if (tmplParam) {
                m_pAtt->setType(tmplParam);
                return true;
            }
        }
        UMLClassifierList namesList(m_pUmldoc->concepts());
        bool matchFound = false;

        foreach (UMLClassifier* obj, namesList) {
            if (obj->fullyQualifiedName() == typeName) {
                m_pAtt->setType(obj);
                matchFound = true;
                break;
            }
        }
        if (!matchFound) {
            // Nothing found: Create a new type on the fly.
            // @todo There should be an extra dialog to decide whether to
            // create a datatype or a class. For now, we create a class.
            uDebug() << typeName << " not found."
                << " Creating a new class for the type.";
            UMLObject *newObj = Object_Factory::createUMLObject(UMLObject::ot_Class, typeName);
            m_pAtt->setType(newObj);
        }

        m_docWidget->apply();
        m_pAtt->setInitialValue(getInitialValue()); // set the initial value
    }
    return true;
}

