#include "potrepository.h"

#include "Core/Database/databasemanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

PotRepository::PotRepository()
{
}

//
// Création / Modification
//

bool PotRepository::save(PotData& pot, int tableId)
{
    QSqlQuery query(DatabaseManager::getInstance().database());

    //
    // Création
    //

    if (pot.id() == -1)
    {
        query.prepare(R"(
            INSERT INTO pot
            (
                table_id,
                numero_pot,
                etat,
                nom_plante,
                date_plantation
            )
            VALUES
            (
                :table_id,
                :numero_pot,
                :etat,
                :nom_plante,
                :date_plantation
            )
        )");

        query.bindValue(":table_id", tableId);
        query.bindValue(":numero_pot", pot.numeroPot());
        query.bindValue(":etat", static_cast<int>(pot.etat()));
        query.bindValue(":nom_plante", pot.nomPlante());
        query.bindValue(":date_plantation", pot.datePlantation());

        if (!query.exec())
        {
            qDebug()
            << "[BDD] Impossible de créer le pot :"
            << query.lastError().text();

            return false;
        }

        pot.setId(query.lastInsertId().toInt());

        qDebug()
            << "[BDD] Pot créé. ID ="
            << pot.id();

        return true;
    }

    //
    // Vérification existence
    //

    PotData existing;

    if (!findById(pot.id(), existing))
    {
        qDebug()
        << "[BDD] Modification impossible : pot inexistant";

        return false;
    }

    //
    // Modification
    //

    query.prepare(R"(
        UPDATE pot
        SET
            numero_pot = :numero_pot,
            etat = :etat,
            nom_plante = :nom_plante,
            date_plantation = :date_plantation
        WHERE id = :id
    )");

    query.bindValue(":numero_pot", pot.numeroPot());
    query.bindValue(":etat", static_cast<int>(pot.etat()));
    query.bindValue(":nom_plante", pot.nomPlante());
    query.bindValue(":date_plantation", pot.datePlantation());
    query.bindValue(":id", pot.id());

    if (!query.exec())
    {
        qDebug()
        << "[BDD] Impossible de modifier le pot :"
        << query.lastError().text();

        return false;
    }

    qDebug()
        << "[BDD] Pot modifié. ID ="
        << pot.id();

    return true;
}

//
// Chargement
//

QVector<PotData> PotRepository::loadByTable(int tableId)
{
    QVector<PotData> pots;

    QSqlQuery query(DatabaseManager::getInstance().database());

    query.prepare(R"(
        SELECT
            id,
            numero_pot,
            etat,
            nom_plante,
            date_plantation
        FROM pot
        WHERE table_id = :table_id
        ORDER BY numero_pot
    )");

    query.bindValue(":table_id", tableId);

    if (!query.exec())
    {
        qDebug()
        << "[BDD] Impossible de charger les pots :"
        << query.lastError().text();

        return pots;
    }

    while (query.next())
    {
        PotData pot;

        fillPotFromQuery(query, pot);

        pots.append(pot);
    }

    qDebug()
        << "[BDD]"
        << pots.size()
        << "pot(s) chargé(s).";

    return pots;
}

//
// Recherche
//

bool PotRepository::findById(int id, PotData& pot)
{
    QSqlQuery query(DatabaseManager::getInstance().database());

    query.prepare(R"(
        SELECT
            id,
            numero_pot,
            etat,
            nom_plante,
            date_plantation
        FROM pot
        WHERE id = :id
    )");

    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug()
        << "[BDD] Erreur recherche pot :"
        << query.lastError().text();

        return false;
    }

    if (!query.next())
    {
        qDebug()
        << "[BDD] Aucun pot trouvé avec l'ID"
        << id;

        return false;
    }

    return fillPotFromQuery(query, pot);
}

//
// Suppression
//

bool PotRepository::remove(const PotData& pot)
{
    PotData existing;

    if (!findById(pot.id(), existing))
    {
        qDebug()
        << "[BDD] Suppression impossible : pot inexistant";

        return false;
    }

    QSqlQuery query(DatabaseManager::getInstance().database());

    query.prepare(R"(
        DELETE FROM pot
        WHERE id = :id
    )");

    query.bindValue(":id", pot.id());

    if (!query.exec())
    {
        qDebug()
        << "[BDD] Impossible de supprimer le pot :"
        << query.lastError().text();

        return false;
    }

    qDebug()
        << "[BDD] Pot supprimé. ID ="
        << pot.id();

    return true;
}

bool PotRepository::removeByTableId(int tableId)
{
    QSqlQuery query(DatabaseManager::getInstance().database());

    query.prepare(R"(
        DELETE FROM pot
        WHERE table_id = :table_id
    )");

    query.bindValue(":table_id", tableId);

    if (!query.exec())
    {
        qDebug()
        << "[BDD] Impossible de supprimer les pots de la table"
        << tableId
        << ":"
        << query.lastError().text();

        return false;
    }

    qDebug()
        << "[BDD]"
        << query.numRowsAffected()
        << "pot(s) supprimé(s) pour la table"
        << tableId;

    return true;
}

//
// Outils
//

bool PotRepository::fillPotFromQuery(QSqlQuery& query, PotData& pot)
{
    pot.setId(query.value("id").toInt());

    pot.setNumeroPot(query.value("numero_pot").toInt());

    pot.setEtat(
        static_cast<EtatPot>(
            query.value("etat").toInt()));

    pot.setNomPlante(query.value("nom_plante").toString());

    pot.setDatePlantation(query.value("date_plantation").toString());

    return true;
}
