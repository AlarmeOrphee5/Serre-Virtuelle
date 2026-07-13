#include "settingspage.h"
#include "DataManager/Settings/settingsmanager.h"

#include "Core/Communs/cardwidget.h"
#include "Core/UI/uigenerale.h"
#include "Core/Communs/appinfo.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>


static QLabel* createSectionTitle(const QString& text)
{
    QLabel* label = new QLabel(text);

    UIGenerale::applyText(
        label,
        UIGenerale::TextStyle::SectionTitle
        );

    return label;
}


SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    setupConnections();
    loadSettings();
}


void SettingsPage::setupUI()
{
    UIGenerale::applyPage(this);


    QVBoxLayout* layout =
        new QVBoxLayout(this);


    layout->setContentsMargins(
        25,
        25,
        25,
        25
        );

    layout->setSpacing(
        15
        );


    setupHeader();
    setupAppearance();
    setupData();
    setupDashboard();
    setupAbout();


    layout->addStretch();


    m_applyButton =
        new QPushButton("✓ Appliquer");


    m_resetButton =
        new QPushButton("Réinitialiser");


    UIGenerale::applyButton(
        m_applyButton,
        UIGenerale::ButtonStyle::Primary
        );


    UIGenerale::applyButton(
        m_resetButton,
        UIGenerale::ButtonStyle::Secondary
        );


    QHBoxLayout* buttons =
        new QHBoxLayout;


    buttons->addWidget(
        m_resetButton
        );


    buttons->addStretch();


    buttons->addWidget(
        m_applyButton
        );


    layout->addLayout(
        buttons
        );
}


void SettingsPage::setupHeader()
{
    auto* layout =
        qobject_cast<QVBoxLayout*>(this->layout());


    QLabel* title = new QLabel("Paramètres");

    UIGenerale::applyText(
        title,
        UIGenerale::TextStyle::PageTitle
        );

    QLabel* subtitle =
        new QLabel(
            "Configuration générale de l'application"
            );

    UIGenerale::applyText(
        subtitle,
        UIGenerale::TextStyle::Description
        );


    layout->addWidget(title);
    layout->addWidget(subtitle);
    layout->addWidget(UIGenerale::createSeparator());
}


void SettingsPage::setupAppearance()
{
    auto* layout =
        qobject_cast<QVBoxLayout*>(this->layout());


    CardWidget* card = new CardWidget;

    QVBoxLayout* v = card->innerLayout();


    v->addWidget(
        createSectionTitle("Apparence")
        );


    QLabel* themeLabel =
        new QLabel("Thème");
    UIGenerale::applyText(
        themeLabel,
        UIGenerale::TextStyle::Body
        );


    m_themeCombo = new QComboBox;
    UIGenerale::applyComboBox(
        m_themeCombo
        );

    m_themeCombo->addItems({
        "Sombre",
        "Clair"
    });


    v->addWidget(themeLabel);
    v->addWidget(m_themeCombo);


    layout->addWidget(card);
}


void SettingsPage::setupData()
{
    auto* layout =
        qobject_cast<QVBoxLayout*>(this->layout());


    CardWidget* card = new CardWidget;

    QVBoxLayout* v = card->innerLayout();


    v->addWidget(
        createSectionTitle("Données")
        );


    m_databasePath = new QLineEdit;
    UIGenerale::applyLineEdit(
        m_databasePath
        );
    m_databasePath->setReadOnly(true);


    m_databaseBrowseButton =
        new QPushButton("Modifier");
    UIGenerale::applyButton(m_databaseBrowseButton, UIGenerale::ButtonStyle::Secondary);


    QHBoxLayout* row = new QHBoxLayout;

    row->addWidget(m_databasePath);
    row->addWidget(m_databaseBrowseButton);


    v->addLayout(row);


    layout->addWidget(card);
}


void SettingsPage::setupDashboard()
{
    auto* layout =
        qobject_cast<QVBoxLayout*>(this->layout());


    CardWidget* card = new CardWidget;

    QVBoxLayout* v = card->innerLayout();


    v->addWidget(
        createSectionTitle("Tableau de bord")
        );


    m_showStatsCheck =
        new QCheckBox(
            "Afficher les statistiques"
            );
    UIGenerale::applyCheckBox(
        m_showStatsCheck
        );


    m_showInactiveCheck =
        new QCheckBox(
            "Afficher les éléments inactifs"
            );
    UIGenerale::applyCheckBox(
        m_showInactiveCheck
        );


    v->addWidget(m_showStatsCheck);
    v->addWidget(m_showInactiveCheck);


    layout->addWidget(card);
}


void SettingsPage::setupAbout()
{
    auto* layout =
        qobject_cast<QVBoxLayout*>(this->layout());


    CardWidget* card = new CardWidget;

    QVBoxLayout* v = card->innerLayout();


    v->addWidget(
        createSectionTitle("À propos")
        );


    QLabel* info =
        new QLabel(
            QString(
                "%1<br>"
                "Version %2<br>"
                "Qt %3<br><br>"
                "Auteur : <a href=\"%4\">%5</a>"
                )
                .arg(AppInfo::name())
                .arg(AppInfo::version())
                .arg(AppInfo::qtVersion())
                .arg(AppInfo::github())
                .arg(AppInfo::autheur())
            );
    info->setTextFormat(Qt::RichText);
    info->setOpenExternalLinks(true);

    UIGenerale::applyText(
        info,
        UIGenerale::TextStyle::Description
        );


    v->addWidget(info);


    layout->addWidget(card);
}


void SettingsPage::setupConnections()
{
    connect(
        m_applyButton,
        &QPushButton::clicked,
        this,
        &SettingsPage::saveSettings
        );
}


void SettingsPage::loadSettings()
{
    // A connecter avec SettingsManager
}


void SettingsPage::saveSettings()
{
    // A connecter avec SettingsManager
}
