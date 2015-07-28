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
#include "settingsdialog.h"

// app includes
#include "autolayoutoptionpage.h"
#include "classoptionspage.h"
#include "codeimportoptionspage.h"
#include "codegenoptionspage.h"
#include "umlwidgetstylepage.h"
#include "codevieweroptionspage.h"
#include "generaloptionpage.h"
#include "dialog_utils.h"
#include "debug_utils.h"
#include "icon_utils.h"
#include "layoutgenerator.h"

// kde includes
#include <KColorButton>
#if QT_VERSION < 0x050000
#include <kfontchooser.h>
#include <KIntSpinBox>
#endif

// qt includes
#include <QCheckBox>
#if QT_VERSION >= 0x050000
#include <QFontDialog>
#endif
#include <QGroupBox>
#if QT_VERSION >= 0x050000
#include <QSpinBox>
#endif

//TODO don't do that, but it's better than hardcoded in the functions body
#define FILL_COLOR QColor(255, 255, 192) 
#define LINK_COLOR Qt::red
#define TEXT_COLOR Qt::black


SettingsDialog::SettingsDialog(QWidget * parent, Settings::OptionState *state)
  : MultiPageDialogBase(parent, true)
{
    setCaption(i18n("Umbrello Setup"));
    m_bChangesApplied = false;
    m_pOptionState = state;
    setupGeneralPage();
    setupFontPage();
    setupUIPage();
    setupClassPage();
    setupCodeImportPage();
    setupCodeGenPage();
    setupCodeViewerPage(state->codeViewerState);
    setupAutoLayoutPage();
    connect(this, SIGNAL(okClicked()), this, SLOT(slotOk()));
    connect(this, SIGNAL(applyClicked()), this, SLOT(slotApply()));
    connect(this, SIGNAL(defaultClicked()), this, SLOT(slotDefault()));
}

SettingsDialog::~SettingsDialog()
{
}

/**
 * Set current page
 *
 * @param page the page to set
 */
void SettingsDialog::setCurrentPage(PageType page)
{
    KPageWidgetItem *currentPage;

    switch(page) {
    case FontPage:
        currentPage = pageFont;
        break;
    case UserInterfacePage:
        currentPage = pageUserInterface;
        break;
    case AutoLayoutPage:
        currentPage = pageAutoLayout;
        break;
    case CodeImportPage:
        currentPage = pageCodeImport;
        break;
    case CodeGenerationPage:
        currentPage = pageCodeGen;
        break;
    case CodeViewerPage:
        currentPage = pageCodeViewer;
        break;
    case ClassPage:
        currentPage = pageClass;
        break;
    case GeneralPage:
    default:
        currentPage = pageGeneral;
        break;
    }
    MultiPageDialogBase::setCurrentPage(currentPage);
}


