#pragma once

#include "potdata.h"

#include <QString>
#include <QVector>


class TableCultureData
{
public:

    explicit TableCultureData(const QString& name = "");


    // Nom de la table
    QString name() const;
    void setName(const QString& name);


    // Etat de la table
    bool estActive() const;
    void setActive(bool active);


    // Gestion des pots
    QVector<PotData>& pots();
    const QVector<PotData>& pots() const;


    int nombrePots() const;
    int nombrePotsActifs() const;


    PotData& pot(int index);
    const PotData& pot(int index) const;


    // Debug / export futur
    QString toString() const;


private:

    QString m_name;

    bool m_active = false;

    QVector<PotData> m_pots;
};
