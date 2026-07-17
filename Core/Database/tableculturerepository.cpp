#include "tableculturerepository.h"

#include "Core/Database/databasemanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


TableCultureRepository::TableCultureRepository()
{
}


QVector<TableCultureData> TableCultureRepository::loadAll()
{
    QVector<TableCultureData> tables;

    QSqlQuery query(
        DatabaseManager::getInstance().database()
        );

    if(!query.exec(R"(
        SELECT
            id,
            numero,
            nom,
            active,
            date_creation
        FROM table_culture
        ORDER BY numero
    )"))
    {
        qDebug()
        << "[BDD] Impossible de charger les tables :"
        << query.lastError().text();

        return tables;
    }

    PotRepository potRepository;

    while(query.next())
    {
        TableCultureData table;

        // Remplit les informations de la table
        fillTableFromQuery(query, table);

        // Charge les pots associés à cette table
        table.pots() = potRepository.loadByTable(table.id());

        tables.append(table);
    }

    qDebug()
        << "[BDD]"
        << tables.size()
        << "table(s) chargée(s).";

    return tables;
}



bool TableCultureRepository::save(
    TableCultureData& table)
{
    QSqlQuery query(
        DatabaseManager::getInstance().database()
        );


    if(table.id() == -1)
    {
        query.prepare(R"(
            INSERT INTO table_culture
            (
                numero,
                nom,
                active,
                date_creation
            )
            VALUES
            (
                :numero,
                :nom,
                :active,
                :date_creation
            )
        )");


        query.bindValue(
            ":numero",
            table.numero()
            );

        query.bindValue(
            ":nom",
            table.name()
            );

        query.bindValue(
            ":active",
            table.estActive()
            );

        query.bindValue(
            ":date_creation",
            table.dateCreation()
            );


        if(!query.exec())
        {
            qDebug()
            << "[BDD] Impossible de créer la table :"
            << query.lastError().text();

            return false;
        }


        table.setId(
            query.lastInsertId().toInt()
            );


        qDebug()
            << "[BDD] Table créée. ID ="
            << table.id();


        return true;
    }



    query.prepare(R"(
        UPDATE table_culture
        SET
            numero = :numero,
            nom = :nom,
            active = :active,
            date_creation = :date_creation
        WHERE id = :id
    )");


    query.bindValue(":numero", table.numero());
    query.bindValue(":nom", table.name());
    query.bindValue(":active", table.estActive());
    query.bindValue(":date_creation", table.dateCreation());
    query.bindValue(":id", table.id());


    if(!query.exec())
    {
        qDebug()
        << "[BDD] Impossible de modifier la table :"
        << query.lastError().text();

        return false;
    }


    if(query.numRowsAffected() == 0)
    {
        qDebug()
        << "[BDD] Aucune table modifiée pour ID"
        << table.id();

        return false;
    }


    qDebug()
        << "[BDD] Table mise à jour. ID ="
        << table.id();


    return true;
}



bool TableCultureRepository::findById(
    int id,
    TableCultureData& table)
{
    QSqlQuery query(
        DatabaseManager::getInstance().database()
        );


    query.prepare(R"(
        SELECT
            id,
            numero,
            nom,
            active,
            date_creation
        FROM table_culture
        WHERE id = :id
    )");


    query.bindValue(
        ":id",
        id
        );


    if(!query.exec())
    {
        qDebug()
        << "[BDD] Erreur recherche table :"
        << query.lastError().text();

        return false;
    }


    if(!query.next())
    {
        return false;
    }


    return fillTableFromQuery(
        query,
        table
        );
}



bool TableCultureRepository::exists(
    int id)
{
    TableCultureData table;

    return findById(
        id,
        table
        );
}



bool TableCultureRepository::remove(
    const TableCultureData& table)
{
    if(!exists(table.id()))
    {
        qDebug()
        << "[BDD] Suppression impossible : table inexistante";

        return false;
    }


    QSqlQuery query(
        DatabaseManager::getInstance().database()
        );


    query.prepare(R"(
        DELETE FROM table_culture
        WHERE id = :id
    )");


    query.bindValue(
        ":id",
        table.id()
        );


    if(!query.exec())
    {
        qDebug()
        << "[BDD] Impossible de supprimer la table :"
        << query.lastError().text();

        return false;
    }


    if(query.numRowsAffected() == 0)
    {
        qDebug()
        << "[BDD] Aucune table supprimée";

        return false;
    }


    qDebug()
        << "[BDD] Table supprimée. ID ="
        << table.id();


    return true;
}



bool TableCultureRepository::fillTableFromQuery(
    QSqlQuery& query,
    TableCultureData& table)
{
    table.setId(
        query.value("id").toInt()
        );

    table.setNumero(
        query.value("numero").toInt()
        );

    table.setName(
        query.value("nom").toString()
        );

    table.setActiveSilent(
        query.value("active").toBool()
        );

    table.setDateCreation(
        query.value("date_creation").toString()
        );


    return true;
}
