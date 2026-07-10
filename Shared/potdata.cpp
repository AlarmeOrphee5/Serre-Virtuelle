#include "potdata.h"


PotData::PotData(int numeroPot, EtatPot etat)
    : m_numeroPot(numeroPot),
    m_etat(etat)
{

}

//---------------------------------
// Numéro
//---------------------------------

int PotData::numeroPot() const
{
    return m_numeroPot;
}


void PotData::setNumeroPot(int numero)
{
    m_numeroPot = numero;
}


//---------------------------------
// Etat
//---------------------------------

EtatPot PotData::etat() const
{
    return m_etat;
}


void PotData::setEtat(EtatPot etat)
{
    m_etat = etat;
}


//---------------------------------
// Plante
//---------------------------------

QString PotData::nomPlante() const
{
    return m_nomPlante;
}


void PotData::setNomPlante(const QString& nom)
{
    m_nomPlante = nom;
}


//---------------------------------
// Date plantation
//---------------------------------

QString PotData::datePlantation() const
{
    return m_datePlantation;
}


void PotData::setDatePlantation(const QString& date)
{
    m_datePlantation = date;
}

QString PotData::toString() const
{
    QList<EtatPot> etats = tousLesEtats();

    if(m_etat == etats.at(0))
    {
        return "Pot n°" + QString::number(m_numeroPot)
               + " | "
               + (m_nomPlante.isEmpty() ? "Vide" : m_nomPlante)
               + " | "
               + labelFromEtat(m_etat);
    }


    if(m_etat == etats.at(7))
    {
        return "Pot n°" + QString::number(m_numeroPot)
               + " | "
               + labelFromEtat(m_etat);
    }


    if(m_nomPlante.isEmpty())
    {
        return "Pot n°" + QString::number(m_numeroPot)
               + " | "
               + labelFromEtat(m_etat)
               + " | Vide";
    }


    return "Pot n°" + QString::number(m_numeroPot)
           + " | "
           + m_nomPlante
           + " | "
           + labelFromEtat(m_etat)
           + " | Planté le : "
           + (m_datePlantation.isEmpty() ? "—" : m_datePlantation);
}
