#include "modulecard.h"
#include "../Shared/UI/uigenerale.h"
#include "cardwidget.h"

#include <QVBoxLayout>
#include <QLabel>


ModuleCard::ModuleCard(const ModuleInfo& info, QWidget* parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);

    setStyleSheet(
        "ModuleCard {"
        "background:transparent;"
        "border:none;"
        "}"
        );

    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Fixed
        );

    setFixedHeight(110);


    QVBoxLayout* outer =
        new QVBoxLayout(this);

    outer->setContentsMargins(
        0,
        0,
        0,
        0
        );

    outer->setSpacing(0);


    // Utilisation du widget de carte commun
    CardWidget* card =
        new CardWidget(this);


    QVBoxLayout* layout =
        card->innerLayout();


    layout->setContentsMargins(
        14,
        12,
        14,
        12
        );

    layout->setSpacing(2);


    // Icône
    QLabel* icon =
        new QLabel(info.icon);
    icon->setStyleSheet(
        "font-size:18px;"
        "background:transparent;"
        "border:none;"
        );


    // Valeur principale
    m_valueLabel =
        new QLabel(info.value);
    UIGenerale::applyText(
        m_valueLabel,
        UIGenerale::TextStyle::Value
        );


    // Titre
    QLabel* title =
        new QLabel(info.title);
    UIGenerale::applyText(
        title,
        UIGenerale::TextStyle::Description
        );

    // Sous-titre
    m_subtitleLabel =
        new QLabel(info.subtitle);
    UIGenerale::applyText(
        m_subtitleLabel,
        UIGenerale::TextStyle::Muted
        );

    layout->addWidget(icon);
    layout->addWidget(m_valueLabel);
    layout->addWidget(title);
    layout->addWidget(m_subtitleLabel);


    outer->addWidget(card);
}


void ModuleCard::setValue(const QString& value)
{
    m_valueLabel->setText(value);
}


void ModuleCard::setSubtitle(const QString& subtitle)
{
    m_subtitleLabel->setText(subtitle);
}
