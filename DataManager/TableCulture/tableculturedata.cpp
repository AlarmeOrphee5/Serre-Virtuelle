#include "tableculturedata.h"
#include <QRandomGenerator>


TableCultureData::TableCultureData(const QString& name, int nombrePots)
    : m_name(name),
    m_active(false)
{
    for (int i = 0; i < nombrePots; i++)
        m_pots.append(PotData(i + 1, EtatPot::Inactif));
}

//--------------------------------------------------
// Nom
//--------------------------------------------------

QString TableCultureData::name() const { return m_name; }

void TableCultureData::setName(const QString& name) { m_name = name; }

//--------------------------------------------------
// Etat
//--------------------------------------------------

bool TableCultureData::estActive() const { return m_active; }

void TableCultureData::setActive(bool active)
{
    m_active = active;

    if (!m_active)
    {
        reinitialiserPots();
        return;
    }
}

void TableCultureData::setActiveSilent(bool active)
{
    // Active ou désactive sans toucher aux états des pots
    // Utile pour la duplication
    m_active = active;
}

//--------------------------------------------------
// Gestion des pots
//--------------------------------------------------

QVector<PotData>& TableCultureData::pots() { return m_pots; }

const QVector<PotData>& TableCultureData::pots() const { return m_pots; }

int TableCultureData::nombrePots() const { return m_pots.size(); }

PotData& TableCultureData::pot(int index)
{
    Q_ASSERT(indexValide(index));
    return m_pots[index];
}

const PotData& TableCultureData::pot(int index) const
{
    Q_ASSERT(indexValide(index));
    return m_pots[index];
}

bool TableCultureData::indexValide(int index) const
{
    return index >= 0 && index < m_pots.size();
}

void TableCultureData::copierPotsDepuis(const TableCultureData& source)
{
    // Copie les états pot par pot jusqu'à la taille minimale des deux tables
    int limite = qMin(m_pots.size(), source.pots().size());
    for (int i = 0; i < limite; i++)
        m_pots[i].setEtat(source.pots()[i].etat());
}

void TableCultureData::reinitialiserPots()
{
    for (PotData& pot : m_pots)
        if (pot.etat() != EtatPot::HorsService)
            pot.setEtat(EtatPot::Inactif);
}

//--------------------------------------------------
// Nombre de pots actifs
//--------------------------------------------------

int TableCultureData::nombrePotsActifs() const
{
    int count = 0;
    for (const PotData& pot : m_pots)
        if (pot.etat() != EtatPot::Inactif && pot.etat() != EtatPot::HorsService)
            count++;
    return count;
}

//--------------------------------------------------
// Debug
//--------------------------------------------------

QString TableCultureData::toString() const
{
    return QString("Table : %1 | Etat : %2 | Pots : %3 | Actifs : %4")
        .arg(m_name)
        .arg(m_active ? "Active" : "Inactive")
        .arg(m_pots.size())
        .arg(nombrePotsActifs());
}

//--------------------------------------------------
// Id / Numero / Date
//--------------------------------------------------

int TableCultureData::id() const { return m_id; }
void TableCultureData::setId(int id) { m_id = id; }

int TableCultureData::numero() const { return m_numero; }
void TableCultureData::setNumero(int numero) { m_numero = numero; }

QString TableCultureData::dateCreation() const { return m_dateCreation; }
void TableCultureData::setDateCreation(const QString& date) { m_dateCreation = date; }