void SettingsDialog::setupUIPage()
{
    // FIXME: merge with UMLWidgetStylePage
    //setup UI page
    QWidget * page = new QWidget();
    QVBoxLayout* uiPageLayout = new QVBoxLayout(page);
    
    pageUserInterface = createPage(i18n("User Interface"), i18n("User Interface Settings"),
                                   Icon_Utils::it_Properties_UserInterface, page);

    m_UiWidgets.colorGB = new QGroupBox(i18nc("color group box", "Color"), page);
    QGridLayout * colorLayout = new QGridLayout(m_UiWidgets.colorGB);
    colorLayout->setSpacing(spacingHint());
    colorLayout->setMargin(fontMetrics().height());
    uiPageLayout->addWidget(m_UiWidgets.colorGB);
    
    uiPageLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    m_UiWidgets.textColorCB = new QCheckBox(i18n("Custom text color:"), m_UiWidgets.colorGB);
    colorLayout->addWidget(m_UiWidgets.textColorCB, 0, 0);

    m_UiWidgets.textColorB = new KColorButton(m_pOptionState->uiState.textColor, m_UiWidgets.colorGB);
    //m_UiWidgets.lineColorB->setObjectName(m_UiWidgets.colorGB);
    colorLayout->addWidget(m_UiWidgets.textColorB, 0, 1);

    m_UiWidgets.lineColorCB = new QCheckBox(i18n("Custom line color:"), m_UiWidgets.colorGB);
    colorLayout->addWidget(m_UiWidgets.lineColorCB, 1, 0);

    m_UiWidgets.lineColorB = new KColorButton(m_pOptionState->uiState.lineColor, m_UiWidgets.colorGB);
    //m_UiWidgets.lineColorB->setObjectName(m_UiWidgets.colorGB);
    colorLayout->addWidget(m_UiWidgets.lineColorB, 1, 1);

//     m_UiWidgets.lineDefaultB = new QPushButton(i18n("D&efault Color"), m_UiWidgets.colorGB);
//     colorLayout->addWidget(m_UiWidgets.lineDefaultB, 0, 2);

    m_UiWidgets.fillColorCB = new QCheckBox(i18n("Custom fill color:"), m_UiWidgets.colorGB);
    colorLayout->addWidget(m_UiWidgets.fillColorCB, 2, 0);

    m_UiWidgets.fillColorB = new KColorButton(m_pOptionState->uiState.fillColor, m_UiWidgets.colorGB);
    colorLayout->addWidget(m_UiWidgets.fillColorB, 2, 1);

    m_UiWidgets.gridColorCB = new QCheckBox(i18n("Custom grid color:"), m_UiWidgets.colorGB);
    colorLayout->addWidget(m_UiWidgets.gridColorCB, 3, 0);

    m_UiWidgets.gridColorB = new KColorButton(m_pOptionState->uiState.gridDotColor, m_UiWidgets.colorGB);
    colorLayout->addWidget(m_UiWidgets.gridColorB, 3, 1);

    m_UiWidgets.bgColorCB = new QCheckBox(i18n("Custom background color:"), m_UiWidgets.colorGB);
    colorLayout->addWidget(m_UiWidgets.bgColorCB, 4, 0);

    m_UiWidgets.bgColorB = new KColorButton(m_pOptionState->uiState.backgroundColor, m_UiWidgets.colorGB);
    colorLayout->addWidget(m_UiWidgets.bgColorB, 4, 1);

    m_UiWidgets.lineWidthCB = new QCheckBox(i18n("Custom line width:"), m_UiWidgets.colorGB);
    colorLayout->addWidget(m_UiWidgets.lineWidthCB, 5, 0);

#if QT_VERSION >= 0x050000
    m_UiWidgets.lineWidthB = new QSpinBox(m_UiWidgets.colorGB);
    m_UiWidgets.lineWidthB->setMinimum(0);
    m_UiWidgets.lineWidthB->setMaximum(10);
    m_UiWidgets.lineWidthB->setSingleStep(1);
    m_UiWidgets.lineWidthB->setValue(m_pOptionState->uiState.lineWidth);
#else
    m_UiWidgets.lineWidthB = new KIntSpinBox(0, 10, 1, m_pOptionState->uiState.lineWidth, m_UiWidgets.colorGB);
#endif
    colorLayout->addWidget(m_UiWidgets.lineWidthB, 5, 1);
    
    m_UiWidgets.useFillColorCB = new QCheckBox(i18n("&Use fill color"), m_UiWidgets.colorGB);
    //colorLayout->setRowStretch(3, 2);
    colorLayout->addWidget(m_UiWidgets.useFillColorCB, 6, 0);
    m_UiWidgets.useFillColorCB->setChecked(m_pOptionState->uiState.useFillColor);

    //connect button signals up
    connect(m_UiWidgets.textColorCB, SIGNAL(toggled(bool)), this, SLOT(slotTextCBChecked(bool)));
    connect(m_UiWidgets.lineColorCB, SIGNAL(toggled(bool)), this, SLOT(slotLineCBChecked(bool)));
    connect(m_UiWidgets.fillColorCB, SIGNAL(toggled(bool)), this, SLOT(slotFillCBChecked(bool)));
    connect(m_UiWidgets.gridColorCB, SIGNAL(toggled(bool)), this, SLOT(slotGridCBChecked(bool)));
    connect(m_UiWidgets.bgColorCB, SIGNAL(toggled(bool)), this, SLOT(slotBgCBChecked(bool)));
    connect(m_UiWidgets.lineWidthCB, SIGNAL(toggled(bool)), this, SLOT(slotLineWidthCBChecked(bool)));

    //TODO Once the new scene is complete, so something better, it does not worth it for now
    if (m_UiWidgets.textColorB->color() == TEXT_COLOR) {
        m_UiWidgets.textColorCB->setChecked(false);
        m_UiWidgets.textColorB->setDisabled(true);
    }
    else {
        m_UiWidgets.textColorCB->setChecked(true);
    }

    if (m_UiWidgets.fillColorB->color() == FILL_COLOR) {
        m_UiWidgets.fillColorCB->setChecked(false);
        m_UiWidgets.fillColorB->setDisabled(true);
    }
    else {
        m_UiWidgets.fillColorCB->setChecked(true);
    }
    
    if (m_UiWidgets.lineColorB->color() == LINK_COLOR) {
        m_UiWidgets.lineColorCB->setChecked(false);
        m_UiWidgets.lineColorB->setDisabled(true);
    }
    else {
        m_UiWidgets.lineColorCB->setChecked(true);
    }

    if (m_UiWidgets.lineWidthB->value() == 0) {
        m_UiWidgets.lineWidthCB->setChecked(false);
        m_UiWidgets.lineWidthB->setDisabled(true);
    }
    else {
        m_UiWidgets.lineWidthCB->setChecked(true);
        m_UiWidgets.lineWidthB->setDisabled(false);
    }
}

