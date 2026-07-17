#pragma once

#include "DataManager/TableCulture/tableculturedata.h"
#include "potrepository.h"

#include <QVector>


class TableCultureRepository
{
public:

    TableCultureRepository();


    // Création / modification
    bool save(TableCultureData& table);


    // Chargement complet
    QVector<TableCultureData> loadAll();


    // Chargement d'une table précise
    bool findById(int id, TableCultureData& table);


    // Suppression
    bool remove(const TableCultureData& table);


    // Vérification
    bool exists(int id);


private:

    bool fillTableFromQuery(
        class QSqlQuery& query,
        TableCultureData& table
        );
};
