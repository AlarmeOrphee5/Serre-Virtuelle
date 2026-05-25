#include "potwidget.h"

PotWidget::PotWidget(int numero, EtatPot etat, QWidget* parent)
    : QPushButton(parent),
    m_numeroPot(numero),
    m_etat(etat)
{
    setFixedSize(18, 18);
    setAttribute(Qt::WA_StyledBackground, true);
    setMouseTracking(true);

    updateStyle();
    updateTooltip();
}

void PotWidget::setEtat(EtatPot etat)
{
    m_etat = etat;
    updateStyle();
    updateTooltip();
}

EtatPot PotWidget::etat() const
{
    return m_etat;
}

void PotWidget::updateStyle()
{
    this->setStyleSheet(QString(R"(
    QPushButton {
        background:%1;
        border-radius:9px;
        border:1px solid transparent;
    }

    QPushButton:hover {
        border:1px solid white;
    }
    )").arg(colorFromEtat(m_etat)));
}

void PotWidget::updateTooltip()
{
    setToolTip(toString());
}

QString PotWidget::nomPlante() const
{
    return m_nomPlante;
}

void PotWidget::setNomPlante(const QString& newNomPlante)
{
    m_nomPlante = newNomPlante;
    updateTooltip();
}

int PotWidget::numeroPot() const
{
    return m_numeroPot;
}

void PotWidget::setNumeroPot(int newNumeroPot)
{
    m_numeroPot = newNumeroPot;
    updateTooltip();
}

QString PotWidget::datePlantation() const
{
    return m_datePlantation;
}

void PotWidget::setDatePlantation(const QString& newDatePlantation)
{
    m_datePlantation = newDatePlantation;
    updateTooltip();
}

QString PotWidget::toString()
{
    QList<EtatPot> etats = tousLesEtats();
    if(m_etat == etats.at(0))
    {
        return "Pot n°" + QString::number(m_numeroPot)
               + " | " + (m_nomPlante.isEmpty() ? "Vide" : m_nomPlante)
               + " | " + labelFromEtat(m_etat);
    }
    if(m_etat == etats.at(7))
    {
        return "Pot n°" + QString::number(m_numeroPot)
               + " | " + labelFromEtat(m_etat);
    }
    if(m_nomPlante.isEmpty())
    {
        return "Pot n°" + QString::number(m_numeroPot)
               + " | " + labelFromEtat(m_etat)
               + " | " + (m_nomPlante.isEmpty() ? "Vide" : m_nomPlante);
    }
    return "Pot n°" + QString::number(m_numeroPot)
           + " | " + (m_nomPlante.isEmpty() ? "Vide" : m_nomPlante)
           + " | " + labelFromEtat(m_etat)
           + " | Planté le : " + (m_datePlantation.isEmpty() ? "—" : m_datePlantation);
}