void SettingsDialog::setupGeneralPage()
{
    m_pGeneralPage = new GeneralOptionPage;
    pageGeneral = createPage(i18nc("general settings page", "General"), i18n("General Settings"),
                             Icon_Utils::it_Properties_General, m_pGeneralPage);
    m_pGeneralPage->setMinimumSize(310, 330);

}

void SettingsDialog::setupClassPage()
{
    m_pClassPage = new ClassOptionsPage(0, m_pOptionState, false);
    pageClass = createPage(i18nc("class settings page", "Class"), i18n("Class Settings"),
                           Icon_Utils::it_Properties_Class, m_pClassPage);
}

void SettingsDialog::setupCodeImportPage()
{
    m_pCodeImportPage = new CodeImportOptionsPage;
    pageCodeImport = createPage(i18n("Code Importer"), i18n("Code Import Settings"),
                                Icon_Utils::it_Properties_CodeImport, m_pCodeImportPage);
}

void SettingsDialog::setupCodeGenPage()
{
    m_pCodeGenPage = new CodeGenOptionsPage;
    connect(m_pCodeGenPage, SIGNAL(languageChanged()), this, SLOT(slotApply()));

    pageCodeGen = createPage(i18n("Code Generation"), i18n("Code Generation Settings"),
                             Icon_Utils::it_Properties_CodeGeneration, m_pCodeGenPage);
}

void SettingsDialog::setupCodeViewerPage(Settings::CodeViewerState options)
{
    //setup code generation settings page
    m_pCodeViewerPage = new CodeViewerOptionsPage(options);
    pageCodeViewer = createPage(i18n("Code Viewer"), i18n("Code Viewer Settings"),
                                Icon_Utils::it_Properties_CodeViewer, m_pCodeViewerPage);
}

void SettingsDialog::setupFontPage()
{
#if QT_VERSION >= 0x050000
    m_FontWidgets.chooser = new QFontDialog();
    m_FontWidgets.chooser->setCurrentFont(m_pOptionState->uiState.font);
    m_FontWidgets.chooser->setOption(QFontDialog::NoButtons);
#else
    m_FontWidgets.chooser = new KFontChooser(0, KFontChooser::NoDisplayFlags, QStringList(), 0);
    m_FontWidgets.chooser->setFont(m_pOptionState->uiState.font);
#endif
    pageFont = createPage(i18n("Font"), i18n("Font Settings"),
                          Icon_Utils::it_Properties_Font, m_FontWidgets.chooser);
}

void SettingsDialog::setupAutoLayoutPage()
{
    m_pAutoLayoutPage = new AutoLayoutOptionPage;
    pageAutoLayout = createPage(i18n("Auto Layout"), i18n("Auto Layout Settings"),
                                Icon_Utils::it_Properties_AutoLayout, m_pAutoLayoutPage);
}

void SettingsDialog::slotApply()
{
    applyPage(currentPage());
    //do no emit signal applyClicked in the slot slotApply->infinite loop
    //emit applyClicked();
}

void SettingsDialog::slotOk()
{
    applyPage(pageClass);
    applyPage(pageGeneral);
    applyPage(pageUserInterface);
    applyPage(pageCodeViewer);
    applyPage(pageCodeImport);
    applyPage(pageCodeGen);
    applyPage(pageFont);
    applyPage(pageAutoLayout);
    accept();
}

