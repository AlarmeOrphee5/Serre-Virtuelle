#pragma once

#include "DataManager/Pot/potdata.h"

#include <QVector>


class PotRepository
{
public:

    PotRepository();


    // Création / modification
    bool save(
        PotData& pot,
        int tableId
        );


    // Chargement des pots d'une table
    QVector<PotData> loadByTable(
        int tableId
        );


    // Recherche
    bool findById(
        int id,
        PotData& pot
        );


    // Suppression
    bool remove(
        const PotData& pot
        );
    bool removeByTableId(int tableId);


private:

    bool fillPotFromQuery(
        class QSqlQuery& query,
        PotData& pot
        );
};
