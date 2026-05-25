#include "cardwidget.h"

#include <QVBoxLayout>

CardWidget::CardWidget(QWidget* parent)
    : QWidget(parent)
{
    // CardWidget lui-même est transparent, comme TableCulture
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("CardWidget { background: transparent; border: none; }");

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);

    // m_card porte le fond arrondi + bordure
    m_card = new QWidget(this);
    m_card->setAttribute(Qt::WA_StyledBackground, true);
    m_card->setObjectName("CardInner");
    m_card->setStyleSheet(R"(
        QWidget#CardInner {
            background-color: #151922;
            border-radius: 14px;
            border: 1px solid rgba(255,255,255,0.08);
        }
    )");

    m_innerLayout = new QVBoxLayout(m_card);
    m_innerLayout->setContentsMargins(14, 14, 14, 14);
    m_innerLayout->setSpacing(10);

    outerLayout->addWidget(m_card);
}

QVBoxLayout* CardWidget::innerLayout() const
{
    return m_innerLayout;
}
