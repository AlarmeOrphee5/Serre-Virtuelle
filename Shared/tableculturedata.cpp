#include "tableculturedata.h"
#include <QRandomGenerator>


TableCultureData::TableCultureData(const QString& name)
    : m_name(name),
    m_active(false)
{
    for (int i = 0; i < 24; i++)
    {
        m_pots.append(
            PotData(i + 1, EtatPot::Inactif)
            );
    }
}

//--------------------------------------------------
// Nom
//--------------------------------------------------

QString TableCultureData::name() const
{
    return m_name;
}


void TableCultureData::setName(const QString& name)
{
    m_name = name;
}


//--------------------------------------------------
// Etat de la table
//--------------------------------------------------

bool TableCultureData::estActive() const
{
    return m_active;
}


void TableCultureData::setActive(bool active)
{
    m_active = active;


    if(!m_active)
    {
        for(PotData& pot : m_pots)
        {
            if(pot.etat() != EtatPot::HorsService)
                pot.setEtat(EtatPot::Inactif);
        }

        return;
    }


    QList<EtatPot> etats = tousLesEtats();


    for(PotData& pot : m_pots)
    {
        if(pot.etat() == EtatPot::HorsService)
            continue;


        int r =
            QRandomGenerator::global()->bounded(
                etats.size()
                );


        pot.setEtat(
            etats[r]
            );
    }
}


//--------------------------------------------------
// Gestion des pots
//--------------------------------------------------

QVector<PotData>& TableCultureData::pots()
{
    return m_pots;
}


const QVector<PotData>& TableCultureData::pots() const
{
    return m_pots;
}


int TableCultureData::nombrePots() const
{
    return m_pots.size();
}


PotData& TableCultureData::pot(int index)
{
    return m_pots[index];
}


const PotData& TableCultureData::pot(int index) const
{
    return m_pots[index];
}


//--------------------------------------------------
// Texte résumé
//--------------------------------------------------

QString TableCultureData::toString() const
{
    QString texte;


    texte += "Table : " + m_name;
    texte += "\nEtat : ";

    if (m_active)
        texte += "Active";
    else
        texte += "Inactive";


    texte += "\nNombre de pots : "
             + QString::number(m_pots.size());


    return texte;
}

//--------------------------------------------------
// Calcul pot Actif
//--------------------------------------------------
int TableCultureData::nombrePotsActifs() const
{
    int count = 0;

    for(const PotData& pot : m_pots)
    {
        if(pot.etat() != EtatPot::Inactif &&
            pot.etat() != EtatPot::HorsService)
        {
            count++;
        }
    }

    return count;
}
