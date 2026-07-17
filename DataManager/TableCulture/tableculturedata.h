#pragma once

#include "DataManager/Pot/potdata.h"

#include <QString>
#include <QVector>


class TableCultureData
{
public:

    explicit TableCultureData(const QString& name = "", int nombrePots = 24);

    // Nom
    QString name() const;
    void setName(const QString& name);

    // Etat
    bool estActive() const;
    void setActive(bool active);

    // Activation sans randomisation — utile pour la duplication
    void setActiveSilent(bool active);

    // Gestion des pots
    QVector<PotData>& pots();
    const QVector<PotData>& pots() const;

    int nombrePots() const;
    int nombrePotsActifs() const;

    PotData& pot(int index);
    const PotData& pot(int index) const;

    // Vérifie qu'un index est valide
    bool indexValide(int index) const;

    // Copie les états des pots depuis une autre table
    void copierPotsDepuis(const TableCultureData& source);

    // Remet tous les pots à Inactif (sauf HorsService)
    void reinitialiserPots();

    // Debug / export
    QString toString() const;

    int id() const;
    void setId(int id);

    int numero() const;
    void setNumero(int numero);

    QString dateCreation() const;
    void setDateCreation(const QString& date);

private:

    int     m_id           = -1;
    int     m_numero       = 0;
    QString m_name;
    bool    m_active       = false;
    QString m_dateCreation;
    QVector<PotData> m_pots;
};
