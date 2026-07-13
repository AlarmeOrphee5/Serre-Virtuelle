#include "cardwidget.h"

#include "../Shared/UI/uigenerale.h"

#include <QVBoxLayout>


CardWidget::CardWidget(QWidget* parent)
    : QWidget(parent)
{
    // Widget extérieur transparent
    setAttribute(
        Qt::WA_StyledBackground,
        true
        );


    setStyleSheet(
        "CardWidget {"
        "background:transparent;"
        "border:none;"
        "}"
        );


    QVBoxLayout* outerLayout =
        new QVBoxLayout(this);


    outerLayout->setContentsMargins(
        0,
        0,
        0,
        0
        );

    outerLayout->setSpacing(0);



    // Partie visuelle de la carte
    m_card = new QWidget(this);


    m_card->setAttribute(
        Qt::WA_StyledBackground,
        true
        );


    m_card->setObjectName(
        "CardInner"
        );


    UIGenerale::applyCard(
        m_card
        );



    m_innerLayout =
        new QVBoxLayout(m_card);


    m_innerLayout->setContentsMargins(
        14,
        14,
        14,
        14
        );


    m_innerLayout->setSpacing(
        10
        );


    outerLayout->addWidget(
        m_card
        );
}



QVBoxLayout* CardWidget::innerLayout() const
{
    return m_innerLayout;
}
