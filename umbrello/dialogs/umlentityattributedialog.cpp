/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *  copyright (C) 2002-2014                                                *
 *  Umbrello UML Modeller Authors <umbrello-devel@kde.org>                 *
 ***************************************************************************/

// own header
#include "umlentityattributedialog.h"

// app includes
#include "entityattribute.h"
#include "classifier.h"
#include "umldoc.h"
#include "uml.h"
#include "umlstereotypewidget.h"
#include "codegenerator.h"
#include "dialog_utils.h"
#include "object_factory.h"
#include "umlclassifierlist.h"

// kde includes
#include <klineedit.h>
#include <kcombobox.h>
#include <kcompletion.h>
#include <KLocalizedString>
#include <KMessageBox>

// qt includes
#include <QApplication>
#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLayout>
#include <QRadioButton>
#include <QVBoxLayout>

UMLEntityAttributeDialog::UMLEntityAttributeDialog(QWidget * pParent, UMLEntityAttribute * pEntityAttribute)
  : SinglePageDialogBase(pParent)
{
    setCaption(i18n("Entity Attribute Properties"));
    m_pEntityAttribute = pEntityAttribute;
    setupDialog();
}

UMLEntityAttributeDialog::~UMLEntityAttributeDialog()
{
}

/**
 *   Sets up the dialog.
 */
void UMLEntityAttributeDialog::setupDialog()
{
    int margin = fontMetrics().height();
    QFrame *frame = new QFrame(this);
    setMainWidget(frame);
    QVBoxLayout * mainLayout = new QVBoxLayout(frame);

    m_pValuesGB = new QGroupBox(i18n("General Properties"), frame);
    QGridLayout * valuesLayout = new QGridLayout(m_pValuesGB);
    valuesLayout->setMargin(margin);
    valuesLayout->setSpacing(10);

    m_pTypeL = new QLabel(i18n("&Type:"), m_pValuesGB);
    valuesLayout->addWidget(m_pTypeL, 0, 0);

    m_pTypeCB = new KComboBox(true, m_pValuesGB);
    valuesLayout->addWidget(m_pTypeCB, 0, 1);
    m_pTypeL->setBuddy(m_pTypeCB);

    Dialog_Utils::makeLabeledEditField(valuesLayout, 1,
                                    m_pNameL, i18nc("name of entity attribute", "&Name:"),
                                    m_pNameLE, m_pEntityAttribute->name());

    Dialog_Utils::makeLabeledEditField(valuesLayout, 2,
                                    m_pInitialL, i18n("&Default value:"),
                                    m_pInitialLE, m_pEntityAttribute->getInitialValue());

    m_stereotypeWidget = new UMLStereotypeWidget(m_pEntityAttribute);
    m_stereotypeWidget->addToLayout(valuesLayout, 3);

    Dialog_Utils::makeLabeledEditField(valuesLayout, 4,
                                    m_pValuesL, i18n("Length/Values:"),
                                    m_pValuesLE, m_pEntityAttribute->getValues());

    m_pAutoIncrementCB = new QCheckBox(i18n("&Auto increment"), m_pValuesGB);
    m_pAutoIncrementCB->setChecked(m_pEntityAttribute->getAutoIncrement());
    valuesLayout->addWidget(m_pAutoIncrementCB, 5, 0);

    m_pNullCB = new QCheckBox(i18n("Allow &null"), m_pValuesGB);
    m_pNullCB->setChecked(m_pEntityAttribute->getNull());
    valuesLayout->addWidget(m_pNullCB, 6, 0);

    // enable/disable isNull depending on the state of Auto Increment Check Box
    slotAutoIncrementStateChanged(m_pAutoIncrementCB->isChecked());

    m_pAttributesL = new QLabel(i18n("Attributes:"), m_pValuesGB);
    valuesLayout->addWidget(m_pAttributesL, 7, 0);

    m_pAttributesCB = new KComboBox(true, m_pValuesGB);
#if QT_VERSION < 0x050000
    m_pAttributesCB->setCompletionMode(KGlobalSettings::CompletionPopup);
#endif
    valuesLayout->addWidget(m_pAttributesCB, 7, 1);
    m_pTypeL->setBuddy(m_pAttributesCB);

    insertAttribute(m_pEntityAttribute->getAttributes());
    insertAttribute(QString::fromLatin1("binary"), m_pAttributesCB->count());
    insertAttribute(QString::fromLatin1("unsigned"), m_pAttributesCB->count());
    insertAttribute(QString::fromLatin1("unsigned zerofill"), m_pAttributesCB->count());

    mainLayout->addWidget(m_pValuesGB);

    m_pScopeGB = new QGroupBox(i18n("Indexing"), frame);
    QHBoxLayout* scopeLayout = new QHBoxLayout(m_pScopeGB);
    scopeLayout->setMargin(margin);

    m_pNoneRB = new QRadioButton(i18n("&Not Indexed"), m_pScopeGB);
    scopeLayout->addWidget(m_pNoneRB);

    /*
    m_pPublicRB = new QRadioButton(i18n("&Primary"), m_pScopeGB);
    scopeLayout->addWidget(m_pPublicRB);

    m_pProtectedRB = new QRadioButton(i18n("&Unique"), m_pScopeGB);
    scopeLayout->addWidget(m_pProtectedRB);
    */

    m_pPrivateRB = new QRadioButton(i18n("&Indexed"), m_pScopeGB);
    scopeLayout->addWidget(m_pPrivateRB);

    mainLayout->addWidget(m_pScopeGB);
    UMLEntityAttribute::DBIndex_Type scope = m_pEntityAttribute->indexType();

    /*
    if (scope == UMLEntityAttribute::Primary)
        m_pPublicRB->setChecked(true);
    else if(scope == UMLEntityAttribute::Unique)
        m_pProtectedRB->setChecked(true);
    else */

    if (scope == UMLEntityAttribute::Index)
        m_pPrivateRB->setChecked(true);
    else {
        m_pNoneRB->setChecked(true);
    }

    m_pTypeCB->setDuplicatesEnabled(false); // only allow one of each type in box
#if QT_VERSION < 0x050000
    m_pTypeCB->setCompletionMode(KGlobalSettings::CompletionPopup);
#endif
    insertTypesSorted(m_pEntityAttribute->getTypeName());

    m_pNameLE->setFocus();
    connect(m_pNameLE, SIGNAL(textChanged(QString)), SLOT(slotNameChanged(QString)));
    connect(m_pAutoIncrementCB, SIGNAL(clicked(bool)), this, SLOT(slotAutoIncrementStateChanged(bool)));
    slotNameChanged(m_pNameLE->text());
}

