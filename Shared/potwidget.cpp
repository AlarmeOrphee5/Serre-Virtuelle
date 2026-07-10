#include "potwidget.h"

#include <QString>


PotWidget::PotWidget(PotData& data, QWidget* parent)
    : QPushButton(parent),
    m_data(data)
{
    setFixedSize(18, 18);
    setAttribute(Qt::WA_StyledBackground, true);
    setMouseTracking(true);

    updateStyle();
    updateTooltip();
}


//--------------------------------------------------
// Accès aux données
//--------------------------------------------------

PotData& PotWidget::data()
{
    return m_data;
}


const PotData& PotWidget::data() const
{
    return m_data;
}


//--------------------------------------------------
// Etat du pot
//--------------------------------------------------

void PotWidget::setEtat(EtatPot etat)
{
    if (m_data.etat() == etat)
        return;

    m_data.setEtat(etat);

    updateStyle();
    updateTooltip();

    emit etatChanged();
}


EtatPot PotWidget::etat() const
{
    return m_data.etat();
}


//--------------------------------------------------
// Plante
//--------------------------------------------------

QString PotWidget::nomPlante() const
{
    return m_data.nomPlante();
}


void PotWidget::setNomPlante(const QString& newNomPlante)
{
    m_data.setNomPlante(newNomPlante);

    updateTooltip();
}


//--------------------------------------------------
// Date plantation
//--------------------------------------------------

QString PotWidget::datePlantation() const
{
    return m_data.datePlantation();
}


void PotWidget::setDatePlantation(const QString& newDatePlantation)
{
    m_data.setDatePlantation(newDatePlantation);

    updateTooltip();
}


//--------------------------------------------------
// Numéro du pot
//--------------------------------------------------

int PotWidget::numeroPot() const
{
    return m_data.numeroPot();
}


void PotWidget::setNumeroPot(int newNumeroPot)
{
    m_data.setNumeroPot(newNumeroPot);

    updateTooltip();
}


//--------------------------------------------------
// Affichage
//--------------------------------------------------

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
    )").arg(colorFromEtat(m_data.etat())));
}


void PotWidget::updateTooltip()
{
    QString tooltip;

    tooltip += "Pot : " + QString::number(m_data.numeroPot());


    if (!m_data.nomPlante().isEmpty())
    {
        tooltip += "\nPlante : "
                   + m_data.nomPlante();
    }


    if (!m_data.datePlantation().isEmpty())
    {
        tooltip += "\nPlantation : "
                   + m_data.datePlantation();
    }


    setToolTip(m_data.toString());
}
