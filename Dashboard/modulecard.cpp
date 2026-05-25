#include "modulecard.h"

#include <QVBoxLayout>
#include <QLabel>

ModuleCard::ModuleCard(const ModuleInfo& info, QWidget* parent)
    : QWidget(parent)
{
    // ModuleCard transparente, m_card porte le fond arrondi
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("ModuleCard { background: transparent; border: none; }");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(110);

    QVBoxLayout* outer = new QVBoxLayout(this);
    outer->setContentsMargins(0,0,0,0);
    outer->setSpacing(0);

    QWidget* card = new QWidget(this);
    card->setAttribute(Qt::WA_StyledBackground, true);
    card->setObjectName("ModuleCardInner");
    card->setStyleSheet(R"(
        QWidget#ModuleCardInner {
            background-color: #151922;
            border-radius: 14px;
            border: 1px solid rgba(255,255,255,0.08);
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(card);
    layout->setContentsMargins(14,12,14,12);
    layout->setSpacing(2);

    // Icône
    QLabel* icon = new QLabel(info.icon);
    icon->setStyleSheet("font-size:18px; background:transparent; border:none;");

    // Valeur principale
    m_valueLabel = new QLabel(info.value);
    m_valueLabel->setStyleSheet(
        "color:white; font-size:22px; font-weight:700;"
        "background:transparent; border:none;"
        );

    // Titre
    QLabel* title = new QLabel(info.title);
    title->setStyleSheet(
        "color:#9aa4b2; font-size:11px; font-weight:600;"
        "background:transparent; border:none;"
        );

    // Sous-titre
    m_subtitleLabel = new QLabel(info.subtitle);
    m_subtitleLabel->setStyleSheet(
        "color:#5c6370; font-size:10px;"
        "background:transparent; border:none;"
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

// modulecard.cpp
void ModuleCard::setSubtitle(const QString& subtitle)
{
    m_subtitleLabel->setText(subtitle);
}