void UMLEntityAttributeDialog::slotNameChanged(const QString &_text)
{
    enableButtonOk(!_text.isEmpty());
}

/**
 * Checks if changes are valid and applies them if they are,
 * else returns false
 */
bool UMLEntityAttributeDialog::apply()
{
    QString name = m_pNameLE->text();
    if (name.isEmpty()) {
        KMessageBox::error(this, i18n("You have entered an invalid entity attribute name."),
                           i18n("Entity Attribute Name Invalid"), 0);
        m_pNameLE->setText(m_pEntityAttribute->name());
        return false;
    }
    UMLClassifier * pConcept = dynamic_cast<UMLClassifier *>(m_pEntityAttribute->parent());
    UMLObject *o = pConcept->findChildObject(name);
    if (o && o != m_pEntityAttribute) {
        KMessageBox::error(this, i18n("The entity attribute name you have chosen is already being used in this operation."),
                           i18n("Entity Attribute Name Not Unique"), 0);
        m_pNameLE->setText(m_pEntityAttribute->name());
        return false;
    }
    m_pEntityAttribute->setName(name);
    m_pEntityAttribute->setInitialValue(m_pInitialLE->text());
    m_stereotypeWidget->apply();
    m_pEntityAttribute->setValues(m_pValuesLE->text());
    m_pEntityAttribute->setAttributes(m_pAttributesCB->currentText());
    m_pEntityAttribute->setAutoIncrement(m_pAutoIncrementCB->isChecked());
    m_pEntityAttribute->setNull(m_pNullCB->isChecked());

    /*
    if (m_pPublicRB->isChecked()) {
        m_pEntityAttribute->setIndexType(UMLEntityAttribute::Primary);
    } else if (m_pProtectedRB->isChecked()) {
        m_pEntityAttribute->setIndexType(UMLEntityAttribute::Unique);
    } else
    */

    if (m_pPrivateRB->isChecked()) {
        m_pEntityAttribute->setIndexType(UMLEntityAttribute::Index);
    } else {
        m_pEntityAttribute->setIndexType(UMLEntityAttribute::None);
    }

    QString typeName = m_pTypeCB->currentText();
    UMLDoc *pDoc = UMLApp::app()->document();
    UMLClassifierList dataTypes = pDoc->datatypes();
    foreach (UMLClassifier* dat, dataTypes) {
        if (typeName == dat->name()) {
            m_pEntityAttribute->setType(dat);
            return true;
        }
    }
    UMLObject *obj = pDoc->findUMLObject(typeName);
    UMLClassifier *classifier = dynamic_cast<UMLClassifier*>(obj);
    if (classifier == NULL) {
        // If it's obviously a pointer type (C++) then create a datatype.
        // Else we don't know what it is so as a compromise create a class.
        UMLObject::ObjectType ot =
            (typeName.contains(QChar::fromLatin1('*')) ? UMLObject::ot_Datatype
                                                      : UMLObject::ot_Class);
        obj = Object_Factory::createUMLObject(ot, typeName);
        if (obj == NULL)
            return false;
        classifier = static_cast<UMLClassifier*>(obj);
    }
    m_pEntityAttribute->setType(classifier);
    return true;
}

/**
 * Inserts @p type into the type-combobox as well as its completion object.
 */
void UMLEntityAttributeDialog::insertTypesSorted(const QString& type)
{
    QStringList types;
    // add the data types
    UMLDoc * pDoc = UMLApp::app()->document();
    UMLClassifierList dataTypes = pDoc->datatypes();
    if (dataTypes.count() == 0) {
        // Switch to SQL as the active language if no datatypes are set.
        UMLApp::app()->setActiveLanguage(Uml::ProgrammingLanguage::SQL);
        pDoc->addDefaultDatatypes();
        qApp->processEvents();
        dataTypes = pDoc->datatypes();
    }
    foreach (UMLClassifier* dat, dataTypes) {
        types << dat->name();
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
    m_pTypeCB->completionObject()->addItem(type);
}

/**
 * Inserts @p type into the type-combobox as well as its completion object.
 */
void UMLEntityAttributeDialog::insertAttribute(const QString& type, int index)
{
    m_pAttributesCB->insertItem(index, type);
    m_pAttributesCB->completionObject()->addItem(type);
}

/**
 * Is activated when the auto increment state is changed.
 */
void UMLEntityAttributeDialog::slotAutoIncrementStateChanged(bool checked)
{
    if (checked == true) {
        m_pNullCB->setChecked(false);
        m_pNullCB->setEnabled(false);
    } else if (checked == false) {
        m_pNullCB->setEnabled(true);
    }

}