void SettingsDialog::slotDefault()
{
    // Defaults hard coded.  Make sure that this is alright.
    // If defaults are set anywhere else, like in setting up config file, make sure the same.
    KPageWidgetItem *current = currentPage();
    if (current ==  pageGeneral)
    {
        m_pGeneralPage->setDefaults();
    }
    else if (current == pageFont)
    {
#if QT_VERSION >= 0x050000
        m_FontWidgets.chooser->setCurrentFont(parentWidget()->font());
#else
        m_FontWidgets.chooser->setFont(parentWidget()->font());
#endif
    }
    else if (current == pageUserInterface)
    {
        m_UiWidgets.useFillColorCB->setChecked(true);
        m_UiWidgets.textColorB->setColor(TEXT_COLOR);
        m_UiWidgets.fillColorB->setColor(FILL_COLOR);
        m_UiWidgets.lineColorB->setColor(LINK_COLOR);
        m_UiWidgets.lineWidthB->setValue(0);
    }
    else if (current == pageClass)
    {
        m_pClassPage->setDefaults();
    }
    else if (current == pageCodeImport)
    {
        m_pCodeImportPage->setDefaults();
    }
    else if (current == pageCodeGen)
    {
    }
    else if (current == pageCodeViewer)
    {
    }
    else if (current == pageAutoLayout)
    {
        m_pAutoLayoutPage->setDefaults();
    }
}

void SettingsDialog::applyPage(KPageWidgetItem*item)
{
    m_bChangesApplied = true;
    if (item == pageGeneral)
    {
        m_pGeneralPage->apply();
    }
    else if (item == pageFont)
    {
#if QT_VERSION >= 0x050000
        m_pOptionState->uiState.font = m_FontWidgets.chooser->currentFont();
#else
        m_pOptionState->uiState.font = m_FontWidgets.chooser->font();
#endif
    }
    else if (item == pageUserInterface)
    {
        m_pOptionState->uiState.useFillColor = m_UiWidgets.useFillColorCB->isChecked();
        m_pOptionState->uiState.fillColor = m_UiWidgets.fillColorB->color();
        m_pOptionState->uiState.textColor = m_UiWidgets.textColorB->color();
        m_pOptionState->uiState.lineColor = m_UiWidgets.lineColorB->color();
        m_pOptionState->uiState.lineWidth = m_UiWidgets.lineWidthB->value();
        m_pOptionState->uiState.backgroundColor = m_UiWidgets.bgColorB->color();
        m_pOptionState->uiState.gridDotColor = m_UiWidgets.gridColorB->color();
    }
    else if (item == pageClass)
    {
        m_pClassPage->apply();
    }
    else if (item == pageCodeImport)
    {
        m_pCodeImportPage->apply();
    }
    else if (item == pageCodeGen)
    {
        m_pCodeGenPage->apply();
    }
    else if (item == pageCodeViewer)
    {
        m_pCodeViewerPage->apply();
        m_pOptionState->codeViewerState = m_pCodeViewerPage->getOptions();
    }
    else if (item == pageAutoLayout)
    {
        m_pAutoLayoutPage->apply();
    }
}

void SettingsDialog::slotTextCBChecked(bool value)
{
    if (value == false) {
        m_UiWidgets.textColorB->setColor(TEXT_COLOR);
        m_UiWidgets.textColorB->setDisabled(true);
    }
    else {
        m_UiWidgets.textColorB->setDisabled(false);
    }
}

void SettingsDialog::slotLineCBChecked(bool value)
{
    if (value == false) {
        m_UiWidgets.lineColorB->setColor(LINK_COLOR);
        m_UiWidgets.lineColorB->setDisabled(true);
    }
    else {
        m_UiWidgets.lineColorB->setDisabled(false);
    }
}

void SettingsDialog::slotFillCBChecked(bool value)
{
    if (value == false) {
        m_UiWidgets.fillColorB->setColor(FILL_COLOR);
        m_UiWidgets.fillColorB->setDisabled(true);
    }
    else {
        m_UiWidgets.fillColorB->setDisabled(false);
    }
}

void SettingsDialog::slotGridCBChecked(bool value)
{
    if (value == false) {
        QPalette palette;
        m_UiWidgets.gridColorB->setColor(palette.alternateBase().color());
        m_UiWidgets.gridColorB->setDisabled(true);
    }
    else {
        m_UiWidgets.gridColorB->setDisabled(false);
    }
}

void SettingsDialog::slotBgCBChecked(bool value)
{
    if (value == false) {
        QPalette palette;
        m_UiWidgets.bgColorB->setColor(palette.base().color());
        m_UiWidgets.bgColorB->setDisabled(true);
    }
    else {
        m_UiWidgets.bgColorB->setDisabled(false);
    }
}

void SettingsDialog::slotLineWidthCBChecked(bool value)
{
    if (value == false) {
        m_UiWidgets.lineWidthB->setValue(0);
        m_UiWidgets.lineWidthB->setDisabled(true);
    }
    else {
        m_UiWidgets.lineWidthB->setDisabled(false);
    }
}

QString SettingsDialog::getCodeGenerationLanguage()
{
    return m_pCodeGenPage->getLanguage();
}

